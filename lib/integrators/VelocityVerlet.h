/*
 * VelocityVerlet.h
 *
 *  Created on: 8 Feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_INTEGRATORS_VELOCITYVERLET_H_
#define LIB_INTEGRATORS_VELOCITYVERLET_H_

#include "Integrator.h"

namespace ashell {

class VelocityVerlet: public Integrator {
public:
	VelocityVerlet(double dt);
	virtual ~VelocityVerlet();

	void step(ullint step);

protected:
	double _dt;
	double _dt_half;

	vector_vec3 _forces;
};

} /* namespace ashell */

#endif /* LIB_INTEGRATORS_VELOCITYVERLET_H_ */
