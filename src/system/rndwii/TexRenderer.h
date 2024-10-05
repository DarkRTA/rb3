#pragma once

#include "obj/ObjMacros.h"
#include "rndobj/TexRenderer.h"

class WiiTexRenderer : public RndTexRenderer {
    WiiTexRenderer();
    virtual ~WiiTexRenderer();
    OBJ_CLASSNAME(WiiTexRenderer)
    OBJ_SET_TYPE(WiiTexRenderer)
    virtual void Enter();

    void DrawPreClear();
};
