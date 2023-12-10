#ifndef QUAZAL_REFCOUNTEDOBJECT_HPP
#define QUAZAL_REFCOUNTEDOBJECT_HPP
#include "rootobject.hpp"

namespace Quazal {
    class RefCountedObject : RootObject {
    public:
        RefCountedObject();
        virtual ~RefCountedObject();
        virtual RefCountedObject* AcquireRef();
        virtual void ReleaseRef();
        short GetRefCount() const;

        short ref_count;
    };
}

#endif