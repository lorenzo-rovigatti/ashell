/*
 * MathUtils.h
 *
 *  Created on: 24 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_UTILS_MATHUTILS_H_
#define LIB_UTILS_MATHUTILS_H_

namespace ashell {

class MathUtils {
public:
	MathUtils() = delete;
	virtual ~MathUtils();

	static double gaussian();
};

} /* namespace ashell */

#endif /* LIB_UTILS_MATHUTILS_H_ */
