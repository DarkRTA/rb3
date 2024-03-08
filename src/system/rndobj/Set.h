#ifndef RNDOBJ_SET_H
#define RNDOBJ_SET_H

#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include <vector>

class RndSet : public Hmx::Object {
    RndSet();
    virtual ~RndSet();
    
    // ObjPtrList<Hmx::Object, ObjectDir> list;
    std::vector<int> i_have_no_idea;
};

#endif // RNDOBJ_SET_H
