#pragma once

#include "obj/ObjMacros.h"
#include "rndobj/Cam.h"

class WiiCam : public RndCam {
    WiiCam();
    OBJ_CLASSNAME(WiiCam)
    OBJ_SET_TYPE(WiiCam)
    virtual void Select();
    virtual u32 ProjectZ(float);

    static Transform sViewToWiiViewXfm;
    static Transform sWiiViewToViewXfm;
};
