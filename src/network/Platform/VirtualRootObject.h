#ifndef PLATFORM_VIRTUALROOTOBJECT_H
#define PLATFORM_VIRTUALROOTOBJECT_H

namespace Quazal {
    class VirtualRootObject {
    public:
        static void *operator new(unsigned long, char *, unsigned int);
        static void operator delete(void *);
    };
}

#endif // PLATFORM_VIRTUALROOTOBJECT_H
