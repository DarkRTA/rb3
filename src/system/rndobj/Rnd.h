#ifndef RNDOBJ_RND_H
#define RNDOBJ_RND_H

#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Console.h"
#include "rndobj/Draw.h"
#include "rndobj/Overlay.h"

class Rnd : public Hmx::Object, public RndOverlay::Callback { // there's some multiple inheritance bs goin on here and i don't like it
public:
    struct PointTest {
        
    };
    Rnd();
    virtual ~Rnd() {}
    virtual DataNode Handle(DataArray*, bool);

    virtual float UpdateOverlay(RndOverlay*, float);

    float unk_0x20, unk_0x24, unk_0x28, unk_0x2C;
    int mWidth, mHeight; // 0x30, 0x34
    int mScreenBpp; // 0x38
    int unk_0x3C;
    Timer mFrameTimer; // 0x40

    RndOverlay* unk_0x70, *unk_0x74, *unk_0x78;
    RndConsole* mConsole; // 0x80

    int mAspectRatio; // 0xE0

    ObjPtrList<RndDrawable, ObjectDir> mDraws; // 0x120

    void PreInit(); void Init(); void Terminate(); void ReInit();
    void ShowConsole(bool); bool ConsoleShowing();
    void SetShowTimers(bool, bool);
    void UpdateRate(); void UpdateHeap();
    float DrawTimers(float);
    float YRatio();

    DataNode OnScreenDump(const DataArray*);
    DataNode OnScreenDumpUnique(const DataArray*);
    DataNode OnScaleObject(const DataArray*);
    DataNode OnReflect(const DataArray*);
};

#endif // RNDOBJ_RND_H