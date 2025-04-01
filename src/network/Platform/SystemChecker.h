#pragma once

typedef void SystemCheckCallbackFunc(const char *, const char *, unsigned int);

namespace Quazal {
    class SystemChecker {
    public:
        static SystemCheckCallbackFunc *s_pfGetSystemCheckInfo;
    };
}
