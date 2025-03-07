#pragma once

#include "rndobj/PostProc.h"
#include "rndwii/Tex.h"
#include "types.h"

class WiiSplitPostProc : public PostProcessor {
    WiiSplitPostProc();
    virtual ~WiiSplitPostProc();
    virtual void OnGPHangRecover();
    virtual void BeginWorld();
    virtual void EndWorld();
    virtual void DoPost();
    virtual float Priority() { return 10; }

    void DrawWorldTex();
    void DrawFinalTex();
    void DrawWorldColorTex();

    WiiTex *mTex;
    u8 unk_0x8, unk_0x9;

    NEW_OVERLOAD
    DELETE_OVERLOAD
};
