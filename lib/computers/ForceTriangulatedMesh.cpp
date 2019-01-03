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

	// TODO: normals have to be chosen all in the same direction
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
	double unused;
	std::tie(_V0, unused) = _get_volume_and_area();
}

void ForceTriangulatedMesh::set_A0_from_conf() {
	double unused;
	std::tie(unused, _A0) = _get_volume_and_area();
}

void ForceTriangulatedMesh::_compute_forces(ullint step) {
	double volume, area;
	std::tie(volume, area) = _get_volume_and_area();

	double gamma_t = _kv * (volume - _V0) / (6. * _V0);
	double alpha_t = _ka * (area - _A0) / (4. * _A0);
	for(auto &triangle : _sys_props->triangles()) {
		uint v0 = triangle->vertex_indices[0];
		uint v1 = triangle->vertex_indices[1];
		uint v2 = triangle->vertex_indices[2];

		vec3 &com = triangle->com;
		vec3 &normal = triangle->normal;
		vec3 &r_21 = triangle->r_21;
		vec3 &r_10 = triangle->r_10;
		vec3 &r_02 = triangle->r_02;

		_forces[v0] += -gamma_t * (normal / 3. + com.cross(r_21));
		_forces[v1] += -gamma_t * (normal / 3. + com.cross(r_02));
		_forces[v2] += -gamma_t * (normal / 3. + com.cross(r_10));

		// TODO: update the energy of the single particles

		// area terms
		double alpha_t_triangle = alpha_t / triangle->area;

		_forces[v0] += -alpha_t_triangle * normal.cross(r_21);
		_forces[v1] += -alpha_t_triangle * normal.cross(r_02);
		_forces[v2] += -alpha_t_triangle * normal.cross(r_10);

		// TODO: update the energy of the single particles
	}

	if(step % 1000 == 0) {
		printf("V: %lf\n", volume);
	}

	_energy += _kv * SQR(volume - _V0) / (2. * _V0);
	_energy += _ka * SQR(area - _A0) / (2. * _A0);
}

std::tuple<double, double> ForceTriangulatedMesh::_get_volume_and_area() {
	const vector_vec3 &poss = _particles->positions();
	double volume = 0.;
	double area = 0.;
	for(auto &triangle : _sys_props->triangles()) {
		triangle->update(poss, _sys_props->box());

		volume += triangle->volume;
		area += triangle->area;
	}

	return std::tuple<double, double>(volume, area);
}

} /* namespace ashell */
