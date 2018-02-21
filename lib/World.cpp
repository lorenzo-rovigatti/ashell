/*
 * World.cpp
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#include "World.h"

#include <algorithm>

namespace ashell {

std::shared_ptr<System> World::_current_system;
std::vector<std::shared_ptr<System> > World::_systems;

World::~World() {

}

std::shared_ptr<System> World::current_system() {
	if(_systems.size() == 0) {
		throw std::runtime_error("World: there are no initialised systems: use World::new_system first");
	}

	return _current_system;
}

std::shared_ptr<System> World::new_system() {
	auto new_syst = std::shared_ptr<System>(new System());
	_current_system = new_syst;
	_systems.push_back(new_syst);

	new_syst->init();

	return new_syst;
}

void World::remove_system(std::shared_ptr<System> syst) {
	auto syst_it = find(_systems.begin(), _systems.end(), syst);
	if(syst_it != _systems.end()) {
		_systems.erase(syst_it);
	}
	else {
		throw std::runtime_error("World: trying to remove a system that was not initialised");
	}
}

} /* namespace ashell */

#ifdef ASHELL_PYTHON
#include "defs_to_python.h"

namespace ashell {

void export_world() {
	bpy::class_<World, std::shared_ptr<World> >("World", bpy::no_init)
			.def("current_system", &World::current_system).staticmethod("current_system")
			.def("new_system", &World::new_system).staticmethod("new_system")
			.def("remove_system", &World::remove_system).staticmethod("remove_system");
}

}
#endif
