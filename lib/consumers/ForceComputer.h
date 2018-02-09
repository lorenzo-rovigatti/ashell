/*
 * ForceComputer.h
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_CONSUMERS_FORCECOMPUTER_H_
#define LIB_CONSUMERS_FORCECOMPUTER_H_

#include "Consumer.h"

namespace ashell {

class ForceComputer: public Consumer {
public:
	ForceComputer();
	virtual ~ForceComputer();

	double energy() {
		return _energy;
	}

	const vector_vec3 &forces() const {
		return _forces;
	}

protected:
	double _energy;
	vector_scalar _energies;
	vector_vec3 _forces;
};

} /* namespace ashell */

#endif /* LIB_CONSUMERS_FORCECOMPUTER_H_ */
