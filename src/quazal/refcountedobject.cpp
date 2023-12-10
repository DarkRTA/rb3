#include "refcountedobject.hpp"

Quazal::RefCountedObject::RefCountedObject(){
    ref_count = 1;
}

Quazal::RefCountedObject::~RefCountedObject(){
    ref_count = 0;
}