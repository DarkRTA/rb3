#ifndef RB3_TRIANGLE_HPP
#define RB3_TRIANGLE_HPP
#include "vector3.hpp"

class Triangle {
public:
	Vector3 vec1;
	Vector3 vec2;
	Vector3 vec3;
	Vector3 vec4;
	
	void Set(const Vector3&, const Vector3&, const Vector3&); // fn_800DEDA4
};

#endif
