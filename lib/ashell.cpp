/*
 * ashell.cpp
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#ifdef ASHELL_PYTHON
#include <boost/python.hpp>

namespace boost {
   template<class T> T* get_pointer(std::shared_ptr<T> p){
	   return p.get();
   }
}

namespace ashell {

// forward declarations
void export_box();
void export_computer();
void export_cuboid();
void export_initialiser();
void export_particles();
void export_system();
void export_system_properties();
void export_world();

BOOST_PYTHON_MODULE(_ashell) {
	export_box();
	export_computer();
	export_cuboid();
	export_initialiser();
	export_particles();
	export_system();
	export_system_properties();
	export_world();
}

}
#endif
