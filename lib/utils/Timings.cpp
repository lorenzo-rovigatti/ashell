/*
 * timings.cpp
 *
 *  Created on: 21/mar/2014
 *      Author: flavio 
 */

#include "Timings.h"

#include <boost/log/trivial.hpp>
#include <boost/format.hpp>

#include <algorithm>

#ifdef CUDA
#include <cuda_runtime_api.h>
#define SYNCHRONIZE() cudaDeviceSynchronize()
#else
#define SYNCHRONIZE()
#endif

#ifdef MOSIX
#define ASHELL_CLOCK() 0
#else
#define ASHELL_CLOCK() clock()
#endif

using std::string;

Timer::Timer(std::string desc) : Timer(desc, nullptr) {
	_desc = desc;
	_parent = nullptr;
}

Timer::Timer(std::string desc, Timer *my_parent) {
	_desc = desc;
	_parent = my_parent;
}

Timer::~Timer() {

}

void Timer::update_time_spent_in_children(ullint child_time) {
	_time_spent_in_children += child_time;
}

void Timer::resume() {
	if(_active) {
		string error = boost::str(boost::format("Resuming the already active timer %s") % _desc);
		throw std::runtime_error(error);
	}
	_last = ASHELL_CLOCK();
	_active = true;
}

void Timer::pause() {
	SYNCHRONIZE();
	if(!_active) {
		string error = boost::str(boost::format("Pausing the already inactive timer %s") % _desc);
		throw std::runtime_error(error);
	}
	_time += (ASHELL_CLOCK() - _last);
	_active = false;
}

// this should work regardless of the timers being active
long long int Timer::get_time() {
	if(_active) return (long long int) (_time + (ASHELL_CLOCK() - _last));
	else return (long long int) _time;
}

/***************** END OF TIMER CLASS *********************/

// singleton
std::shared_ptr<TimingManager> TimingManager::_timingManager(nullptr);

TimingManager::TimingManager() {

}

TimingManager::~TimingManager() {

}

std::shared_ptr<TimingManager> TimingManager::instance() {
	if(_timingManager == nullptr) {
		_timingManager = std::shared_ptr<TimingManager>(new TimingManager());
	}
	return _timingManager;
}

Timer *TimingManager::new_timer(std::string desc) {
	if(_desc_map.count(desc) != 0) {
		string error = boost::str(boost::format("Timer %s already exists! Aborting") % desc);
		throw std::runtime_error(error);
	}

	Timer *timer = new Timer(desc);
	_timers.push_back(std::shared_ptr<Timer>(timer));
	_desc_map[desc] = timer;

	BOOST_LOG_TRIVIAL(debug)<< "Adding a new timer with description '" << desc << "' and no parent";

	return timer;
}

Timer *TimingManager::new_timer(std::string desc, std::string parent_desc) {
	if(_desc_map.count(desc) != 0) {
		string error = boost::str(boost::format("Timer '%s' already exists! Aborting") % desc);
		throw std::runtime_error(error);
	}
	if(_desc_map.count(parent_desc) == 0) {
		string error = boost::str(boost::format("Cannot add timer '%s' because parent timer '%s' does not exist") % desc % parent_desc);
		throw std::runtime_error(error);
	}

	Timer *timer = new Timer(desc, get_timer_by_desc(parent_desc));
	_timers.push_back(std::shared_ptr<Timer>(timer));
	_desc_map[desc] = timer;

	BOOST_LOG_TRIVIAL(debug)<< "Adding a new timer with description '" << desc << "' and parent '" << parent_desc << "'";

	return timer;
}

void TimingManager::print(ullint total_steps) {
	// mylist will be ordered as a tree
	std::vector<std::string> mylist;
	while(mylist.size() < _timers.size()) {
		for(auto timer : _timers) {
			auto p = timer->parent();

			if(p == nullptr) {
				mylist.push_back(timer->get_desc());
			}
			else {
				// find the name of the parent
				std::vector<std::string>::iterator it = std::find(mylist.begin(), mylist.end(), p->get_desc());
				if(it != mylist.end()) {
					it++;
					mylist.insert(it, timer->get_desc());
				}
			}
		}
	}

	// now the list is ordered in the order we want to print it
	double tot = (double) get_timer_by_desc("Simulation")->get_time() / CPSF;
	if(tot < 1e-10) {
		BOOST_LOG_TRIVIAL(info) << "No timings available (either oxDNA was compiled with MOSIX=1 or no simulation steps were performed)";
		return;
	}

	std::string to_log = boost::str(boost::format("Total Running Time: %lf s, per step: %lf ms\n") % tot % (tot / total_steps * 1000.));
	to_log += boost::str(boost::format("Timings, in seconds, by Timer (total, own, spent in children)\n"));
	for(auto desc : mylist) {
		std::string summary;
		Timer *t = get_timer_by_desc(desc);
		Timer *p = t->parent();
		while(p != nullptr) {
			summary += "***";
			p = p->parent();
		}
		summary += "> ";
		summary += t->get_desc();

		long long int own_time_signed = t->get_time() - t->time_spent_in_children();
		if(own_time_signed < 0) {
			BOOST_LOG_TRIVIAL(warning) << "The total time measured by the '" << t->get_desc() << "' timer is smaller than the sum of the times measured by its children";
		}
		ullint own_time = (ullint) own_time_signed;

		to_log += boost::str(boost::format("%-30s %12.3lf (%5.1lf%%) %12.3lf (%5.1f%%) %12.3lf (%5.1f%%)\n") %
				summary %
				(t->get_time() / CPSF) %
				(t->get_time() / CPSF / tot * 100.) %
				(own_time / CPSF) %
				(own_time / CPSF / tot * 100.) %
				(t->time_spent_in_children() / CPSF) %
				(t->time_spent_in_children() / CPSF / tot * 100.)
				);
	}

	BOOST_LOG_TRIVIAL(info) << "Performance summary:\n\n" << to_log;
}
