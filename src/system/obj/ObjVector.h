#ifndef OBJ_OBJVECTOR_H
#define OBJ_OBJVECTOR_H
#include "types.h"
#include <vector>
#include "obj/Object.h"

template <class T1, class T2 = u16> class ObjVector : public std::vector<T1, T2> {
public:
    ObjVector(Hmx::Object* o) : mOwner(o) {}
    Hmx::Object* mOwner;
};

#endif
