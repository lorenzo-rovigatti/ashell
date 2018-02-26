/*
 * ThermostatFactory.cpp
 *
 *  Created on: 26 feb 2018
 *      Author: lorenzo
 */

#include "ThermostatFactory.h"

#include "Andersen.h"
#include "../../utils/InputFile.h"

namespace ashell {

ThermostatFactory::~ThermostatFactory() {

}

std::shared_ptr<Updater> ThermostatFactory::make_thermostat(std::string thermostat_name, InputFile &input) {
	std::shared_ptr<Updater> new_thermostat;

	if(thermostat_name == "andersen") {
		double dt;
		input.value_as_number("dt", dt, 1);
		uint newtonian_steps;
		input.value_as_uint("newtonian_steps", newtonian_steps, 1);
		double D0;
		input.value_as_number("bare_diffusion_coefficient", D0, 1);

		double newtonian_time = dt * newtonian_steps;
		new_thermostat = std::shared_ptr<Updater>(new Andersen(newtonian_time, D0));
	}
	else {
		std::string error = boost::str(boost::format("Invalid thermostat '%s'") % thermostat_name);
		throw std::runtime_error(error);
	}

	return new_thermostat;
}

} /* namespace ashell */
