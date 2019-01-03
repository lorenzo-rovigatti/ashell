/*
 * Topology.cpp
 *
 *  Created on: 02 gen 2019
 *      Author: lorenzo
 */

#include "Topology.h"

#include "boxes/Box.h"
#include "Particles.h"

namespace ashell {

template<uint link_size>
TopologyLink<link_size>::TopologyLink(uint n_type, std::initializer_list<uint> l) :
				type(n_type),
				size(link_size) {
	if(l.size() != link_size) {
		throw std::runtime_error(boost::str(boost::format("Invalid initialisation of a topological link of size %u (got %u parameters instead)") % link_size % l.size()));
	}
	std::copy(l.begin(), l.end(), members.begin());
}

template<uint link_size>
void TopologyLink<link_size>::add_param(double new_param) {
	params.push_back(new_param);
}

template class TopologyLink<2>;
template class TopologyLink<3>;
template class TopologyLink<4>;

TopologyTriangle::TopologyTriangle(uint n_type, std::initializer_list<uint> l) :
				TopologyLink<3>(n_type, l) {
	vertex_indices[0] = this->members[0];
	vertex_indices[1] = this->members[1];
	vertex_indices[2] = this->members[2];

	volume = -1.;
	area = -1.;
}

void TopologyTriangle::swap_normal() {
	uint tmp = vertex_indices[0];
	vertex_indices[0] = vertex_indices[1];
	vertex_indices[1] = tmp;
}

void TopologyTriangle::update(const vector_vec3 &poss, const std::shared_ptr<Box> &box) {
	vertices[0] = poss[this->vertex_indices[0]];
	vertices[1] = poss[this->vertex_indices[1]];
	vertices[2] = poss[this->vertex_indices[2]];

	r_10 = box->minimum_image(vertices[0], vertices[1]);
	r_21 = box->minimum_image(vertices[1], vertices[2]);
	r_02 = box->minimum_image(vertices[2], vertices[0]);

	normal = r_02.cross(r_10);
	com = (vertices[0] + vertices[1] + vertices[2]) / 3.;

	volume = normal.dot(com) / 6.;
	area = normal.norm() / 2.;
}

} /* namespace ashell */
