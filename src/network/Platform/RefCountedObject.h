#ifndef PLATFORM_REFCOUNTEDOBJECT_H
#define PLATFORM_REFCOUNTEDOBJECT_H
#include "Platform/RootObject.h"
#include "Platform/CriticalSection.h"

namespace Quazal {
    class RefCountedObject : public RootObject {
    public:
        static CriticalSection s_oCS;

        RefCountedObject();
        virtual ~RefCountedObject();
        virtual RefCountedObject* AcquireRef();
        virtual void ReleaseRef();

        unsigned short GetRefCount() const;

        unsigned short m_ui16RefCount;
    };
}

#endif
