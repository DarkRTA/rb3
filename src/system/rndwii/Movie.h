#pragma once

#include "obj/ObjMacros.h"
#include "rndobj/Movie.h"
#include "rndobj/SIVideo.h"
class WiiMovie : public RndMovie {
    WiiMovie();
    virtual ~WiiMovie();
    OBJ_CLASSNAME(WiiMovie)
    OBJ_SET_TYPE(WiiMovie)
    virtual float EndFrame() { return (int)mVideoData.mHeight; }
    virtual void SetFile(const FilePath &, bool);
    virtual void SetTex(RndTex *);
    virtual void SetFrame(float frame, float blend);

    void Update();
    void StreamReadFinish();
    void StreamNextBuffer();
    void StreamRestart(int);

    SIVideo mVideoData; // 0x2c
    u32 unk_0x40, unk_0x44, unk_0x48, unk_0x4c, unk_0x50;

    void *unk_0x54;
};
