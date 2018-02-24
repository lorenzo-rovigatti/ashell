/*
 * BoxFactory.cpp
 *
 *  Created on: 24 feb 2018
 *      Author: lorenzo
 */

#include "BoxFactory.h"

#include "Cuboid.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace ashell {

BoxFactory::~BoxFactory() {

}

std::shared_ptr<Box> BoxFactory::make_box(std::string input_line) {
	std::shared_ptr<Box> new_box;

	std::vector<std::string> spl_input;
	boost::split(spl_input, input_line, boost::is_any_of("\t "), boost::token_compress_on);

	if(spl_input[0] == "cube") {
		if(spl_input.size() != 2) {
			std::string error = boost::str(boost::format("The cuboid box line '%s' should have 2 fields, not %d") % input_line % spl_input.size());
			throw std::runtime_error(error);
		}

		double L = boost::lexical_cast<double>(spl_input[1]);
		new_box = std::shared_ptr<Box>(new Cuboid(L));
	}
	else if(spl_input[0] == "cuboid") {
		if(spl_input.size() != 4) {
			std::string error = boost::str(boost::format("The cuboid box line '%s' should have 4 fields, not %d") % input_line % spl_input.size());
			throw std::runtime_error(error);
		}

		double Lx = boost::lexical_cast<double>(spl_input[1]);
		double Ly = boost::lexical_cast<double>(spl_input[2]);
		double Lz = boost::lexical_cast<double>(spl_input[3]);
		new_box = std::shared_ptr<Box>(new Cuboid(Lx, Ly, Lz));
	}
	else {
		std::string error = boost::str(boost::format("Invalid box line '%s'") % input_line);
		throw std::runtime_error(error);
	}

	return new_box;
}

} /* namespace ashell */
