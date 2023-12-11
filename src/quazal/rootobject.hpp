#ifndef QUAZAL_ROOTOBJECT_HPP
#define QUAZAL_ROOTOBJECT_HPP

namespace Quazal {
    class RootObject {
    public:
        // virtual ~RootObject();
        // virtual RootObject* AcquireRef() = 0;
        // virtual void ReleaseRef() = 0;
        void* operator new(unsigned long);
        void* operator new(unsigned long, const char*, unsigned int);
        void* operator new[](unsigned long);
        void* operator new[](unsigned long, const char*, unsigned int);
        void operator delete(void*);
        void operator delete[](void*);
    };
}

#endif