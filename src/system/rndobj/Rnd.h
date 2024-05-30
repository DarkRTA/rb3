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

class Rnd : public Hmx::Object, public RndOverlay::Callback { // there's some multiple inheritance bs goin on here and i don't like it
public:
    struct PointTest {
        
    };
    Rnd();
    virtual ~Rnd() {}
    virtual DataNode Handle(DataArray*, bool);

    virtual float UpdateOverlay(RndOverlay*, float);
    virtual void SetShrinkToSafeArea(bool b) { mShrinkToSafe = b; }
    virtual void PreInit(), Init(), ReInit(), Terminate();
    virtual void SetClearColor(const Hmx::Color& c) { mColor = c; }
    virtual void ForceColorClear() {}
    virtual void ScreenDump(const char*), ScreenDumpUnique(const char*);
    virtual void DrawRect(const Hmx::Rect&, const Hmx::Color&, RndMat*, const Hmx::Color*, const Hmx::Color*);

    virtual void BeginDrawing(), EndDrawing();

    Hmx::Color mColor; // 0x20
    int mWidth, mHeight; // 0x30, 0x34
    int mScreenBpp; // 0x38
    int unk_0x3C;
    Timer mFrameTimer; // 0x40

    RndOverlay* unk_0x70, *unk_0x74, *unk_0x78;
    RndConsole* mConsole; // 0x80

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
    float YRatio();
    void Modal(bool&, char*, bool);

    DataNode OnScreenDump(const DataArray*);
    DataNode OnScreenDumpUnique(const DataArray*);
    DataNode OnScaleObject(const DataArray*);
    DataNode OnReflect(const DataArray*);
};

extern Rnd* TheRnd;

#endif // RNDOBJ_RND_H