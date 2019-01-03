/*
 * ForceComputerFactory.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: lorenzo
 */

#include "ForceComputerFactory.h"

#include "../utils/InputFile.h"

#include "ForceLink.h"
#include "ForceDihedral.h"
#include "ForceTriangulatedMesh.h"
#include "ForceTwoBodyIsotropic.h"

namespace ashell {

ForceComputerFactory::~ForceComputerFactory() {

}

std::shared_ptr<ForceComputer> ForceComputerFactory::make_potential(InputFile &inp) {
	std::shared_ptr<ForceComputer> potential;

	std::string type;
	inp.value_as_string("type", type, 1);
	if(type == "harmonic_force") {
		double k, r0;
		inp.value_as_number("k", k, 1);
		inp.value_as_number("r0", r0, 1);
		potential = std::shared_ptr<HarmonicForce>(new HarmonicForce( {k, r0} ));
	}
	else if(type == "FENE_force") {
		double U, r0;
		inp.value_as_number("U", U, 1);
		inp.value_as_number("r0", r0, 1);
		potential = std::shared_ptr<FENEForce>(new FENEForce( {U, r0} ));
	}
	else if(type == "stress_free_bond_force") {
		double U, x0;
		inp.value_as_number("U", U, 1);
		inp.value_as_number("x0", x0, 1);
		potential = std::shared_ptr<StressFreeBondForce>(new StressFreeBondForce( {U, x0} ));
	}
	else if(type == "lennard_jones_force") {
		double rc;
		inp.value_as_number("rc", rc, 1);
		double sigma = 1.;
		inp.value_as_number("sigma", sigma, 0);
		potential = std::shared_ptr<LennardJonesForce>(new LennardJonesForce( {rc, sigma} ));
	}
	else if(type == "force_triangulated_mesh") {
		double kv, ka;
		inp.value_as_number("kv", kv, 1);
		inp.value_as_number("ka", ka, 1);
		auto mesh = std::shared_ptr<ForceTriangulatedMesh>(new ForceTriangulatedMesh());
		mesh->set_kv(kv);
		mesh->set_ka(ka);

		bool V0_from_conf = false;
		inp.value_as_bool("V0_from_conf", V0_from_conf, 0);
		if(V0_from_conf) {
			mesh->set_V0_from_conf();
		}
		else {
			double V0;
			inp.value_as_number("V0", V0, 1);
			mesh->set_V0(V0);
		}

		bool A0_from_conf = false;
		inp.value_as_bool("A0_from_conf", A0_from_conf, 0);
		if(A0_from_conf) {
			mesh->set_A0_from_conf();
		}
		else {
			double A0;
			inp.value_as_number("A0", A0, 1);
			mesh->set_A0(A0);
		}

		potential = mesh;
	}
	else if(type == "force_dihedral") {
		double kb, theta0;
		inp.value_as_number("kb", kb, 1);
		inp.value_as_number("theta0", theta0, 1);
		auto dihedral = std::shared_ptr<ForceDihedral>(new ForceDihedral());
		dihedral->set_kb(kb);
		dihedral->set_theta0(theta0);
		potential = dihedral;
	}
	else {
		std::string error = boost::str(boost::format("Unknown potential type '%s'") % type);
		throw std::runtime_error(error);
	}

	return potential;
}

} /* namespace ashell */
