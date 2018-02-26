/*
 * Integrator.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_INTEGRATORS_INTEGRATOR_H_
#define LIB_INTEGRATORS_INTEGRATOR_H_

#include <memory>

#include "../Updater.h"

namespace ashell {

class Integrator: public Updater {
public:
	Integrator();
	virtual ~Integrator();

	virtual void step(ullint step);
};

} /* namespace ashell */

#endif /* LIB_INTEGRATORS_INTEGRATOR_H_ */
