/*
 * Updater.cpp
 *
 *  Created on: 26 feb 2018
 *      Author: lorenzo
 */

#include "Updater.h"

#include "../World.h"

namespace ashell {

Updater::Updater() :
				_sys_props(World::current_system()->system_properties()),
				_particles(_sys_props->particles()) {

}

Updater::~Updater() {

}

void Updater::update(ullint step) {
	throw std::runtime_error("Updater::update() should never be called");
}

} /* namespace ashell */
