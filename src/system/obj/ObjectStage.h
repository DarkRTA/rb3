#pragma once
#include "obj/ObjPtr_p.h"
#include "utl/BinStream.h"

class ObjectStage : public ObjPtr<Hmx::Object> {
public:
    ObjectStage() : ObjPtr<Hmx::Object>(sOwner) {}
    ObjectStage(Hmx::Object *o) : ObjPtr<Hmx::Object>(sOwner, o) {}
    virtual ~ObjectStage() {}

    // copy ctor - calls ObjPtr copy ctor

    static Hmx::Object *sOwner;
};

void Interp(const ObjectStage &, const ObjectStage &, float, Hmx::Object *&);
BinStream &operator<<(BinStream &, const ObjectStage &);
BinStream &operator>>(BinStream &, ObjectStage &);
