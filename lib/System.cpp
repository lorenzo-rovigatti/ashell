/*
 * System.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "System.h"

#include "SystemProperties.h"
#include "integrators/Integrator.h"

#include <boost/python.hpp>

namespace ashell {

System::System() {
	_sys_props = std::shared_ptr<SystemProperties>(new SystemProperties());
}

System::~System() {

}

void System::run(ullint steps) {
	for(ullint i = 0; i < steps; i++) {
		_sys_props->integrator()->step(i);
	}
}

void export_system() {
	boost::python::class_<System, std::shared_ptr<System> >("System")
			.def("run", &System::run)
			.def("system_properties", &System::system_properties);
}

} /* namespace ashell */
