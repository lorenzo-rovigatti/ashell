/*
 * main.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "../lib/defs.h"
#include "../lib/World.h"
#include "../lib/boxes/Cuboid.h"
#include "../lib/computers/ForceLink.h"
#include "../lib/computers/ForceTwoBodyIsotropic.h"
#include "../lib/Initialiser.h"
#include "../lib/integrators/VelocityVerlet.h"

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

	std::string conf;
	if(my_inp.value_as_string("configuration_file", conf, 0) == KEY_FOUND) {

	}
	else {
		int N;
		my_inp.value_as_int("N", &N, 1);
		sys_props->particles()->set_N(N);

		sys_props->set_box(std::shared_ptr<Box>(new Cuboid(10., 10., 10.)));

		BOOST_LOG_TRIVIAL(info) << "Initialising a random configuration with N = " << N << " particles";
		Initialiser::make_random_N2(sys_props);
	}

	double dt;
	my_inp.value_as_number("dt", &dt, 1);
	sys_props->set_integrator(std::shared_ptr<Integrator>(new VelocityVerlet(dt)));

	double T;
	my_inp.value_as_number("T", &T, 1);
	sys_props->set_T(T);

	ullint steps;
	my_inp.value_as_ullint("steps", &steps, 1);

//	_sys_props->add_link(std::shared_ptr<TopologyLink<2>>(new TopologyLink<2>(0, {0, 1})));
	sys_props->add_force(std::shared_ptr<LennardJonesForce>(new LennardJonesForce()));
	sys_props->add_force(std::shared_ptr<FENEForce>(new FENEForce()));

	system->run(steps);

	return 0;
}
