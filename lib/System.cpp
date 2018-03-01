/*
 * System.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "System.h"

#include "computers/ForceComputer.h"
#include "computers/observables/Cogli1Configuration.h"
#include "computers/observables/Configuration.h"
#include "computers/observables/Step.h"
#include "computers/observables/TotalEnergy.h"
#include "OutputObservable.h"
#include "updaters/integrators/Integrator.h"
#include "updaters/Updater.h"
#include "SystemProperties.h"
#include "Topology.h"

#include <csignal>

namespace ashell {

void gbl_terminate (int arg) {
	// we make it so pressing ctrl+c twice kills the program no matter what.
	if(!System::started || System::stop) signal(arg, SIG_DFL);
	BOOST_LOG_TRIVIAL(info) << "# Caught SIGNAL " << arg << "; setting stop = true\n";
	System::stop = true;
}

bool System::stop = false;
bool System::started = false;

System::System() :
				_sys_props(std::shared_ptr<SystemProperties>(new SystemProperties())),
				_integrator(nullptr),
				_current_step(0),
				_print_defaults_every(1000) {
	// here we handle a few SIG* signals;
	signal(SIGTERM, gbl_terminate);
	signal(SIGABRT, gbl_terminate);
	signal(SIGINT, gbl_terminate);
	signal(SIGUSR2, gbl_terminate);
}

System::~System() {
	for(auto output : _after_clean_outputs) {
		output->print_output(_current_step);
	}
}

void System::init() {
	std::shared_ptr<OutputObservable> to_stdout(new OutputObservable("stdout", _print_defaults_every));
	std::shared_ptr<OutputObservable> to_energy(new OutputObservable("energy.dat", _print_defaults_every));
	std::shared_ptr<OutputObservable> to_cogli1_traj(new OutputObservable("trajectory.mgl", _print_defaults_every));

	auto step_obs = std::shared_ptr<Step>(new Step());
	auto energy_obs = std::shared_ptr<TotalEnergy>(new TotalEnergy());

	to_stdout->add_observable(step_obs);
	to_energy->add_observable(step_obs);

	to_stdout->add_observable(energy_obs);
	to_energy->add_observable(energy_obs);

	to_cogli1_traj->add_observable(std::shared_ptr<Cogli1Configuration>(new Cogli1Configuration()));

	_default_outputs.push_back(to_stdout);
	_default_outputs.push_back(to_energy);
	_default_outputs.push_back(to_cogli1_traj);
	_outputs.push_back(to_stdout);
	_outputs.push_back(to_energy);
	_outputs.push_back(to_cogli1_traj);

	std::shared_ptr<OutputObservable> last_conf(new OutputObservable("last_conf.dat", 0));
	last_conf->add_observable(std::shared_ptr<Configuration>(new Configuration()));
	_after_clean_outputs.push_back(last_conf);
}

void System::run(ullint steps) {
	if(_sys_props == nullptr) {
		throw std::runtime_error("System::init should be called before System::run");
	}

	// we compute all the forces at the beginning so that the observables can work
	// with updated data
	for(auto &force_computer : _sys_props->forces()) {
		force_computer->compute(_current_step);
	}

	System::started = true;
	for(ullint i = 0; i < steps && !System::stop; i++) {
		for(auto output : _outputs) {
			if(output->is_ready(_current_step)) output->print_output(_current_step);
		}

		for(auto updater: _updaters) {
			updater->update(_current_step);
		}

		_integrator->step(_current_step);
		_current_step++;
	}
	System::started = false;
}

void System::add_updater(std::shared_ptr<Updater> new_updater) {
	_updaters.push_back(new_updater);
}

void System::set_integrator(std::shared_ptr<Integrator> n_integrator) {
	_integrator = n_integrator;
}

void System::set_print_defaults_every(ullint n_print_defaults_every) {
	_print_defaults_every = n_print_defaults_every;
	for(auto output : _default_outputs) {
		output->set_print_every(_print_defaults_every);
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
