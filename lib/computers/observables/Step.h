/*
 * Step.h
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_OBSERVABLES_STEP_H_
#define LIB_COMPUTERS_OBSERVABLES_STEP_H_

#include "../../computers/observables/Observable.h"

namespace ashell {

class Step: public Observable {
public:
	Step();
	virtual ~Step();

	std::string as_string() override;

protected:
	void _observe(ullint step) override;

	ullint _curr_step;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_STEP_H_ */
