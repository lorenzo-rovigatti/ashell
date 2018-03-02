/*
 * timings.h 
 *
 *  Created on: 21/mar/2014
 *      Author: flavio 
 */

#ifndef TIMINGS_H_
#define TIMINGS_H_

#include "../defs.h"

#include <ctime>
#include <vector>
#include <map>
#include <string>

#ifndef CPS
#define CPS (CLOCKS_PER_SEC)
#define CPSF ((double)(CLOCKS_PER_SEC))
#endif

class Timer {
private:
	/// string describing the timer
	std::string _desc;

	/// time elapsed between pauses
	clock_t _time;

	/// last time that the timer was started
	clock_t _last;

	/// whether the timer is running or paused
	bool _active;

public:
	Timer();
	Timer(std::string desc);
	~Timer();

	/// resumes (or starts) the timer
	void resume();

	/// pauses the timer
	void pause();

	/// resets the timer
	void reset() {
		_time = (clock_t) 0;
	}

	/// returns the time passed as a llint; works for active and inactive timers
	long long int get_time();

	/// returns the time passed, converted in seconds, as a double
	double get_seconds() {
		return (double) _time / (double) CPS;
	}

	/// returns the time passed, converted in seconds, as a float
	float get_secondsf() {
		return (float) get_seconds();
	}

	/// returns the description of the clock
	std::string get_desc() {
		return _desc;
	}

	/// returns whether the timer is active
	bool is_active() {
		return _active;
	}
};

/// new attempt at a singleton to be able to add from anywhere within the code a timer and have it do what expected
class TimingManager {
private:
	std::vector<Timer> _allocated_timers;
	std::vector<Timer *> _timers;
	std::map<Timer *, Timer *> _parents;
	std::map<std::string, Timer *> _desc_map;

	static std::shared_ptr<TimingManager> _timingManager;

public:
	TimingManager();
	virtual ~TimingManager();

	/// creates a new orphan timer
	Timer *new_timer(std::string desc);

	/// creates a new orphan timer
	Timer *new_timer(std::string desc, std::string parent_desc);

	/// return the Timer pointer associated to a given description
	Timer *get_timer_by_desc(std::string desc) {
		return _desc_map[desc];
	}

	/// singleton
	static std::shared_ptr<TimingManager> instance();

	/// prints 
	void print(ullint total_steps);
};
#endif

