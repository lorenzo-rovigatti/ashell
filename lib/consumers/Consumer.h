/*
 * Consumer.h
 *
 *  Created on: 09 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_CONSUMERS_CONSUMER_H_
#define LIB_CONSUMERS_CONSUMER_H_

#include "../SystemProperties.h"
#include "../defs.h"

namespace ashell {

class Consumer {
public:
	Consumer();
	virtual ~Consumer();

	virtual bool should_consume(ullint step);
	virtual void consume(ullint step);

protected:
	bool _ever_consumed;
	ullint _last_step;
	std::shared_ptr<SystemProperties> _sys_props;
	std::shared_ptr<Particles> _particles;
};

} /* namespace ashell */

#endif /* LIB_CONSUMERS_CONSUMER_H_ */
