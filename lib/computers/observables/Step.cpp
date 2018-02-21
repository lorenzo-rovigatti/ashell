/*
 * Step.cpp
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#include "Step.h"

namespace ashell {

Step::Step() :
				_curr_step(0) {

}

Step::~Step() {

}

std::string Step::as_string() {
	return boost::str(boost::format("%lld") % _curr_step);
}

void Step::_observe(ullint step) {
	_curr_step = step;
}

} /* namespace ashell */
