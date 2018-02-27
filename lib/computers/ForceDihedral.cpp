/*
 * ForceDihedral.cpp
 *
 *  Created on: 27 feb 2018
 *      Author: lorenzo
 */

#include "ForceDihedral.h"

#include <Eigen/Dense>

namespace ashell {

ForceDihedral::ForceDihedral(std::string name) :
				ForceComputer(name),
				_kb(50.),
				_theta0(0.) {

}

ForceDihedral::~ForceDihedral() {

}

void ForceDihedral::set_kb(double n_kb) {
	_kb = n_kb;
}

void ForceDihedral::set_theta0(double n_theta0) {
	_theta0 = n_theta0;
}

void ForceDihedral::_compute_forces(ullint step) {
	const vector_vec3 &poss = _particles->positions();
	const auto &dihedrals = _sys_props->dihedrals();

	for(auto &dihedral : dihedrals) {
		uint i = dihedral->members[0];
		uint j = dihedral->members[1];
		uint k = dihedral->members[2];
		uint l = dihedral->members[3];

		vec3 i_pos = poss[i];
		vec3 j_pos = poss[j];
		vec3 l_pos = poss[k];
		vec3 k_pos = poss[l];

		// see Sofia Biagi's thesis, pag. 114
		vec3 r_ij = _sys_props->box()->minimum_image(i_pos, j_pos);
		vec3 r_kj = _sys_props->box()->minimum_image(k_pos, j_pos);
		vec3 r_kl = _sys_props->box()->minimum_image(k_pos, l_pos);

		double r_kj_sqr = r_kj.dot(r_kj);
		double r_kj_mod = sqrt(r_kj_sqr);

		vec3 m = r_ij.cross(r_kj);
		vec3 n = r_kj.cross(r_kl);

		double m_sqr = m.dot(m);
		double n_sqr = n.dot(n);

		double costheta = m.dot(n) / (sqrt(m_sqr) * sqrt(n_sqr));
		if(costheta > 1.) costheta = 1.;
		if(costheta < -1.) costheta = -1.;

		// IUPAC vs polymer conventions
		double theta = acos(costheta) - M_PI;
		if(r_ij.dot(n) < 0.) theta = -theta;

		double dVdtheta = _kb * sin(theta - _theta0);
		vec3 F_i = (-dVdtheta * r_kj_mod / m_sqr) * m;
		vec3 F_l = (dVdtheta * r_kj_mod / n_sqr) * n;

		// We compute Fj and Fk from Fi and Fl by knowing that  F_i + Fj + Fk + Fl == 0
		// and that the dihedral potential energy function is rotationally invariant
		vec3 S = (r_ij.dot(r_kj) / r_kj_sqr) * F_i - (r_kl.dot(r_kj) / r_kj_sqr) * F_l;

		_forces[i] += F_i;
		_forces[j] += -F_i + S;
		_forces[k] += -F_l - S;
		_forces[l] += F_l;

		double energy = _kb * (1. - cos(theta - _theta0));

		_energy += energy;
		_energies[i] += energy / 4.;
		_energies[j] += energy / 4.;
		_energies[k] += energy / 4.;
		_energies[l] += energy / 4.;
	}
}

} /* namespace ashell */
