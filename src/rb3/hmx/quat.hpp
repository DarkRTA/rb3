#ifndef HMX_QUAT_HPP
#define HMX_QUAT_HPP

namespace Hmx {
    class Quat {
    public:
        float x;
        float y;
        float z;
        float w;

        void Set(float, float, float, float);
    };
}

#endif
