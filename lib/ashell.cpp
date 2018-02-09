/*
 * ashell.cpp
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#include "boxes/Cuboid.h"
#include "Initialiser.h"
#include "Particles.h"
#include "System.h"
#include "SystemProperties.h"
#include "World.h"

#include <boost/python.hpp>

namespace boost {
   template<class T> T* get_pointer(std::shared_ptr<T> p){
	   return p.get();
   }
}

namespace ashell {

void export_box();
void export_cuboid();
void export_initialiser();
void export_particles();
void export_system();
void export_system_properties();
void export_world();

BOOST_PYTHON_MODULE(_ashell) {
	export_box();
	export_cuboid();
	export_initialiser();
	export_particles();
	export_system();
	export_system_properties();
	export_world();
}

}
