/*
 * Particles.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "Particles.h"

namespace ashell {

Particles::Particles(int N) :
				_N(N),
				_poss(N, vec3(0., 0., 0.)),
				_vels(N, vec3(0., 0., 0.)) {

}

Particles::~Particles() {

}

} /* namespace ashell */
