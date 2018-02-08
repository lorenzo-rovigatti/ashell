/*
 * Particles.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_PARTICLES_H_
#define LIB_PARTICLES_H_

#include "math_defs.h"

#include <vector>

namespace ashell {

class Particles {
public:
	Particles(int N);
	virtual ~Particles();

	int N() const {
		return _N;
	}

	void set_N(int nN) {
		_N = nN;
	}


private:
	int _N;
	vector_vec3 _poss;
	vector_vec3 _vels;
};

} /* namespace ashell */

#endif /* LIB_PARTICLES_H_ */
