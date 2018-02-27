/*
 * ForceDihedral.h
 *
 *  Created on: 27 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_FORCEDIHEDRAL_H_
#define LIB_COMPUTERS_FORCEDIHEDRAL_H_

#include "ForceComputer.h"

namespace ashell {

class ForceDihedral: public ForceComputer {
public:
	ForceDihedral(std::string name="force_dihedral");
	virtual ~ForceDihedral();

	void set_kb(double n_kb);
	void set_theta0(double n_theta0);

private:
	void _compute_forces(ullint step) override;

	double _kb;
	double _theta0;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_FORCEDIHEDRAL_H_ */
