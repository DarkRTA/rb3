#ifndef HMX_QUAT_HPP
#define HMX_QUAT_HPP
#include "../vector3.hpp"

namespace Hmx {
    class Quat {
    public:
        float x;
        float y;
        float z;
        float w;

        void Set(float, float, float, float);
        void Set(const Vector3&, float);
        void Set(const Vector3&);
    };
}

#endif
