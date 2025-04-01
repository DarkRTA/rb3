#pragma once

namespace Quazal {
    class VirtualRootObject {
    public:
        static void *operator new(unsigned long, char *, unsigned int);
        static void operator delete(void *);
    };
}
