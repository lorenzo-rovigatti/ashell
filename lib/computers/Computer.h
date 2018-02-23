/*
 * Consumer.h
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_COMPUTERS_COMPUTER_H_
#define LIB_COMPUTERS_COMPUTER_H_

#include "../SystemProperties.h"
#include "../defs.h"

namespace ashell {

class Computer {
public:
	Computer(std::string n_name="computer");
	virtual ~Computer();

	virtual bool should_compute(ullint step);
	virtual void compute(ullint step);

	virtual const std::string &name() const {
		return _name;
	}

protected:
	bool _ever_computed;
	ullint _last_step;
	const std::shared_ptr<SystemProperties> _sys_props;
	const std::shared_ptr<Particles> _particles;
	std::string _name;
};

} /* namespace ashell */

#endif /* LIB_COMPUTERS_COMPUTER_H_ */
