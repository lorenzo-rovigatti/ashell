/*
 * ForceTwoBody.h
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_FORCETWOBODYISOTROPIC_H_
#define LIB_COMPUTERS_FORCETWOBODYISOTROPIC_H_

#include "../computers/ForceComputer.h"

namespace ashell {

template<class potential>
class ForceTwoBodyIsotropic: public ForceComputer {
public:
	ForceTwoBodyIsotropic(std::string name="force_two_body_isotropic");
	virtual ~ForceTwoBodyIsotropic();

private:
	void _compute_forces(ullint step) override;

	potential _potential;
};

} /* namespace ashell */

#include "../computers/potentials/LennardJones.h"
template class ashell::ForceTwoBodyIsotropic<ashell::LennardJones>;
using LennardJonesForce = ashell::ForceTwoBodyIsotropic<ashell::LennardJones>;

#endif /* LIB_COMPUTERS_FORCETWOBODYISOTROPIC_H_ */
