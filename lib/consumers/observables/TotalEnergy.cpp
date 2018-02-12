/*
 * TotalEnergy.cpp
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#include "TotalEnergy.h"

#include <boost/format.hpp>

namespace ashell {

TotalEnergy::TotalEnergy() {
	_potential_obs = std::shared_ptr<PotentialEnergy>(new PotentialEnergy());
	_kinetic_obs = std::shared_ptr<KineticEnergy>(new KineticEnergy());
}

TotalEnergy::~TotalEnergy() {

}

std::string TotalEnergy::as_string() {
	double pot_energy = _potential_obs->as_scalar();
	double kin_energy = _kinetic_obs->as_scalar();
	double tot_energy = pot_energy + kin_energy;

	return boost::str(boost::format("%lf %lf %lf") % pot_energy % kin_energy % tot_energy);
}

void TotalEnergy::_observe(ullint step) {
	_potential_obs->consume(step);
	_kinetic_obs->consume(step);
}

} /* namespace ashell */
