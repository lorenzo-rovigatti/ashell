/*
 * ExternalForce.cpp
 *
 *  Created on: 1 Mar 2018
 *      Author: lorenzo
 */

#include "ExternalForce.h"

namespace ashell {

ExternalForce::ExternalForce(std::vector<int> target_particles, std::string name) :
				ForceComputer(name),
				_target_particles(target_particles) {
}

ExternalForce::~ExternalForce() {

}

void ExternalForce::_compute_forces(ullint step) {
	uint N = _sys_props->particles()->N();
	for(uint i : _target_particles) {
		if(i >= N) {
			std::string error = boost::str(boost::format("A %s external force was told to act on the non-existent particle n. %u") % _name % i);
			throw std::runtime_error(error);
		}
		_compute_force_on_particle(step, i);
	}
}

void ExternalForce::_compute_force_on_particle(ullint step, uint idx) {
	throw std::runtime_error("Calling an unimplemented ExternalForce::_compute_force_on_particle(uint) method");
}

} /* namespace ashell */
