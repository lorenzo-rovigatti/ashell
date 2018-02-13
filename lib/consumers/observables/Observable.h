/*
 * Observable.h
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_CONSUMERS_OBSERVABLES_OBSERVABLE_H_
#define LIB_CONSUMERS_OBSERVABLES_OBSERVABLE_H_

#include "../Consumer.h"

namespace ashell {

class Observable : public Consumer {
public:
	Observable(std::string n_name="consumer");
	virtual ~Observable();

	virtual void consume(ullint step);
	virtual double as_scalar();
	virtual std::string as_string();

protected:
	virtual void _observe(ullint step);

	ullint _last_step;
};

} /* namespace ashell */

#endif /* LIB_CONSUMERS_OBSERVABLES_OBSERVABLE_H_ */
