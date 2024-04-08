#include "Platform/RefCountedObject.h"
#include "Platform/ScopedCS.h"

Quazal::CriticalSection Quazal::RefCountedObject::s_oCS(0);

Quazal::RefCountedObject::RefCountedObject(){
    m_ui16RefCount = 1;
}

Quazal::RefCountedObject::~RefCountedObject(){
    m_ui16RefCount = 0;
}

Quazal::RefCountedObject* Quazal::RefCountedObject::AcquireRef(){
    Quazal::ScopedCS scope(s_oCS);
    m_ui16RefCount++;
    return this;
}

void Quazal::RefCountedObject::ReleaseRef(){
    bool b = false;
    {
        Quazal::ScopedCS scope(s_oCS);
        if(m_ui16RefCount == 1) b = true;
        else m_ui16RefCount--;
    }
    if(b) delete this;
}

// Quazal::RefCountedObject *Quazal::RefCountedObject::AcquireRef() {
//     ScopedCS scope(s_oCS);
//     ref_count++;
//     return this;
// }

// void Quazal::RefCountedObject::ReleaseRef() {
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

unsigned short Quazal::RefCountedObject::GetRefCount() const { return m_ui16RefCount; }
