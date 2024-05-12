#ifndef OBJ_OBJLIST_H
#define OBJ_OBJLIST_H
#include <list>
#include "utl/BinStream.h"
#include "obj/Object.h"

template <class T> class ObjList : public std::list<T> {
public:
    ObjList(Hmx::Object* o) : mOwner(o) {}
    Hmx::Object* mOwner;
};

#endif
