/*
 * Integrator.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "Integrator.h"

#include <boost/log/trivial.hpp>

namespace ashell {

Integrator::Integrator(std::shared_ptr<SystemProperties> sys_props) :
				_sys_props(sys_props) {

}

Integrator::~Integrator() {

}

void Integrator::step() {
	BOOST_LOG_TRIVIAL(info) << "Performing a step";
}

} /* namespace ashell */
