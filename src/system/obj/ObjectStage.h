#ifndef OBJ_OBJECTSTAGE_H
#define OBJ_OBJECTSTAGE_H
#include "obj/ObjPtr_p.h"
#include "utl/BinStream.h"

class ObjectStage : public ObjPtr<Hmx::Object, ObjectDir> {
public:
    ObjectStage() : ObjPtr<Hmx::Object, ObjectDir>(sOwner, 0) {}
    ObjectStage(Hmx::Object* o) : ObjPtr<Hmx::Object, ObjectDir>(sOwner, o) {}
    virtual ~ObjectStage(){}

    // copy ctor - calls ObjPtr copy ctor

    static Hmx::Object* sOwner;
};

void Interp(const ObjectStage&, const ObjectStage&, float, Hmx::Object*&);
BinStream& operator<<(BinStream&, const ObjectStage&);
BinStream& operator>>(BinStream&, ObjectStage&);

#endif
