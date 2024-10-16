#include "meta_band/AccomplishmentProgress.h"
#include "Accomplishment.h"
#include "Campaign.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/GameMessages.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/AccomplishmentCategory.h"
#include "meta_band/AccomplishmentGroup.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/MetaPerformer.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "stl/_pair.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

GamerAwardStatus::GamerAwardStatus() : unk8(-1), unkc(0), unk10(0) {
    mSaveSizeMethod = &SaveSize;
}

GamerAwardStatus::~GamerAwardStatus(){

}

void GamerAwardStatus::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << unk8;
    stream << unkc;
}

int GamerAwardStatus::SaveSize(int){
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "GamerpicAward", 8);
    }
    return 8;
}

void GamerAwardStatus::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    stream >> unk8;
    int iii = 0;
    stream >> iii;
    unkc = iii;
}

AccomplishmentProgress::AccomplishmentProgress(BandProfile* profile) : mParentProfile(profile), mMetaScore(0), mUploadDirty(1), unk648(0) {
    Clear();
    mSaveSizeMethod = &SaveSize;
}

AccomplishmentProgress::~AccomplishmentProgress(){
    for(std::list<GamerAwardStatus*>::iterator it = mGamerAwardStatusList.begin(); it != mGamerAwardStatusList.end(); ++it){
        delete *it;
    }
    mGamerAwardStatusList.clear();
}

void AccomplishmentProgress::Clear(){
    mHardCoreStatusUpdatePending = false;
    mUploadDirty = false;
    mAccomplishments.clear();
    unk64.clear();
    unkb0.clear();
    mNewRewardVignettes.clear();
    mNewAwards.clear();
    unk7c.clear();
    mAwards.clear();
    unk648 = 0;
    mMetaScore = 0;
    mTotalGemsSmashed = 0;
    mTotalGuitarHopos = 0;
    mTotalBassHopos = 0;
    mTotalUpstrums = 0;
    mTotalTimesRevived = 0;
    mTotalSaves = 0;
    mTotalAwesomes = 0;
    mTotalDoubleAwesomes = 0;
    mTotalTripleAwesomes = 0;
    mCareerFills = 0;
    mBestBandScore = 0;

    for(int i = 0; i < kNumScoreTypes; i++){
        mBestStreak[i] = 0;
        mBestScore[i] = 0;
        mTotalOverdriveDeploys[i] = 0;
        mTotalOverdriveTime[i] = 0;
        mTotalOverdrivePhrases[i] = 0;
        mTotalUnisonPhrases[i] = 0;
        mMostOverdriveDeploys[i] = 0;
        mMostOverdriveTime[i] = 0;
        mMostUnisonPhrases[i] = 0;
        mTotalBREsHit[i] = 0;
        for(int j = 0; j < kNumDifficulties; j++){
            mBestStars[i][j] = 0;
            mBestSolo[i][j] = 0;
            mBestAccuracy[i][j] = 0;
            mBestHoposPercent[i][j] = 0;
        }
    }

    for(int i = 0; i < kNumDifficulties; i++){
        mBestPercussionPercent[i] = 0;
        mBestKickPercent[i] = 0;
        mBestProKickPercent[i] = 0;
        mTotalDrumRollCount[i] = 0;
        mTotalProDrumRollCount[i] = 0;
        mBestSoloButtonPercent[i] = 0;
        mBestDrumRollPercent[i] = 0;
    }
    mTotalSongsPlayed = 0;
    mTourTotalSongsPlayed = 0;
    mToursPlayedMap.clear();
    mTourMostStarsMap.clear();
    mToursGotAllStarsMap.clear();
    mGigTypeCompletedMap.clear();
    unk645 = false;
}

bool AccomplishmentProgress::AddAccomplishment(Symbol s){
    if(!IsAccomplished(s)){
        Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(s);
        MILO_ASSERT(pAccomplishment, 0xC1);
        NotifyPlayerOfAccomplishment(s, pAccomplishment->GetIconArt());
        LocalBandUser* pUser = mParentProfile->GetAssociatedLocalBandUser();
        MILO_ASSERT(pUser, 199);
        MetaPerformer* pPerformer = MetaPerformer::Current();
        MILO_ASSERT(pPerformer, 0xCB);
        TheAccomplishmentMgr->AddGoalAcquisitionInfo(s, pUser->UserName(), pPerformer->Song());
        if(pAccomplishment->HasAward()){
            AddAward(pAccomplishment->GetAward(), s);
        }
        int lbhcstatus = TheAccomplishmentMgr->GetLeaderboardHardcoreStatus(mAccomplishments.size());
        TheAccomplishmentMgr->GetIconHardCoreStatus(mAccomplishments.size());
        mAccomplishments.insert(s);
        unk64.insert(s);

        Symbol cat = pAccomplishment->GetCategory();
        AccomplishmentCategory* pCategory = TheAccomplishmentMgr->GetAccomplishmentCategory(cat);
        MILO_ASSERT(pCategory, 0xEC);
        if(TheAccomplishmentMgr->IsCategoryComplete(mParentProfile, cat)){
            NotifyPlayerOfCategoryComplete(cat);
            if(pCategory->HasAward()){
                AddAward(pCategory->GetAward(), cat);
            }
        }

        Symbol group = pCategory->GetGroup();
        AccomplishmentGroup* pGroup = TheAccomplishmentMgr->GetAccomplishmentGroup(group);
        MILO_ASSERT(pGroup, 0xFB);
        if(TheAccomplishmentMgr->IsGroupComplete(mParentProfile, group)){
            NotifyPlayerOfGroupComplete(group);
            if(pGroup->HasAward()){
                AddAward(pGroup->GetAward(), group);
            }
        }

        Symbol level4 = TheCampaign->GetCampaignLevelForMetaScore(mMetaScore);
        int metascoreval = TheAccomplishmentMgr->GetMetaScoreValue(pAccomplishment->GetMetaScoreValue());
        SetMetaScore(mMetaScore + metascoreval);
        Symbol level5 = TheCampaign->GetCampaignLevelForMetaScore(mMetaScore);
        if(level5 != level4){
            // MILO ASSERT pLevel
        }
        return true;
    }
    else return false;
}

bool AccomplishmentProgress::IsAccomplished(Symbol s) const {
    return mAccomplishments.find(s) != mAccomplishments.end();
}

bool AccomplishmentProgress::HasNewAwards() const {
    return !mNewAwards.empty();
}

Symbol AccomplishmentProgress::GetFirstNewAward() const {
    MILO_ASSERT(HasNewAwards(), 0x158);
    return mNewAwards.front().first;
}

Symbol AccomplishmentProgress::GetFirstNewAwardReason() const {
    MILO_ASSERT(HasNewAwards(), 0x161);
    return mNewAwards.front().second;
}

void AccomplishmentProgress::ClearFirstNewAward(){
    MILO_ASSERT(HasNewAwards(), 0x16A);
    mNewAwards.pop_front();
    mParentProfile->MakeDirty();
}

void AccomplishmentProgress::AddNewRewardVignette(Symbol s){
    std::list<Symbol>::iterator it;
    for(it = mNewRewardVignettes.begin(); it != mNewRewardVignettes.end() && *it != s; ++it);
    if(it == mNewRewardVignettes.end()){
        mNewRewardVignettes.push_back(s);
    }
    unkb0.insert(s);
    mParentProfile->MakeDirty();
}

bool AccomplishmentProgress::IsUploadDirty() const {
    return mUploadDirty || !unk64.empty();
}

bool AccomplishmentProgress::HasNewRewardVignettes() const {
    return !mNewRewardVignettes.empty();
}

Symbol AccomplishmentProgress::GetFirstNewRewardVignette() const {
    MILO_ASSERT(HasNewRewardVignettes(), 0x18C);
    return mNewRewardVignettes.front();
}

void AccomplishmentProgress::ClearFirstNewRewardVignette(){
    MILO_ASSERT(HasNewRewardVignettes(), 0x194);
    mNewRewardVignettes.pop_front();
    mParentProfile->MakeDirty();
}

bool AccomplishmentProgress::HasNewRewardVignetteFestival() const {
    return !unk645;
}

void AccomplishmentProgress::ClearNewRewardVignetteFestival(){
    unk645 = true;
    unkb0.insert(campaign_rewardvignette_festival_replay_screen);
}

bool AccomplishmentProgress::AddAward(Symbol s1, Symbol s2){
    if(!HasAward(s1)){
        mAwards.insert(s1);
        mNewAwards.push_back(std::make_pair(s1, s2));
        Award* pAward = TheAccomplishmentMgr->GetAward(s1);
        MILO_ASSERT(pAward, 0x1BD);
        pAward->GrantAwards(mParentProfile);
        mParentProfile->MakeDirty();
        return true;
    }
    else return false;
}

bool AccomplishmentProgress::HasAward(Symbol s) const {
    return mAwards.find(s) != mAwards.end();
}

void AccomplishmentProgress::Poll(){}

void AccomplishmentProgress::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << mUploadDirty;
    FixedSizeSaveable::SaveStd(stream, mAccomplishments, 1000);
    FixedSizeSaveable::SaveStd(stream, unk64, 1000);
    FixedSizeSaveable::SaveStd(stream, mAwards, 500);
    FixedSizeSaveable::SaveStd(stream, mNewRewardVignettes, 20);
    FixedSizeSaveable::SaveStd(stream, unkb0, 20);
    stream << mHardCoreStatusUpdatePending;
    stream << mMetaScore;
    stream << mTotalGemsSmashed;
    stream << mTotalGuitarHopos;
    stream << mTotalBassHopos;
    stream << mTotalUpstrums;
    stream << mTotalTimesRevived;
    stream << mTotalSaves;
    stream << mTotalAwesomes;
    stream << mTotalDoubleAwesomes;
    stream << mTotalTripleAwesomes;
    stream << mCareerFills;
    stream << mBestBandScore;
    for(int i = 0; i < 11; i++){
        stream << mBestStreak[i];
        stream << mBestScore[i];
        stream << mTotalOverdriveDeploys[i];
        stream << mTotalOverdriveTime[i];
        stream << mTotalOverdrivePhrases[i];
        stream << mTotalUnisonPhrases[i];
        stream << mMostOverdriveDeploys[i];
        stream << mMostOverdriveTime[i];
        stream << mMostUnisonPhrases[i];
        stream << mTotalBREsHit[i];
        for(int j = 0; j < 4; j++){
            stream << mBestStars[i][j];
            stream << mBestSolo[i][j];
            stream << mBestAccuracy[i][j];
            stream << mBestHoposPercent[i][j];
        }
    }
    for(int i = 0; i < 4; i++){
        stream << mBestPercussionPercent[i];
        stream << mBestKickPercent[i];
        stream << mBestProKickPercent[i];
        stream << mTotalDrumRollCount[i];
        stream << mTotalProDrumRollCount[i];
        stream << mBestSoloButtonPercent[i];
        stream << mBestDrumRollPercent[i];
    }
    stream << mTotalSongsPlayed;
    stream << mTourTotalSongsPlayed;
    stream << unk645;
    FixedSizeSaveable::SaveStd(stream, mToursPlayedMap, 10, 8);
    FixedSizeSaveable::SaveStd(stream, mTourMostStarsMap, 10, 8);
    FixedSizeSaveable::SaveStd(stream, mToursGotAllStarsMap, 10, 8);
    FixedSizeSaveable::SaveStd(stream, mGigTypeCompletedMap, 0x32, 8);
    FixedSizeSaveable::SaveStdPtr(stream, mGamerAwardStatusList, 0x32, GamerAwardStatus::SaveSize(0x97));
}

int AccomplishmentProgress::SaveSize(int i){
    int i3 = 0x2c9e;
    if(i >= 0x91) i3 = 0x2cbe;
    int size = GamerAwardStatus::SaveSize(i);
    size *= 0x32;
    size += i3;
    size += 0x2BD;
    REPORT_SIZE("AccomplishmentProgress", size);
}

void AccomplishmentProgress::SetHardCoreStatusUpdatePending(bool b){
    if(b != mHardCoreStatusUpdatePending){
        mHardCoreStatusUpdatePending = b;
        mParentProfile->MakeDirty();
    }
}

bool AccomplishmentProgress::IsHardCoreStatusUpdatePending(){ return mHardCoreStatusUpdatePending; }

void AccomplishmentProgress::SendHardCoreStatusUpdateToRockCentral(){
    unk648++;
    SetHardCoreStatusUpdatePending(true);
}

void AccomplishmentProgress::HandlePendingGamerRewards(){}

int AccomplishmentProgress::GetNumCompleted() const { return mAccomplishments.size(); }

int AccomplishmentProgress::GetNumCompletedInCategory(Symbol s) const {
    int num = 0;
    std::set<Symbol>* accset = TheAccomplishmentMgr->GetAccomplishmentSetForCategory(s);
    if(accset){
        for(std::set<Symbol>::iterator it = accset->begin(); it != accset->end(); ++it){
            Symbol key = *it;
            if(!TheAccomplishmentMgr->IsAvailableToView(key)) continue;
            if(!IsAccomplished(key)) continue;
            num++;
        }
    }
    return num;
}

int AccomplishmentProgress::GetNumCompletedInGroup(Symbol group) const {
    MILO_ASSERT(group != gNullStr, 0x3F5);
    std::list<Symbol>* pCategoryList = TheAccomplishmentMgr->GetCategoryListForGroup(group);
    MILO_ASSERT(pCategoryList, 0x3F8);
    int num = 0;
    for(std::list<Symbol>::iterator it = pCategoryList->begin(); it != pCategoryList->end(); ++it){
        num += GetNumCompletedInCategory(*it);
    }
    return num;
}

void AccomplishmentProgress::SetMetaScore(int score){
    mMetaScore = score;
}

int AccomplishmentProgress::GetMetaScore() const { return mMetaScore; }

int AccomplishmentProgress::GetTotalGemsSmashed() const { return mTotalGemsSmashed; }
int AccomplishmentProgress::GetTotalGuitarHopos() const { return mTotalGuitarHopos; }
int AccomplishmentProgress::GetTotalBassHopos() const { return mTotalBassHopos; }
int AccomplishmentProgress::GetTotalUpstrums() const { return mTotalUpstrums; }
int AccomplishmentProgress::GetTotalTimesRevived() const { return mTotalTimesRevived; }
int AccomplishmentProgress::GetTotalSaves() const { return mTotalSaves; }
int AccomplishmentProgress::GetTotalAwesomes() const { return mTotalAwesomes; }
int AccomplishmentProgress::GetTotalDoubleAwesomes() const { return mTotalDoubleAwesomes; }
int AccomplishmentProgress::GetTotalTripleAwesomes() const { return mTotalTripleAwesomes; }
int AccomplishmentProgress::GetCareerFills() const { return mCareerFills; }
int AccomplishmentProgress::GetBestStars(ScoreType s, Difficulty d) const { return mBestStars[s][d]; }

int AccomplishmentProgress::GetBestStarsAtMinDifficulty(ScoreType s, Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mBestStars[s][i];
        if(curbest > best) best = curbest;
    }
    return best;
}

int AccomplishmentProgress::GetBestSolo(ScoreType s, Difficulty d) const { return mBestSolo[s][d]; }

int AccomplishmentProgress::GetBestSoloAtMinDifficulty(ScoreType s, Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mBestSolo[s][i];
        if(curbest > best) best = curbest;
    }
    return best;
}

int AccomplishmentProgress::GetBestAccuracy(ScoreType s, Difficulty d) const { return mBestAccuracy[s][d]; }

int AccomplishmentProgress::GetBestAccuracyAtMinDifficulty(ScoreType s, Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mBestAccuracy[s][i];
        if(curbest > best) best = curbest;
    }
    return best;
}

int AccomplishmentProgress::GetBestHoposPercent(ScoreType s, Difficulty d) const { return mBestHoposPercent[s][d]; }

int AccomplishmentProgress::GetBestHoposPercentAtMinDifficulty(ScoreType s, Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mBestHoposPercent[s][i];
        if(curbest > best) best = curbest;
    }
    return best;
}

int AccomplishmentProgress::GetBestStreak(ScoreType s) const { return mBestStreak[s]; }
int AccomplishmentProgress::GetBestScore(ScoreType s) const { return mBestScore[s]; }
int AccomplishmentProgress::GetBestBandScore() const { return mBestBandScore; }
int AccomplishmentProgress::GetTotalOverdriveDeploys(ScoreType s) const { return mTotalOverdriveDeploys[s]; }
int AccomplishmentProgress::GetTotalOverdriveTime(ScoreType s) const { return mTotalOverdriveTime[s]; }
int AccomplishmentProgress::GetTotalOverdrivePhrases(ScoreType s) const { return mTotalOverdrivePhrases[s]; }
int AccomplishmentProgress::GetTotalUnisonPhrases(ScoreType s) const { return mTotalUnisonPhrases[s]; }
int AccomplishmentProgress::GetMostOverdriveDeploys(ScoreType s) const { return mMostOverdriveDeploys[s]; }
int AccomplishmentProgress::GetMostOverdriveTime(ScoreType s) const { return mMostOverdriveTime[s]; }
int AccomplishmentProgress::GetMostUnisonPhrases(ScoreType s) const { return mMostUnisonPhrases[s]; }
int AccomplishmentProgress::GetTotalBREsHit(ScoreType s) const { return mTotalBREsHit[s]; }
int AccomplishmentProgress::GetBestPercussionPercent(Difficulty d) const { return mBestPercussionPercent[d]; }

int AccomplishmentProgress::GetBestPercussionPercentAtMinDifficulty(Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mBestPercussionPercent[i];
        if(curbest > best) best = curbest;
    }
    return best;
}

int AccomplishmentProgress::GetTotalDrumRollCount(Difficulty d) const { return mTotalDrumRollCount[d]; }

int AccomplishmentProgress::GetTotalDrumRollCountAtMinDifficulty(Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mTotalDrumRollCount[i];
        if(curbest > best) best = curbest;
    }
    return best;
}

int AccomplishmentProgress::GetTotalProDrumRollCount(Difficulty d) const { return mTotalProDrumRollCount[d]; }

int AccomplishmentProgress::GetTotalProDrumRollCountAtMinDifficulty(Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mTotalProDrumRollCount[i];
        if(curbest > best) best = curbest;
    }
    return best;
}

int AccomplishmentProgress::GetBestKickPercent(Difficulty d) const { return mBestKickPercent[d]; }

int AccomplishmentProgress::GetBestKickPercentAtMinDifficulty(Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mBestKickPercent[i];
        if(curbest > best) best = curbest;
    }
    return best;
}

int AccomplishmentProgress::GetBestProKickPercent(Difficulty d) const { return mBestProKickPercent[d]; }

int AccomplishmentProgress::GetBestProKickPercentAtMinDifficulty(Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mBestProKickPercent[i];
        if(curbest > best) best = curbest;
    }
    return best;
}

int AccomplishmentProgress::GetBestDrumRollPercent(Difficulty d) const { return mBestDrumRollPercent[d]; }

int AccomplishmentProgress::GetBestDrumRollPercentAtMinDifficulty(Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mBestDrumRollPercent[i];
        if(curbest > best) best = curbest;
    }
    return best;
}

int AccomplishmentProgress::GetBestSoloButtonPercent(Difficulty d) const { return mBestSoloButtonPercent[d]; }

int AccomplishmentProgress::GetBestSoloButtonPercentAtMinDifficulty(Difficulty d) const {
    int best = 0;
    for(int i = d; i < kNumDifficulties; i++){
        int curbest = mBestSoloButtonPercent[i];
        if(curbest > best) best = curbest;
    }
    return best;
}

void AccomplishmentProgress::ClearStepTrackingMap(){ mStepTrackingMap.clear(); }

int AccomplishmentProgress::GetCurrentValue(Symbol s){
    int val = 0;
    std::map<Symbol, int>::iterator it = mStepTrackingMap.find(s);
    if(it != mStepTrackingMap.end()) val = it->second;
    return val;
}

void AccomplishmentProgress::SetCurrentValue(Symbol s, int val){
    mStepTrackingMap[s] = val;
}

int AccomplishmentProgress::GetTotalSongsPlayed() const { return mTotalSongsPlayed; }
int AccomplishmentProgress::GetTourTotalSongsPlayed() const { return mTourTotalSongsPlayed; }

int AccomplishmentProgress::GetToursPlayed() const {
    int num = 0;
    for(std::map<Symbol, int>::const_iterator it = mToursPlayedMap.begin(); it != mToursPlayedMap.end(); ++it){
        num += it->second;
    }
    return num;
}

int AccomplishmentProgress::GetToursPlayed(Symbol s) const {
    int val = 0;
    std::map<Symbol, int>::const_iterator it = mToursPlayedMap.find(s);
    if(it != mToursPlayedMap.end()) val = it->second;
    return val;
}

int AccomplishmentProgress::GetTourMostStars(Symbol s) const {
    int val = 0;
    std::map<Symbol, int>::const_iterator it = mTourMostStarsMap.find(s);
    if(it != mTourMostStarsMap.end()) val = it->second;
    return val;
}

int AccomplishmentProgress::GetToursGotAllStars() const {
    int num = 0;
    for(std::map<Symbol, int>::const_iterator it = mToursGotAllStarsMap.begin(); it != mToursGotAllStarsMap.end(); ++it){
        num += it->second;
    }
    return num;
}

int AccomplishmentProgress::GetToursGotAllStars(Symbol s) const {
    int val = 0;
    std::map<Symbol, int>::const_iterator it = mToursGotAllStarsMap.find(s);
    if(it != mToursGotAllStarsMap.end()) val = it->second;
    return val;
}

int AccomplishmentProgress::GetQuestCompletedCount() const {
    int num = 0;
    for(std::map<int, int>::const_iterator it = mGigTypeCompletedMap.begin(); it != mGigTypeCompletedMap.end(); ++it){
        num += it->second;
    }
    return num;
}

int AccomplishmentProgress::GetQuestCompletedCount(TourGameType ty) const {
    int val = 0;
    std::map<int, int>::const_iterator it = mGigTypeCompletedMap.find(ty);
    if(it != mGigTypeCompletedMap.end()) val = it->second;
    return val;
}

void AccomplishmentProgress::SetTotalSongsPlayed(int songs){
    mTotalSongsPlayed = songs;
    MILO_ASSERT(mParentProfile, 0x6D4);
    mParentProfile->MakeDirty();
}

void AccomplishmentProgress::SetTourTotalSongsPlayed(int songs){
    mTourTotalSongsPlayed = songs;
    MILO_ASSERT(mParentProfile, 0x6DD);
    mParentProfile->MakeDirty();
}

void AccomplishmentProgress::SetToursPlayed(Symbol s, int tours){
    mToursPlayedMap[s] = tours;
    MILO_ASSERT(mParentProfile, 0x6E6);
    mParentProfile->MakeDirty();
}

void AccomplishmentProgress::UpdateTourPlayed(Symbol s){
    int tourcount = GetToursPlayed(s);
    SetToursPlayed(s, tourcount + 1);
}

void AccomplishmentProgress::UpdateMostStars(Symbol s, int stars){
    int moststars = GetTourMostStars(s);
    if(stars > moststars){
        SetMostStars(s, stars);
    }
}

void AccomplishmentProgress::SetMostStars(Symbol s, int stars){
    mTourMostStarsMap[s] = stars;
    MILO_ASSERT(mParentProfile, 0x700);
    mParentProfile->MakeDirty();
}

void AccomplishmentProgress::SetToursGotAllStars(Symbol s, int stars){
    mToursGotAllStarsMap[s] = stars;
    MILO_ASSERT(mParentProfile, 0x709);
    mParentProfile->MakeDirty();
}

void AccomplishmentProgress::SetQuestCompletedCount(TourGameType ty, int count){
    mGigTypeCompletedMap[ty] = count;
    MILO_ASSERT(mParentProfile, 0x712);
    mParentProfile->MakeDirty();
}

BEGIN_HANDLERS(AccomplishmentProgress)
    HANDLE_EXPR(get_icon_hardcore_status, TheAccomplishmentMgr->GetIconHardCoreStatus(mAccomplishments.size()))
    HANDLE_ACTION(add_award, AddAward(_msg->Sym(2), _msg->Sym(3)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_CHECK(0x795)
END_HANDLERS