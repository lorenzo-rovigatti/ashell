/*
 * Observable.cpp
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#include "Observable.h"

#include <boost/format.hpp>

namespace ashell {

using std::string;

Observable::Observable(std::string n_name) :
				Consumer(n_name),
				_last_step(0) {

}

Observable::~Observable() {

}

void Observable::consume(ullint step) {
	if(!should_consume(step)) return;
	_observe(step);
}

double Observable::as_scalar() {
	throw std::runtime_error("Calling an unimplemented Observable::as_scalar() method");
	return 0.;
}

string Observable::as_string() {
	return boost::str(boost::format("%lf") % as_scalar());
}

void Observable::_observe(ullint step) {
	throw std::runtime_error("Calling an unimplemented Observable::_observe() method");
}

} /* namespace ashell */