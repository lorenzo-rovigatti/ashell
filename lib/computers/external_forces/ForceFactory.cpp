/*
 * ForceFactory.cpp
 *
 *  Created on: 02 mar 2018
 *      Author: lorenzo
 */

#include "ForceFactory.h"

#include "ConstantForce.h"
#include "../../utils/InputFile.h"

namespace ashell {

ForceFactory::~ForceFactory() {

}

std::shared_ptr<ExternalForce> ForceFactory::make_force(InputFile &inp) {
	std::shared_ptr<ExternalForce> force;

	std::vector<int> particles;
	inp.value_as_int_vector("particles", particles, 1);

	std::string type;
	inp.value_as_string("type", type, 1);
	if(type == "constant") {
		double F0;
		inp.value_as_number("F0", F0, 1);
		vec3 direction;
		inp.value_as_vec3("direction", direction, 1);
		force = std::shared_ptr<ExternalForce>(new ConstantForce(direction, F0, particles));

		std::string msg = boost::str(boost::format("Adding a ConstantForce with F0 = %lf along (%lf, %lf, %lf)") % F0 % direction(0) % direction(1) % direction(2));
		BOOST_LOG_TRIVIAL(info) << msg;
	}
	else {
		std::string error = boost::str(boost::format("Unknown force type '%s'") % type);
		throw std::runtime_error(error);
	}

	return force;
}

} /* namespace ashell */
