/*
 * Box.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "Box.h"

namespace ashell {

Box::Box() {

}

Box::~Box() {

}

void Box::register_to_box_changes(BoxCallbackSlot slot) {
	_changed_signal.connect(slot);
}

} /* namespace ashell */
