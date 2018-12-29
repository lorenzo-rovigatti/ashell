/*
 * ForceTriangle.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: lorenzo
 */

#include "ForceTriangle.h"

namespace ashell {

ForceTriangle::ForceTriangle(std::string name) :
				ForceComputer(name),
				_kv(100.),
				_V0(0.) {

}

ForceTriangle::~ForceTriangle() {

}

void ForceTriangle::set_kv(double n_kv) {
	_kv = n_kv;
}

void ForceTriangle::set_V0(double n_V0) {
	_V0 = n_V0;
}

void ForceTriangle::_compute_forces(ullint step) {
	const vector_vec3 &poss = _particles->positions();

	// see Sofia Biagi's thesis, pag. 114
	double volume = 0.;
	// we make a first loop to compute the overall volume
	for(auto &triangle : _sys_props->triangles()) {
		uint i = triangle->members[0];
		uint j = triangle->members[1];
		uint k = triangle->members[2];

		vec3 i_pos = poss[i];
		vec3 j_pos = poss[j];
		vec3 k_pos = poss[k];

		vec3 r_kj = _sys_props->box()->minimum_image(j_pos, k_pos);
		vec3 r_ik = _sys_props->box()->minimum_image(k_pos, i_pos);
//		vec3 r_ji = _sys_props->box()->minimum_image(i_pos, j_pos);

		vec3 normal = r_kj.cross(r_ik);
		vec3 com = (i_pos + j_pos + k_pos) / 3.;

		volume += normal.dot(com) / 6.;
	}

	double gamma_t = _kv * (volume - _V0) / (6. * _V0);
	// and then a second loop to evalue the forces
	for(auto &triangle : _sys_props->triangles()) {
		uint i = triangle->members[0];
		uint j = triangle->members[1];
		uint k = triangle->members[2];

		vec3 i_pos = poss[i];
		vec3 j_pos = poss[j];
		vec3 k_pos = poss[k];

		// see Sofia Biagi's thesis, pag. 114
		vec3 r_kj = _sys_props->box()->minimum_image(j_pos, k_pos);
		vec3 r_ik = _sys_props->box()->minimum_image(k_pos, i_pos);
		vec3 r_ji = _sys_props->box()->minimum_image(i_pos, j_pos);

		vec3 normal = r_kj.cross(r_ik);
		vec3 com = (i_pos + j_pos + k_pos) / 3.;

		_forces[i] += -gamma_t * (normal / 3. + com.cross(r_kj));
		_forces[j] += -gamma_t * (normal / 3. + com.cross(r_ik));
		_forces[k] += -gamma_t * (normal / 3. + com.cross(r_ji));

		// TODO: update the energy of the single particles
	}

	_energy += _kv * SQR(volume - _V0) / (2. * _V0);
}

} /* namespace ashell */
