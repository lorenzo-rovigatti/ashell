/*
 * Cogli1Configuration.cpp
 *
 *  Created on: 26 feb 2018
 *      Author: lorenzo
 */

#include "Cogli1Configuration.h"

#include "../../boxes/Cuboid.h"

#include <iostream>
#include <sstream>

namespace ashell {

using std::endl;

Cogli1Configuration::Cogli1Configuration(std::string n_name) :
				Observable(n_name) {

}

Cogli1Configuration::~Cogli1Configuration() {

}

std::string Cogli1Configuration::as_string() {
	return _configuration;
}

void Cogli1Configuration::_observe(ullint step) {
	std::stringstream ss;

	Cuboid *box = dynamic_cast<Cuboid *>(_sys_props->box().get());
	vec3 edges = box->edges();

	ss << ".Box:" << edges(0) << "," << edges(1) << "," << edges(2);

	auto poss = _particles->positions();
	auto vels = _particles->velocities();
	for(uint i = 0; i < _particles->N(); i++) {
		auto line = boost::format("%lf %lf %lf @ 0.5 C[red]") % poss[i][0] % poss[i][1] % poss[i][2];
		ss << endl << line;
	}

	_configuration = ss.str();
}

} /* namespace ashell */
