#ifndef BANDTRACK_GEMSMASHER_H
#define BANDTRACK_GEMSMASHER_H

#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Mesh.h"
#include <vector>

class GemSmasher {
public:
    GemSmasher(int, RndDir*, bool);
    ~GemSmasher();
    void Reset(bool);

    int mSlot; // 0x0
    RndDir* mDir; bool Null() const; bool Showing() const; // 0x4
    EventTrigger* mHitSmashTrig; void Hit(); // 0x8
    EventTrigger* mHitDrumsTrig; void HitDrum(); // 0xC
    EventTrigger* mHitDrumsBonus; void HitDrumBonus(); // 0x10
    EventTrigger* mHitCymsTrig; void HitCymbal(); // 0x14
    EventTrigger* mHitCymsBonus; void HitCymbalBonus(); // 0x18
    EventTrigger* mHitChordTrig; void HitChord(); // 0x1C
    EventTrigger* mHitChordBonus; void HitChordBonus(); // 0x20
    EventTrigger* mHitBonus; void HitBonus(); // 0x24
    EventTrigger* mBREHitTrig; void CodaHit(); // 0x28
    EventTrigger* mBREHitChord; void CodaHitChord(); // 0x2C
    EventTrigger* mMissTrig; void Miss(); // 0x30
    EventTrigger* mBurnTrig; void Burn(); // 0x34
    EventTrigger* mBurnBonusTrig; void BurnBonus(); // 0x38
    EventTrigger* mBurnChordTrig; void BurnChord(); // 0x3C
    EventTrigger* mBREBurnTrig; void CodaBurn(); // 0x40
    EventTrigger* mBREBurnChord; void CodaBurnChord(); // 0x44
    EventTrigger* mStopBurnTrig; void StopBurn(); // 0x48
    EventTrigger* mHitFillTrig; void FillHit(int); // 0x4C
    std::vector<EventTrigger*> mMoreTriggers; // 0x50
    EventTrigger* mPressTrig; // 0x58
    EventTrigger* mReleaseTrig; // 0x5C
    EventTrigger* mMissAfterRelease; // 0x60
    RndMesh* mGemSmasherGlow; // 0x64
    bool mGlowing, mBurning, unk_0x6A; bool Glowing() const; void SetGlowing(bool); // 0x68, 0x69, 0x6A
};

#endif // BANDTRACK_GEMSMASHER_H
