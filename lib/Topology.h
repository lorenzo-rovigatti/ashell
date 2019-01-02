/*
 * Topology.h
 *
 *  Created on: 13 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_TOPOLOGY_H_
#define LIB_TOPOLOGY_H_

#include "defs.h"

namespace ashell {

class Particles;
class Box;

// TODO: it may be worth making this class hash-able so that instances can be stored in std::set's
template<uint link_size>
struct TopologyLink {
	TopologyLink(uint n_type, std::initializer_list<uint> l);

	virtual ~TopologyLink() {}

	virtual void add_param(double new_param);

	uint N_params() {
		return params.size();
	}

	uint type;
	uint size;
	std::array<uint, link_size> members;
	std::vector<double> params;
};

struct TopologyTriangle: public TopologyLink<3> {
	TopologyTriangle(uint n_type, std::initializer_list<uint> l);

	virtual ~TopologyTriangle() {}

	void swap_normal();
	void update(const vector_vec3 &poss, const std::shared_ptr<Box> &box);

	std::array<uint, 3> vertex_indices;
	std::array<vec3, 3> vertices;
	vec3 r_10, r_21, r_02;
	vec3 com;
	vec3 normal;
};

using TopologyBond = TopologyLink<2>;
using TopologyAngle = TopologyLink<3>;
using TopologyDihedral = TopologyLink<4>;

}
/* namespace ashell */

#endif /* LIB_TOPOLOGY_H_ */
