#include "Stats.h"
#include "math/MathFuncs.h"

Stats::Stats() : mHitCount(0), mMissCount(0), m0x08(0), m0x0c(0), mPersistentStreak(0), mLongestPersistentStreak(0), mNotesHitFraction(0), mFailedDeploy(0), mDeployCount(0), mFillHitCount(0), m0x28(0), m0x2c(0),
    m0x30(0), m0x34(0), mFinalized(0), mSoloPercentage(0), m0x3c(0), mPerfectSoloWithSoloButtons(0), m0x41(0), mNumberOfSingers(0), m0x48(0), mDoubleHarmonyHit(0), mDoubleHarmonyPhraseCount(0),
    mTripleHarmonyHit(0), mTripleHarmonyPhraseCount(0), m0x5c(0), m0x60(0), m0x64(0), m0x68(0), m0x6c(0), mAccuracy(0), m0x8c(0), mSolo(0), mOverdrive(0), mSustain(0), mScoreStreak(0),
    mBandContribution(0), mCodaPoints(0), m0xa8(0), m0x09(0), mTambourine(0), mHarmony(0), m0xb4(0), m0xb8(0), unkc4(3), unkd4(3), unkdc(3, -1.0f), unke4(3, -1.0f), mPlayersSaved(0),
    unkf0(3, 2.0f), mTimesSaved(0), unkfc(3, 2.0f), unk104(3, -1), unk120(3), mTotalOverdriveDuration(0), unk140(3), mTotalMultiplierDuration(0), m0x14c(0), m0x150(0), mEndGameScore(0),
    mEndGameCrowdLevel(0), mEndGameOverdrive(0), mOverdrivePhrasesCompleted(0), mOverdrivePhraseCount(0), mUnisonPhraseCompleted(0), mUnisonPhraseCount(0), mHopoGemInfo1(0), mHopoGemInfo2(0),
    mHopoGemInfo3(0), mHighGemsHitHigh(0), mHighGemsHitLow(0), mHighFretGemCount(0), mSustainGemsHitCompletely(0), mSustainGemsHitPartially(0), mSustainGemCount(0), m0x194(0), mRollCount(0),
    mRollsHitCompletely(0), mTrillCount(0), mTrillsHitCompletely(0), mTrillsHitPartially(0), mSymbolGemInfo1(0), mSymbolGemInfo2(0), mSymbolGemInfo3(0), unk1c0(0), unk1c4(0), unk1c8(0) {

}

void Stats::BuildHitStreak(int i, float f) {
    mHitCount++;
    unk1c8 += f;
    BuildStreak(unkbc, i);
    mPersistentStreak++;
    mLongestPersistentStreak = Max(mLongestPersistentStreak, mPersistentStreak);
}

int Stats::GetCurrentStreak() const {
    return unkbc.mDuration;
}

void Stats::SetCurrentStreak(int currentStreak) {
    unkbc.mDuration = currentStreak;
}

int Stats::GetLongestStreak() const {
    return unkc4[0].mDuration;
}

void Stats::SetPersistentStreak(int i) {
    mPersistentStreak = i;
    mLongestPersistentStreak = Max(mLongestPersistentStreak, i);
}

void Stats::EndHitStreak() {
    EndStreak(unkbc, unkc4);
    mPersistentStreak = 0;
}

void Stats::BuildMissStreak(int i) {
    mMissCount++;
    BuildStreak(unkcc, i);
}

void Stats::EndMissStreak() {
    EndStreak(unkcc, unkd4);
}

void Stats::BuildStreak(Stats::StreakInfo& info, int i) {
    if(info.mDuration == 0) info.mStart = i;
    info.mDuration++;
}

void Stats::EndStreak(Stats::StreakInfo& info, std::vector<Stats::StreakInfo>& vec) {
    if(info.mDuration > 0) SaveHighest(vec, info);
    info = StreakInfo();
}

template <class T>
void Stats::SaveHighest(std::vector<T>& vec, const T& item){
    std::vector<T>::iterator it;
    for(it = vec.begin(); it != vec.end(); ++it){
        if(*it > item){
            it = vec.erase(it);
            vec.insert(it, item);
            break;
        }
    }
}

void Stats::SetFinalized(bool b){
    mFinalized = b;
    if(b){
        for(int i = 0; i < m0x78.size(); i++){
            m0x78[i].Finalize();
        }
    }
}

void Stats::UpdateBestSolo(int i){
    int item = i;
    SaveHighest(unk104, item);
    int& asdf = unk104[0];
    MaxEq(asdf, 0);
    mSoloPercentage = asdf;
}

void Stats::SetSoloButtonedSoloPercentage(int i){
    if(m0x3c < i) m0x3c = i;
}

void Stats::SetVocalSingerAndPartCounts(int, int) {}
void Stats::SetSingerPartPercentage(int, int, float) {}

void Stats::GetSingerRankedPercentage(int, int) const {}

void Stats::GetSingerRankedPart(int, int) const {}

void Stats::SetSingerPitchDeviationInfo(int, float, float) {}
void Stats::UpdateBestTambourineSection(int) {}
void Stats::SaveForEndGame(BinStream&) const {}
void Stats::LoadForEndGame(BinStream&) {}
void Stats::SaveSingerStats(BinStream&) const {}
void Stats::LoadSingerStats(BinStream&) {}

void Stats::AddAccuracy(int accuracy) { mAccuracy += accuracy; }
void Stats::AddOverdrive(float overdrive) { mOverdrive += overdrive;}
void Stats::AddSolo(int solo) { mSolo += solo;}
void Stats::AddSustain(float sustain) { mSustain += sustain; }
void Stats::AddScoreStreak(float scoreStreak) { mScoreStreak += scoreStreak; }
void Stats::AddBandContribution(float bandContribution ) { mBandContribution += bandContribution; }
void Stats::AddCodaPoints(int codaPoints) { mCodaPoints += codaPoints; }
void Stats::AddTambourine(float tambourine) { mTambourine += tambourine; }
void Stats::AddHarmony(int harmony) { mHarmony += harmony; }

int Stats::GetAccuracy() const { return mAccuracy; }
float Stats::GetOverdrive() const { return mOverdrive; }
int Stats::GetSolo() const { return mSolo; }
float Stats::GetSustain() const { return mSustain; }
float Stats::GetScoreStreak() const { return mScoreStreak; }
float Stats::GetBandContribution() const { return mBandContribution; }
int Stats::GetCodaPoints() const { return mCodaPoints; }
float Stats::GetTambourine() const { return mTambourine; }
int Stats::GetHarmony() const { return mHarmony; }

void Stats::SetNoScorePercent(float) {}
void Stats::FailedNoScore() const {}
void Stats::AddFailurePoint(float) {}
void Stats::AddToPlayersSaved(int, float) {}
void Stats::AddToTimesSaved(float, float) {}
void Stats::DeployOverdrive(float, int) {}
void Stats::StopDeployingOverdrive(float, int) {}
void Stats::BeginStreakMultiplier(float, int) {}
void Stats::EndStreakMultiplier(float, int) {}
void Stats::BeginMultiplier(Stats::MultiplierInfo&, float, int, float) {}
void Stats::EndMultiplier(Stats::MultiplierInfo&, std::vector<Stats::MultiplierInfo>&, float, int, float, float&) {}

void Stats::GetUnisonPhrasePercent() const {}

void Stats::SetHopoGemInfo(int, int, int) {}
void Stats::IncrementHighFretGemsHit(bool) {}
void Stats::IncrementSustainGemsHit(bool) {}
void Stats::AddRoll(bool) {}
void Stats::IncrementTrillsHit(bool) {}
void Stats::SetCymbalGemInfo(int, int, int) {}
void Stats::SetSectionInfo(int, Symbol, float, float) {}

void Stats::GetSectionInfo(int) const {}

void Stats::GetAverageMsError() const {}

SingerStats::SingerStats(int) {}
void SingerStats::Finalize() {}
void SingerStats::SetPartPercentage(int, float) {}
void SingerStats::GetRankData(int) const {}

void SingerStats::SetPitchDeviationInfo(float param_1, float param_2) {
    mPitchDeviation1 = param_1;
    mPitchDeviation2 = param_2;
}

void SingerStats::GetPitchDeviationInfo(float&, float&) const {}


Stats::StreakInfo::StreakInfo() : mStart(-1), mDuration(0) {}

BinStream& operator<<(BinStream& bs, const Stats::StreakInfo& info){
    bs << info.mStart;
    bs << info.mDuration;
    return bs;
}

BinStream& operator>>(BinStream& bs, Stats::StreakInfo& info){
    bs >> info.mStart;
    bs >> info.mDuration;
    return bs;
}

Stats::MultiplierInfo::MultiplierInfo() : mStartMs(-1.0f), mDurationMs(0), mStartingMultiplier(0), mEndingMultiplier(0), mPoints(0) {}

bool operator>(const Stats::MultiplierInfo& info1, const Stats::MultiplierInfo& info2){
    if(info1.mPoints == info2.mPoints){
        return info1.mDurationMs < info2.mDurationMs;
    }
    else return info1.mPoints < info2.mPoints;
}

Stats::SectionInfo::SectionInfo() : unk4(-1.0f), unk8(0) {}

BinStream& operator<<(BinStream& bs, const Stats::SectionInfo& info){
    bs << info.unk0;
    bs << info.unk4;
    bs << info.unk8;
    return bs;
}

BinStream& operator>>(BinStream& bs, Stats::SectionInfo& info){
    bs >> info.unk0;
    bs >> info.unk4;
    bs >> info.unk8;
    return bs;
}