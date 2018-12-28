/*
 * ForceComputerFactory.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: lorenzo
 */

#include "ForceComputerFactory.h"

#include "../utils/InputFile.h"

#include "ForceDihedral.h"
#include "ForceLink.h"
#include "ForceTwoBodyIsotropic.h"

namespace ashell {

ForceComputerFactory::ForceComputerFactory() {

}

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
		double k, r0;
		inp.value_as_number("k", k, 1);
		inp.value_as_number("r0", r0, 1);
		potential = std::shared_ptr<FENEForce>(new FENEForce( {k, r0} ));
	}
	else if(type == "lennard_jones_force") {
		double rc;
		inp.value_as_number("rc", rc, 1);
		potential = std::shared_ptr<LennardJonesForce>(new LennardJonesForce( {rc} ));
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
