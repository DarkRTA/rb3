#pragma once
#include "obj/Object.h"
#include "os/Debug.h"

void UnhookGroupParents(Hmx::Object *);
void UnhookAllParents(Hmx::Object *);

template <class T>
T *NewRndCopy(const T *obj) {
    T *result = dynamic_cast<T *>(Hmx::Object::NewObject(T::StaticClassName()));
    MILO_ASSERT(result, 0x22);
    result->Copy(obj, Hmx::Object::kCopyShallow);
    return result;
}