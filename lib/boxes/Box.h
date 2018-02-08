/*
 * Box.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_BOXES_BOX_H_
#define LIB_BOXES_BOX_H_

#include "../math_defs.h"

#include <boost/signals2.hpp>

namespace ashell {

using BoxSignal = boost::signals2::signal<void ()>;
using BoxCallbackSlot = BoxSignal::slot_type;

/**
 * The box class has a signal as a memeber. As a result, it cannot be copied
 * and hence inherits from boost::noncopyable
 */
class Box: public boost::noncopyable {
public:
	Box();
	virtual ~Box();

	virtual void register_to_box_changes(BoxCallbackSlot slot);
	virtual vec3 random_point_in_box() = 0;

private:
	BoxSignal _changed_signal;
};

} /* namespace ashell */

#endif /* LIB_BOXES_BOX_H_ */
