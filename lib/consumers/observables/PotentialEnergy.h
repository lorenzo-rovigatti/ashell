/*
 * PotentialEnergy.h
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_CONSUMERS_OBSERVABLES_POTENTIALENERGY_H_
#define LIB_CONSUMERS_OBSERVABLES_POTENTIALENERGY_H_

#include "Observable.h"

namespace ashell {

class PotentialEnergy: public Observable {
public:
	PotentialEnergy();
	virtual ~PotentialEnergy();

	virtual double as_scalar();

protected:
	virtual void _observe(ullint step);

	double _energy;
};

} /* namespace ashell */

#endif /* LIB_CONSUMERS_OBSERVABLES_POTENTIALENERGY_H_ */
