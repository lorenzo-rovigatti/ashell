/*
 * System.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_SYSTEM_H_
#define LIB_SYSTEM_H_

#include <memory>

namespace ashell {

class SystemProperties;

class System {
public:
	System();
	virtual ~System();

	void run(long long int steps);

	std::shared_ptr<SystemProperties> system_properties() const {
		return _sys_props;
	}

protected:
	std::shared_ptr<SystemProperties> _sys_props;
};

} /* namespace ashell */

#endif /* LIB_SYSTEM_H_ */
