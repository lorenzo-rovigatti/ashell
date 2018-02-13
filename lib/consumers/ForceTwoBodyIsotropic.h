/*
 * ForceTwoBody.h
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_CONSUMERS_FORCETWOBODYISOTROPIC_H_
#define LIB_CONSUMERS_FORCETWOBODYISOTROPIC_H_

#include "ForceComputer.h"

namespace ashell {

template<class potential>
class ForceTwoBodyIsotropic: public ForceComputer {
public:
	ForceTwoBodyIsotropic(std::string name="force_two_body_isotropic");
	virtual ~ForceTwoBodyIsotropic();

private:
	virtual void _compute_forces(ullint step);

	potential _potential;
};

} /* namespace ashell */

#include "potentials/LennardJones.h"
template class ashell::ForceTwoBodyIsotropic<ashell::LennardJones>;
using LennardJonesForce = ashell::ForceTwoBodyIsotropic<ashell::LennardJones>;

#endif /* LIB_CONSUMERS_FORCETWOBODYISOTROPIC_H_ */
