/*
 * Integrator.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_INTEGRATORS_INTEGRATOR_H_
#define LIB_INTEGRATORS_INTEGRATOR_H_

#include "../SystemProperties.h"

namespace ashell {

class Integrator {
public:
	Integrator(std::shared_ptr<SystemProperties> sys_props);
	virtual ~Integrator();

	void step();

protected:
	const std::shared_ptr<SystemProperties> _sys_props;
};

} /* namespace ashell */

#endif /* LIB_INTEGRATORS_INTEGRATOR_H_ */
