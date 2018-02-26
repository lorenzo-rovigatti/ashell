/*
 * System.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_SYSTEM_H_
#define LIB_SYSTEM_H_

#include "defs.h"
#include "OutputObservable.h"
#include "SystemProperties.h"
#include "updaters/Updater.h"

#include <memory>

namespace ashell {

class System {
public:
	System();
	virtual ~System();

	void init();
	void run(ullint steps);
	void add_updater(std::shared_ptr<Updater> new_updater);

	auto system_properties() const {
		return _sys_props;
	}

	ullint print_defaults_every() {
		return _print_defaults_every;
	}

	void set_print_defaults_every(ullint n_print_defaults_every);

protected:
	void _sanity_check();

	std::shared_ptr<SystemProperties> _sys_props;
	std::vector<std::shared_ptr<Updater>> _updaters;
	std::vector<std::shared_ptr<OutputObservable>> _outputs;
	std::vector<std::shared_ptr<OutputObservable>> _default_outputs;
	std::vector<std::shared_ptr<OutputObservable>> _after_clean_outputs;
	ullint _current_step;
	ullint _print_defaults_every;
};

} /* namespace ashell */

#endif /* LIB_SYSTEM_H_ */
