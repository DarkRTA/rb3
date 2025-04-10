#pragma once
#include "rndobj/MultiMesh.h"

class WiiMultiMesh : public RndMultiMesh {
public:
    WiiMultiMesh() : unk34(0) {}
    OBJ_CLASSNAME(WiiMultiMesh)
    OBJ_SET_TYPE(WiiMultiMesh)
    virtual void DrawShowing();
    virtual ~WiiMultiMesh() {}

    bool unk34;
};
