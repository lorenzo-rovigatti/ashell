/*
 * ConstantForce.h
 *
 *  Created on: 1 Mar 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_EXTERNAL_FORCES_CONSTANTFORCE_H_
#define LIB_COMPUTERS_EXTERNAL_FORCES_CONSTANTFORCE_H_

#include "ExternalForce.h"

namespace ashell {

class ConstantForce: public ExternalForce {
public:
	ConstantForce(vec3 direction, double F0, std::vector<int> target_particles, std::string name="force_computer");
	virtual ~ConstantForce();

protected:
	virtual void _compute_force_on_particle(ullint step, uint idx) override;

	vec3 _direction;
	double _F0;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_EXTERNAL_FORCES_CONSTANTFORCE_H_ */
