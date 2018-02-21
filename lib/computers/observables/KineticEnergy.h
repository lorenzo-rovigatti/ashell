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

	double as_scalar() override;

protected:
	void _observe(ullint step) override;

	double _kinetic_energy;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_KINETICENERGY_H_ */
