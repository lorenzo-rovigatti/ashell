/*
 * FENE.h
 *
 *  Created on: 13 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_POTENTIALS_FENE_H_
#define LIB_COMPUTERS_POTENTIALS_FENE_H_

#include "../../defs.h"
#include "../../Topology.h"

namespace ashell {

class FENE {
public:
	FENE(std::initializer_list<double> params) {
		if(params.size() != 2) {
			throw std::runtime_error(boost::str(boost::format("FENE expects a parameter list of length 2, not %u") % params.size()));
		}
		auto iter = params.begin();
		_U = *iter;
		iter++;
		_rfene_sqr = SQR(*iter);
	}

	virtual ~FENE() {

	}

	bool evaluate(std::shared_ptr<TopologyLink<2>> link, double &energy, double &force_over_r, double r_sqr) {
		if(r_sqr >= _rfene_sqr) {
			throw std::runtime_error(boost::str(boost::format("A distance between particles exceeds the FENE distance (%lf > %lf)") % sqrt(r_sqr) % sqrt(_rfene_sqr)));
		}

		energy = -_U * _rfene_sqr * log(1. - r_sqr / _rfene_sqr);
		force_over_r = -2. * _U * _rfene_sqr / (_rfene_sqr - r_sqr);

		return true;
	}

private:
	double _U;
	double _rfene_sqr;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_POTENTIALS_FENE_H_ */
