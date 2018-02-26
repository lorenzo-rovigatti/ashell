/*
 * ThermostatFactory.h
 *
 *  Created on: 26 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_UPDATERS_THERMOSTATS_THERMOSTATFACTORY_H_
#define LIB_UPDATERS_THERMOSTATS_THERMOSTATFACTORY_H_

#include "../Updater.h"

namespace ashell {

class InputFile;

class ThermostatFactory {
public:
	ThermostatFactory() = delete;
	virtual ~ThermostatFactory();

	static std::shared_ptr<Updater> make_thermostat(std::string thermostat_name, InputFile &input);
};

} /* namespace ashell */

#endif /* LIB_UPDATERS_THERMOSTATS_THERMOSTATFACTORY_H_ */
