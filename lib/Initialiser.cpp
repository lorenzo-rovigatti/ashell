/*
 * Initialiser.cpp
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#include "Initialiser.h"

#include "boxes/BoxFactory.h"
#include "SystemProperties.h"
#include "utils/MathUtils.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>

namespace ashell {

Initialiser::~Initialiser() {

}

void Initialiser::make_random_configuration_N2(std::shared_ptr<SystemProperties> sys_props) {
	int N = sys_props->particles()->N();
	auto box = sys_props->box();

	vector_vec3 poss(1, box->random_point_in_box());
	while((int) poss.size() != N) {
		vec3 n_pos = box->random_point_in_box();
		bool insert = true;
		for(auto &pos : poss) {
			vec3 dist = box->minimum_image(pos, n_pos);
			if(dist.dot(dist) < 1.) {
				insert = false;
			}
		}
		if(insert) poss.push_back(n_pos);
	}

	sys_props->particles()->positions_writable() = poss;

	set_random_velocities(sys_props);
}

void Initialiser::init_configuration_from_filename(std::shared_ptr<SystemProperties> sys_props, std::string filename) {
	std::ifstream inp(filename.c_str());

	if(inp.bad() || !inp.good()) {
		std::string error = boost::str(boost::format("Configuration file '%s' not found") % filename);
		throw std::runtime_error(error);
	}

	std::string line;
	// time step
	std::getline(inp, line);
	// number of particles
	std::getline(inp, line);
	uint N = boost::lexical_cast<uint>(line);

	// box line
	std::getline(inp, line);
	sys_props->set_box(std::shared_ptr<Box>(BoxFactory::make_box(line)));

	auto particles = sys_props->particles();
	particles->set_N(N);
	vector_vec3 &poss = particles->positions_writable();
	vector_vec3 &vels = particles->velocities_writable();

	uint N_read = 0;
	while(std::getline(inp, line)) {
		// sanity check
		if(N_read > N) {
			std::string error = boost::str(boost::format("Configuration file '%s' contains more particle lines than the value specified in the header (%d)") % filename % N);
			throw std::runtime_error(error);
		}

		std::vector<std::string> spl_line;
		// split the string into tokens. The last argument makes sure that adjacent whitespace is compressed and
		// considered as a single separator
		boost::split(spl_line, line, boost::is_any_of("\t "), boost::token_compress_on);
		if(spl_line.size() != 6) {
			std::string error = boost::str(boost::format("Line number %d contains %d fields, should be 6") % (N_read + 3) % spl_line.size());
			throw std::runtime_error(error);
		}

		poss[N_read] = vec3(
				boost::lexical_cast<double>(spl_line[0]),
				boost::lexical_cast<double>(spl_line[1]),
				boost::lexical_cast<double>(spl_line[2])
		);

		vels[N_read] = vec3(
				boost::lexical_cast<double>(spl_line[3]),
				boost::lexical_cast<double>(spl_line[4]),
				boost::lexical_cast<double>(spl_line[5])
		);

		N_read++;
	}

	if(N_read != N) {
		std::string error = boost::str(boost::format("Configuration file '%s' contains fewer particle lines than the value specified in the header (%d)") % filename % N);
		throw std::runtime_error(error);
	}

	inp.close();
}

void Initialiser::init_topology_from_filename(std::shared_ptr<SystemProperties> sys_props, std::string filename) {
	std::ifstream inp(filename.c_str());

	if(inp.bad() || !inp.good()) {
		std::string error = boost::str(boost::format("Configuration file '%s' not found") % filename);
		throw std::runtime_error(error);
	}

	std::string line;
	while(std::getline(inp, line)) {
		boost::trim(line);
		// skip empty lines or lines starting with #
		if(line.size() == 0 || boost::starts_with(line, "#")) continue;

		std::vector<std::string> spl_line;
		boost::split(spl_line, line, boost::is_any_of("\t "), boost::token_compress_on);

		if(boost::starts_with("link", spl_line[0])) {
			uint link_type = boost::lexical_cast<uint>(spl_line[1]);
			uint p_idx = boost::lexical_cast<uint>(spl_line[2]);
			uint q_idx = boost::lexical_cast<uint>(spl_line[3]);

			sys_props->add_link(std::shared_ptr<TopologyLink<2>>(new TopologyLink<2>(link_type, {p_idx, q_idx})));
		}
		else {
			std::string error = boost::str(boost::format("The topology file '%s' contains the invalid line '%s'") % filename % line);
			throw std::runtime_error(error);
		}
	}

	inp.close();
}

void Initialiser::set_random_velocities(std::shared_ptr<SystemProperties> sys_props) {
	double rescale_factor = sqrt(sys_props->T());

	for(auto &vel : sys_props->particles()->velocities_writable()) {
		vel(0) = MathUtils::gaussian() * rescale_factor;
		vel(1) = MathUtils::gaussian() * rescale_factor;
		vel(2) = MathUtils::gaussian() * rescale_factor;
	}
}

} /* namespace ashell */

#ifdef ASHELL_PYTHON
#include "defs_to_python.h"

namespace ashell {

void export_initialiser() {
	bpy::class_<Initialiser, std::shared_ptr<Initialiser> >("Initialiser", bpy::no_init)
			.def("make_random", &Initialiser::make_random_configuration_N2).staticmethod("make_random");
}

}
#endif
