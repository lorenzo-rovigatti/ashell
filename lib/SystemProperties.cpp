/*
 * SystemProperties.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "SystemProperties.h"

#include "boxes/Box.h"
#include "integrators/Integrator.h"
#include "Particles.h"

#include "boxes/Cuboid.h"

#include <boost/python.hpp>

namespace ashell {

SystemProperties::SystemProperties() {
	_box = std::shared_ptr<Box>(new Cuboid(10., 10., 10.));
}

SystemProperties::~SystemProperties() {

}

void export_system_properties() {
	boost::python::class_<SystemProperties>("SystemProperties")
			.add_property("box", &SystemProperties::box)
			.add_property("integrator", &SystemProperties::integrator)
			.add_property("particles", &SystemProperties::particles);
}

} /* namespace ashell */
