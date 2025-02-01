#pragma once
#include "obj/Object.h"
#include "char/CharClip.h"

class MsgSource;

class CharClipDisplay { // size 0x68
public:
    CharClipDisplay()
        : unk0(0), unk4(0), unk8(0), unkc(0), unk10(0), unk14(0), unk18(0), unk1c(0),
          unk20(0), unk64(0) {}

    MsgSource *FindSource(Hmx::Object *);
    void SetClip(CharClip *, bool);
    void SetText(const char *);
    void SetStartEnd(float, float, bool);

    static void Init(ObjectDir *);
    static float LineSpacing();

    static float sZoom;
    static float sEm;
    static ObjectDir *sDir;

    CharClip *unk0;
    float unk4;
    float unk8;
    float unkc;
    float unk10;
    float unk14;
    float unk18;
    float unk1c;
    float unk20;
    char *unk24;
    int unk28;
    int unk2c;
    int unk30;
    int unk34;
    int unk38;
    int unk3c;
    int unk40;
    int unk44;
    int unk48;
    int unk4c;
    int unk50;
    int unk54;
    int unk58;
    int unk5c;
    int unk60;
    float unk64;
};
