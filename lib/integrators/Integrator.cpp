/*
 * Integrator.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "Integrator.h"

#include "../World.h"

namespace ashell {

Integrator::Integrator() :
				_sys_props(World::current_system()->system_properties()),
				_particles(_sys_props->particles()) {

}

Integrator::~Integrator() {

}

void Integrator::step(ullint step) {
	throw std::runtime_error("Integrator::step() should never be called");
}

} /* namespace ashell */

#ifdef PYTHON_ASHELL
#include "../defs_to_python.h"

namespace ashell {

}
void export_integrator() {
	bpy::class_<Integrator, std::shared_ptr<Integrator> >("Integrator");
}

}
#endif
