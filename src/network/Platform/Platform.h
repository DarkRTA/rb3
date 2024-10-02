#pragma once

#include "Platform/RandomNumberGenerator.h"
#include "Platform/RootObject.h"
#include "Platform/SystemError.h"
#include "types.h"

namespace Quazal {
    struct Platform : public RootObject {
        static Platform* _Instance;
        static RandomNumberGenerator s_oRNG;
        static ErrorDescriptionTable m_oErrorTable;
        Platform() {}
        static Platform* CreateInstance();
        static void DeleteInstance();
        static u32 GetRandomNumber(unsigned int);
        static float GetRealRandomNumber(float);
        static void Breakpoint();
        static void Sleep(uint);
    };
}
