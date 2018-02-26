/*
 * Cogli1Configuration.h
 *
 *  Created on: 26 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_OBSERVABLES_COGLI1CONFIGURATION_H_
#define LIB_COMPUTERS_OBSERVABLES_COGLI1CONFIGURATION_H_

#include "Observable.h"

namespace ashell {

class Cogli1Configuration: public Observable {
public:
	Cogli1Configuration(std::string n_name="cogli1_configuration");
	virtual ~Cogli1Configuration();

	std::string as_string() override;

protected:
	void _observe(ullint step) override;

	std::string _configuration;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_COGLI1CONFIGURATION_H_ */
