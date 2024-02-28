#ifndef PLATFORM_ROOTOBJECT_H
#define PLATFORM_ROOTOBJECT_H

namespace Quazal {
    class RootObject {
    public:
        void* operator new(unsigned long);
        void* operator new(unsigned long, const char *, unsigned int);
        void* operator new[](unsigned long);
        void* operator new[](unsigned long, const char *, unsigned int);
        void operator delete(void *);
        void operator delete[](void *);
    };
}

#endif
