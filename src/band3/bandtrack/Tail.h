#pragma once
#include "bandtrack/GemRepTemplate.h"

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
    void
    Init(int, const Transform &, bool, Symbol, RndGroup *, const SlideInfo &, Tail *);
};
