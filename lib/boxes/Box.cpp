/*
 * Box.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "Box.h"

#include <boost/python.hpp>

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

void export_box() {
	boost::python::class_<Box, std::shared_ptr<Box>, boost::noncopyable>("Box")
				.def("random_point_in_box", boost::python::pure_virtual(&Box::random_point_in_box));
}

} /* namespace ashell */
