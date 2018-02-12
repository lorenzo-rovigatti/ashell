/*
 * Step.h
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_CONSUMERS_OBSERVABLES_STEP_H_
#define LIB_CONSUMERS_OBSERVABLES_STEP_H_

#include "Observable.h"

namespace ashell {

class Step: public Observable {
public:
	Step();
	virtual ~Step();

	virtual std::string as_string();

protected:
	virtual void _observe(ullint step);

	ullint _curr_step;
};

} /* namespace ashell */

#endif /* LIB_CONSUMERS_OBSERVABLES_STEP_H_ */
