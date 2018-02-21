/*
 * System.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "System.h"

#include "boxes/Cuboid.h"
#include "computers/ForceLink.h"
#include "computers/ForceTwoBodyIsotropic.h"
#include "computers/observables/Configuration.h"
#include "computers/observables/Step.h"
#include "computers/observables/TotalEnergy.h"
#include "Initialiser.h"
#include "integrators/VelocityVerlet.h"
#include "SystemProperties.h"
#include "Topology.h"

namespace ashell {

System::System() :
				_current_step(0) {
	_sys_props = std::shared_ptr<SystemProperties>(new SystemProperties());
}

System::~System() {
	for(auto output : _after_clean_outputs) {
		output->print_output(_current_step);
	}
}

void System::init() {
	_sys_props->set_box(std::shared_ptr<Box>(new Cuboid(10., 10., 10.)));
	_sys_props->set_particles(std::shared_ptr<Particles>(new Particles(100)));
	_sys_props->set_integrator(std::shared_ptr<Integrator>(new VelocityVerlet(0.001)));
	_sys_props->set_T(1.0);

//	_sys_props->add_link(std::shared_ptr<TopologyLink<2>>(new TopologyLink<2>(0, {0, 1})));
	_sys_props->add_force(std::shared_ptr<LennardJonesForce>(new LennardJonesForce()));
	_sys_props->add_force(std::shared_ptr<FENEForce>(new FENEForce()));

	Initialiser::make_random_N2(_sys_props);

	std::shared_ptr<OutputObservable> to_stdout(new OutputObservable("stdout", 10));
	to_stdout->add_observable(std::shared_ptr<Step>(new Step()));
	to_stdout->add_observable(std::shared_ptr<TotalEnergy>(new TotalEnergy()));
	_outputs.push_back(to_stdout);

	std::shared_ptr<OutputObservable> last_conf(new OutputObservable("last_conf.dat", 0));
	last_conf->add_observable(std::shared_ptr<Configuration>(new Configuration()));
	_after_clean_outputs.push_back(last_conf);
}

void System::run(ullint steps) {
	if(_sys_props == nullptr) {
		throw std::runtime_error("System::init should be called before System::run");
	}

	for(ullint i = 0; i < steps; i++) {
		_sys_props->integrator()->step(_current_step);
		_current_step++;

		for(auto output : _outputs) {
			if(output->is_ready(_current_step)) output->print_output(_current_step);
		}
	}
}


} /* namespace ashell */

#ifdef ASHELL_PYTHON
#include "defs_to_python.h"

namespace ashell {

	void export_system() {
		bpy::class_<System, std::shared_ptr<System> >("System").def("init", &System::init).def("run", &System::run).def("system_properties", &System::system_properties);
	}

}
#endif
