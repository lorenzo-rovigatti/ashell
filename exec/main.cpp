/*
 * main.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "../lib/defs.h"
#include "../lib/World.h"
#include "../lib/boxes/BoxFactory.h"
#include "../lib/computers/external_forces/ForceFactory.h"
#include "../lib/computers/ForceDihedral.h"
#include "../lib/computers/ForceLink.h"
#include "../lib/computers/ForceTwoBodyIsotropic.h"
#include "../lib/Initialiser.h"
#include "../lib/updaters/integrators/VelocityVerlet.h"
#include "../lib/updaters/thermostats/ThermostatFactory.h"
#include "../lib/utils/Timings.h"

#include <iostream>
#include "../lib/utils/InputFile.h"

using namespace ashell;

void init_from_input(InputFile &inp, std::shared_ptr<System> system) {
	auto sys_props = system->system_properties();

	double dt;
	inp.value_as_number("dt", dt, 1);
	system->set_integrator(std::shared_ptr<Integrator>(new VelocityVerlet(dt)));

	double T;
	inp.value_as_number("T", T, 1);
	sys_props->set_T(T);

	ullint print_defaults_every;
	inp.value_as_integer<ullint>("print_defaults_every", print_defaults_every, 1);
	system->set_print_defaults_every(print_defaults_every);

	ullint print_configuration_every;
	inp.value_as_integer<ullint>("print_configuration_every", print_configuration_every, 1);
	system->set_print_configuration_every(print_configuration_every);

	std::string conf_filename;
	if(inp.value_as_string("configuration_file", conf_filename, 0) == KeyState::FOUND) {
		Initialiser::init_configuration_from_filename(sys_props, conf_filename);

		std::string topology_filename;
		if(inp.value_as_string("topology_file", topology_filename, 0) == KeyState::FOUND) {
			Initialiser::init_topology_from_filename(sys_props, topology_filename);
		}

		bool random_velocities = false;
		inp.value_as_bool("random_velocities", random_velocities, 0);
		if(random_velocities) {
			BOOST_LOG_TRIVIAL(info)<< "Initialising the configuration with random velocities";
			Initialiser::set_random_velocities(sys_props);
		}
	}
	else {
		uint N;
		inp.value_as_integer<uint>("initial_N", N, 1);
		sys_props->particles()->set_N(N);

		std::string box_string;
		inp.value_as_string("initial_box", box_string, 1);
		sys_props->set_box(std::shared_ptr<Box>(BoxFactory::make_box(box_string)));

		BOOST_LOG_TRIVIAL(info) << "Initialising a random configuration with N = " << N << " particles";
		Initialiser::make_random_configuration_N2(sys_props);
	}

	std::string thermostat;
	if(inp.value_as_string("thermostat", thermostat, 0) == KeyState::FOUND) {
		system->add_updater(ThermostatFactory::make_thermostat(thermostat, inp));
	}

	// initialise external forces
	auto ext_forces = inp.get_aggregated("external_force");
	for(auto ext_force_input : ext_forces) {
		auto new_force = ForceFactory::make_force(ext_force_input);
		sys_props->add_force(new_force);
	}
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cerr << "Usage is '" << argv[0] << " input_file'" << std::endl;
		exit(1);
	}

	TimingManager::instance()->new_timer("Simulation");
	TimingManager::instance()->new_timer("Initialisation", "Simulation");
	TimingManager::instance()->new_timer("Main loop", "Simulation");
	TimingManager::instance()->new_timer("Integration", "Main loop");
	TimingManager::instance()->new_timer("Force calculation", "Main loop");
	TimingManager::instance()->new_timer("Analysis", "Main loop");

	TimingManager::instance()->get_timer_by_desc("Simulation")->resume();
	TimingManager::instance()->get_timer_by_desc("Initialisation")->resume();

	auto system = World::new_system();
	InputFile my_inp;

	try {
		my_inp.load_from_filename(argv[1]);
		init_from_input(my_inp, system);

		auto sys_props = system->system_properties();
//		sys_props->add_force(std::shared_ptr<LennardJonesForce>(new LennardJonesForce({1.122462048309373})));
//		sys_props->add_force(std::shared_ptr<FENEForce>(new FENEForce({15., 2.5})));
		sys_props->add_force(std::shared_ptr<HarmonicForce>(new HarmonicForce( { 1., 1. })));
		sys_props->add_force(std::shared_ptr<ForceDihedral>(new ForceDihedral()));
	}
	catch(std::exception &e) {
		BOOST_LOG_TRIVIAL(error)<< "Caught the following error during the initialisation, aborting\n" << e.what();
		return 1;
	}

	TimingManager::instance()->get_timer_by_desc("Initialisation")->pause();

	ullint steps;
	try {
		my_inp.value_as_integer<ullint>("steps", steps, 1);
		system->run(steps);
	}
	catch(std::exception &e) {
		BOOST_LOG_TRIVIAL(error)<< "Caught the following error during the run, aborting\n" << e.what();
		return 1;
	}

	TimingManager::instance()->get_timer_by_desc("Simulation")->pause();
	TimingManager::instance()->print(steps);

	return 0;
}
