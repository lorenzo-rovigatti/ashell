/*
 * Initialiser.cpp
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#include "Initialiser.h"

#include "defs_to_python.h"

namespace ashell {

Initialiser::Initialiser() {

}

Initialiser::~Initialiser() {

}

std::shared_ptr<Particles> Initialiser::make_random(int N, std::shared_ptr<Box> box) {
	vector_vec3 poss(N);
	for(auto &pos : poss) {
		pos = box->random_point_in_box();
	}

	std::shared_ptr<Particles> particles(new Particles(N, poss));

	return particles;
}

void export_initialiser() {
	bpy::class_<Initialiser, std::shared_ptr<Initialiser> >("Initialiser", bpy::no_init)
			.def("make_random", &Initialiser::make_random).staticmethod("make_random");
}

} /* namespace ashell */
