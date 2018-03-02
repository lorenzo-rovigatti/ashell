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

Timer::Timer() {
	_time = (clock_t) 0;
	_last = (clock_t) 0;
	_active = false;
	_desc = std::string("Uninitialised timer");
}

Timer::Timer(std::string arg) {
	_desc = std::string(arg);
	_time = (clock_t) 0;
	_last = (clock_t) 0;
	_active = false;
}

Timer::~Timer() {
	BOOST_LOG_TRIVIAL(debug)<< "Timer with desc " << _desc << " deleted";
}

void Timer::resume() {
	if(_active) {
		string error = boost::str(boost::format("resuming already active timer %s") % _desc);
		throw std::runtime_error(error);
	}
	_last = ASHELL_CLOCK();
	_active = true;
}

void Timer::pause() {
	SYNCHRONIZE();
	if(!_active) {
		string error = boost::str(boost::format("pausing resuming already inactive timer %s") % _desc);
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
//	for(unsigned int i = 0; i < _timers.size(); i++) {
//		if(_timers[i] != NULL) {
//			BOOST_LOG_TRIVIAL(debug)<< "Trying to delete timer...";
//			delete _timers[i];
//		}
//	}
}

std::shared_ptr<TimingManager> TimingManager::instance() {
	if(_timingManager == NULL) {
		_timingManager = std::shared_ptr<TimingManager>(new TimingManager());
	}
	return _timingManager;
}

Timer *TimingManager::new_timer(std::string desc) {
	if(_desc_map.count(desc) != 0) {
		string error = boost::str(boost::format("timer %s already used! Aborting") % desc);
		throw std::runtime_error(error);
	}

	Timer *timer = new Timer(desc);

	_timers.push_back(timer);
	_parents[timer] = (Timer *) NULL;
	_desc_map[desc] = timer;

	BOOST_LOG_TRIVIAL(debug)<< "Adding new timer with description " << desc << " and no parent";

	return timer;
}

Timer *TimingManager::new_timer(std::string desc, std::string parent_desc) {
	if(_desc_map.count(desc) != 0) {
		string error = boost::str(boost::format("timer %s already used! Aborting") % desc);
		throw std::runtime_error(error);
	}
	if(_desc_map.count(parent_desc) == 0) {
		string error = boost::str(boost::format("Cannot add timer %s because parent timer %s does not exist") % desc % parent_desc);
		throw std::runtime_error(error);
	}

	Timer * timer = new Timer(desc);
	_timers.push_back(timer);
	_parents[timer] = get_timer_by_desc(parent_desc);
	_desc_map[desc] = timer;

	BOOST_LOG_TRIVIAL(debug)<< "Adding new timer with description " << desc << " and parent " << parent_desc;

	return timer;
}

void TimingManager::print(ullint total_steps) {
	// times (including children) 
	std::map<Timer *, ullint> totaltimes;
	for(unsigned int i = 0; i < _timers.size(); i++)
		totaltimes[_timers[i]] = _timers[i]->get_time();

	// times in children 
	std::map<Timer *, ullint> sum_of_children;
	for(unsigned int i = 0; i < _timers.size(); i++)
		sum_of_children[_timers[i]] = 0;
	for(unsigned int i = 0; i < _timers.size(); i++) {
		Timer * t = _timers[i];
		Timer * p = _parents[t];
		while(p != NULL) {
			sum_of_children[p] += totaltimes[t];
			p = _parents[p];
		}
	}

	// own time (not in children)
	std::map<Timer *, ullint> own_time;
	for(unsigned int i = 0; i < _timers.size(); i++) {
		Timer * t = _timers[i];
		own_time[t] = totaltimes[t] - sum_of_children[t];
	}

	// mylist will be ordered as a tree
	std::vector<std::string> mylist;
	while(mylist.size() < _timers.size()) {
		for(unsigned int i = 0; i < _timers.size(); i++) {
			Timer * t = _timers[i];
			Timer * p = _parents[t];

			if(p == NULL) {
				mylist.push_back(t->get_desc());
			}
			else {
				// troviamo il nome del parente
				std::vector<std::string>::iterator it = std::find(mylist.begin(), mylist.end(), p->get_desc());
				if(it != mylist.end()) {
					it++;
					mylist.insert(it, t->get_desc());
				}
			}
		}
	}

	// now the list is ordered in the order we want to print it
	double tot = (double) get_timer_by_desc("Simulation")->get_time() / CPSF;
	if(tot < 1e-10) {
		BOOST_LOG_TRIVIAL(info)<< "No timings available (either oxDNA was compiled with MOSIX=1 or no simulation steps were performed)";
		return;
	}

	std::string to_log = boost::str(boost::format("Total Running Time: %g s, per step: %g ms\n") % tot % (tot / total_steps * 1000.));
	to_log += boost::str(boost::format("Timings, in seconds, by Timer (total, own, spent in children)"));
	for(unsigned int i = 0; i < mylist.size(); i++) {
		char mystr[512] = "";
		Timer * t = get_timer_by_desc(mylist[i]);
		Timer * p = _parents[t];
		int generations = 0;
		while(p != NULL) {
			generations++;
			p = _parents[p];
		}
		for(int j = 0; j < generations; j++) {
			strcat(mystr, "***");
		}
		strcat(mystr, "> ");
		strcat(mystr, t->get_desc().c_str());
//		to_log += boost::str(boost::format("%-30s %12.3lf (%5.1lf\%) %12.3lf (%5.1f\%) %12.3lf (%5.1f\%)") %
//				mystr %
//				(totaltimes[t] / CPSF) %
//				(totaltimes[t] / CPSF / tot * 100.) %
//				(own_time[t] / CPSF) %
//				(own_time[t] / CPSF / tot * 100.) %
//				(sum_of_children[t] / CPSF) %
//				(sum_of_children[t] / CPSF / tot * 100.)
//				);
	}

	BOOST_LOG_TRIVIAL(info) << "Performance summary:\n" << to_log;
}

