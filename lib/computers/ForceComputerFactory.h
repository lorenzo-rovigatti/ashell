/*
 * ForceComputerFactory.h
 *
 *  Created on: Dec 28, 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_FORCECOMPUTERFACTORY_H_
#define LIB_COMPUTERS_FORCECOMPUTERFACTORY_H_

#include "ForceComputer.h"

namespace ashell {

class InputFile;

class ForceComputerFactory {
public:
	virtual ~ForceComputerFactory();

	static std::shared_ptr<ForceComputer> make_potential(InputFile &inp);

private:
	ForceComputerFactory();
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_FORCECOMPUTERFACTORY_H_ */
