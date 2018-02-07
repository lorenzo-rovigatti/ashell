/*
 * System.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "../lib/System.h"

#include <iostream>
#include <boost/python.hpp>

namespace ashell {

using namespace std;
using namespace boost::python;

System::System() {

}

System::~System() {

}

void System::run(long long int steps) {
	for(int i = 0; i < steps; i++) {
		cout << "Step " << i << endl;
	}
}

BOOST_PYTHON_MODULE(system) {
	class_<System>("System")
			.def("run", &System::run);
}

} /* namespace ashell */
