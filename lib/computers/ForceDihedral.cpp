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
				_kb(100.),
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

	for(auto &dihedral : _sys_props->dihedrals()) {
		uint i = dihedral->members[0];
		uint j = dihedral->members[1];
		uint k = dihedral->members[2];
		uint l = dihedral->members[3];

		vec3 i_pos = poss[i];
		vec3 j_pos = poss[j];
		vec3 k_pos = poss[k];
		vec3 l_pos = poss[l];

		// see Sofia Biagi's thesis, pag. 114
		vec3 r_ij = _sys_props->box()->minimum_image(j_pos, i_pos);
		vec3 r_kj = _sys_props->box()->minimum_image(j_pos, k_pos);
		vec3 r_kl = _sys_props->box()->minimum_image(l_pos, k_pos);

		double r_kj_sqr = r_kj.dot(r_kj);
		double r_kj_mod = sqrt(r_kj_sqr);

		vec3 m = r_ij.cross(r_kj);
		vec3 n = r_kj.cross(r_kl);

		double m_sqr = m.dot(m);
		double n_sqr = n.dot(n);

		double costheta = m.dot(n) / (sqrt(m_sqr) * sqrt(n_sqr));
		if(costheta > 1.) costheta = 1.;
		if(costheta < -1.) costheta = -1.;

		double theta = acos(costheta);
		if(r_ij.dot(n) < 0.) theta = -theta;
		// we use the so-called polymer convention, for which theta(polymer) = theta(IUPAC) +/- pi
		theta -= M_PI;

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

//		BOOST_LOG_TRIVIAL(info) << costheta << " " << (theta*180/M_PI) << " " << energy;

		_energy += energy;
		_energies[i] += energy / 4.;
		_energies[j] += energy / 4.;
		_energies[k] += energy / 4.;
		_energies[l] += energy / 4.;
	}
}

} /* namespace ashell */
