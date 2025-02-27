#include "Stats.h"
#include "decomp.h"
#include "math/Utl.h"
#include "os/Debug.h"
#include <algorithm>

DECOMP_FORCEACTIVE(
    Stats,
    __FILE__,
    "index < mHitStreaks.size()",
    "index < mFailurePoints.size()",
    "index < mSavedPoints.size()",
    "index < mClosestPlayersSaved.size()",
    "index < mClosestTimesSaved.size()",
    "index < mBestOverdriveDeployments.size()",
    "index < mBestStreakMultipliers.size()"
)

Stats::Stats()
    : mHitCount(0), mMissCount(0), m0x08(0), m0x0c(0), mPersistentStreak(0),
      mLongestPersistentStreak(0), mNotesHitFraction(0), mFailedDeploy(0),
      mDeployCount(0), mFillHitCount(0), mUpstrumCount(0), mDownstrumCount(0), m0x30(0),
      m0x34(0), mFinalized(0), mSoloPercentage(0), mSoloButtonedSoloPercentage(0),
      mPerfectSoloWithSoloButtons(0), m0x41(0), mSingerCount(0), mVocalPartCount(0),
      mDoubleHarmonyHit(0), mDoubleHarmonyPhraseCount(0), mTripleHarmonyHit(0),
      mTripleHarmonyPhraseCount(0), m0x5c(0), mTambourineCount(0), mTambourineHitCount(0),
      m0x68(0), m0x6c(0), mAccuracy(0), m0x8c(0), mSolo(0), mOverdrive(0), mSustain(0),
      mScoreStreak(0), mBandContribution(0), mCodaPoints(0), mHasCoda(0), mHasSolos(0),
      mTambourine(0), mHarmony(0), mFullCombo(0), mNoScorePercent(0), mHitStreaks(3),
      mMissStreaks(3), mFailurePoints(3, -1.0f), mSavedPoints(3, -1.0f), mPlayersSaved(0),
      mClosestPlayersSaved(3, 2.0f), mTimesSaved(0), mClosestTimesSaved(3, 2.0f),
      mBestSolos(3, -1), mBestOverdriveDeployments(3), mTotalOverdriveDurationMs(0),
      mBestStreakMultipliers(3), mTotalMultiplierDuration(0), m0x14c(0), m0x150(0),
      mEndGameScore(0), mEndGameCrowdLevel(0), mEndGameOverdrive(0),
      mOverdrivePhrasesCompleted(0), mOverdrivePhraseCount(0), mUnisonPhraseCompleted(0),
      mUnisonPhraseCount(0), mHopoGemsHopoed(0), mHopoGemsStrummed(0), mHopoGemCount(0),
      mHighGemsHitHigh(0), mHighGemsHitLow(0), mHighFretGemCount(0),
      mSustainGemsHitCompletely(0), mSustainGemsHitPartially(0), mSustainGemCount(0),
      mAverageMultiplier(0), mRollCount(0), mRollsHitCompletely(0), mTrillCount(0),
      mTrillsHitCompletely(0), mTrillsHitPartially(0), mCymbalGemInfo1(0),
      mCymbalGemInfo2(0), mCymbalGemInfo3(0), unk1c0(0), unk1c4(0), unk1c8(0) {}

void Stats::BuildHitStreak(int i, float f) {
    mHitCount++;
    unk1c8 += f;
    BuildStreak(mCurrentHitStreak, i);
    mPersistentStreak++;
    mLongestPersistentStreak = Max(mLongestPersistentStreak, mPersistentStreak);
}

int Stats::GetCurrentStreak() const { return mCurrentHitStreak.mDuration; }

void Stats::SetCurrentStreak(int currentStreak) {
    mCurrentHitStreak.mDuration = currentStreak;
}

int Stats::GetLongestStreak() const { return mHitStreaks[0].mDuration; }

void Stats::SetPersistentStreak(int i) {
    mPersistentStreak = i;
    mLongestPersistentStreak = Max(mLongestPersistentStreak, i);
}

void Stats::EndHitStreak() {
    EndStreak(mCurrentHitStreak, mHitStreaks);
    mPersistentStreak = 0;
}

void Stats::BuildMissStreak(int i) {
    mMissCount++;
    BuildStreak(mCurrentMissStreak, i);
}

void Stats::EndMissStreak() { EndStreak(mCurrentMissStreak, mMissStreaks); }

void Stats::BuildStreak(Stats::StreakInfo &info, int i) {
    if (info.mDuration == 0)
        info.mStart = i;
    info.mDuration++;
}

void Stats::EndStreak(Stats::StreakInfo &info, std::vector<Stats::StreakInfo> &vec) {
    if (info.mDuration > 0)
        SaveHighest(vec, info);
    info = StreakInfo();
}

void Stats::SetFinalized(bool b) {
    mFinalized = b;
    if (b) {
        for (int i = 0; i < mSingerStats.size(); i++) {
            mSingerStats[i].Finalize();
        }
    }
}

void Stats::UpdateBestSolo(int i) {
    int item = i;
    SaveHighest(mBestSolos, item);
    int &asdf = mBestSolos[0];
    MaxEq(asdf, 0);
    mSoloPercentage = asdf;
}

void Stats::SetSoloButtonedSoloPercentage(int i) {
    if (mSoloButtonedSoloPercentage < i)
        mSoloButtonedSoloPercentage = i;
}

void Stats::SetVocalSingerAndPartCounts(int i, int j) {
    mSingerCount = i;
    mVocalPartCount = j;
    mVocalPartPercentages.resize(j);
    mSingerStats.clear();
    for (int x = 0; x < i; x++) {
        mSingerStats.push_back(SingerStats(j));
    }
}

void Stats::SetSingerPartPercentage(int i, int j, float f) {
    mSingerStats[i].SetPartPercentage(j, f);
}

float Stats::GetSingerRankedPercentage(int i, int j) const {
    return mSingerStats[i].unk0[j].second;
}

int Stats::GetSingerRankedPart(int i, int j) const {
    return mSingerStats[i].unk0[j].first;
}

void Stats::SetSingerPitchDeviationInfo(int i, float f1, float f2) {
    mSingerStats[i].SetPitchDeviationInfo(f1, f2);
}

void Stats::UpdateBestTambourineSection(int i) { MaxEq(m0x5c, i); }

void Stats::SaveForEndGame(BinStream &bs) const {
    bs << mHitCount;
    bs << mHitStreaks;
    bs << mPersistentStreak;
    bs << mLongestPersistentStreak;
    bs << mNotesHitFraction;
    bs << mAverageMultiplier;
    bs << mFailedDeploy;
    bs << mPlayersSaved;
    bs << mFillHitCount;
    bs << mDownstrumCount;
    bs << mUpstrumCount;
    bs << mDeployCount;
    bs << mSoloPercentage;
    bs << mDoubleHarmonyHit;
    bs << mDoubleHarmonyPhraseCount;
    bs << mTripleHarmonyHit;
    bs << mTripleHarmonyPhraseCount;
    bs << mSingerCount;
    bs << mVocalPartCount;
    bs << mAccuracy;
    bs << m0x8c;
    bs << mOverdrive;
    bs << mSolo;
    bs << mSustain;
    bs << mScoreStreak;
    bs << mBandContribution;
    bs << mCodaPoints;
    bs << mHasCoda;
    bs << mHasSolos;
    bs << mOverdrivePhrasesCompleted;
    bs << mOverdrivePhraseCount;
    bs << mUnisonPhraseCompleted;
    bs << mUnisonPhraseCount;
    bs << mTambourine;
    bs << mHarmony;
    bs << mFullCombo;
    bs << mNoScorePercent;
    bs << mSections;
    bs << unk1c0;
    bs << unk1c4;
    bs << unk1c8;
    SaveSingerStats(bs);
}

void Stats::LoadForEndGame(BinStream &bs) {
    bs >> mHitCount;
    bs >> mHitStreaks;
    bs >> mPersistentStreak;
    bs >> mLongestPersistentStreak;
    bs >> mNotesHitFraction;
    bs >> mAverageMultiplier;
    bs >> mFailedDeploy;
    bs >> mPlayersSaved;
    bs >> mFillHitCount;
    bs >> mDownstrumCount;
    bs >> mUpstrumCount;
    bs >> mDeployCount;
    bs >> mSoloPercentage;
    bs >> mDoubleHarmonyHit;
    bs >> mDoubleHarmonyPhraseCount;
    bs >> mTripleHarmonyHit;
    bs >> mTripleHarmonyPhraseCount;
    bs >> mSingerCount;
    bs >> mVocalPartCount;
    bs >> mAccuracy;
    bs >> m0x8c;
    bs >> mOverdrive;
    bs >> mSolo;
    bs >> mSustain;
    bs >> mScoreStreak;
    bs >> mBandContribution;
    bs >> mCodaPoints;
    bs >> mHasCoda;
    bs >> mHasSolos;
    bs >> mOverdrivePhrasesCompleted;
    bs >> mOverdrivePhraseCount;
    bs >> mUnisonPhraseCompleted;
    bs >> mUnisonPhraseCount;
    bs >> mTambourine;
    bs >> mHarmony;
    bs >> mFullCombo;
    bs >> mNoScorePercent;
    bs >> mSections;
    bs >> unk1c0;
    bs >> unk1c4;
    bs >> unk1c8;
    LoadSingerStats(bs);
}

void Stats::SaveSingerStats(BinStream &bs) const {
    for (int i = 0; i < mSingerCount; i++) {
        const SingerStats &stats = mSingerStats[i];
        for (int j = 0; j < mVocalPartCount; j++) {
            const std::pair<int, float> &p = stats.unk0[j];
            bs << p.first;
            bs << p.second;
        }
        float f1, f2;
        stats.GetPitchDeviationInfo(f1, f2);
        bs << f1;
        bs << f2;
    }
}

void Stats::LoadSingerStats(BinStream &bs) {
    for (int i = 0; i < mSingerCount; i++) {
        SingerStats singerStats(mVocalPartCount);
        for (int j = 0; j < mVocalPartCount; j++) {
            int part;
            float pct;
            bs >> part;
            bs >> pct;
            singerStats.SetPartPercentage(part, pct);
        }
        float dev1, dev2;
        bs >> dev1;
        bs >> dev2;
        singerStats.SetPitchDeviationInfo(dev1, dev2);
        singerStats.Finalize();
        mSingerStats.push_back(singerStats);
    }
}

void Stats::AddAccuracy(int accuracy) { mAccuracy += accuracy; }
void Stats::AddOverdrive(float overdrive) { mOverdrive += overdrive; }
void Stats::AddSolo(int solo) { mSolo += solo; }
void Stats::AddSustain(float sustain) { mSustain += sustain; }
void Stats::AddScoreStreak(float scoreStreak) { mScoreStreak += scoreStreak; }
void Stats::AddBandContribution(float bandContribution) {
    mBandContribution += bandContribution;
}
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

void Stats::SetNoScorePercent(float pct) {
    *this = Stats();
    mNoScorePercent = pct;
}

bool Stats::FailedNoScore() const { return mNoScorePercent != 0; }

void Stats::AddFailurePoint(float fp) { SaveNewest(mFailurePoints, fp); }
void Stats::AddToPlayersSaved(int i, float f) {
    if (i > 0) {
        mPlayersSaved += i;
        SaveLowest(mClosestPlayersSaved, f);
    }
}

void Stats::AddToTimesSaved(float f1, float f2) {
    mTimesSaved++;
    SaveLowest(mClosestTimesSaved, f1);
    SaveNewest(mSavedPoints, f2);
}

void Stats::DeployOverdrive(float f, int i) {
    BeginMultiplier(mCurrentOverdriveDeployment, f, i, mOverdrive);
}

void Stats::StopDeployingOverdrive(float f, int i) {
    EndMultiplier(
        mCurrentOverdriveDeployment,
        mBestOverdriveDeployments,
        f,
        i,
        mOverdrive,
        mTotalOverdriveDurationMs
    );
}

void Stats::BeginStreakMultiplier(float f, int i) {
    BeginMultiplier(mCurrentStreakMultiplier, f, i, mScoreStreak);
}

void Stats::EndStreakMultiplier(float f, int i) {
    EndMultiplier(
        mCurrentStreakMultiplier,
        mBestStreakMultipliers,
        f,
        i,
        mScoreStreak,
        mTotalMultiplierDuration
    );
}

void Stats::BeginMultiplier(Stats::MultiplierInfo &info, float f1, int i, float f2) {
    info.mStartMs = f1;
    info.mStartingMultiplier = i;
    info.mPoints = f2;
}

void Stats::EndMultiplier(
    Stats::MultiplierInfo &info,
    std::vector<Stats::MultiplierInfo> &vec,
    float f1,
    int i,
    float f2,
    float &fref
) {
    if (info.mStartMs < 0)
        return;
    info.mEndingMultiplier = i;
    info.mDurationMs = f1 - info.mStartMs;
    info.mPoints = f2 - info.mPoints;
    SaveHighest(vec, info);
    fref += info.mDurationMs;
    info = MultiplierInfo();
}

int Stats::GetUnisonPhrasePercent() const {
    if (mUnisonPhraseCount == 0)
        return 0;
    else
        return ((float)mUnisonPhraseCompleted / (float)mUnisonPhraseCount) * 100.0f;
}

void Stats::SetHopoGemInfo(int i1, int i2, int i3) {
    mHopoGemsHopoed = i1;
    mHopoGemsStrummed = i2;
    mHopoGemCount = i3;
}

void Stats::IncrementHighFretGemsHit(bool b) {
    if (b)
        mHighGemsHitHigh++;
    else
        mHighGemsHitLow++;
}

void Stats::IncrementSustainGemsHit(bool b) {
    if (b)
        mSustainGemsHitCompletely++;
    else
        mSustainGemsHitPartially++;
}

void Stats::AddRoll(bool b) {
    if (b)
        mRollsHitCompletely++;
    mRollCount++;
}

void Stats::IncrementTrillsHit(bool b) {
    if (b)
        mTrillsHitCompletely++;
    else
        mTrillsHitPartially++;
}

void Stats::SetCymbalGemInfo(int i1, int i2, int i3) {
    mCymbalGemInfo1 = i3;
    mCymbalGemInfo2 = i1;
    mCymbalGemInfo3 = i2;
}

void Stats::SetSectionInfo(int index, Symbol s, float f1, float f2) {
    MILO_ASSERT(index < mSections.size(), 0x36F);
    SectionInfo &info = mSections[index];
    info.unk0 = s;
    info.unk4 = f1;
    info.unk8 = f2;
}

const Stats::SectionInfo &Stats::GetSectionInfo(int index) const {
    MILO_ASSERT(index < mSections.size(), 0x378);
    return mSections[index];
}

float Stats::GetAverageMsError() const {
    if (mHitCount == 0)
        return 0;
    else
        return unk1c8 / mHitCount;
}

SingerStats::SingerStats(int count) {
    for (int i = 0; i < count; i++) {
        unk0.push_back(std::pair<int, float>(i, 0.0f));
    }
}

void SingerStats::Finalize() {
    std::sort(unk0.begin(), unk0.end(), PartPercentageSorter());
}

void SingerStats::SetPartPercentage(int, float) {}

const std::pair<int, float> &SingerStats::GetRankData(int part) const {
    return unk0[part];
}

void SingerStats::SetPitchDeviationInfo(float param_1, float param_2) {
    mPitchDeviation1 = param_1;
    mPitchDeviation2 = param_2;
}

void SingerStats::GetPitchDeviationInfo(float &f1, float &f2) const {
    f1 = mPitchDeviation1;
    f2 = mPitchDeviation2;
}

Stats::StreakInfo::StreakInfo() : mStart(-1), mDuration(0) {}

BinStream &operator<<(BinStream &bs, const Stats::StreakInfo &info) {
    bs << info.mStart;
    bs << info.mDuration;
    return bs;
}

BinStream &operator>>(BinStream &bs, Stats::StreakInfo &info) {
    bs >> info.mStart;
    bs >> info.mDuration;
    return bs;
}

Stats::MultiplierInfo::MultiplierInfo()
    : mStartMs(-1.0f), mDurationMs(0), mStartingMultiplier(0), mEndingMultiplier(0),
      mPoints(0) {}

bool operator>(const Stats::MultiplierInfo &info1, const Stats::MultiplierInfo &info2) {
    if (info1.mPoints == info2.mPoints) {
        return info1.mDurationMs < info2.mDurationMs;
    } else
        return info1.mPoints < info2.mPoints;
}

Stats::SectionInfo::SectionInfo() : unk4(-1.0f), unk8(0) {}

BinStream &operator<<(BinStream &bs, const Stats::SectionInfo &info) {
    bs << info.unk0;
    bs << info.unk4;
    bs << info.unk8;
    return bs;
}

BinStream &operator>>(BinStream &bs, Stats::SectionInfo &info) {
    bs >> info.unk0;
    bs >> info.unk4;
    bs >> info.unk8;
    return bs;
}
