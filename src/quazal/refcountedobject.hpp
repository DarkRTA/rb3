#ifndef QUAZAL_REFCOUNTEDOBJECT_HPP
#define QUAZAL_REFCOUNTEDOBJECT_HPP
#include "rootobject.hpp"
#include "criticalsection.hpp"

namespace Quazal {
    class RefCountedObject : RootObject {
    public:
        static CriticalSection s_oCS;

        RefCountedObject();
        virtual ~RefCountedObject();
        virtual RefCountedObject* AcquireRef();
        virtual void ReleaseRef();
        unsigned short GetRefCount() const;

        unsigned short ref_count;
    };
}

#endif