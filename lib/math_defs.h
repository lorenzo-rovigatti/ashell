/*
 * math_defs.h
 *
 *  Created on: 08 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_MATH_DEFS_H_
#define LIB_MATH_DEFS_H_

#include <Eigen/Core>
#include <Eigen/StdVector>

using vec3 = Eigen::Vector3d;
using mat3 = Eigen::Matrix3d;

using vector_vec3 = std::vector<vec3, Eigen::aligned_allocator<vec3> >;

#endif /* LIB_MATH_DEFS_H_ */
