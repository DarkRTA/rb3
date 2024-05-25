#ifndef OBJ_OBJVERSION_H
#define OBJ_OBJVERSION_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

class ObjVersion {
public:
    ObjVersion(Hmx::Object* o, int i) : obj(0, o), revs(i) {}
    ObjPtr<Hmx::Object, ObjectDir> obj;
    int revs;
};

#endif
