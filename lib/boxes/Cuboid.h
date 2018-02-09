/*
 * Cuboid.h
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_BOXES_CUBOID_H_
#define LIB_BOXES_CUBOID_H_

#include "Box.h"

namespace ashell {

class Cuboid: public Box {
public:
	Cuboid(double L);
	Cuboid(double Lx, double Ly, double Lz);
	virtual ~Cuboid();

	virtual vec3 random_point_in_box();
	virtual vec3 minimum_image(vec3 p, vec3 q);

protected:
	vec3 _box;
};

} /* namespace ashell */

#endif /* LIB_BOXES_CUBOID_H_ */
