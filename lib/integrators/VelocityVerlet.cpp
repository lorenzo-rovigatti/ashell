/*
 * VelocityVerlet.cpp
 *
 *  Created on: 8 Feb 2018
 *      Author: lorenzo
 */

#include "VelocityVerlet.h"

#include <iostream>
#include "../computers/ForceComputer.h"

namespace ashell {

VelocityVerlet::VelocityVerlet(double dt) :
				Integrator(),
				_dt(dt),
				_dt_half(dt / 2.),
				_forces(0) {
}

VelocityVerlet::~VelocityVerlet() {

}

void VelocityVerlet::step(ullint step) {
	uint N = _particles->N();
	if(N != _forces.size()) {
		_forces.resize(N, vec3(0., 0., 0.));
	}

	vector_vec3 &poss = _particles->positions_writable();
	vector_vec3 &vels = _particles->velocities_writable();

	for(uint i = 0; i < N; i++) {
		vels[i] += _forces[i] * _dt_half;
		poss[i] += vels[i] * _dt;
		_forces[i] = vec3(0., 0., 0.);
	}

	double energy = 0.;
	for(auto &force_computer : _sys_props->forces()) {
		force_computer->compute(step);
		energy +=  force_computer->energy();
		auto computer_forces = force_computer->forces();
		for(uint i = 0; i < N; i++) {
			_forces[i] += computer_forces[i];
		}
	}

	for(uint i = 0; i < N; i++) {
		vels[i] += _forces[i] * _dt_half;
	}
}

} /* namespace ashell */

#ifdef ASHELL_PYTHON
#include "../defs_to_python.h"

namespace ashell {

using namespace boost::python;
void export_velocity_verlet() {
	class_<VelocityVerlet, std::shared_ptr<VelocityVerlet>, bases<Integrator>, boost::noncopyable>("VelocityVerlet", init<double>());
}

}
#endif
