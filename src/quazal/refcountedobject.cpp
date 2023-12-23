#include "refcountedobject.hpp"
#include "scopedcs.hpp"

Quazal::RefCountedObject::RefCountedObject() {
    ref_count = 1;
}

Quazal::RefCountedObject::~RefCountedObject() {
    ref_count = 0;
}

Quazal::RefCountedObject *Quazal::RefCountedObject::AcquireRef() {
    ScopedCS scope(s_oCS);
    ref_count++;
    return this;
}

void Quazal::RefCountedObject::ReleaseRef() {
    bool b = false;
    {
        ScopedCS scope(s_oCS);
        if (ref_count == 1)
            b = true;
        else
            ref_count--;
    }
    if (b)
        delete this;
}

unsigned short Quazal::RefCountedObject::GetRefCount() const {
    return ref_count;
}