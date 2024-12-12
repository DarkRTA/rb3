#pragma once

#include "bandobj/BandCharacter.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Env.h"
#include "rndobj/Mat.h"
#include "rndobj/Cam.h"
#include "rndwii/Lit.h"

class WiiEnviron : public RndEnviron {
public:
    WiiEnviron();
    virtual ~WiiEnviron();
    OBJ_CLASSNAME(WiiEnviron)
    OBJ_SET_TYPE(WiiEnviron)

    bool SetLight(int, WiiLight *);
    void RenderCharactersToShadowBuffers();

    static RndMat *mShadowMat;
    static RndCam *mShadowCam;
    static ObjPtrList<BandCharacter> mShadowedCharacters;
    static bool mbEnableShadows;
    static bool mbRenderingShadows;
    static bool mbShowShadowTextureOnScreen;
    static bool mShadowLightSet;
};
