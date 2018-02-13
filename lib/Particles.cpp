/*
 * Particles.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "Particles.h"

#include "defs_to_python.h"

namespace ashell {

Particles::Particles(uint N) :
				Particles(N, vector_vec3(N, vec3(0., 0., 0.)), vector_vec3(N, vec3(0., 0., 0.))) {

}

Particles::Particles(uint N, const vector_vec3 &poss) :
				Particles(N, poss, vector_vec3(N, vec3(0., 0., 0.))) {

}

Particles::Particles(uint N, const vector_vec3 &poss, const vector_vec3 &vels) :
				_N(N),
				_poss(poss),
				_vels(vels) {

}

Particles::~Particles() {

}

using namespace boost::python;
void export_particles() {
	class_<Particles, std::shared_ptr<Particles> >("Particles", init<int>()).add_property("N", &Particles::N, &Particles::set_N);
//			.add_property("positions", &Particles::positions)
//			.add_property("velocities", &Particles::velocities)
//			.add_property("forces", &Particles::forces);
}

} /* namespace ashell */
