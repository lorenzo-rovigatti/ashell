/*
 * ForceTriangle.h
 *
 *  Created on: Dec 29, 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_FORCETRIANGLE_H_
#define LIB_COMPUTERS_FORCETRIANGLE_H_

#include "ForceComputer.h"

namespace ashell {

class ForceTriangle: public ForceComputer {
public:
	ForceTriangle(std::string name="force_dihedral");
	virtual ~ForceTriangle();

	void set_kv(double n_kv);
	void set_V0(double n_V0);

private:
	void _compute_forces(ullint step) override;

	double _kv;
	double _V0;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_FORCETRIANGLE_H_ */
