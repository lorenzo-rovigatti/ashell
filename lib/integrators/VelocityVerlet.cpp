/*
 * VelocityVerlet.cpp
 *
 *  Created on: 8 Feb 2018
 *      Author: lorenzo
 */

#include "VelocityVerlet.h"
#include "../consumers/ForceComputer.h"
#include "../defs_to_python.h"

#include <iostream>

namespace ashell {

VelocityVerlet::VelocityVerlet(double dt) :
				Integrator(),
				_dt(dt),
				_dt_half(dt / 2),
				_forces(_particles->N(), vec3(0., 0., 0.)) {

}

VelocityVerlet::~VelocityVerlet() {

}

void VelocityVerlet::step(ullint step) {
	int N = _particles->N();

	vector_vec3 &poss = _particles->positions_writable();
	vector_vec3 &vels = _particles->velocities_writable();

	for(int i = 0; i < N; i++) {
		vels[i] += _forces[i] * _dt_half;
		poss[i] += vels[i] * _dt;
		_forces[i] = vec3(0., 0., 0.);
	}

	double energy = 0.;
	auto pair_force_computers = _sys_props->pair_forces();
	for(auto &pair_force_computer : pair_force_computers) {
		pair_force_computer->consume(step);
		energy +=  pair_force_computer->energy();
		auto computer_forces = pair_force_computer->forces();
		for(int i = 0; i < N; i++) {
			_forces[i] += computer_forces[i];
		}
	}

	for(int i = 0; i < N; i++) {
		vels[i] += _forces[i] * _dt_half;
	}
}

using namespace boost::python;
void export_velocity_verlet() {
	class_<VelocityVerlet, std::shared_ptr<VelocityVerlet>, bases<Integrator>, boost::noncopyable>("VelocityVerlet", init<double>());
}

} /* namespace ashell */
