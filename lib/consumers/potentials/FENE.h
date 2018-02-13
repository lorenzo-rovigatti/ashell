/*
 * FENE.h
 *
 *  Created on: 13 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_CONSUMERS_POTENTIALS_FENE_H_
#define LIB_CONSUMERS_POTENTIALS_FENE_H_

#include "../../defs.h"

#include <boost/format.hpp>

namespace ashell {

class FENE {
public:
	FENE(std::initializer_list<double> params) {
		_rfene_sqr = SQR(1.5);
	}

	virtual ~FENE() {

	}

	bool evaluate(double &energy, double &force_over_r, double r_sqr) {
		if(r_sqr >= _rfene_sqr) {
			throw std::runtime_error(boost::str(boost::format("A distance between particles exceeds the FENE distance (%lf > %lf)") % sqrt(r_sqr) % sqrt(_rfene_sqr)));
		}

		energy = -15 * _rfene_sqr * log(1. - r_sqr / _rfene_sqr);
		force_over_r = -30 * _rfene_sqr / (_rfene_sqr - r_sqr);

		return true;
	}

private:
	double _rfene_sqr;
};

} /* namespace ashell */

#endif /* LIB_CONSUMERS_POTENTIALS_FENE_H_ */
