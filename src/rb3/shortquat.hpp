#ifndef RB3_SHORTQUAT_HPP
#define RB3_SHORTQUAT_HPP

class ShortQuat {
public:
    short x, y, z, w;
    void Set(const Hmx::Quat&);
	void operator=(const ShortQuat&);
};

#endif
