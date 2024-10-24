#pragma once
#include "game/Defines.h"
#include "obj/Object.h"
#include "ui/UILabel.h"

class Instarank : public virtual Hmx::Object {
public:
    // for SOME reason, for this specific TU, the class members are declared before the virtual funcs
    bool mIsValid; // 0x4
    int unk8;
    bool unkc;
    ScoreType unk10;
    int unk14;
    bool unk18;
    String unk1c;
    String unk28;

    Instarank();
    virtual ~Instarank(){}

    void Clear();
    void Init(int, bool, ScoreType, int, bool, String, String);
    void UpdateRankLabel(UILabel*);
    bool HasHighscore() const;
    void UpdateString1Label(UILabel*);
    void UpdateString2Label(UILabel*);
};