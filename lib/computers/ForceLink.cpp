/*
 * ForceLink.cpp
 *
 *  Created on: 13 feb 2018
 *      Author: lorenzo
 */

#include "../computers/ForceLink.h"

namespace ashell {

template<class potential>
ForceLink<potential>::ForceLink(std::string name) :
				ForceComputer(name),
				_potential({}) {

}

template<class potential>
ForceLink<potential>::~ForceLink() {

}

template<class potential>
void ForceLink<potential>::_compute_forces(ullint step) {
	const vector_vec3 &poss = _particles->positions();
	const auto &links = _sys_props->links();

	for(auto &link : links) {
		uint p = link->members[0];
		uint q = link->members[1];

		vec3 p_pos = poss[p];
		vec3 q_pos = poss[q];

		vec3 dist = _sys_props->box()->minimum_image(p_pos, q_pos);
		double r_sqr = dist.dot(dist);
		double energy = 0.;
		double force_over_r = 0.;
		_potential.evaluate(energy, force_over_r, r_sqr);

		_energy += energy;
		_energies[p] += energy;
		_energies[q] += energy;

		vec3 force = dist * force_over_r;
		_forces[p] -= force;
		_forces[q] += force;
	}
}

} /* namespace ashell */
