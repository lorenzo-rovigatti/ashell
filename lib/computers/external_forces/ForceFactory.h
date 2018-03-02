/*
 * ForceFactory.h
 *
 *  Created on: 02 mar 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_EXTERNAL_FORCES_FORCEFACTORY_H_
#define LIB_COMPUTERS_EXTERNAL_FORCES_FORCEFACTORY_H_

#include "ExternalForce.h"

namespace ashell {

class InputFile;

class ForceFactory {
public:
	ForceFactory() = delete;
	virtual ~ForceFactory();

	static std::shared_ptr<ExternalForce> make_force(InputFile &inp);
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_EXTERNAL_FORCES_FORCEFACTORY_H_ */
