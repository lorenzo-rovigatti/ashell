/*
 * Andersen.h
 *
 *  Created on: 26 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_UPDATERS_THERMOSTATS_ANDERSEN_H_
#define LIB_UPDATERS_THERMOSTATS_ANDERSEN_H_

#include "../Updater.h"

namespace ashell {

class Andersen: public Updater {
public:
	Andersen(double newtonian_time, double D0);
	virtual ~Andersen();

	void update(ullint step) override;

protected:
	double _newtonian_time;
	double _D0;
};

} /* namespace ashell */

#endif /* LIB_UPDATERS_THERMOSTATS_ANDERSEN_H_ */
