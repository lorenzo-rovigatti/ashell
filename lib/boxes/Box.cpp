/*
 * Box.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "Box.h"

#include "../defs_to_python.h"

namespace ashell {

Box::Box() {

}

Box::~Box() {

}

void Box::register_to_box_changes(BoxCallbackSlot slot) {
	_changed_signal.connect(slot);
}

vec3 Box::random_point_in_box() {
	throw std::runtime_error("Box::random_point_in_box() should never be called");
	return vec3();
}

vec3 Box::minimum_image(const vec3 &p, const vec3 &q) {
	throw std::runtime_error("Box::minimum_image(vec3, vec3) should never be called");
	return vec3();
}

void export_box() {
	bpy::class_<Box, std::shared_ptr<Box>, boost::noncopyable>("Box")
				.def("random_point_in_box", &Box::random_point_in_box);
}

} /* namespace ashell */
