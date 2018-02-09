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

	std::shared_ptr<Box> box() const {
		return _box;
	}
	std::shared_ptr<Integrator> integrator() const {
		return _integrator;
	}
	std::shared_ptr<Particles> particles() const {
		return _particles;
	}

	double T() {
		return _T;
	}

	void set_T(double nT) {
		_T = nT;
	}

private:
	std::shared_ptr<Box> _box;
	std::shared_ptr<Integrator> _integrator;
	std::shared_ptr<Particles> _particles;

	double _T;
};

} /* namespace ashell */

#endif /* LIB_SYSTEMPROPERTIES_H_ */
