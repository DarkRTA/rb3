#ifndef QUAZAL_PLATFORM_HPP
#define QUAZAL_PLATFORM_HPP
#include "rootobject.hpp"
#include "randomnumbergenerator.hpp"

namespace Quazal {
    class Platform : RootObject {
    public:
        static Platform *_Instance;
        static RandomNumberGenerator s_oRNG;

        Platform();
        ~Platform();
        void CreateInstance();
        void DeleteInstance();
        static void SetRandomNumberSeed(unsigned int);
        static unsigned int GetRandomNumber(unsigned int);
        static float GetRealRandomNumber(float);
        void Breakpoint();
        void Sleep(unsigned int);
    };
}

#endif