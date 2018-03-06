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

	const auto &links() const {
		return _links;
	}

	const auto &angles() const {
		return _angles;
	}

	const auto &dihedrals() const {
		return _dihedrals;
	}

	void set_box(std::shared_ptr<Box> n_box);
	void set_T(double nT);

	void add_link(std::shared_ptr<TopologyLink<2>> n_l);
	void add_angle(std::shared_ptr<TopologyLink<3>> n_a);
	void add_dihedral(std::shared_ptr<TopologyLink<4>> n_d);

private:
	std::shared_ptr<Box> _box;
	std::shared_ptr<Particles> _particles;

	std::vector<std::shared_ptr<TopologyLink<2>>> _links;
	std::vector<std::shared_ptr<TopologyLink<3>>> _angles;
	std::vector<std::shared_ptr<TopologyLink<4>>> _dihedrals;

	double _T;
};

} /* namespace ashell */

#endif /* LIB_SYSTEMPROPERTIES_H_ */
