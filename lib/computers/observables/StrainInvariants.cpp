/*
 * StrainInvariants.cpp
 *
 *  Created on: Dec 23, 2018
 *      Author: lorenzo
 */

#include "StrainInvariants.h"

#define QUICKHULL_IMPLEMENTATION
#include <quickhull/quickhull.h>
#include <Eigen/Eigenvalues>

#include <iostream>
#include <sstream>

namespace ashell {

using std::endl;

StrainInvariants::StrainInvariants(std::string n_name) :
		Observable(n_name) {

}

StrainInvariants::~StrainInvariants() {

}

std::string StrainInvariants::as_string() {
	return _line;
}

void StrainInvariants::_observe(ullint step) {
	std::stringstream ss;

	std::vector<qh_vertex_t> vertices(_particles->N());

	auto poss = _particles->positions();
	vec3 com(0., 0., 0.);
	for(uint i = 0; i < _particles->N(); i++) {
		com += poss[i];
	}
	com /= _particles->N();

	for(uint i = 0; i < _particles->N(); i++) {
		vec3 v = poss[i] - com;
		vertices[i].x = v[0];
		vertices[i].y = v[1];
		vertices[i].z = v[2];
	}

	qh_mesh_t mesh = qh_quickhull3d(vertices.data(), _particles->N());

	vec3 ch_com(0., 0., 0.);
	double ch_volume = 0.;
	for(uint i = 0; i < mesh.nindices; i += 3) {
		vec3 p1(mesh.vertices[mesh.indices[i + 0]].x, mesh.vertices[mesh.indices[i + 0]].y, mesh.vertices[mesh.indices[i + 0]].z);
		vec3 p2(mesh.vertices[mesh.indices[i + 1]].x, mesh.vertices[mesh.indices[i + 1]].y, mesh.vertices[mesh.indices[i + 1]].z);
		vec3 p3(mesh.vertices[mesh.indices[i + 2]].x, mesh.vertices[mesh.indices[i + 2]].y, mesh.vertices[mesh.indices[i + 2]].z);

		ch_volume += (p1.dot(p2.cross(p3))) / 6.;
		ch_com += (p1 + p2 + p3);
	}

	ch_com /= mesh.nindices;

	// Gyration tensor
	mat3 gyration_tensor;
	for(int i = 0, j = 0; i < (int)mesh.nindices; i += 3, j++) {
		vec3 p1(mesh.vertices[mesh.indices[i + 0]].x, mesh.vertices[mesh.indices[i + 0]].y, mesh.vertices[mesh.indices[i + 0]].z);
		vec3 p2(mesh.vertices[mesh.indices[i + 1]].x, mesh.vertices[mesh.indices[i + 1]].y, mesh.vertices[mesh.indices[i + 1]].z);
		vec3 p3(mesh.vertices[mesh.indices[i + 2]].x, mesh.vertices[mesh.indices[i + 2]].y, mesh.vertices[mesh.indices[i + 2]].z);
		vec3 triangle_com = (p1 + p2 + p3) / 3. - ch_com;

		gyration_tensor(0, 0) += SQR(triangle_com[0]);
		gyration_tensor(0, 1) += triangle_com[0] * triangle_com[1];
		gyration_tensor(0, 2) += triangle_com[0] * triangle_com[2];

		gyration_tensor(1, 1) += SQR(triangle_com[1]);
		gyration_tensor(1, 2) += triangle_com[1] * triangle_com[2];

		gyration_tensor(2, 2) += SQR(triangle_com[2]);
	}
	gyration_tensor(1, 0) = gyration_tensor(0, 1);
	gyration_tensor(2, 0) = gyration_tensor(0, 2);
	gyration_tensor(2, 1) = gyration_tensor(1, 2);
	gyration_tensor /= mesh.nindices / 3.;

	vec3 eigenvalues = gyration_tensor.eigenvalues().real();

	double eigen_volume = 4 * M_PI * sqrt(3) * sqrt(eigenvalues[0]) * sqrt(eigenvalues[1]) * sqrt(eigenvalues[2]);

	ss << " " << ch_volume;
	ss << " " << eigen_volume;
	ss << " " << sqrt(eigenvalues[0]);
	ss << " " << sqrt(eigenvalues[1]);
	ss << " " << sqrt(eigenvalues[2]);

	qh_free_mesh(mesh);

	_line = ss.str();
}

} /* namespace ashell */
