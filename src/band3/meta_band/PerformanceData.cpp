#include "PerformanceData.h"
#include "MetaPanel.h"
#include "os/DateTime.h"
#include "network/net/NetSession.h"

PerformanceData::PerformanceData() : m0x24(-1), m0x28(false), mIsOnline(false), mIsPlaytest(false), mIsCheating(false), 
mScoreType(kScoreBand), mDifficulty(kDifficultyEasy), mStars(0), mBattleId(0), mTimestamp(0), mMode(gNullStr), mStats() {
    mSaveSizeMethod = SaveSize;
    InitializeStatsVectors();
}

PerformanceData::~PerformanceData() {

}

#pragma push
#pragma dont_inline on
void PerformanceData::Initialize(const Stats& stats, int songId, ScoreType scoreType, Difficulty difficulty, Symbol mode, int stars, int battleId, bool b) {
    m0x24 = 0;
    if(MetaPanel::sIsPlaytest) mIsPlaytest = true;
    mIsOnline = !TheNetSession->IsLocal();
    m0x28 = true;
    mMode = mode;
    mSongId = songId;
    mScoreType = scoreType;
    mDifficulty = difficulty;
    mStars = stars;
    mBattleId = battleId;
    mIsCheating = b;
    DateTime dt;
    GetDateAndTime(dt);
    mTimestamp = dt.ToCode();
    Stats thestats(stats);
    Prune(thestats);
    mStats = thestats;
}
#pragma pop

void PerformanceData::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << m0x24;
    stream << m0x28;
    stream << mIsPlaytest;
    stream << mIsOnline;
    stream << mIsCheating;
    FixedSizeSaveable::SaveFixedSymbol(stream, mMode);
    stream << mSongId;
    stream << mScoreType;
    stream << mDifficulty;
    stream << mStars;
    stream << mBattleId;
    stream << mTimestamp;
    FixedSizeSaveable::SaveStd(stream, mStats.mAccessPerformanceAwards, 0x32);
    stream << mStats.mEndGameScore;
    stream << mStats.mNotesHitFraction;
    stream << mStats.mHitCount;
    stream << mStats.mMissCount;
    FixedSizeSaveable::SaveStd(stream, mStats.mFailurePoints, 3, 4);
    FixedSizeSaveable::SaveStd(stream, mStats.mSavedPoints, 3, 4);
    FixedSizeSaveable::SaveStd(stream, mStats.mClosestTimesSaved, 3, 4);
    FixedSizeSaveable::SaveStd(stream, mStats.mClosestPlayersSaved, 3, 4);
    stream << mStats.mTimesSaved;
    stream << mStats.mPlayersSaved;
    stream << mStats.mCurrentHitStreak.mStart;
    stream << mStats.mCurrentHitStreak.mDuration;
    stream << mStats.mEndGameOverdrive;
    stream << mStats.mEndGameCrowdLevel;
    stream << mStats.GetCodaPoints();
    stream << mStats.mOverdrivePhrasesCompleted;
    stream << mStats.mOverdrivePhraseCount;
    stream << mStats.mUnisonPhraseCompleted;
    stream << mStats.mUnisonPhraseCount;
    FixedSizeSaveable::SaveStd(stream, mStats.unk104, 3, 4);
    stream << mStats.mHitStreaks.size();
}

int PerformanceData::SaveSize(int i) {
    int savesize = 6;
    if(i >= 0x97) savesize = 7;
    if(i >= 0x94) savesize++;
    savesize += 0x31e;
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "PerformanceData", savesize);
    }
    return savesize;
}

#pragma push
#pragma dont_inline on
void PerformanceData::LoadFixed(FixedSizeSaveableStream& stream, int rev) {
    stream >> m0x24;
    stream >> m0x28;
    stream >> mIsPlaytest;
    if(rev >= 0x97) stream >> mIsOnline;
    if(rev >= 0x94) stream >> mIsCheating;
    FixedSizeSaveable::LoadFixedSymbol(stream, mMode);
    stream >> mSongId;
    int scoretype = 0;
    stream >> scoretype;
    mScoreType = (ScoreType)scoretype;
    int diff = 0;
    stream >> diff;
    mDifficulty = (Difficulty)diff;
    stream >> mStars;
    stream >> mBattleId;
    stream >> mTimestamp;
    FixedSizeSaveable::LoadStd(stream, mStats.AccessPerformanceAwards(), 0x32);
    mStats.SetEndGameScore(stream.ReadInt());
    mStats.SetNotesHitFraction(stream.ReadFloat());
    mStats.SetHitCount(stream.ReadInt());
    mStats.SetMissCount(stream.ReadInt());
    std::vector<float>& failpoints = mStats.AccessFailurePoints();
    failpoints.clear();
    std::vector<float>& savepoints = mStats.AccessSavedPoints();
    savepoints.clear();
    std::vector<float>& closesttimessaved = mStats.AccessClosestTimesSaved();
    closesttimessaved.clear();
    std::vector<float>& closestplayerssaved = mStats.AccessClosestPlayersSaved();
    closestplayerssaved.clear();
    FixedSizeSaveable::LoadStd(stream, failpoints, 3, 4);
    FixedSizeSaveable::LoadStd(stream, savepoints, 3, 4);
    FixedSizeSaveable::LoadStd(stream, closesttimessaved, 3, 4);
    FixedSizeSaveable::LoadStd(stream, closestplayerssaved, 3, 4);
    
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetTimesSaved((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetPlayersSaved((Stats *)(this + 0x48),iVar2);
//   piVar3 = (int *)Stats::AccessCurrentStreakInfo((Stats *)(this + 0x48));
//   BinStream::operator_>>((BinStream *)param_1,piVar3);
//   BinStream::operator_>>((BinStream *)param_1,piVar3 + 1);
//   dVar9 = (double)FixedSizeSaveableStream::ReadFloat(param_1);
//   Stats::SetEndGameOverdrive((Stats *)(this + 0x48),(float)dVar9);
//   dVar9 = (double)FixedSizeSaveableStream::ReadFloat(param_1);
//   Stats::SetEndGameCrowdLevel((Stats *)(this + 0x48),(float)dVar9);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetCodaPoints((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetOverdrivePhrasesCompleted((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetOverdrivePhraseCount((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetUnisonPhrasesCompleted((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetUnisonPhraseCount((Stats *)(this + 0x48),iVar2);
//   this_04 = (vector<> *)Stats::AccessBestSolos((Stats *)(this + 0x48));
//   stlpmtx_std::vector<><>::clear((vector<><> *)this_04);
//   FixedSizeSaveable::LoadStd(param_1,this_04,3,4);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetHitStreakCount((Stats *)(this + 0x48),iVar2);
//   iVar8 = 0;
//   do {
//     if (iVar8 < iVar2) {
//       piVar3 = (int *)Stats::AccessHitStreak((Stats *)(this + 0x48),iVar8);
//       BinStream::operator_>>((BinStream *)param_1,piVar3);
//       BinStream::operator_>>((BinStream *)param_1,piVar3 + 1);
//     }
//     else {
//       FixedSizeSaveableStream::ReadInt(param_1);
//       FixedSizeSaveableStream::ReadInt(param_1);
//     }
//     iVar8 = iVar8 + 1;
//   } while (iVar8 < 3);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetMissStreakCount((Stats *)(this + 0x48),iVar2);
//   iVar8 = 0;
//   do {
//     if (iVar8 < iVar2) {
//       piVar3 = (int *)Stats::AccessMissStreak((Stats *)(this + 0x48),iVar8);
//       BinStream::operator_>>((BinStream *)param_1,piVar3);
//       BinStream::operator_>>((BinStream *)param_1,piVar3 + 1);
//     }
//     else {
//       FixedSizeSaveableStream::ReadInt(param_1);
//       FixedSizeSaveableStream::ReadInt(param_1);
//     }
//     iVar8 = iVar8 + 1;
//   } while (iVar8 < 3);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetBestOverdriveDeploymentsCount((Stats *)(this + 0x48),iVar2);
//   iVar8 = 0;
//   do {
//     if (iVar8 < iVar2) {
//       pfVar4 = (float *)Stats::AccessBestOverdriveDeployment((Stats *)(this + 0x48),iVar8);
//       BinStream::operator_>>((BinStream *)param_1,pfVar4);
//       BinStream::operator_>>((BinStream *)param_1,pfVar4 + 1);
//       BinStream::operator_>>((BinStream *)param_1,(int *)(pfVar4 + 2));
//       BinStream::operator_>>((BinStream *)param_1,(int *)(pfVar4 + 3));
//       BinStream::operator_>>((BinStream *)param_1,pfVar4 + 4);
//     }
//     else {
//       FixedSizeSaveableStream::ReadInt(param_1);
//       FixedSizeSaveableStream::ReadInt(param_1);
//       FixedSizeSaveableStream::ReadFloat(param_1);
//       FixedSizeSaveableStream::ReadFloat(param_1);
//       FixedSizeSaveableStream::ReadInt(param_1);
//     }
//     iVar8 = iVar8 + 1;
//   } while (iVar8 < 3);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetBestStreakMultipliersCount((Stats *)(this + 0x48),iVar2);
//   iVar8 = 0;
//   do {
//     if (iVar8 < iVar2) {
//       pfVar4 = (float *)Stats::AccessBestStreakMultiplier((Stats *)(this + 0x48),iVar8);
//       BinStream::operator_>>((BinStream *)param_1,pfVar4);
//       BinStream::operator_>>((BinStream *)param_1,pfVar4 + 1);
//       BinStream::operator_>>((BinStream *)param_1,(int *)(pfVar4 + 2));
//       BinStream::operator_>>((BinStream *)param_1,(int *)(pfVar4 + 3));
//       BinStream::operator_>>((BinStream *)param_1,pfVar4 + 4);
//     }
//     else {
//       FixedSizeSaveableStream::ReadInt(param_1);
//       FixedSizeSaveableStream::ReadInt(param_1);
//       FixedSizeSaveableStream::ReadFloat(param_1);
//       FixedSizeSaveableStream::ReadFloat(param_1);
//       FixedSizeSaveableStream::ReadInt(param_1);
//     }
//     iVar8 = iVar8 + 1;
//   } while (iVar8 < 3);
//   dVar9 = (double)FixedSizeSaveableStream::ReadFloat(param_1);
//   Stats::SetTotalOverdriveDuration((Stats *)(this + 0x48),(float)dVar9);
//   dVar9 = (double)FixedSizeSaveableStream::ReadFloat(param_1);
//   Stats::SetTotalMultiplierDuration((Stats *)(this + 0x48),(float)dVar9);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetRollsHitCompletely((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetRollCount((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   iVar8 = FixedSizeSaveableStream::ReadInt(param_1);
//   iVar5 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetHopoGemInfo((Stats *)(this + 0x48),iVar5,iVar8,iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetHighGemsHitHigh((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetHighGemsHitLow((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetHighFretGemCount((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetSustainGemsHitCompletely((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetSustainGemsHitPartially((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetSustainGemCount((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetTrillsHitCompletely((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetTrillsHitPartially((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetTrillCount((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   iVar8 = FixedSizeSaveableStream::ReadInt(param_1);
//   iVar5 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetCymbalGemInfo((Stats *)(this + 0x48),iVar5,iVar8,iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetDoubleHarmonyHit((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetDoubleHarmonyPhraseCount((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetTripleHarmonyHit((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetTripleHarmonyPhraseCount((Stats *)(this + 0x48),iVar2);
//   iVar2 = FixedSizeSaveableStream::ReadInt(param_1);
//   iVar8 = FixedSizeSaveableStream::ReadInt(param_1);
//   Stats::SetVocalSingerAndPartCounts((Stats *)(this + 0x48),iVar2,iVar8);
//   iVar5 = 0;
//   do {
//     if (iVar5 < iVar2) {
//       this_05 = (SingerStats *)Stats::AccessSingerStats((Stats *)(this + 0x48),iVar5);
//       iVar7 = 0;
//       do {
//         if (iVar7 < iVar8) {
//           dVar9 = (double)FixedSizeSaveableStream::ReadFloat(param_1);
//           iVar6 = FixedSizeSaveableStream::ReadInt(param_1);
//           SingerStats::SetPartPercentage(this_05,iVar6,(float)dVar9);
//         }
//         else {
//           FixedSizeSaveableStream::ReadInt(param_1);
//           FixedSizeSaveableStream::ReadFloat(param_1);
//         }
//         iVar7 = iVar7 + 1;
//       } while (iVar7 < 3);
//       dVar9 = (double)FixedSizeSaveableStream::ReadFloat(param_1);
//       dVar10 = (double)FixedSizeSaveableStream::ReadFloat(param_1);
//       SingerStats::SetPitchDeviationInfo(this_05,(float)dVar10,(float)dVar9);
//     }
//     else {
//       iVar7 = 0;
//       do {
//         FixedSizeSaveableStream::ReadInt(param_1);
//         FixedSizeSaveableStream::ReadFloat(param_1);
//         iVar7 = iVar7 + 1;
//       } while (iVar7 < 3);
//       FixedSizeSaveableStream::ReadFloat(param_1);
//       FixedSizeSaveableStream::ReadFloat(param_1);
//     }
//     iVar5 = iVar5 + 1;
//   } while (iVar5 < 3);
//   return;
}
#pragma pop

void PerformanceData::Prune(Stats&) {}

void PerformanceData::InitializeStatsVectors() {}

BEGIN_HANDLERS(PerformanceData)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x2a8);
END_HANDLERS

void Stats::SetTimesSaved(int timesSaved) { mTimesSaved = timesSaved; }
void Stats::SetPlayersSaved(int playersSaved) { mPlayersSaved = playersSaved; }
void Stats::AccessCurrentStreakInfo() {}
void Stats::SetEndGameOverdrive(float endGameOverdrive) { mEndGameOverdrive = endGameOverdrive; }
void Stats::SetEndGameCrowdLevel(float endGameCrowdLevel) { mEndGameCrowdLevel = endGameCrowdLevel; }
void Stats::SetCodaPoints(int codaPoints) { mCodaPoints = codaPoints; }
void Stats::SetOverdrivePhrasesCompleted(int overdrivePhrasesCompleted) { mOverdrivePhrasesCompleted = overdrivePhrasesCompleted; }
void Stats::SetOverdrivePhraseCount(int overdrivePhraseCount) { mOverdrivePhraseCount = overdrivePhraseCount; }
void Stats::SetUnisonPhrasesCompleted(int unisonPhrasesCompleted) { mUnisonPhraseCompleted = unisonPhrasesCompleted; }
void Stats::SetUnisonPhraseCount(int unisonPhraseCount) { mUnisonPhraseCount = unisonPhraseCount; }
void Stats::AccessBestSolos() {}
void Stats::SetHitStreakCount(int hitStreakCount) { }
void Stats::AccessHitStreak(int) {}
void Stats::SetMissStreakCount(int missStreakCount) { }
void Stats::AccessMissStreak(int) {}
void Stats::SetBestOverdriveDeploymentsCount(int bestOverdriveDeploymentsCount) { }
void Stats::AccessBestOverdriveDeployment(int) {}
void Stats::SetBestStreakMultipliersCount(int bestStreakMultipliersCount) {}
void Stats::AccessBestStreakMultiplier(int) {}
void Stats::SetTotalOverdriveDuration(float totalOverdriveDuration) { mTotalOverdriveDurationMs = totalOverdriveDuration; }
void Stats::SetTotalMultiplierDuration(float totalMultiplierDuration) { mTotalMultiplierDuration = totalMultiplierDuration; }
void Stats::SetRollsHitCompletely(int rollsHitCompletely) { mRollsHitCompletely = rollsHitCompletely; }
void Stats::SetRollCount(int rollCount) { mRollCount = rollCount; }
void Stats::SetHighGemsHitHigh(int highGemsHitHigh) { mHighGemsHitHigh = highGemsHitHigh; }
void Stats::SetHighGemsHitLow(int highGemsHitLow) { mHighGemsHitLow = highGemsHitLow; }
void Stats::SetHighFretGemCount(int highFretGemCount) { mHighFretGemCount = highFretGemCount; }
void Stats::SetSustainGemsHitCompletely(int sustainGemsHitCompletely) { mSustainGemsHitCompletely = sustainGemsHitCompletely; }
void Stats::SetSustainGemsHitPartially(int sustainGemsHitPartially) { mSustainGemsHitPartially = sustainGemsHitPartially; }
void Stats::SetSustainGemCount(int sustainGemCount) { mSustainGemCount = sustainGemCount; }
void Stats::SetTrillsHitCompletely(int trillsHitCompletely) { mTrillsHitCompletely = trillsHitCompletely; }
void Stats::SetTrillsHitPartially(int trillsHitPartially) { mTrillsHitPartially = trillsHitPartially; }
void Stats::SetTrillCount(int trillCount) { mTrillCount = trillCount; }
void Stats::SetDoubleHarmonyHit(int doubleHarmonyHit) { mDoubleHarmonyHit = doubleHarmonyHit; }
void Stats::SetDoubleHarmonyPhraseCount(int doubleHarmonyPhraseCount) { mDoubleHarmonyPhraseCount = doubleHarmonyPhraseCount; }
void Stats::SetTripleHarmonyHit(int tripleHarmonyHit) { mTripleHarmonyHit = tripleHarmonyHit; }
void Stats::SetTripleHarmonyPhraseCount(int tripleHarmonyPhraseCount) { mTripleHarmonyPhraseCount = tripleHarmonyPhraseCount; }
void Stats::AccessSingerStats(int) {}
