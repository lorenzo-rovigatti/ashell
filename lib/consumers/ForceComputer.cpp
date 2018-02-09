/*
 * ForceComputer.cpp
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#include "ForceComputer.h"

namespace ashell {

ForceComputer::ForceComputer() :
				Consumer(),
				_energy(0.),
				_energies(_particles->N(), 0.),
				_forces(_particles->N(), vec3(0., 0., 0.)) {

}

ForceComputer::~ForceComputer() {

}

} /* namespace ashell */
