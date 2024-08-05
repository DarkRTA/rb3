#ifndef CHAR_CHARCLIPDISPLAY_H
#define CHAR_CHARCLIPDISPLAY_H
#include "obj/Object.h"
#include "char/CharClip.h"

class MsgSource;

class CharClipDisplay {
public:

    MsgSource* FindSource(Hmx::Object*);
    void SetClip(CharClip*, bool);
    void SetText(const char*);
    void SetStartEnd(float, float, bool);

    static void Init(ObjectDir*);
    static float LineSpacing();

    static float sZoom;
    static float sEm;
    static ObjectDir* sDir;

    CharClip* unk0;
    float unk4;
    float unk8;
    float unkc;
    float unk10;
    float unk14;
    int unk18;
    int unk1c;
    int unk20;
    char* unk24;
};

#endif