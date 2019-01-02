/*
 * SystemProperties.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "SystemProperties.h"

#include "Particles.h"

#include <algorithm>

namespace ashell {

SystemProperties::SystemProperties() :
				_box(nullptr),
				_particles(std::shared_ptr<Particles>(new Particles(1))),
				_T(1.0) {

}

SystemProperties::~SystemProperties() {

}

void SystemProperties::set_box(std::shared_ptr<Box> n_box) {
	_box = n_box;
}

void SystemProperties::set_T(double nT) {
	_T = nT;
}

void SystemProperties::add_bond(std::shared_ptr<TopologyBond> n_b) {
	_bonds.push_back(n_b);
}

void SystemProperties::add_angle(std::shared_ptr<TopologyAngle> n_a) {
	_angles.push_back(n_a);
}

void SystemProperties::add_triangle(std::shared_ptr<TopologyTriangle> n_t) {
	_triangles.push_back(n_t);
}

void SystemProperties::add_dihedral(std::shared_ptr<TopologyDihedral> n_d) {
	_dihedrals.push_back(n_d);
}

void SystemProperties::update_topology() {
	// here we normalise the normals of the triangles so that
	// 1) normals of neighbouring triangles are concordant
	// 2) the volume of the object enclosed by the triangle mesh is positive

	// we start by updating all the triangles so that centres of mass, normals, vertices and edges are initialised
	for(auto &triangle : triangles()) {
		triangle->update(particles()->positions(), box());
	}

	// this lambda function returns true whether the two triangles passed as arguments share at least one vertex
	auto are_neighbours = [] (const std::shared_ptr<TopologyTriangle> &t1, const std::shared_ptr<TopologyTriangle> &t2) {
		for(auto vertex : t1->vertex_indices) {
			auto it = std::find(t2->vertex_indices.begin(), t2->vertex_indices.end(), vertex);
			if(it != t2->vertex_indices.end()) {
				return true;
			}
		}
		return false;
	};

	// this vector keeps track of the triangles that have been already visited
	std::vector<bool> normal_initialised(triangles().size(), false);
	// this lambda function loops over all triangles, check which one is t_ref's neighbour and ensures that the normals of t_ref
	// and of its neighbours are concordant
	// NOTE: we have to explicitly specify the type of the lambda function because we use it recursively
	std::function<void(const std::shared_ptr<TopologyTriangle> &)> flip_neigh_normals = [&] (const std::shared_ptr<TopologyTriangle> &t_ref) {
		// TODO: build a neighbour list to get rid of the O(N^2) (N == N_triangles) complexity
		for(uint i = 0; i < triangles().size(); i++) {
			auto t_curr = triangles()[i];
			if(!normal_initialised[i] && are_neighbours(t_curr, t_ref)) {
				if(t_curr->normal.dot(t_ref->normal) < 0.) {
					t_curr->swap_normal();
					t_curr->update(particles()->positions(), box());
				}
				normal_initialised[i] = true;
				flip_neigh_normals(t_curr);
			}
		}
	};

	// here we start the recursive process
	flip_neigh_normals(triangles()[0]);

	// now we compute the volume enclosed
	double volume = 0.;
	for(auto &triangle : triangles()) {
		volume += triangle->normal.dot(triangle->com) / 6.;
	}
	// if the volume comes out negative we flip *all* the normals
	if(volume < 0.) {
		for(auto &triangle : triangles()) {
			triangle->swap_normal();
		}
	}
}

} /* namespace ashell */

#ifdef ASHELL_PYTHON
#include "defs_to_python.h"

namespace ashell {

	void export_system_properties() {
		bpy::class_<SystemProperties, std::shared_ptr<SystemProperties> >("SystemProperties")
		.add_property("box", &SystemProperties::box, &SystemProperties::set_box)
		.add_property("integrator", &SystemProperties::integrator, &SystemProperties::set_integrator)
		.add_property("particles", &SystemProperties::particles, &SystemProperties::set_particles)
		.add_property("T", &SystemProperties::T, &SystemProperties::set_T);
	}

}
#endif
