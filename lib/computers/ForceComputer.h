/*
 * ForceComputer.h
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_FORCECOMPUTER_H_
#define LIB_COMPUTERS_FORCECOMPUTER_H_

#include "../computers/Computer.h"

namespace ashell {

class ForceComputer: public Computer {
public:
	ForceComputer(std::string name="force_computer");
	virtual ~ForceComputer();

	virtual void consume(ullint step);

	double energy() {
		return _energy;
	}

	const vector_vec3 &forces() const {
		return _forces;
	}

protected:
	virtual void _compute_forces(ullint step);

	double _energy;
	vector_scalar _energies;
	vector_vec3 _forces;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_FORCECOMPUTER_H_ */
