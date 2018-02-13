/*
 * Topology.h
 *
 *  Created on: 13 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_TOPOLOGY_H_
#define LIB_TOPOLOGY_H_

#include "defs.h"

#include <boost/format.hpp>

namespace ashell {

class Topology {
public:
	Topology();
	virtual ~Topology();
};

template<uint link_size>
struct TopologyLink {
	TopologyLink(uint n_type, std::initializer_list<uint> l) :
					type(n_type),
					size(link_size) {
		if(l.size() != link_size) {
			throw std::runtime_error(boost::str(boost::format("Invalid initialisation of a topological link of size %u (got %u parameters instead)") % link_size % l.size()));
		}
		std::copy(l.begin(), l.end(), members);
	}

	uint type;
	uint size;
	std::array<uint, link_size> members;
};

}
/* namespace ashell */

#endif /* LIB_TOPOLOGY_H_ */
