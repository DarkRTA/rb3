#include "meta_band/MetaPerformer.h"
#include "game/Performer.h"
#include "meta_band/Utl.h"

MetaPerformer* MetaPerformer::sMetaPerformer;

PerformerStatsInfo::PerformerStatsInfo() : mInstrumentMask(0), mScoreType(kScoreBand), unkc(-1), unk10(-1), mDifficulty(kDifficultyEasy), mScore(0), mStars(0), mAccuracy(0), mStreak(0), mAwesomes(0), mDoubleAwesomes(0),
    mTripleAwesomes(0), mSoloPercent(0), unk38(0), mUnisonPhrasesHit(0) {

}

PerformerStatsInfo::~PerformerStatsInfo(){

}

void PerformerStatsInfo::Clear(){
    mInstrumentMask = 0;
    unkc = -1;
    unk10 = -1;
    mScoreType = kScoreBand;
    mDifficulty = kDifficultyEasy;
    mScore = 0;
    mStars = 0;
    mAccuracy = 0;
    mStreak = 0;
    mAwesomes = 0;
    mDoubleAwesomes = 0;
    mTripleAwesomes = 0;
    mSoloPercent = 0;
    unk38 = 0;
    mUnisonPhrasesHit = 0;
}

void PerformerStatsInfo::Update(int i1, int i2, ScoreType ty, Difficulty diff, short s, Performer* performer){
    MILO_ASSERT(!performer->GetQuarantined(), 0x62);
    Stats& stats = performer->mStats;
    unkc = i1;
    unk10 = i2;
    mInstrumentMask = s;
    mScoreType = ty;
    mDifficulty = diff;
    if(ty == kScoreBand) mScore = performer->GetScore();
    else mScore = performer->GetIndividualScore();
    mStars = performer->GetNumStars();
    mAccuracy = performer->GetNotesHitFraction(0) * 100.0f;
    mStreak = stats.GetLongestStreak();
    mAwesomes = stats.mHitCount;
    mDoubleAwesomes = stats.mDoubleHarmonyHit;
    mTripleAwesomes = stats.mTripleHarmonyHit;
    mSoloPercent = stats.mSoloPercentage;
    unk38 = ((float)stats.mHopoGemInfo1 / (float)stats.mHopoGemInfo3) * 100.0f;
    mUnisonPhrasesHit = stats.mUnisonPhraseCompleted;
}

BandStatsInfo::BandStatsInfo(){}

BandStatsInfo::~BandStatsInfo(){ Clear(); }

void BandStatsInfo::Clear(){
    mSoloStats.clear();
    mBandStats.Clear();
}

void BandStatsInfo::UpdateBandStats(Difficulty d, short s, Performer* p){
    mBandStats.Update(-1, -1, kScoreBand, d, s, p);
}

const PerformerStatsInfo& BandStatsInfo::GetBandStats() const { return mBandStats; }

BandProfile* BandStatsInfo::GetSoloProfile(int index) const {
    MILO_ASSERT(index < mSoloStats.size(), 0xB6);
    BandProfile* profile = mSoloStats[index].first;
    MILO_ASSERT(profile, 0xBB);
    return profile;
}

const PerformerStatsInfo& BandStatsInfo::GetSoloStats(int index) const {
    MILO_ASSERT(index < mSoloStats.size(), 0xC3);
    return mSoloStats[index].second;
}

QuickplayPerformerImpl::QuickplayPerformerImpl(){}
bool QuickplayPerformerImpl::IsRandomSetList() const { return false; }
bool QuickplayPerformerImpl::HasSyncPermission() const { return IsLeaderLocal(); }

void MetaPerformer::Init(){
    MILO_ASSERT(!sMetaPerformer, 0xE9);
    sMetaPerformer = new MetaPerformer(*TheSongMgr, "meta_performer");
}