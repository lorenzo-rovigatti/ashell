/*
 * Box.h
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_BOXES_BOX_H_
#define LIB_BOXES_BOX_H_

#include "../defs.h"

#include <boost/signals2.hpp>

namespace ashell {

using BoxSignal = boost::signals2::signal<void ()>;
using BoxCallbackSlot = BoxSignal::slot_type;

/**
 * The box class has a signal as a member. As a result, it cannot be copied
 * and hence inherits from boost::noncopyable
 */
class Box: public boost::noncopyable {
public:
	Box();
	virtual ~Box();

	virtual std::string as_string();

	virtual void register_to_box_changes(BoxCallbackSlot slot);
	virtual vec3 random_point_in_box();
	virtual vec3 minimum_image(const vec3 &p, const vec3 &q);

private:
	BoxSignal _changed_signal;
};

} /* namespace ashell */

#endif /* LIB_BOXES_BOX_H_ */
