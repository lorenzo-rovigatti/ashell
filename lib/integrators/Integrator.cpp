/*
 * Integrator.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "Integrator.h"

#include "../defs_to_python.h"
#include "../World.h"

#include <boost/log/trivial.hpp>

namespace ashell {

Integrator::Integrator() {
	_particles = World::current_system()->system_properties()->particles();
}

Integrator::~Integrator() {

}

void Integrator::step(ullint step) {
	throw std::runtime_error("Integrator::step() should never be called");
}

void export_integrator() {
	bpy::class_<Integrator, std::shared_ptr<Integrator> >("Integrator");
}

} /* namespace ashell */
