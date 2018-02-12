/*
 * System.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "System.h"

#include "boxes/Cuboid.h"
#include "consumers/ForceTwoBodyIsotropic.h"
#include "consumers/observables/TotalEnergy.h"
#include "Initialiser.h"
#include "integrators/VelocityVerlet.h"
#include "SystemProperties.h"
#include "defs_to_python.h"

namespace ashell {

System::System() {
	_sys_props = nullptr;
}

System::~System() {

}

void System::init() {
	_sys_props = std::shared_ptr<SystemProperties>(new SystemProperties());

	_sys_props->set_box(std::shared_ptr<Box>(new Cuboid(10., 10., 10.)));
	_sys_props->set_particles(Initialiser::make_random_N2(100, _sys_props->box()));
	_sys_props->set_integrator(std::shared_ptr<Integrator>(new VelocityVerlet(0.001)));
	_sys_props->set_T(1.0);

	_sys_props->add_pair_force(std::shared_ptr<LennardJonesForce>(new LennardJonesForce));

	std::shared_ptr<OutputObservable> to_stdout(new OutputObservable("stdout", 10));
	to_stdout->add_observable(std::shared_ptr<TotalEnergy>(new TotalEnergy()));
	_outputs.push_back(to_stdout);
}

void System::run(ullint steps) {
	if(_sys_props == nullptr) {
		throw std::runtime_error("System::init should be called before System::run");
	}
	for(ullint i = 0; i < steps; i++) {
		_sys_props->integrator()->step(i);

		for(auto output : _outputs) {
			if(output->is_ready(i)) output->print_output(i);
		}
	}
}

void export_system() {
	bpy::class_<System, std::shared_ptr<System> >("System").def("init", &System::init).def("run", &System::run).def("system_properties", &System::system_properties);
}

} /* namespace ashell */
