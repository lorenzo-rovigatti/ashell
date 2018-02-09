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
	void set_box(std::shared_ptr<Box> n_box) {
		_box = n_box;
	}

	std::shared_ptr<Integrator> integrator() const {
		return _integrator;
	}
	void set_integrator(std::shared_ptr<Integrator> n_integrator) {
		_integrator = n_integrator;
	}

	std::shared_ptr<Particles> particles() const {
		return _particles;
	}

	void set_particles(std::shared_ptr<Particles> n_particles) {
		_particles = n_particles;
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
