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

#include <memory>

namespace ashell {

class System {
public:
	System();
	virtual ~System();

	void init();
	void run(ullint steps);

	auto system_properties() const {
		return _sys_props;
	}

protected:
	void _sanity_check();

	std::shared_ptr<SystemProperties> _sys_props;
	std::vector<std::shared_ptr<OutputObservable> > _outputs;
	std::vector<std::shared_ptr<OutputObservable> > _after_clean_outputs;
	ullint _current_step;
};

} /* namespace ashell */

#endif /* LIB_SYSTEM_H_ */
