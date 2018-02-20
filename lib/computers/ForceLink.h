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
	ForceLink(std::string name="force_link");
	virtual ~ForceLink();

protected:
	virtual void _compute_forces(ullint step);

	potential _potential;
};

} /* namespace ashell */

#include "../computers/potentials/FENE.h"
template class ashell::ForceLink<ashell::FENE>;
using FENEForce = ashell::ForceLink<ashell::FENE>;

#endif /* LIB_COMPUTERS_FORCELINK_H_ */
