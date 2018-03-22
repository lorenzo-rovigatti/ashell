/*
 * ObservableFactory.cpp
 *
 *  Created on: 22 Mar 2018
 *      Author: lorenzo
 */

#include "ObservableFactory.h"

#include "Configuration.h"
#include "../../utils/InputFile.h"

namespace ashell {

ObservableFactory::ObservableFactory() {
}

ObservableFactory::~ObservableFactory() {
}

std::shared_ptr<Observable> ObservableFactory::make_observable(InputFile &inp) {
	std::shared_ptr<Observable> obs;

	std::string type;
	inp.value_as_string("type", type, 1);
	if(type == "configuration") {
		obs = std::shared_ptr<Configuration>(new Configuration());
	}
	else {
		std::string error = boost::str(boost::format("Unknown observable type '%s'") % type);
		throw std::runtime_error(error);
	}

	return obs;
}

} /* namespace ashell */
