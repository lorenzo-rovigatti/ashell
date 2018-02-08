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

vec3 Cuboid::random_point_in_box() {
	// Random() returns numbers between -1 and 1
	return _box.cwiseProduct(0.5 * (vec3::Random() + vec3(1., 1., 1.)));
}

using namespace boost::python;
void export_cuboid() {
	// Cuboid inherits from a noncopyable parent (Box), which means is non-copyable itself
	class_<Cuboid, std::shared_ptr<Cuboid>, bases<Box>, boost::noncopyable>("Cuboid", init<double>())
			.def(init<double, double, double>());
}

} /* namespace ashell */
