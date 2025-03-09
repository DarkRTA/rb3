#pragma once

#include "obj/ObjMacros.h"
#include "rndobj/MultiMesh.h"
class WiiMultiMesh : public RndMultiMesh, virtual Hmx::Object {
    virtual void DrawShowing();
    OBJ_CLASSNAME(WiiMultiMesh)
    OBJ_SET_TYPE(WiiMultiMesh)
    virtual ~WiiMultiMesh() {}
};
