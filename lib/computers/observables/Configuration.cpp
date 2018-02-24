/*
 * Configuration.cpp
 *
 *  Created on: 20 Feb 2018
 *      Author: lorenzo
 */

#include "Configuration.h"

#include <iostream>
#include <sstream>

namespace ashell {

using std::endl;

Configuration::Configuration(std::string n_name) :
				Observable(n_name) {

}

Configuration::~Configuration() {

}

std::string Configuration::as_string() {
	return _configuration;
}

void Configuration::_observe(ullint step) {
	std::stringstream ss;

	ss << step << endl;
	ss << _particles->N() << endl;
	ss << _sys_props->box()->as_string();

	auto poss = _particles->positions();
	auto vels = _particles->velocities();
	for(uint i = 0; i < _particles->N(); i++) {
		auto line = boost::format("%lf %lf %lf %lf %lf %lf") % poss[i][0] % poss[i][1] % poss[i][2] % vels[i][0] % vels[i][1] % vels[i][2];
		ss << endl << line;
	}

	_configuration = ss.str();
}

} /* namespace ashell */
