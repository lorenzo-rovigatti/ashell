/*
 * ForceTwoBody.cpp
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#include "ForceTwoBodyIsotropic.h"

#include "../defs_to_python.h"

namespace ashell {

template<class potential>
ForceTwoBodyIsotropic<potential>::ForceTwoBodyIsotropic() :
				ForceComputer(),
				_potential(2.5) {

}

template<class potential>
ForceTwoBodyIsotropic<potential>::~ForceTwoBodyIsotropic() {

}

template<class potential>
void ForceTwoBodyIsotropic<potential>::consume(ullint step) {
	if(!should_consume(step)) return;

	int N = _particles->N();
	vector_vec3 &poss = _particles->positions_writable();

	if(N != (int) _energies.size()) {
		_energies.resize(N);
		_forces.resize(N);
	}

	_energy = 0.;
	std::fill(_energies.begin(), _energies.end(), 0.);
	std::fill(_forces.begin(), _forces.end(), vec3(0., 0., 0.));

	for(int p = 0; p < N; p++) {
		vec3 p_pos = poss[p];
		for(int q = p + 1; q < N; q++) {
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
