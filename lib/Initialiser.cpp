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

std::shared_ptr<Particles> Initialiser::make_random_N2(int N, std::shared_ptr<Box> box) {
	vector_vec3 poss(1, box->random_point_in_box());
	while((int) poss.size() != N) {
		vec3 n_pos = box->random_point_in_box();
		bool insert = true;
		for(auto &pos : poss) {
			vec3 dist = box->minimum_image(pos, n_pos);
			if(dist.dot(dist) < 1.) {
				insert = false;
			}
		}
		if(insert) poss.push_back(n_pos);
	}

	std::shared_ptr<Particles> particles(new Particles(N, poss));

	return particles;
}

void export_initialiser() {
	bpy::class_<Initialiser, std::shared_ptr<Initialiser> >("Initialiser", bpy::no_init)
			.def("make_random", &Initialiser::make_random_N2).staticmethod("make_random");
}

} /* namespace ashell */
