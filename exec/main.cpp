/*
 * main.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "../lib/defs.h"
#include "../lib/World.h"
#include "../lib/boxes/BoxFactory.h"
#include "../lib/computers/external_forces/ConstantForce.h"
#include "../lib/computers/ForceDihedral.h"
#include "../lib/computers/ForceLink.h"
#include "../lib/computers/ForceTwoBodyIsotropic.h"
#include "../lib/Initialiser.h"
#include "../lib/updaters/integrators/VelocityVerlet.h"
#include "../lib/updaters/thermostats/ThermostatFactory.h"

#include <iostream>
#include "../lib/utils/InputFile.h"

using namespace ashell;

int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cerr << "Usage is '" << argv[0] << " input_file'" << std::endl;
		exit(1);
	}

	InputFile my_inp;
	my_inp.load_from_filename(argv[1]);

	auto system = World::new_system();
	auto sys_props = system->system_properties();

	double dt;
	my_inp.value_as_number("dt", dt, 1);
	system->set_integrator(std::shared_ptr<Integrator>(new VelocityVerlet(dt)));

	double T;
	my_inp.value_as_number("T", T, 1);
	sys_props->set_T(T);

	ullint steps;
	my_inp.value_as_ullint("steps", steps, 1);

	ullint print_defaults_every;
	my_inp.value_as_ullint("print_defaults_every", print_defaults_every, 0);
	system->set_print_defaults_every(print_defaults_every);

	std::string conf_filename;
	if(my_inp.value_as_string("configuration_file", conf_filename, 0) == KEY_FOUND) {
		Initialiser::init_configuration_from_filename(sys_props, conf_filename);

		std::string topology_filename;
		if(my_inp.value_as_string("topology_file", topology_filename, 0) == KEY_FOUND) {
			Initialiser::init_topology_from_filename(sys_props, topology_filename);
		}

		bool random_velocities = false;
		my_inp.value_as_bool("random_velocities", random_velocities, 0);
		if(random_velocities) {
			BOOST_LOG_TRIVIAL(info) << "Initialising the configuration with random velocities";
			Initialiser::set_random_velocities(sys_props);
		}
	}
	else {
		int N;
		my_inp.value_as_int("initial_N", N, 1);
		sys_props->particles()->set_N(N);

		std::string box_string;
		my_inp.value_as_string("initial_box", box_string, 1);
		sys_props->set_box(std::shared_ptr<Box>(BoxFactory::make_box(box_string)));

		BOOST_LOG_TRIVIAL(info) << "Initialising a random configuration with N = " << N << " particles";
		Initialiser::make_random_configuration_N2(sys_props);
	}

	std::string thermostat;
	if(my_inp.value_as_string("thermostat", thermostat, 0) == KEY_FOUND) {
		system->add_updater(ThermostatFactory::make_thermostat(thermostat, my_inp));
	}

//	sys_props->add_force(std::shared_ptr<LennardJonesForce>(new LennardJonesForce({1.122462048309373})));
//	sys_props->add_force(std::shared_ptr<FENEForce>(new FENEForce({15., 2.5})));
	sys_props->add_force(std::shared_ptr<HarmonicForce>(new HarmonicForce({1., 1.})));
	sys_props->add_force(std::shared_ptr<ForceDihedral>(new ForceDihedral()));

	sys_props->add_force(std::shared_ptr<ConstantForce>(new ConstantForce(vec3(-1., 0., 0.), 50., std::vector<int>(1, 484))));
	sys_props->add_force(std::shared_ptr<ConstantForce>(new ConstantForce(vec3(1., 0., 0.), 50., std::vector<int>(1, 110))));

	system->run(steps);

	return 0;
}
