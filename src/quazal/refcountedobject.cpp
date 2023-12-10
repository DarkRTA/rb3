#include "refcountedobject.hpp"
#include "scopedcs.hpp"

Quazal::RefCountedObject::RefCountedObject(){
    ref_count = 1;
}

Quazal::RefCountedObject::~RefCountedObject(){
    ref_count = 0;
}

Quazal::RefCountedObject* Quazal::RefCountedObject::AcquireRef(){
    ScopedCS scope(s_oCS);
    ref_count++;
    return this;
}

void Quazal::RefCountedObject::ReleaseRef(){
    ScopedCS scope(s_oCS);
    unsigned short cnt = ref_count;
    if(cnt != 1) ref_count = cnt - 1;
    scope.~ScopedCS();
    if(cnt != 0)
        delete this;
}

unsigned short Quazal::RefCountedObject::GetRefCount() const {
    return ref_count;
}