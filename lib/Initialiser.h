/*
 * Initialiser.h
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_INITIALISER_H_
#define LIB_INITIALISER_H_

#include "Particles.h"

#include <memory>

namespace ashell {

class SystemProperties;

class Initialiser {
public:
	Initialiser() = delete;
	virtual ~Initialiser();

	static void make_random_N2(std::shared_ptr<SystemProperties> sys_props);
	static void make_random(std::shared_ptr<SystemProperties> sys_props);
};

} /* namespace ashell */

#endif /* LIB_INITIALISER_H_ */
