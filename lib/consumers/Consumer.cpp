/*
 * Consumer.cpp
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#include "Consumer.h"

#include "../World.h"
#include "../defs_to_python.h"

namespace ashell {

Consumer::Consumer(std::string name) :
				_ever_consumed(false),
				_last_step(0),
				_name(name) {
	_sys_props = World::current_system()->system_properties();
	_particles = _sys_props->particles();
}

Consumer::~Consumer() {

}

bool Consumer::should_consume(ullint step) {
	if(!_ever_consumed) {
		_ever_consumed = true;
		_last_step = step;
		return true;
	}

	if(step != _last_step) {
		_last_step = step;
		return true;
	}

	return false;
}

void Consumer::consume(ullint step) {
	throw std::runtime_error("Calling an unimplemented Consumer::consume() method");
}

void export_consumer() {
	bpy::class_<Consumer>("Consumer").def("should_consume", &Consumer::should_consume).def("consume", &Consumer::consume);
}

} /* namespace ashell */
