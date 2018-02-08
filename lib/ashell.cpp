/*
 * ashell.cpp
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#include "System.h"
#include "SystemProperties.h"
#include "boxes/Cuboid.h"

#include <boost/python.hpp>

namespace ashell {

void export_system();
void export_system_properties();
void export_cuboid();

BOOST_PYTHON_MODULE(_ashell) {
	export_system();
	export_system_properties();
	export_cuboid();
}

}
