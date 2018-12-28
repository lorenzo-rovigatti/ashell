/*
 * ObservableFactory.h
 *
 *  Created on: 22 Mar 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_OBSERVABLES_OBSERVABLEFACTORY_H_
#define LIB_COMPUTERS_OBSERVABLES_OBSERVABLEFACTORY_H_

#include "Observable.h"

namespace ashell {

class InputFile;

class ObservableFactory {
public:
	virtual ~ObservableFactory();

	static std::shared_ptr<Observable> make_observable(InputFile &inp);

private:
	ObservableFactory();
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_OBSERVABLEFACTORY_H_ */
