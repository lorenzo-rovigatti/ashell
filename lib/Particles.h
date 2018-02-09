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
	Particles(int N, const vector_vec3 &poss);
	Particles(int N, const vector_vec3 &poss, const vector_vec3 &vels);
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
	vector_vec3 &positions_writable() {
		return _poss;
	}

	const vector_vec3 &velocities() const {
		return _vels;
	}

	vector_vec3 &velocities_writable() {
		return _vels;
	}

private:
	int _N;
	vector_vec3 _poss;
	vector_vec3 _vels;
};

} /* namespace ashell */

#endif /* LIB_PARTICLES_H_ */
