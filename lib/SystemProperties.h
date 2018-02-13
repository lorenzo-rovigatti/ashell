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

class ForceComputer;
class Integrator;

class SystemProperties {
public:
	SystemProperties();
	virtual ~SystemProperties();

	auto box() const {
		return _box;
	}
	void set_box(std::shared_ptr<Box> n_box) {
		_box = n_box;
	}

	auto integrator() const {
		return _integrator;
	}
	void set_integrator(std::shared_ptr<Integrator> n_integrator) {
		_integrator = n_integrator;
	}

	auto particles() const {
		return _particles;
	}

	void set_particles(std::shared_ptr<Particles> n_particles) {
		_particles = n_particles;
	}

	double T() {
		return _T;
	}

	void set_T(double nT) {
		_T = nT;
	}

	void add_force(const std::shared_ptr<ForceComputer> n_force) {
		_forces.push_back(n_force);
	}

	void add_link(std::shared_ptr<TopologyLink<2>> n_l) {
		_links.push_back(n_l);
	}

	void add_angle(std::shared_ptr<TopologyLink<3>> n_a) {
		_angles.push_back(n_a);
	}

	void add_dihedral(std::shared_ptr<TopologyLink<4>> n_d) {
		_dihedrals.push_back(n_d);
	}

	const auto &forces() const {
		return _forces;
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

private:
	std::shared_ptr<Box> _box;
	std::shared_ptr<Integrator> _integrator;
	std::shared_ptr<Particles> _particles;
	std::vector<std::shared_ptr<ForceComputer>> _forces;

	std::vector<std::shared_ptr<TopologyLink<2>>> _links;
	std::vector<std::shared_ptr<TopologyLink<3>>> _angles;
	std::vector<std::shared_ptr<TopologyLink<4>>> _dihedrals;

	double _T;
};

} /* namespace ashell */

#endif /* LIB_SYSTEMPROPERTIES_H_ */
