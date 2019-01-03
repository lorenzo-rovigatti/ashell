/*
 * MeshProperties.h
 *
 *  Created on: 03 gen 2019
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_OBSERVABLES_MESHPROPERTIES_H_
#define LIB_COMPUTERS_OBSERVABLES_MESHPROPERTIES_H_

#include "Observable.h"

namespace ashell {

class MeshProperties: public virtual Observable {
public:
	MeshProperties(std::string n_name="mesh_properties");
	virtual ~MeshProperties();

	std::string as_string() override;

protected:
	void _observe(ullint step) override;

	std::string _line;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_OBSERVABLES_MESHPROPERTIES_H_ */
