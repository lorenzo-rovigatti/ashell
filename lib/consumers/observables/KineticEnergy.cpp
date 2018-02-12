/*
 * KineticEnergy.cpp
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#include "KineticEnergy.h"

#include <boost/format.hpp>

namespace ashell {

KineticEnergy::KineticEnergy() :
				_kinetic_energy(0.) {

}

KineticEnergy::~KineticEnergy() {

}

double KineticEnergy::as_scalar() {
	return _kinetic_energy;
}

void KineticEnergy::_observe(ullint step) {
	_kinetic_energy = 0.;
	auto velocities = _particles->velocities();
	for(auto &v : velocities) {
		_kinetic_energy += 0.5 * v.dot(v);
	}
}

} /* namespace ashell */
