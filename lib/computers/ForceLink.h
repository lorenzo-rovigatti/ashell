/*
 * ForceLink.h
 *
 *  Created on: 13 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_FORCELINK_H_
#define LIB_COMPUTERS_FORCELINK_H_

#include "../computers/ForceComputer.h"

namespace ashell {

template<class potential>
class ForceLink: public ForceComputer {
public:
	ForceLink(std::initializer_list<double> params, std::string name="force_link");
	virtual ~ForceLink();

protected:
	void _compute_forces(ullint step) override;

	potential _potential;
};

} /* namespace ashell */

#include "../computers/potentials/FENE.h"
template class ashell::ForceLink<ashell::FENE>;
using FENEForce = ashell::ForceLink<ashell::FENE>;

#include "../computers/potentials/Harmonic.h"
template class ashell::ForceLink<ashell::Harmonic>;
using HarmonicForce = ashell::ForceLink<ashell::Harmonic>;

#include "../computers/potentials/StressFreeBond.h"
template class ashell::ForceLink<ashell::StressFreeBond>;
using StressFreeBondForce = ashell::ForceLink<ashell::StressFreeBond>;

#endif /* LIB_COMPUTERS_FORCELINK_H_ */
