/*
 * ForceBond.h
 *
 *  Created on: 13 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_FORCEBOND_H_
#define LIB_COMPUTERS_FORCEBOND_H_

#include "../computers/ForceComputer.h"

namespace ashell {

template<class potential>
class ForceBond: public ForceComputer {
public:
	ForceBond(std::initializer_list<double> params, std::string name="force_link");
	virtual ~ForceBond();

protected:
	void _compute_forces(ullint step) override;

	potential _potential;
};

} /* namespace ashell */

#include "../computers/potentials/FENE.h"
template class ashell::ForceBond<ashell::FENE>;
using FENEForce = ashell::ForceBond<ashell::FENE>;

#include "../computers/potentials/Harmonic.h"
template class ashell::ForceBond<ashell::Harmonic>;
using HarmonicForce = ashell::ForceBond<ashell::Harmonic>;

#include "../computers/potentials/StressFreeBond.h"
template class ashell::ForceBond<ashell::StressFreeBond>;
using StressFreeBondForce = ashell::ForceBond<ashell::StressFreeBond>;

#endif /* LIB_COMPUTERS_FORCEBOND_H_ */
