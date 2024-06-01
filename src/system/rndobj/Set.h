#ifndef RNDOBJ_SET_H
#define RNDOBJ_SET_H

#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include <vector>

class RndSet : public Hmx::Object {
public:
    RndSet();
    virtual ~RndSet();
    
    NEW_OBJ(RndSet);

    // ObjPtrList<Hmx::Object, ObjectDir> mObjects;
    std::vector<int> mProps;
};

#endif // RNDOBJ_SET_H
