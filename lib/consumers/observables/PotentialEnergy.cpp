/*
 * PotentialEnergy.cpp
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#include "PotentialEnergy.h"

#include "../ForceComputer.h"
#include <boost/format.hpp>

namespace ashell {

PotentialEnergy::PotentialEnergy() : _energy(0.) {

}

PotentialEnergy::~PotentialEnergy() {
}

double PotentialEnergy::as_scalar() {
	return _energy;
}

void PotentialEnergy::_observe(ullint step) {
	_energy = 0.;
	for(auto &force: _sys_props->pair_forces()) {
		_energy += force->energy();
	}
}

} /* namespace ashell */
