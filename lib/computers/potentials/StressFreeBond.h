/*
 * StressFreeBond.h
 *
 *  Created on: 03 jan 2019
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_POTENTIALS_STRESSFREEBOND_H_
#define LIB_COMPUTERS_POTENTIALS_STRESSFREEBOND_H_

#include "../../defs.h"
#include "../../Topology.h"

namespace ashell {

/**
 * This two-body bonded interaction is a sum of a FENE + a 1/r interaction parametrised so that different bonds can have different equilibrium lengths.
 *
 * See Sofia Biagi's PhD thesis, pagg. 40 and 44. Note that in pag. 40 there is a minus sign in front of k_p/r_ij which should not be there.
 */
class StressFreeBond {
public:
	StressFreeBond(std::initializer_list<double> params) {
		if(params.size() != 2) {
			throw std::runtime_error(boost::str(boost::format("StressFreeBond expects a parameter list of length 2, not %u") % params.size()));
		}
		auto iter = params.begin();
		_U = *iter;
		iter++;
		_maximum_length_ratio = *iter;
	}

	virtual ~StressFreeBond() {

	}

	bool evaluate(std::shared_ptr<TopologyLink<2>> bond, double &energy, double &force_over_r, double r_sqr) {
		if(bond->params.size() < 1) {
			throw std::runtime_error(boost::str(boost::format("The bond between particles '%d' and '%d' does not have an associated equilibrium length") % bond->members[0] % bond->members[1]));
		}

		// FENE part
		double eq_length = bond->params[0];
		double eq_length_sqr = SQR(eq_length);
		double maximum_length_sqr = SQR(_maximum_length_ratio * eq_length);

		if(r_sqr >= maximum_length_sqr) {
			throw std::runtime_error(boost::str(boost::format("StressFreeBond: the distance between particles '%s' and '%s' exceeds the maximum distance (%lf > %lf)") % bond->members[0] % bond->members[1] % sqrt(r_sqr) % sqrt(maximum_length_sqr)));
		}

		energy = -_U * maximum_length_sqr * log((maximum_length_sqr - r_sqr) / (maximum_length_sqr - eq_length_sqr));
		force_over_r = -2. * _U * maximum_length_sqr / (maximum_length_sqr - r_sqr);

		// 1/r part
		double r = sqrt(r_sqr);
		double kp = 2. * _U * eq_length * eq_length_sqr * maximum_length_sqr / (maximum_length_sqr - eq_length_sqr);
		energy += kp / r - kp / eq_length;
		force_over_r += kp / (r * r_sqr);

		return true;
	}

private:
	double _U;
	double _maximum_length_ratio;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_POTENTIALS_FENE_H_ */
