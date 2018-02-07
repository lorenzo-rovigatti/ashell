/*
 * System.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_SYSTEM_H_
#define LIB_SYSTEM_H_

namespace ashell {

class System {
public:
	System();
	virtual ~System();

	void run(long long int steps);
};

} /* namespace ashell */

#endif /* LIB_SYSTEM_H_ */
