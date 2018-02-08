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

void System::run(long long int steps) {
	for(int i = 0; i < steps; i++) {
		_sys_props->integrator()->step();
	}
}

void export_system() {
	boost::python::class_<System>("System")
			.def("run", &System::run);
}

} /* namespace ashell */
