#pragma once
#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Mesh.h"
#include <vector>

class GemSmasher {
public:
    GemSmasher(int, RndDir *, bool);
    ~GemSmasher();
    void Reset(bool);
    RndDir *Dir() const { return mDir; }
    bool Null() const;
    bool Showing() const;
    void Hit();
    void HitDrum();
    void HitDrumBonus();
    void HitCymbal();
    void HitCymbalBonus();
    void HitChord();
    void HitChordBonus();
    void HitBonus();
    void CodaHit();
    void CodaHitChord();
    void Miss();
    void Burn();
    void BurnBonus();
    void BurnChord();
    void CodaBurn();
    void CodaBurnChord();
    void StopBurn();
    void FillHit(int);
    bool Glowing() const;
    void SetGlowing(bool);

    int mSlot; // 0x0
    RndDir *mDir; // 0x4
    EventTrigger *mHitSmashTrig; // 0x8
    EventTrigger *mHitDrumsTrig; // 0xc
    EventTrigger *mHitDrumsBonus; // 0x10
    EventTrigger *mHitCymsTrig; // 0x14
    EventTrigger *mHitCymsBonus; // 0x18
    EventTrigger *mHitChordTrig; // 0x1c
    EventTrigger *mHitChordBonus; // 0x20
    EventTrigger *mHitBonus; // 0x24
    EventTrigger *mBREHitTrig; // 0x28
    EventTrigger *mBREHitChord; // 0x2c
    EventTrigger *mMissTrig; // 0x30
    EventTrigger *mBurnTrig; // 0x34
    EventTrigger *mBurnBonusTrig; // 0x38
    EventTrigger *mBurnChordTrig; // 0x3c
    EventTrigger *mBREBurnTrig; // 0x40
    EventTrigger *mBREBurnChord; // 0x44
    EventTrigger *mStopBurnTrig; // 0x48
    EventTrigger *mHitFillTrig; // 0x4c
    std::vector<EventTrigger *> mMoreTriggers; // 0x50
    EventTrigger *mPressTrig; // 0x58
    EventTrigger *mReleaseTrig; // 0x5C
    EventTrigger *mMissAfterRelease; // 0x60
    RndMesh *mGemSmasherGlow; // 0x64
    bool mGlowing; // 0x68
    bool mBurning; // 0x69
    bool mIsKeyboardTrack; // 0x6a - is keyboard track?
};
