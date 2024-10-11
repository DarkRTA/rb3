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
    FixedSizeSaveable::SaveStd(stream, mStats.mBestSolos, 3, 4);
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
    mStats.SetTimesSaved(stream.ReadInt());
    mStats.SetPlayersSaved(stream.ReadInt());
    Stats::StreakInfo& info = mStats.AccessCurrentStreakInfo();
    stream >> info.mStart;
    stream >> info.mDuration;
    mStats.SetEndGameOverdrive(stream.ReadFloat());
    mStats.SetEndGameCrowdLevel(stream.ReadFloat());
    mStats.SetCodaPoints(stream.ReadInt());
    mStats.SetOverdrivePhrasesCompleted(stream.ReadInt());
    mStats.SetOverdrivePhraseCount(stream.ReadInt());
    mStats.SetUnisonPhrasesCompleted(stream.ReadInt());
    mStats.SetUnisonPhraseCount(stream.ReadInt());
    std::vector<int>& bestsolos = mStats.AccessBestSolos();
    bestsolos.clear();
    FixedSizeSaveable::LoadStd(stream, bestsolos, 3, 4);
    int hitcount = stream.ReadInt();
    mStats.SetHitStreakCount(hitcount);
    for(int i = 0; i < 3; i++){
        if(i < hitcount){
            Stats::StreakInfo& info = mStats.AccessHitStreak(i);
            stream >> info.mStart;
            stream >> info.mDuration;
        }
        else {
            stream.ReadInt();
            stream.ReadInt();
        }
    }
    int misscount = stream.ReadInt();
    mStats.SetMissStreakCount(misscount);
    for(int i = 0; i < 3; i++){
        if(i < misscount){
            Stats::StreakInfo& info = mStats.AccessMissStreak(i);
            stream >> info.mStart;
            stream >> info.mDuration;
        }
        else {
            stream.ReadInt();
            stream.ReadInt();
        }
    }
    int oddeploycount = stream.ReadInt();
    mStats.SetBestOverdriveDeploymentsCount(oddeploycount);
    for(int i = 0; i < 3; i++){
        if(i < oddeploycount){
            Stats::MultiplierInfo& info = mStats.AccessBestOverdriveDeployment(i);
            stream >> info.mStartMs;
            stream >> info.mDurationMs;
            stream >> info.mStartingMultiplier;
            stream >> info.mEndingMultiplier;
            stream >> info.mPoints;
        }
        else {
            stream.ReadInt();
            stream.ReadInt();
            stream.ReadFloat();
            stream.ReadFloat();
            stream.ReadInt();
        }
    }
    int multcount = stream.ReadInt();
    mStats.SetBestStreakMultipliersCount(multcount);
    for(int i = 0; i < 3; i++){
        if(i < multcount){
            Stats::MultiplierInfo& info = mStats.AccessBestStreakMultiplier(i);
            stream >> info.mStartMs;
            stream >> info.mDurationMs;
            stream >> info.mStartingMultiplier;
            stream >> info.mEndingMultiplier;
            stream >> info.mPoints;
        }
        else {
            stream.ReadInt();
            stream.ReadInt();
            stream.ReadFloat();
            stream.ReadFloat();
            stream.ReadInt();
        }
    }
    mStats.SetTotalOverdriveDuration(stream.ReadFloat());
    mStats.SetTotalMultiplierDuration(stream.ReadFloat());
    mStats.SetRollsHitCompletely(stream.ReadInt());
    mStats.SetRollCount(stream.ReadInt());
    mStats.SetHopoGemInfo(stream.ReadInt(), stream.ReadInt(), stream.ReadInt());
    mStats.SetHighGemsHitHigh(stream.ReadInt());
    mStats.SetHighGemsHitLow(stream.ReadInt());
    mStats.SetHighFretGemCount(stream.ReadInt());
    mStats.SetSustainGemsHitCompletely(stream.ReadInt());
    mStats.SetSustainGemsHitPartially(stream.ReadInt());
    mStats.SetSustainGemCount(stream.ReadInt());
    mStats.SetTrillsHitCompletely(stream.ReadInt());
    mStats.SetTrillsHitPartially(stream.ReadInt());
    mStats.SetTrillCount(stream.ReadInt());
    mStats.SetCymbalGemInfo(stream.ReadInt(), stream.ReadInt(), stream.ReadInt());
    mStats.SetDoubleHarmonyHit(stream.ReadInt());
    mStats.SetDoubleHarmonyPhraseCount(stream.ReadInt());
    mStats.SetTripleHarmonyHit(stream.ReadInt());
    mStats.SetTripleHarmonyPhraseCount(stream.ReadInt());
    int vocsingercount = stream.ReadInt();
    int vocpartcount = stream.ReadInt();
    mStats.SetVocalSingerAndPartCounts(vocsingercount, vocpartcount);
    for(int i = 0; i < 3; i++){
        if(i < vocsingercount){
            SingerStats& stats = mStats.AccessSingerStats(i);
            for(int j = 0; j < 3; j++){
                if(j < vocpartcount){
                    stats.SetPartPercentage(stream.ReadInt(), stream.ReadFloat());
                }
                else {
                    stream.ReadInt();
                    stream.ReadFloat();
                }
            }
            stats.SetPitchDeviationInfo(stream.ReadFloat(), stream.ReadFloat());
        }
        else {
            for(int j = 0; j < 3; j++){
                stream.ReadInt();
                stream.ReadFloat();
            }
            stream.ReadFloat();
            stream.ReadFloat();
        }
    }
}
#pragma pop

void PerformanceData::Prune(Stats&) {}

void PerformanceData::InitializeStatsVectors() {}

BEGIN_HANDLERS(PerformanceData)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x2a8);
END_HANDLERS