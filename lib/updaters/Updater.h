/*
 * Updater.h
 *
 *  Created on: 26 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_UPDATERS_UPDATER_H_
#define LIB_UPDATERS_UPDATER_H_

#include "../defs.h"
#include "../Particles.h"
#include "../SystemProperties.h"

namespace ashell {

class Updater {
public:
	Updater();
	virtual ~Updater();

	virtual void update(ullint step);

protected:
	const std::shared_ptr<SystemProperties> _sys_props;
	const std::shared_ptr<Particles> _particles;
};

} /* namespace ashell */

#endif /* LIB_UPDATERS_UPDATER_H_ */
