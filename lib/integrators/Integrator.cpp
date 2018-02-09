/*
 * Integrator.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "Integrator.h"

#include <boost/log/trivial.hpp>
#include <boost/python.hpp>

namespace ashell {

Integrator::Integrator() {

}

Integrator::~Integrator() {

}

void Integrator::step(ullint step) {
	throw std::runtime_error("Integrator::step() should never be called");
}

using namespace boost::python;
void export_integrator() {
	class_<Integrator, std::shared_ptr<Integrator> >("Integrator");
}

} /* namespace ashell */
