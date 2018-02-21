/*
 * SystemProperties.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "SystemProperties.h"

#include "computers/ForceComputer.h"
#include "integrators/Integrator.h"
#include "Particles.h"

namespace ashell {

SystemProperties::SystemProperties() :
				_box(nullptr),
				_integrator(nullptr),
				_particles(nullptr),
				_T(1.0) {

}

SystemProperties::~SystemProperties() {

}

void SystemProperties::set_box(std::shared_ptr<Box> n_box) {
	_box = n_box;
}

void SystemProperties::set_integrator(std::shared_ptr<Integrator> n_integrator) {
	_integrator = n_integrator;
}

void SystemProperties::set_particles(std::shared_ptr<Particles> n_particles) {
	_particles = n_particles;
}

void SystemProperties::set_T(double nT) {
	_T = nT;
}

void SystemProperties::add_force(const std::shared_ptr<ForceComputer> n_force) {
	_forces.push_back(n_force);
}

void SystemProperties::add_link(std::shared_ptr<TopologyLink<2>> n_l) {
	_links.push_back(n_l);
}

void SystemProperties::add_angle(std::shared_ptr<TopologyLink<3>> n_a) {
	_angles.push_back(n_a);
}

void SystemProperties::add_dihedral(std::shared_ptr<TopologyLink<4>> n_d) {
	_dihedrals.push_back(n_d);
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
