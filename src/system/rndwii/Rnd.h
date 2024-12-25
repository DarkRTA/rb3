#ifndef RNDWII_RND_H
#define RNDWII_RND_H

#include "math/Geo.h"
#include "revolution/mtx/mtx.h"
#include "rndobj/Rnd.h"
#include <vector>

class WiiRnd : public Rnd {
public:
    enum SharedTexType {
    };

    WiiRnd();
    virtual ~WiiRnd();
    virtual DataNode Handle(DataArray *, bool);

    void SwapFrameBuffer();
    void SetTriFrameRendering(bool);
    void SetOrthoProj();
    void DoPointTests();
    bool GetProgressiveScan();
    void DrawQuad(const Hmx::Rect &);
    void DrawLine(const Vector3 &, const Vector3 &, const Hmx::Color &, bool);
    void WiiPreInit();
    void SetFullScrProj();
    RndTex *GetSharedTex(SharedTexType, bool);

    void *unk_0x1A8, *unk_0x1AC;
    Mtx44 unk_0x1BC, unk_0x1FC, unk_0x23C;
    bool mProgScan; // 0x2AC
    bool unk_0x2B0, unk_0x2B1, unk_0x2B2, unk_0x2B3;
    std::vector<Rnd::PointTest> unk_0x2B4;
    bool unk_0x2BC;
    int mFramesBuffered; // 0x2C0

    static bool mUseLockedCache, mShowParticle, mShowAssetName;
    static void ToggleAssetName() { mShowAssetName = !mShowAssetName; }
    static void ToggleShowParticle() { mShowParticle = !mShowParticle; }
    static void ToggleLockedCache() { mUseLockedCache = !mUseLockedCache; }
    static void SyncFree(void *);
    static void *GetCurrXFB();
};

void SetGPHangDetectEnabled(bool, const char *);
void RndGXBegin(_GXPrimitive prim, _GXVtxFmt fmt, unsigned short verts);
void RndGXEnd();
void RndGxDrawDone();

extern WiiRnd TheWiiRnd;
extern int gSuppressPointTest;
extern bool gbDbgRequestForcedHang;
extern bool gbDbgRequestHangRecovery;
extern bool gRecoveringThisFrame;

#endif // RNDWII_RND_H