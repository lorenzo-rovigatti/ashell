/*
 * OutputObservable.cpp
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#include "OutputObservable.h"

#include <iostream>
#include <sstream>

namespace ashell {

using namespace std;

OutputObservable::OutputObservable(std::string stream_name, ullint print_every) :
				_output(nullptr),
				_print_every(print_every),
				_start_from(0),
				_stop_at(0) {

	if(stream_name == "stderr") {
		_output = &std::cerr;
	}
	else if(stream_name == "stdout") {
		_output = &std::cout;
	}
	else {
		_output_stream.open(stream_name.c_str());
		_output = &_output_stream;
	}

	if(_output->bad() || !_output->good()) {
		throw std::runtime_error(boost::str(boost::format("Stream %s not writable") % stream_name.c_str()));
	}
}

bool OutputObservable::is_ready(ullint step) {
	if(_stop_at > 0 && step > _stop_at) {
		return false;
	}
	if(step < _start_from) {
		return false;
	}
	return ((_print_every != 0) && (step % _print_every == 0));
}

void OutputObservable::print_output(ullint step) {
	stringstream ss;
	for(auto obs : _observables) {
		obs->compute(step);
		if(ss.tellp() > 0) ss << " ";
		ss << obs->as_string();
	}

	ss << endl;
	string to_write = ss.str();
	*_output << to_write;
	_output->flush();
}

OutputObservable::~OutputObservable() {
	if(_output_stream.is_open()) {
		_output_stream.close();
	}
}

} /* namespace ashell */
