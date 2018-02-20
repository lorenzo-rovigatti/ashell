/*
 * KineticEnergy.h
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_OBSERVABLES_KINETICENERGY_H_
#define LIB_COMPUTERS_OBSERVABLES_KINETICENERGY_H_

#include "../../computers/observables/Observable.h"

namespace ashell {

class KineticEnergy: public Observable {
public:
	KineticEnergy();
	virtual ~KineticEnergy();

	virtual double as_scalar();

protected:
	virtual void _observe(ullint step);

	double _kinetic_energy;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_KINETICENERGY_H_ */
