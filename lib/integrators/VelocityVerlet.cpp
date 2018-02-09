/*
 * VelocityVerlet.cpp
 *
 *  Created on: 8 Feb 2018
 *      Author: lorenzo
 */

#include "VelocityVerlet.h"

#include "../defs_to_python.h"

#include <iostream>


namespace ashell {

VelocityVerlet::VelocityVerlet(double dt) :
				Integrator(),
				_dt(dt),
				_dt_half(dt / 2){

}

VelocityVerlet::~VelocityVerlet() {

}

void VelocityVerlet::step(ullint step) {
	int N = _particles->N();

	vector_vec3 &poss = _particles->positions_writable();
	vector_vec3 &vels = _particles->velocities_writable();
	vector_vec3 &forces = _particles->forces_mutable();

	for(int i = 0; i < N; i++) {
		vels[i] += forces[i] * _dt_half;
		poss[i] += vels[i] * _dt;
	}

	// TODO compute forces

	for(int i = 0; i < N; i++) {
		vels[i] += forces[i] * _dt_half;
	}

	std::cout << "step " << step << std::endl;
}

using namespace boost::python;
void export_velocity_verlet() {
	class_<VelocityVerlet, std::shared_ptr<VelocityVerlet>, bases<Integrator>, boost::noncopyable>("VelocityVerlet", init<double>());
}

} /* namespace ashell */
