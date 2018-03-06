/*
 * World.h
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_WORLD_H_
#define LIB_WORLD_H_

#include "System.h"

#include <vector>

namespace ashell {

class World {
public:
	World() = delete;
	virtual ~World();

	static std::shared_ptr<System> current_system();

	static std::shared_ptr<System> new_system();
	static void remove_system(std::shared_ptr<System> syst);

private:
	static std::weak_ptr<System> _current_system;
	static std::vector<std::shared_ptr<System> > _systems;
};

} /* namespace ashell */

#endif /* LIB_WORLD_H_ */
