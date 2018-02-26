/*
 * Andersen.cpp
 *
 *  Created on: 26 feb 2018
 *      Author: lorenzo
 */

#include "Andersen.h"

#include "../../utils/MathUtils.h"

namespace ashell {

Andersen::Andersen(double newtonian_time, double D0) :
				Updater(),
				_newtonian_time(newtonian_time),
				_D0(D0) {

}

Andersen::~Andersen() {

}

void Andersen::update(ullint step) {
	double T = _sys_props->T();
	double p = (2. * T *  _newtonian_time)/(T * _newtonian_time + 2 * _D0);
	double rescale_factor = sqrt(T);

	uint N = _sys_props->particles()->N();
	auto &vels = _sys_props->particles()->velocities_writable();
	for(uint i = 0; i < N; i++) {
		if(drand48() < p) {
			vels[i] = rescale_factor * vec3(MathUtils::gaussian(), MathUtils::gaussian(), MathUtils::gaussian());
		}
	}
}

} /* namespace ashell */
