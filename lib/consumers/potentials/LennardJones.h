/*
 * LennardJones.h
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_CONSUMERS_POTENTIALS_LENNARDJONES_H_
#define LIB_CONSUMERS_POTENTIALS_LENNARDJONES_H_

#include "../../defs.h"

namespace ashell {

class LennardJones {
public:
	LennardJones(double rcut) : _rcut_sqr(SQR(rcut)) {

	}
	virtual ~LennardJones() {

	}

	bool evaluate(double &energy, double &force_over_r, double r_sqr) {
		if(r_sqr >= _rcut_sqr) {
			return false;
		}

		double inv_r_sqr = 1. / r_sqr;
		double part = CUB(inv_r_sqr);
		energy = 4. * (SQR(part) - part);
		force_over_r = -24. * (part - 2. * SQR(part)) / r_sqr;

		return true;
	}

private:
	double _rcut_sqr;
};

} /* namespace ashell */

#endif /* LIB_CONSUMERS_POTENTIALS_LENNARDJONES_H_ */
