#ifndef QUAZAL_WATERMARK_HPP
#define QUAZAL_WATERMARK_HPP
#include "rootobject.hpp"

namespace Quazal {
    class WaterMark : RootObject {
    public:
        WaterMark(const char*, bool, unsigned int);
        ~WaterMark();
    };
}

#endif