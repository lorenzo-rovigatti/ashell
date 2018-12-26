/*
 * StrainInvariants.h
 *
 *  Created on: Dec 23, 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_OBSERVABLES_STRAININVARIANTS_H_
#define LIB_COMPUTERS_OBSERVABLES_STRAININVARIANTS_H_

#include "Observable.h"

namespace ashell {

class StrainInvariants: public Observable {
public:
	StrainInvariants(std::string n_name="StrainInvariants");
	virtual ~StrainInvariants();

	std::string as_string() override;

protected:
	void _observe(ullint step) override;

	std::string _line;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_STRAININVARIANTS_H_ */
