/*
 * Cuboid.cpp
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#include "Cuboid.h"

#include <boost/python.hpp>

namespace ashell {

Cuboid::Cuboid(double L) :
				Box(),
				_box(L, L, L) {

}

Cuboid::Cuboid(double Lx, double Ly, double Lz) :
				Box(),
				_box(Lx, Ly, Lz) {

}

Cuboid::~Cuboid() {

}

using namespace boost::python;
void export_cuboid() {
	// Cuboid inherits from a noncopyable parent (Box) and hence we have to
	// tell it to class_
	class_<Cuboid, bases<Box>, boost::noncopyable>("Cuboid", init<double>())
			.def(init<double, double, double>());
}

} /* namespace ashell */
