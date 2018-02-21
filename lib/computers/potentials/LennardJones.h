/*
 * LennardJones.h
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_POTENTIALS_LENNARDJONES_H_
#define LIB_COMPUTERS_POTENTIALS_LENNARDJONES_H_

#include "../../defs.h"

namespace ashell {

class LennardJones {
public:
	LennardJones(std::initializer_list<double> params) {
		if(params.size() != 1) {
			throw std::runtime_error(boost::str(boost::format("LennardJones expects a parameter list of length 1, not %u") % params.size()));
		}
		_rcut_sqr = SQR(*params.begin());
		double inv_rcut_sqr = 1. / _rcut_sqr;
		double part = CUB(inv_rcut_sqr);
		_E_cut = 4. * (SQR(part) - part);
	}

	virtual ~LennardJones() {

	}

	bool evaluate(double &energy, double &force_over_r, double r_sqr) {
		if(r_sqr >= _rcut_sqr) {
			return false;
		}

		double inv_r_sqr = 1. / r_sqr;
		double part = CUB(inv_r_sqr);
		energy = 4. * (SQR(part) - part) - _E_cut;
		force_over_r = -24. * (part - 2. * SQR(part)) / r_sqr;

		return true;
	}

private:
	double _rcut_sqr;
	double _E_cut;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_POTENTIALS_LENNARDJONES_H_ */
