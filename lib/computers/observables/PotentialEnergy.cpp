/*
 * PotentialEnergy.cpp
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#include "PotentialEnergy.h"

#include "../ForceComputer.h"
#include "../../World.h"

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
	for(auto &force: World::current_system()->forces()) {
		_energy += force->energy();
	}
	_energy /= _particles->N();
}

} /* namespace ashell */
