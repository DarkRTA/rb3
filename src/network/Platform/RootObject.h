#pragma once

namespace Quazal {
    class RootObject {
    public:
        static void *operator new(unsigned long);
        static void *operator new(unsigned long, const char *, unsigned int);
        static void *operator new[](unsigned long);
        static void *operator new[](unsigned long, const char *, unsigned int);
        static void operator delete(void *);
        static void operator delete[](void *);
    };
}
