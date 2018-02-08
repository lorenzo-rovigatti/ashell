/*
 * VelocityVerlet.cpp
 *
 *  Created on: 8 Feb 2018
 *      Author: lorenzo
 */

#include "VelocityVerlet.h"

#include <iostream>
#include <boost/python.hpp>

namespace ashell {

VelocityVerlet::VelocityVerlet(double dt) :
				Integrator(),
				_dt(dt) {

}

VelocityVerlet::~VelocityVerlet() {

}

void VelocityVerlet::step() {
	std::cout << "Step" << std::endl;
}

using namespace boost::python;
void export_velocity_verlet() {
	class_<VelocityVerlet, std::shared_ptr<VelocityVerlet>, bases<Integrator>, boost::noncopyable>("VelocityVerlet", init<double>());
}

} /* namespace ashell */
