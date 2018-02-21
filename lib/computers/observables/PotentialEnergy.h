/*
 * PotentialEnergy.h
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_OBSERVABLES_POTENTIALENERGY_H_
#define LIB_COMPUTERS_OBSERVABLES_POTENTIALENERGY_H_

#include "../../computers/observables/Observable.h"

namespace ashell {

class PotentialEnergy: public Observable {
public:
	PotentialEnergy();
	virtual ~PotentialEnergy();

	double as_scalar() override;

protected:
	void _observe(ullint step) override;

	double _energy;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_POTENTIALENERGY_H_ */
