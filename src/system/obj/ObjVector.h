#ifndef OBJ_OBJVECTOR_H
#define OBJ_OBJVECTOR_H
#include <vector>
#include "utl/BinStream.h"
#include "obj/Object.h"

template <class T> class ObjVector : public std::vector<T> {
public:
    ObjVector(Hmx::Object* o) : mOwner(o) {}
    Hmx::Object* mOwner;
};

#endif
