#include "Stats.h"
#include "game/Performer.h"
#include "game/GameConfig.h"
#include "game/BandUser.h"

Performer::Performer(BandUser* user, Band* band) : unk8(0), unk10(Stats()), unk1dc(band), unk1e0(0), unk1e1(0), unk1e2(0), unk1e4(0), unk1fc(0), unk1fd(1), unk1fe(1), unk1ff(1), unk200(0),
    unk204(0), unk205(1), unk208(0) {
    Difficulty diff = !user ? TheGameConfig->GetAverageDifficulty() : user->GetDifficulty();
    unkc = new CrowdRating(user, diff);
}

SongPos::SongPos() : mTotalTick(0), mMeasure(0), mBeat(0), mTick(0) {}

// Stats::Stats(const Stats& copy) {
//     mHitCount = copy.mHitCount;
//     mMissCount = copy.mMissCount;
//     m0x08 = copy.m0x08;
//     m0x0c = copy.m0x0c;
//     m0x10 = copy.m0x10;
//     m0x14 = copy.m0x14;
//     mNotesHitFraction = copy.mNotesHitFraction;
//     mFailedDeploy = copy.mFailedDeploy;
//     mDeployCount = copy.mDeployCount;
//     mFillHitCount = copy.mFillHitCount;
//     m0x28 = copy.m0x28;
//     m0x2c = copy.m0x2c;
//     m0x30 = copy.m0x30;
//     m0x34 = copy.m0x34;
//     mFinalized = copy.mFinalized;
//     mSoloPercentage = copy.mSoloPercentage;
//     m0x3c = copy.m0x3c;
//     mPerfectSoloWithSoloButtons = copy.mPerfectSoloWithSoloButtons;
//     m0x41 = copy.m0x41;
//     mNumberOfSingers = copy.mNumberOfSingers;
//     m0x48 = copy.m0x48;
//     mDoubleHarmonyHit = copy.mDoubleHarmonyHit;
//     mDoubleHarmonyPhraseCount = copy.mDoubleHarmonyPhraseCount;
//     mTripleHarmonyHit = copy.mTripleHarmonyHit;
//     mTripleHarmonyPhraseCount = copy.mTripleHarmonyPhraseCount;
//     m0x5c = copy.m0x5c;
//     m0x60 = copy.m0x60;
//     m0x64 = copy.m0x64;
//     m0x68 = copy.m0x68;
//     m0x6c = copy.m0x6c;
//     m0x70 = copy.m0x70;
//     m0x78 = copy.m0x78;

// }

Performer::~Performer(){
    RELEASE(unkc);
}

int Stats::GetDoubleHarmonyHit() const { return mDoubleHarmonyHit; }
int Stats::GetDoubleHarmonyPhraseCount() const { return mDoubleHarmonyPhraseCount; }
int Stats::GetTripleHarmonyHit() const { return mTripleHarmonyHit; }
int Stats::GetTripleHarmonyPhraseCount() const { return mTripleHarmonyPhraseCount; }
int Stats::GetHitCount() const { return mHitCount; }
float Stats::GetNotesHitFraction() const { return mNotesHitFraction; }
int Stats::GetNumberOfSingers() const { return mNumberOfSingers; }
void Stats::GetVocalPartPercentage(int) const {}    
bool Stats::GetFailedDeploy() const { return mFailedDeploy; }
int Stats::GetPlayersSaved() const { return mPlayersSaved; }
int Stats::GetFillHitCount() const { return mFillHitCount; }
void Stats::GetStrummedDown() const {}
void Stats::GetStrummedUp() const {}
int Stats::GetDeployCount() const { return mDeployCount; }
int Stats::GetSoloPercentage() const { return mSoloPercentage; }
bool Stats::GetPerfectSoloWithSoloButtons() const { return mPerfectSoloWithSoloButtons; }
bool Stats::GetFinalized() const { return mFinalized; }