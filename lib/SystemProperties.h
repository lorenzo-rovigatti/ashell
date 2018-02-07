/*
 * SystemProperties.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_SYSTEMPROPERTIES_H_
#define LIB_SYSTEMPROPERTIES_H_

#include <memory>

namespace ashell {

class Box;
class Integrator;
class Particles;

class SystemProperties {
public:
	SystemProperties();
	virtual ~SystemProperties();

	std::shared_ptr<Box> box;
	std::shared_ptr<Integrator> integrator;
	std::shared_ptr<Particles> particles;
};

} /* namespace ashell */

#endif /* LIB_SYSTEMPROPERTIES_H_ */
