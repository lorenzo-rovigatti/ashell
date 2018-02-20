/*
 * ForceTwoBody.cpp
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#include "../computers/ForceTwoBodyIsotropic.h"

#include "../defs_to_python.h"

namespace ashell {

template<class potential>
ForceTwoBodyIsotropic<potential>::ForceTwoBodyIsotropic(std::string name) :
				ForceComputer(name),
				_potential({2.5}) {

}

template<class potential>
ForceTwoBodyIsotropic<potential>::~ForceTwoBodyIsotropic() {

}

template<class potential>
void ForceTwoBodyIsotropic<potential>::_compute_forces(ullint step) {
	const vector_vec3 &poss = _particles->positions();

	for(uint p = 0; p < _particles->N(); p++) {
		vec3 p_pos = poss[p];
		for(uint q = p + 1; q < _particles->N(); q++) {
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
}

} /* namespace ashell */
