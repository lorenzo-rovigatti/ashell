/*
 * ForceTriangle.h
 *
 *  Created on: Dec 29, 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_FORCETRIANGULATEDMESH_H_
#define LIB_COMPUTERS_FORCETRIANGULATEDMESH_H_

#include "ForceComputer.h"

namespace ashell {

/**
 * See Sofia Biagi's thesis, pag. 114
 */
class ForceTriangulatedMesh: public ForceComputer {
public:
	ForceTriangulatedMesh(std::string name="force_dihedral");
	virtual ~ForceTriangulatedMesh();

	void set_kv(double n_kv);
	void set_ka(double n_ka);

	void set_V0(double n_V0);
	void set_A0(double n_A0);

	void set_V0_from_conf();
	void set_A0_from_conf();

private:
	void _compute_forces(ullint step) override;

	std::pair<double, double> _get_volume_and_area();

	double _kv;
	double _ka;

	double _V0;
	double _A0;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_FORCETRIANGULATEDMESH_H_ */
