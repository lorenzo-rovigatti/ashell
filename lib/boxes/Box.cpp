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

// this is needed to expose a virtual class
class BoxWrap: public Box, public boost::python::wrapper<Box> {
	vec3 random_point_in_box() {
		return this->get_override("random_point_in_box")();
	}
};

void export_box() {
	boost::python::class_<BoxWrap, boost::noncopyable>("Box")
			.def("random_point_in_box", boost::python::pure_virtual(&Box::random_point_in_box));
}

} /* namespace ashell */
