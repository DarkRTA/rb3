#pragma once
#include "game/Defines.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "ui/UILabel.h"

class Instarank : public virtual Hmx::Object {
public:
    // for SOME reason, for this specific TU, the class members are declared before the
    // virtual funcs
    bool mIsValid; // 0x4
    int unk8; // 0x8 - id?
    bool unkc; // 0xc - is_boi?
    ScoreType mScoreType; // 0x10
    int mInstaRank; // 0x14
    bool mIsPercentile; // 0x18
    String mStr1; // 0x1c
    String mStr2; // 0x28

    Instarank();
    virtual ~Instarank() {}

    void Clear();
    void Init(int, bool, ScoreType, int, bool, String, String);
    void UpdateRankLabel(UILabel *);
    bool HasHighscore() const;
    void UpdateString1Label(UILabel *);
    void UpdateString2Label(UILabel *);
};

DECLARE_MESSAGE(InstarankDoneMsg, "instarank_done")
InstarankDoneMsg() : Message(Type()) {}
END_MESSAGE