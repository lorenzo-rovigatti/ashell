/*
 * System.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_SYSTEM_H_
#define LIB_SYSTEM_H_

#include "defs.h"

#include <memory>

namespace ashell {

class ForceComputer;
class Integrator;
class OutputObservable;
class SystemProperties;
class Updater;

class System {
public:
	System();
	virtual ~System();

	void init();
	void run(ullint steps);
	void add_updater(std::shared_ptr<Updater> new_updater);
	void add_force(std::shared_ptr<ForceComputer> n_force);
	void add_output(std::shared_ptr<OutputObservable> n_output);

	void set_integrator(std::shared_ptr<Integrator> n_integrator);
	void set_print_defaults_every(ullint n_print_defaults_every);
	void set_print_configuration_every(ullint n_print_configuration_every);

	auto integrator() const {
		return _integrator;
	}

	const auto &forces() const {
		return _forces;
	}

	auto system_properties() const {
		return _sys_props;
	}

	ullint print_defaults_every() {
		return _print_defaults_every;
	}

	ullint print_configuration_every() {
		return _print_configuration_every;
	}

	static bool stop;
	static bool started;

protected:
	void _sanity_check();

	std::shared_ptr<SystemProperties> _sys_props;
	std::shared_ptr<Integrator> _integrator;
	std::vector<std::shared_ptr<ForceComputer>> _forces;
	std::vector<std::shared_ptr<Updater>> _updaters;
	std::vector<std::shared_ptr<OutputObservable>> _outputs;
	std::vector<std::shared_ptr<OutputObservable>> _default_outputs;
	std::vector<std::shared_ptr<OutputObservable>> _post_run_outputs;
	std::vector<std::shared_ptr<OutputObservable>> _configuration_outputs;
	ullint _current_step;
	ullint _print_defaults_every;
	ullint _print_configuration_every;
};

} /* namespace ashell */

#endif /* LIB_SYSTEM_H_ */
