/*
 * TotalEnergy.h
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_OBSERVABLES_TOTALENERGY_H_
#define LIB_COMPUTERS_OBSERVABLES_TOTALENERGY_H_

#include "../../computers/observables/KineticEnergy.h"
#include "../../computers/observables/Observable.h"
#include "../../computers/observables/PotentialEnergy.h"

namespace ashell {

class TotalEnergy: public Observable {
public:
	TotalEnergy();
	virtual ~TotalEnergy();

	std::string as_string() override;

protected:
	void _observe(ullint step) override;

	std::shared_ptr<PotentialEnergy> _potential_obs;
	std::shared_ptr<KineticEnergy> _kinetic_obs;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_TOTALENERGY_H_ */
