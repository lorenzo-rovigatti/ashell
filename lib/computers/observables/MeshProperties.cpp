/*
 * MeshProperties.cpp
 *
 *  Created on: 03 gen 2019
 *      Author: lorenzo
 */

#include "MeshProperties.h"

namespace ashell {

MeshProperties::MeshProperties(std::string n_name) {

}

MeshProperties::~MeshProperties() {

}

std::string MeshProperties::as_string() {
	return _line;
}

void MeshProperties::_observe(ullint step) {
	std::stringstream ss;

	double volume = 0.;
	double area = 0.;
	for(auto &triangle :  _sys_props->triangles()) {
		volume += triangle->volume;
		area += triangle->area;
	}

	ss << volume << " " << area;

	_line = ss.str();
}

} /* namespace ashell */
