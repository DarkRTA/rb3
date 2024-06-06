#ifndef RNDWII_RND_H
#define RNDWII_RND_H

#include "math/Geo.h"
#include "revolution/mtx/mtx.h"
#include "rndobj/Rnd.h"
#include <vector>

class WiiRnd : public Rnd { public:
    WiiRnd();
    virtual ~WiiRnd();
    virtual DataNode Handle(DataArray*, bool);

    void SwapFrameBuffer();
    void SetTriFrameRendering(bool);
    void SetOrthoProj();
    void DoPointTests();
    void* GetCurrXFB();
    bool GetProgressiveScan();
    void DrawQuad(const Hmx::Rect&);
    void DrawLine(const Vector3&, const Vector3&, const Hmx::Color&, bool);
    void WiiPreInit();

    void* unk_0x1A8, *unk_0x1AC;
    Mtx44 unk_0x1BC, unk_0x1FC, unk_0x23C;
    bool mProgScan; // 0x2AC
    bool unk_0x2B0, unk_0x2B1, unk_0x2B2, unk_0x2B3;
    std::vector<Rnd::PointTest> unk_0x2B4;
    bool unk_0x2BC;
    int mFramesBuffered; // 0x2C0

    static bool mUseLockedCache, mShowParticle, mShowAssetName;
    static void SyncFree(void*);
};

void RndGXBegin(_GXPrimitive prim, _GXVtxFmt fmt, unsigned short verts);
void RndGXEnd();

WiiRnd TheWiiRnd;

#endif // RNDWII_RND_H