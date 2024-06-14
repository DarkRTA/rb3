#ifndef RNDOBJ_RND_H
#define RNDOBJ_RND_H
#include "math/Color.h"
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Console.h"
#include "rndobj/Draw.h"
#include "rndobj/Mat.h"
#include "rndobj/Overlay.h"
#include "rndobj/PostProc.h"

class RndCam;
class RndEnviron;
class RndFlare;
class RndLight;

enum ProcessCmd {
    kProcessNone = 0,
    kProcessWorld = 1,
    kProcessPost = 2,
    kProcessChar = 4,
    kProcessPostChar = 6,
    kProcessAll = 7
};

class Rnd : public Hmx::Object, public RndOverlay::Callback {
public:
    struct PointTest {
        int unk_0x0, unk_0x4, unk_0x8, unk_0xC;
    };

    enum Aspect {
        kSquare,
        kRegular,
        kWidescreen,
        kLetterbox
    };

    Rnd();
    virtual ~Rnd(){}
    virtual DataNode Handle(DataArray*, bool);
    virtual void PreInit();
    virtual void Init();
    virtual void ReInit(){}
    virtual void Terminate();
    virtual void SetClearColor(const Hmx::Color& c) { mClearColor = c; }
    virtual void ForceColorClear(){}
    virtual void ScreenDump(const char*);
    virtual void ScreenDumpUnique(const char*);
    virtual void DrawRect(const Hmx::Rect&, const Hmx::Color&, RndMat*, const Hmx::Color*, const Hmx::Color*){}
    virtual void DrawString(const char*, const Vector2&, const Hmx::Color&, bool);
    virtual void DrawLine(const Vector3&, const Vector3&, const Hmx::Color&, bool){}
    virtual void BeginDrawing();
    virtual void EndDrawing();
    virtual void MakeDrawTarget(){}
    virtual void SetSync(int i){ mSync = i; }
    virtual int GetFrameID() const;
    virtual int GetCurrentFrameTex(bool){ return 0; } // fix return type
    virtual void ReleaseOwnership(){}
    virtual void AcquireOwnership(){}
    virtual void SetShadowMap(RndTex*, RndCam*, const Hmx::Color*){}
    virtual void SetGSTiming(bool);
    virtual void CaptureNextGpuFrame(){}
    virtual void RemovePointTest(RndFlare*);
    virtual bool HasDeviceReset() const { return 0; }
    virtual void SetAspect(Aspect a){ mAspect = a; }
    virtual float YRatio();
    virtual int GetShadowMap(){ return 0; } // fix return type
    virtual int GetShadowCam(){ return 0; } // fix return type
    virtual void SetShrinkToSafeArea(bool b) { mShrinkToSafe = b; }
    virtual bool GetOverscan() const { return 0; }
    virtual void SetOverscan(bool){}
    virtual void ConfigureRenderMode(){}
    virtual void ChangeYScale(bool){}
    virtual void SetInGame(bool b){ mInGame = b; }
    virtual int BeginQuery(RndDrawable*){ return -1; }
    virtual int EndQuery(int){ return 0; }
    virtual int VisibleSets(std::vector<RndDrawable*>&, std::vector<RndDrawable*>&){ return 0; } // fix return type
    virtual void DoWorldBegin();
    virtual void DoWorldEnd();
    virtual void DoPostProcess();
    virtual void DrawPreClear();
    virtual float UpdateOverlay(RndOverlay*, float);
    virtual bool CanModal(bool){ return 0; }
    virtual void ModalDraw(bool, const char*){}

    bool ShrinkToSafeArea() { return mShrinkToSafe; }
    bool InGame() const { return mInGame; }
    void ShowConsole(bool); bool ConsoleShowing();
    void SetShowTimers(bool, bool);
    bool GetEvenOddDisabled() const;
    void SetEvenOddDisabled(bool);
    void UpdateRate(); void UpdateHeap();
    float DrawTimers(float);
    void Modal(bool&, char*, bool);
    void RegisterPostProcessor(PostProcessor*);
    void UnregisterPostProcessor(PostProcessor*);
    void SetPostProcOverride(RndPostProc*);
    PostProcessor* GetPostProcOverride() const;
    void SetupFont();
    void CreateDefaults();
    void CopyWorldCam(RndCam*);
    void EndWorld();
    void SetProcAndLock(bool);
    bool ProcAndLock() const;
    void DrawRectScreen(const Hmx::Rect&, const Hmx::Color&, RndMat*, const Hmx::Color*, const Hmx::Color*);
    void ResetProcCounter();
    int DrawMode() const { return unk_0xE4; }
    void PreClearDrawAddOrRemove(RndDrawable*, bool, bool);

    DataNode OnShowConsole(const DataArray*);
    DataNode OnToggleTimers(const DataArray*);
    DataNode OnToggleOverlayPosition(const DataArray*);
    DataNode OnToggleTimersVerbose(const DataArray*);
    DataNode OnToggleOverlay(const DataArray*);
    DataNode OnShowOverlay(const DataArray*);
    DataNode OnSetSphereTest(const DataArray*);
    DataNode OnClearColorR(const DataArray*);
    DataNode OnClearColorG(const DataArray*);
    DataNode OnClearColorB(const DataArray*);
    DataNode OnClearColorPacked(const DataArray*);
    DataNode OnSetClearColor(const DataArray*);
    DataNode OnSetClearColorPacked(const DataArray*);
    DataNode OnScreenDump(const DataArray*);
    DataNode OnScreenDumpUnique(const DataArray*);
    DataNode OnScaleObject(const DataArray*);
    DataNode OnReflect(const DataArray*);
    DataNode OnToggleHeap(const DataArray*);
    DataNode OnTestDrawGroups(const DataArray*);

    Hmx::Color mClearColor; // 0x20
    int mWidth; // 0x30
    int mHeight; // 0x34
    int mScreenBpp; // 0x38
    int mDrawCount; // 0x3c
    Timer mDrawTimer; // 0x40
    RndOverlay* mTimersOverlay; // 0x70
    RndOverlay* mRateOverlay; // 0x74
    RndOverlay* mHeapOverlay; // 0x78
    RndOverlay* mStatsOverlay; // 0x7c
    RndConsole* mConsole; // 0x80
    RndMat* unk84; // 0x84
    RndMat* unk88; // 0x88
    RndMat* unk8c; // 0x8c
    RndCam* unk90; // 0x90
    RndCam* unk94; // 0x94
    RndEnviron* unk98; // 0x98
    RndLight* unk9c; // 0x9c

    int unk_arr[8]; // 0xa0 - 0xbc, inclusive

    float unkc0; // 0xc0
    int unkc4; // 0xc4
    int unkc8; // 0xc8
    unsigned int mFrameID; // 0xcc
    const char* unkd0; // 0xd0
    DataArray* mFont; // 0xd4
    int mSync; // 0xd8
    bool unkdc; // 0xdc
    bool mShowSafeArea; // 0xdd
    bool unkde; // 0xde
    bool unkdf; // 0xdf
    Aspect mAspect; // 0xE0
    int unk_0xE4; // 0xe4
    bool unke8; // 0xe8
    bool unke9; // 0xe9
    bool mShrinkToSafe; // 0xEA
    bool mInGame; // 0xeb
    bool unkec; // 0xec
    bool mDisablePostProc; // 0xed
    bool unkee; // 0xee
    bool unkef; // 0xef
    bool unkf0; // 0xf0
    int unkf4; // 0xf4
    int unkf8; // 0xf8
    std::list<PointTest> mPointTests; // 0xfc
    std::list<PostProcessor*> mPostProcessors; // 0x104
    PostProcessor* mPostProcOverride; // 0x10c
    ObjPtrList<RndDrawable, ObjectDir> unk110; // 0x110
    ObjPtrList<RndDrawable, ObjectDir> mDraws; // 0x120
    bool unk130; // 0x130
    bool unk131; // 0x131
    ProcCounter mProcCounter; // 0x134
    ProcessCmd mProcCmds; // 0x14c
    ProcessCmd mLastProcCmds; // 0x150
    std::list<void*> unk154; // 0x154
    int mForceCharLod; // 0x15c
};

extern Rnd* TheRnd;
extern int gSuppressPointTest;

#endif // RNDOBJ_RND_H