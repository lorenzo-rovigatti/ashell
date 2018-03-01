/*
 * ExternalForce.h
 *
 *  Created on: 1 Mar 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_EXTERNAL_FORCES_EXTERNALFORCE_H_
#define LIB_COMPUTERS_EXTERNAL_FORCES_EXTERNALFORCE_H_

#include "../ForceComputer.h"

namespace ashell {

class ExternalForce: public ForceComputer {
public:
	ExternalForce(std::vector<int> target_particles, std::string name="force_computer");
	virtual ~ExternalForce();

protected:
	void _compute_forces(ullint step) override;
	virtual void _compute_force_on_particle(ullint step, uint idx);

	std::vector<int> _target_particles;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_EXTERNAL_FORCES_EXTERNALFORCE_H_ */
