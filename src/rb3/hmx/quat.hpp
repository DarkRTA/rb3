#ifndef HMX_QUAT_HPP
#define HMX_QUAT_HPP
#include "vector3.hpp"
#include "matrix3.hpp"

namespace Hmx {
    class Quat {
    public:
        float x;
        float y;
        float z;
        float w;

        // TODO: get rid of these ctors, if there are any errors, use the Set methods
        Quat() {
        }
        Quat(const Hmx::Matrix3 &);
        Quat(const Vector3 &);
        Quat(const Vector3 &, float);
        void Set(float, float, float, float);
        void Set(const Vector3 &, float);
        void Set(const Vector3 &);
        void Set(const Hmx::Matrix3 &);
        void operator=(const Hmx::Quat &);
    };
}

#endif
