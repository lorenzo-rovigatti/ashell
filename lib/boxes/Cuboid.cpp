/*
 * Cuboid.cpp
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#include "Cuboid.h"

#include "../defs_to_python.h"

#include <Eigen/Eigen>

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
	return _box.array() * ((vec3::Random() + vec3(1., 1., 1.)) * 0.5).array();
}

vec3 Cuboid::minimum_image(const vec3 &p, const vec3 &q) {
	vec3 diff = q - p;
	return diff - ((diff.array() / _box.array()).round() * _box.array()).matrix();
}

void export_cuboid() {
	// Cuboid inherits from a noncopyable parent (Box), which means it is non-copyable itself
	bpy::class_<Cuboid, std::shared_ptr<Cuboid>, bpy::bases<Box>, boost::noncopyable>("Cuboid", bpy::init<double>())
			.def(bpy::init<double, double, double>());
}

} /* namespace ashell */
