/*
 * ConstantForce.cpp
 *
 *  Created on: 1 Mar 2018
 *      Author: lorenzo
 */

#include "ConstantForce.h"

#include <iostream>

namespace ashell {

ConstantForce::ConstantForce(vec3 direction, double F0, std::vector<int> target_particles, std::string name) :
				ExternalForce(target_particles, name),
				_direction(direction),
				_F0(F0) {

}

ConstantForce::~ConstantForce() {

}

void ConstantForce::_compute_force_on_particle(ullint step, uint idx) {
	_forces[idx] += _F0 * _direction;
}

} /* namespace ashell */
