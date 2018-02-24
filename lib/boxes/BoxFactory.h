/*
 * BoxFactory.h
 *
 *  Created on: 24 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_BOXES_BOXFACTORY_H_
#define LIB_BOXES_BOXFACTORY_H_

#include "Box.h"

namespace ashell {

class BoxFactory {
public:
	BoxFactory() = delete;
	virtual ~BoxFactory();

	static std::shared_ptr<Box> make_box(std::string input);
};

} /* namespace ashell */

#endif /* LIB_BOXES_BOXFACTORY_H_ */
