/*
 * Harmonic.h
 *
 *  Created on: 13 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_POTENTIALS_HARMONIC_H_
#define LIB_COMPUTERS_POTENTIALS_HARMONIC_H_

#include "../../defs.h"
#include "../../Topology.h"

namespace ashell {

class Harmonic {
public:
	Harmonic(std::initializer_list<double> params) {
		if(params.size() != 2) {
			throw std::runtime_error(boost::str(boost::format("Harmonic expects a parameter list of length 2, not %u") % params.size()));
		}
		auto iter = params.begin();
		_k = *iter;
		iter++;
		_r0 = *iter;
	}

	virtual ~Harmonic() {

	}

	bool evaluate(std::shared_ptr<TopologyLink<2>> link, double &energy, double &force_over_r, double r_sqr) {
		double r0 = _r0;
		if(link->N_params() > 0) {
			r0 = link->params[0];
		}

		double r_mod = sqrt(r_sqr);
		double delta_r = r_mod - r0;

		energy = 0.5 * _k * SQR(delta_r);
		force_over_r = -_k * delta_r / r_mod;

		return true;
	}

private:
	double _k;
	double _r0;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_POTENTIALS_HARMONIC_H_ */
