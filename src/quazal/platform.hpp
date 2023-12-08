#ifndef QUAZAL_PLATFORM_HPP
#define QUAZAL_PLATFORM_HPP
#include "rootobject.hpp"

namespace Quazal {
    class Platform : RootObject {
    public:
        Platform();
        ~Platform();
        void CreateInstance();
        void DeleteInstance();
        void SetRandomNumberSeed(unsigned int);
        unsigned int GetRandomNumber(unsigned int);
        float GetRealRandomNumber(float);
        void Breakpoint();
        void Sleep(unsigned int);
    };
}

#endif