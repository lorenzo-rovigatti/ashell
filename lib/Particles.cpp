/*
 * Particles.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "Particles.h"

#include <boost/python.hpp>

namespace ashell {

Particles::Particles(int N) :
				_N(N),
				_poss(N, vec3(0., 0., 0.)),
				_vels(N, vec3(0., 0., 0.)) {

}

Particles::~Particles() {

}

using namespace boost::python;
void export_particles() {
	class_<Particles, std::shared_ptr<Particles> >("Particles", init<int>())
			.add_property("N", &Particles::N, &Particles::set_N);
}

} /* namespace ashell */
