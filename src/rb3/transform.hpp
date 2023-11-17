#ifndef RB3_TRANSFORM_HPP
#define RB3_TRANSFORM_HPP
#include "hmx/matrix3.hpp"
#include "vector3.hpp"

class Transform {
public:
	Hmx::Matrix3 rot;
	Vector3 trans;
};

#endif
