/*
 * SystemProperties.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_SYSTEMPROPERTIES_H_
#define LIB_SYSTEMPROPERTIES_H_

#include "boxes/Box.h"
#include "Particles.h"
#include "Topology.h"

#include <memory>

namespace ashell {

using normal_index = std::pair<uint, uint>;

class SystemProperties {
public:
	SystemProperties();
	virtual ~SystemProperties();

	auto box() const {
		return _box;
	}

	auto particles() const {
		return _particles;
	}

	double T() {
		return _T;
	}

	const auto &bonds() const {
		return _bonds;
	}

	const auto &angles() const {
		return _angles;
	}

	const auto &triangles() const {
		return _triangles;
	}

	const auto &dihedrals() const {
		return _dihedrals;
	}

	void set_box(std::shared_ptr<Box> n_box);
	void set_T(double nT);

	void add_bond(std::shared_ptr<TopologyBond> n_b);
	void add_angle(std::shared_ptr<TopologyAngle> n_a);
	void add_triangle(std::shared_ptr<TopologyTriangle> n_t);
	void add_dihedral(std::shared_ptr<TopologyDihedral> n_d);

	void update_topology();

private:
	std::shared_ptr<Box> _box;
	std::shared_ptr<Particles> _particles;

	std::vector<std::shared_ptr<TopologyBond>> _bonds;
	std::vector<std::shared_ptr<TopologyAngle>> _angles;
	std::vector<std::shared_ptr<TopologyTriangle>> _triangles;
	std::vector<std::shared_ptr<TopologyDihedral>> _dihedrals;

	double _T;
};

} /* namespace ashell */

#endif /* LIB_SYSTEMPROPERTIES_H_ */
