#pragma once
#include "bandtrack/DelayLine.h"
#include "bandtrack/GemRepTemplate.h"
#include "math/Interp.h"
#include "rndobj/Group.h"
#include "rndobj/Mesh.h"

class Tail {
public:
    struct SlideInfo {
        SlideInfo() : unk0(0), unk4(0), unk8(0), unkc(0) {}
        bool unk0;
        float unk4;
        float unk8;
        float unkc;
    };

    Tail(GemRepTemplate &);
    virtual ~Tail();

    void Hit();
    void Release();
    void Done();
    void Poll(float, float, float);
    void SetDuration(float, float, float);
    void SetType(Symbol, bool);
    void
    Init(int, const Transform &, bool, Symbol, RndGroup *, const SlideInfo &, Tail *);
    void ReleaseMeshes();
    void ConfigureMeshes(Tail *);
    void UpdateVerts(float, bool);
    void MoveSlot(const Transform &);
    void HandleMistake();

    RndGroup *mGroup; // 0x4
    RndMesh *mTail1; // 0x8
    RndMesh *mTail2; // 0xc
    float unk10; // 0x10
    Symbol unk14; // 0x14
    int mState; // 0x18 - state?
    int mSlot; // 0x1c
    GemRepTemplate &mTemplate; // 0x20
    RndMesh *mTailGeomOwner; // 0x24
    bool unk28; // 0x28
    DelayLine<float, 300> mWhammy; // 0x2c
    float unk4e0; // 0x4e0
    float unk4e4; // 0x4e4
    float unk4e8; // 0x4e8
    float unk4ec; // 0x4ec
    float unk4f0; // 0x4f0
    bool unk4f4; // 0x4f4
    SlideInfo mSlideInfo; // 0x4f8
    ATanInterpolator mInterpolator; // 0x508
};
