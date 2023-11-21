#ifndef RB3_SHORTQUAT_HPP
#define RB3_SHORTQUAT_HPP
#include "hmx/quat.hpp"
#include "hmx/matrix3.hpp"

class ShortQuat {
public:
    short x, y, z, w;
    void Set(const Hmx::Quat&);
	void Set(const Hmx::Matrix3&);
	void operator=(const ShortQuat&);
	void ToQuat(Hmx::Quat&) const;
};

#endif
