/*
 * Particles.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_PARTICLES_H_
#define LIB_PARTICLES_H_

#include "defs.h"

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

	const vector_vec3 &positions() const {
		return _poss;
	}

	const vector_vec3 &velocities() const {
		return _vels;
	}

	const vector_vec3 &forces() const {
			return _forces;
		}

private:
	int _N;
	vector_vec3 _poss;
	vector_vec3 _vels;

	vector_vec3 _forces;
};

} /* namespace ashell */

#endif /* LIB_PARTICLES_H_ */
