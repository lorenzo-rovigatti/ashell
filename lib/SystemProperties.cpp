/*
 * SystemProperties.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "SystemProperties.h"

#include "boxes/Box.h"
#include "Initialiser.h"
#include "integrators/VelocityVerlet.h"
#include "Particles.h"

#include "boxes/Cuboid.h"

#include <boost/python.hpp>

namespace ashell {

SystemProperties::SystemProperties() {
	_box = std::shared_ptr<Box>(new Cuboid(10., 10., 10.));
	_integrator = std::shared_ptr<Integrator>(new VelocityVerlet(0.001));
	_particles = Initialiser::make_random(100, _box);
}

SystemProperties::~SystemProperties() {

}

void export_system_properties() {
	boost::python::class_<SystemProperties, std::shared_ptr<SystemProperties> >("SystemProperties")
			.add_property("box", &SystemProperties::box)
			.add_property("integrator", &SystemProperties::integrator)
			.add_property("particles", &SystemProperties::particles);
}

} /* namespace ashell */
