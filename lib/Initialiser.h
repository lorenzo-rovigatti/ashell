/*
 * Initialiser.h
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_INITIALISER_H_
#define LIB_INITIALISER_H_

#include "Particles.h"
#include "boxes/Box.h"

#include <memory>

namespace ashell {

class Initialiser {
public:
	virtual ~Initialiser();

	static std::shared_ptr<Particles> make_random_N2(int N, std::shared_ptr<Box> box);

private:
	Initialiser();
};

} /* namespace ashell */

#endif /* LIB_INITIALISER_H_ */
