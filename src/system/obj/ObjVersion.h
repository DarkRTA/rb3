#ifndef OBJ_OBJVERSION_H
#define OBJ_OBJVERSION_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

class ObjVersion {
public:
    ObjPtr<Hmx::Object, ObjectDir> ptr;
    int revs;
};

#endif
