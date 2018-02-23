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
				_energies(0),
				_forces(0) {

}

ForceComputer::~ForceComputer() {

}

void ForceComputer::compute(ullint step) {
	if(!should_compute(step)) return;

	uint N = _particles->N();
	if(N != _energies.size()) {
		_energies.resize(N);
		_forces.resize(N);
	}

	_energy = 0.;
	std::fill(_energies.begin(), _energies.end(), 0.);
	std::fill(_forces.begin(), _forces.end(), vec3(0., 0., 0.));

	_compute_forces(step);
}

void ForceComputer::_compute_forces(ullint step) {
	throw std::runtime_error("Calling an unimplemented ForceComputer::_compute_forces() method");
}

} /* namespace ashell */
