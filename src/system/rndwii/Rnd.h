#ifndef RNDWII_RND_H
#define RNDWII_RND_H

#include "math/Geo.h"
#include "revolution/mtx/mtx.h"
#include "rndobj/Rnd.h"
#include "rndwii/SplitPostProc.h"
#include <vector>

class WiiOrthoProj {
public:
    WiiOrthoProj();
    ~WiiOrthoProj();
    float proj[8];
};

class WiiRnd : public Rnd {
public:
    enum SharedTexType {
    };

    WiiRnd();
    virtual ~WiiRnd();
    virtual DataNode Handle(DataArray *, bool);
    virtual void SetAspect(Aspect a) { mAspect = a; }
    virtual void RemovePointTest(RndFlare *);
    virtual void DoPostProcess();

    void SwapFrameBuffer();
    void SetTriFrameRendering(bool);
    void SetOrthoProj();
    void DoPointTests();
    bool GetProgressiveScan();
    void CopyBuffer();
    void DrawQuad(const Hmx::Rect &);
    void DrawQuad(int, int);
    void DrawLine(const Vector3 &, const Vector3 &, const Hmx::Color &, bool);
    void WiiPreInit();
    void SetFullScrProj();
    void PreInit();
    void ClearSwapTables();
    void DrawBlackBackground();
    void KeyboardOpen();
    void KeyboardClose();
    RndTex *GetSharedTex(SharedTexType, bool);

    ushort unk_0x170, unk_0x172;
    u8 unk_0x184, unk_0x185;
    void *unk_0x1A8, *unk_0x1AC, *unk_0x1B0, *unk_0x1B4;
    u32 unk_0x1B8;
    Mtx44 unk_0x1BC, unk_0x1FC, unk_0x23C;
    WiiSplitPostProc *unk_0x274;
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
void MakeWiiMtxTex(const Transform &, bool, Mtx);
void MakeWiiMtx(const Transform &, Mtx &);
uint MakeU32Color(const Hmx::Color &);

extern WiiRnd TheWiiRnd;
extern int gSuppressPointTest;
extern bool gbDbgRequestForcedHang;
extern bool gbDbgRequestHangRecovery;
extern bool gRecoveringThisFrame;

#endif // RNDWII_RND_H