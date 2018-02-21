/*
 * Configuration.h
 *
 *  Created on: 20 Feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_OBSERVABLES_CONFIGURATION_H_
#define LIB_COMPUTERS_OBSERVABLES_CONFIGURATION_H_

#include "Observable.h"

namespace ashell {

class Configuration: public Observable {
public:
	Configuration(std::string n_name="observable");
	virtual ~Configuration();

	std::string as_string() override;

protected:
	void _observe(ullint step) override;

	std::string _configuration;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_CONFIGURATION_H_ */
