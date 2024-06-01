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

class RndCam;
class RndFlare;

class Rnd : public Hmx::Object, public RndOverlay::Callback {
public:
    struct PointTest {
        
    };

    enum Aspect {

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
    virtual void SetSync(int);
    virtual int GetFrameID() const;
    virtual int GetCurrentFrameTex(bool){ return 0; } // fix return type
    virtual void ReleaseOwnership(){}
    virtual void AcquireOwnership(){}
    virtual void SetShadowMap(RndTex*, RndCam*, const Hmx::Color*){}
    virtual void SetGSTiming(bool);
    virtual void CaptureNextGpuFrame(){}
    virtual void RemovePointTest(RndFlare*);
    virtual bool HasDeviceReset() const { return 0; }
    virtual void SetAspect(Aspect);
    virtual float YRatio();
    virtual int GetShadowMap(){ return 0; } // fix return type
    virtual int GetShadowCam(){ return 0; } // fix return type
    virtual void SetShrinkToSafeArea(bool b) { mShrinkToSafe = b; }
    virtual bool GetOverscan() const { return 0; }
    virtual void SetOverscan(bool){}
    virtual void ConfigureRenderMode(){}
    virtual void ChangeYScale(bool){}
    virtual void SetInGame(bool);
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
    int unka0; // 0xa0
    int unka4; // 0xa4
    int unka8; // 0xa8
    int unkac; // 0xac
    int unkb0; // 0xb0
    int unkb4; // 0xb4
    int unkb8; // 0xb8
    int unkbc; // 0xbc

    int mAspectRatio; // 0xE0
    int unk_0xE4;

    bool mShrinkToSafe; // 0xEA
    bool ShrinkToSafeArea() { return mShrinkToSafe; }

    ObjPtrList<RndDrawable, ObjectDir> mDraws; // 0x120

    void ShowConsole(bool); bool ConsoleShowing();
    void SetShowTimers(bool, bool);
    bool GetEvenOddDisabled() const;
    void SetEvenOddDisabled(bool);
    void UpdateRate(); void UpdateHeap();
    float DrawTimers(float);
    void Modal(bool&, char*, bool);

    DataNode OnScreenDump(const DataArray*);
    DataNode OnScreenDumpUnique(const DataArray*);
    DataNode OnScaleObject(const DataArray*);
    DataNode OnReflect(const DataArray*);
};

extern Rnd* TheRnd;

#endif // RNDOBJ_RND_H