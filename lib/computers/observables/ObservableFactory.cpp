/*
 * ObservableFactory.cpp
 *
 *  Created on: 22 Mar 2018
 *      Author: lorenzo
 */

#include "ObservableFactory.h"

#include "../../utils/InputFile.h"

#include "Configuration.h"
#include "MeshProperties.h"
#include "Step.h"
#include "StrainInvariants.h"

namespace ashell {

ObservableFactory::~ObservableFactory() {

}

std::shared_ptr<Observable> ObservableFactory::make_observable(InputFile &inp) {
	std::shared_ptr<Observable> obs;

	std::string type;
	inp.value_as_string("type", type, 1);
	if(type == "configuration") {
		obs = std::shared_ptr<Configuration>(new Configuration());
	}
	else if(type == "step") {
		obs = std::shared_ptr<Step>(new Step());
	}
	else if(type == "strain_invariants") {
		obs = std::shared_ptr<StrainInvariants>(new StrainInvariants());
	}
	else if(type == "mesh_properties") {
		obs = std::shared_ptr<MeshProperties>(new MeshProperties());
	}
	else {
		std::string error = boost::str(boost::format("Unknown observable type '%s'") % type);
		throw std::runtime_error(error);
	}
	obs->parse_input(inp);

	return obs;
}

} /* namespace ashell */
