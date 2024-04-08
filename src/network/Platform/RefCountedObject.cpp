#include "Platform/RefCountedObject.h"
#include "Platform/ScopedCS.h"

namespace Quazal {

    CriticalSection RefCountedObject::s_oCS(0);

    RefCountedObject::RefCountedObject(){
        m_ui16RefCount = 1;
    }

    RefCountedObject::~RefCountedObject(){
        m_ui16RefCount = 0;
    }

    RefCountedObject* RefCountedObject::AcquireRef(){
        ScopedCS scope(s_oCS);
        m_ui16RefCount++;
        return this;
    }

    void RefCountedObject::ReleaseRef(){
        bool b = false;
        {
            ScopedCS scope(s_oCS);
            if(m_ui16RefCount == 1) b = true;
            else m_ui16RefCount--;
        }
        if(b) delete this;
    }

    // RefCountedObject *RefCountedObject::AcquireRef() {
    //     ScopedCS scope(s_oCS);
    //     ref_count++;
    //     return this;
    // }

    // void RefCountedObject::ReleaseRef() {
    //     bool b = false;
    //     {
    //         ScopedCS scope(s_oCS);
    //         if (ref_count == 1)
    //             b = true;
    //         else
    //             ref_count--;
    //     }
    //     if (b)
    //         delete this;
    // }

    unsigned short RefCountedObject::GetRefCount() const { return m_ui16RefCount; }

}
