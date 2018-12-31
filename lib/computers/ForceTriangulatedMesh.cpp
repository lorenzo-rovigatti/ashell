/*
 * ForceTriangle.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: lorenzo
 */

#include "ForceTriangulatedMesh.h"

namespace ashell {

ForceTriangulatedMesh::ForceTriangulatedMesh(std::string name) :
				ForceComputer(name),
				_kv(-1.),
				_ka(-1.),
				_V0(-1.),
				_A0(-1.) {

}

ForceTriangulatedMesh::~ForceTriangulatedMesh() {

}

void ForceTriangulatedMesh::set_kv(double n_kv) {
	_kv = n_kv;
}

void ForceTriangulatedMesh::set_ka(double n_ka) {
	_ka = n_ka;
}

void ForceTriangulatedMesh::set_V0(double n_V0) {
	_V0 = n_V0;
}

void ForceTriangulatedMesh::set_A0(double n_A0) {
	_A0 = n_A0;
}

void ForceTriangulatedMesh::set_V0_from_conf() {
	auto V_A_pair = _get_volume_and_area();
	_V0 = V_A_pair.first;
}

void ForceTriangulatedMesh::set_A0_from_conf() {
	auto V_A_pair = _get_volume_and_area();
	_A0 = V_A_pair.second;
}

void ForceTriangulatedMesh::_compute_forces(ullint step) {
	auto V_A_pair = _get_volume_and_area();
	double volume = V_A_pair.first;
	double area = V_A_pair.second;

	const vector_vec3 &poss = _particles->positions();

	double gamma_t = _kv * (volume - _V0) / (6. * _V0);
	double alpha_t = _ka * (area - _A0) / (4. * _A0);
	// and then a second loop to evalue the forces
	for(auto &triangle : _sys_props->triangles()) {
		uint i = triangle->members[0];
		uint j = triangle->members[1];
		uint k = triangle->members[2];

		vec3 i_pos = poss[i];
		vec3 j_pos = poss[j];
		vec3 k_pos = poss[k];

		vec3 r_kj = _sys_props->box()->minimum_image(j_pos, k_pos);
		vec3 r_ik = _sys_props->box()->minimum_image(k_pos, i_pos);
		vec3 r_ji = _sys_props->box()->minimum_image(i_pos, j_pos);

		// volume terms
		vec3 normal = r_kj.cross(r_ik);
		vec3 com = (i_pos + j_pos + k_pos) / 3.;

		_forces[i] += -gamma_t * (normal / 3. + com.cross(r_kj));
		_forces[j] += -gamma_t * (normal / 3. + com.cross(r_ik));
		_forces[k] += -gamma_t * (normal / 3. + com.cross(r_ji));

		// TODO: update the energy of the single particles

		// area terms
		double triangle_area = normal.norm() / 2.;
		double alpha_t_triangle = alpha_t / triangle_area;

		_forces[i] += -alpha_t_triangle * normal.cross(r_kj);
		_forces[j] += -alpha_t_triangle * normal.cross(r_ik);
		_forces[k] += -alpha_t_triangle * normal.cross(r_ji);

		// TODO: update the energy of the single particles
	}

	_energy += _kv * SQR(volume - _V0) / (2. * _V0);
	_energy += _ka * SQR(area - _A0) / (2. * _A0);
}

std::pair<double, double> ForceTriangulatedMesh::_get_volume_and_area() {
	const vector_vec3 &poss = _particles->positions();
	double volume = 0.;
	double area = 0.;
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

		vec3 normal = r_kj.cross(r_ik);
		vec3 com = (i_pos + j_pos + k_pos) / 3.;

		volume += normal.dot(com) / 6.;
		area += normal.norm() / 2.;
	}

	return std::pair<double, double>(volume, area);
}

} /* namespace ashell */
