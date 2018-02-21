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
