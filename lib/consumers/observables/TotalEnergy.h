/*
 * TotalEnergy.h
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_CONSUMERS_OBSERVABLES_TOTALENERGY_H_
#define LIB_CONSUMERS_OBSERVABLES_TOTALENERGY_H_

#include "Observable.h"
#include "PotentialEnergy.h"
#include "KineticEnergy.h"

namespace ashell {

class TotalEnergy: public Observable {
public:
	TotalEnergy();
	virtual ~TotalEnergy();

	virtual std::string as_string();

protected:
	virtual void _observe(ullint step);

	std::shared_ptr<PotentialEnergy> _potential_obs;
	std::shared_ptr<KineticEnergy> _kinetic_obs;
};

} /* namespace ashell */

#endif /* LIB_CONSUMERS_OBSERVABLES_TOTALENERGY_H_ */
