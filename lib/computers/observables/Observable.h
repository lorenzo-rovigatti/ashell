/*
 * Observable.h
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_OBSERVABLES_OBSERVABLE_H_
#define LIB_COMPUTERS_OBSERVABLES_OBSERVABLE_H_

#include "../../computers/Computer.h"

namespace ashell {

class InputFile;

class Observable : public Computer {
public:
	Observable(std::string n_name="observable");
	virtual ~Observable();

	void parse_input(InputFile &inp);

	void compute(ullint step) override;
	virtual double as_scalar();
	virtual std::string as_string();

protected:
	virtual void _observe(ullint step);

	ullint _last_step;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_OBSERVABLE_H_ */
