/*
 * Consumer.cpp
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#include "../computers/Computer.h"

#include "../World.h"

namespace ashell {

Computer::Computer(std::string name) :
				_ever_computed(false),
				_last_step(0),
				_name(name) {
	_sys_props = World::current_system()->system_properties();
	_particles = _sys_props->particles();
}

Computer::~Computer() {

}

bool Computer::should_compute(ullint step) {
	if(!_ever_computed) {
		_ever_computed = true;
		_last_step = step;
		return true;
	}

	if(step != _last_step) {
		_last_step = step;
		return true;
	}

	return false;
}

void Computer::compute(ullint step) {
	throw std::runtime_error("Calling an unimplemented Computer::compute() method");
}

} /* namespace ashell */

#ifdef ASHELL_PYTHON
#include "../defs_to_python.h"

namespace ashell {

void export_computer() {
	bpy::class_<Computer>("Computer").def("should_compute", &Computer::should_compute).def("compute", &Computer::compute);
}

}
#endif
