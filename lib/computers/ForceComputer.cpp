/*
 * ForceComputer.cpp
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#include "../computers/ForceComputer.h"

namespace ashell {

ForceComputer::ForceComputer(std::string name) :
				Computer(name),
				_energy(0.),
				_energies(_particles->N(), 0.),
				_forces(_particles->N(), vec3(0., 0., 0.)) {

}

ForceComputer::~ForceComputer() {

}

void ForceComputer::consume(ullint step) {
	if(!should_consume(step)) return;

	int N = _particles->N();
	if(N != (int) _energies.size()) {
		_energies.resize(N);
		_forces.resize(N);
	}

	_energy = 0.;
	std::fill(_energies.begin(), _energies.end(), 0.);
	std::fill(_forces.begin(), _forces.end(), vec3(0., 0., 0.));

	_compute_forces(step);
}

void ForceComputer::_compute_forces(ullint step) {
	throw std::runtime_error("Calling an unimplemented Consumer::_compute_forces() method");
}

} /* namespace ashell */
