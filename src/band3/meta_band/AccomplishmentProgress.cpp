#include "meta_band/AccomplishmentProgress.h"
#include "Accomplishment.h"
#include "Campaign.h"
#include "game/BandUser.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/AccomplishmentCategory.h"
#include "meta_band/AccomplishmentGroup.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/MetaPerformer.h"
#include "os/Debug.h"
#include "stl/_pair.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

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

AccomplishmentProgress::AccomplishmentProgress(BandProfile* profile) : mParentProfile(profile), mMetaScore(0), unk644(1), unk648(0) {
    Clear();
    mSaveSizeMethod = &SaveSize;
}

AccomplishmentProgress::~AccomplishmentProgress(){

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
        int lbhcstatus = TheAccomplishmentMgr->GetLeaderboardHardcoreStatus(unk4c.size());
        TheAccomplishmentMgr->GetIconHardCoreStatus(unk4c.size());
        unk4c.insert(s);
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
    return unk4c.find(s) != unk4c.end();
}

bool AccomplishmentProgress::HasNewAwards() const {
    return !unka0.empty();
}

Symbol AccomplishmentProgress::GetFirstNewAward() const {
    MILO_ASSERT(HasNewAwards(), 0x158);
    return unka0.front().first;
}

Symbol AccomplishmentProgress::GetFirstNewAwardReason() const {
    MILO_ASSERT(HasNewAwards(), 0x161);
    return unka0.front().second;
}

void AccomplishmentProgress::ClearFirstNewAward(){
    MILO_ASSERT(HasNewAwards(), 0x16A);
    unka0.pop_front();
    mParentProfile->MakeDirty();
}

void AccomplishmentProgress::AddNewRewardVignette(Symbol s){
    std::list<Symbol>::iterator it;
    for(it = unka8.begin(); it != unka8.end() && *it != s; ++it);
    if(it == unka8.end()){
        unka8.push_back(s);
    }
    unkb0.insert(s);
    mParentProfile->MakeDirty();
}

bool AccomplishmentProgress::IsUploadDirty() const {
    return unk644 || !unk64.empty();
}

bool AccomplishmentProgress::HasNewRewardVignettes() const {
    return !unka8.empty();
}

Symbol AccomplishmentProgress::GetFirstNewRewardVignette() const {
    MILO_ASSERT(HasNewRewardVignettes(), 0x18C);
    return unka8.front();
}

void AccomplishmentProgress::ClearFirstNewRewardVignette(){
    MILO_ASSERT(HasNewRewardVignettes(), 0x194);
    unka8.pop_front();
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
        unk88.insert(s1);
        unka0.push_back(std::make_pair(s1, s2));
        Award* pAward = TheAccomplishmentMgr->GetAward(s1);
        MILO_ASSERT(pAward, 0x1BD);
        pAward->GrantAwards(mParentProfile);
        mParentProfile->MakeDirty();
        return true;
    }
    else return false;
}

bool AccomplishmentProgress::HasAward(Symbol s) const {
    return unk88.find(s) != unk88.end();
}

void AccomplishmentProgress::Poll(){}

void AccomplishmentProgress::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << unk644;
    FixedSizeSaveable::SaveStd(stream, unk4c, 1000);
    FixedSizeSaveable::SaveStd(stream, unk64, 1000);
    FixedSizeSaveable::SaveStd(stream, unk88, 500);
    FixedSizeSaveable::SaveStd(stream, unka8, 20);
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
    stream << unk5dc;
    stream << unk5e0;
    stream << unk645;
    FixedSizeSaveable::SaveStd(stream, unk5e4, 10, 8);
    FixedSizeSaveable::SaveStd(stream, unk5fc, 10, 8);
    FixedSizeSaveable::SaveStd(stream, unk614, 10, 8);
    FixedSizeSaveable::SaveStd(stream, unk62c, 0x32, 8);
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

int AccomplishmentProgress::GetNumCompleted() const { return unk4c.size(); }

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

}

int AccomplishmentProgress::GetBestSolo(ScoreType s, Difficulty d) const { return mBestSolo[s][d]; }

int AccomplishmentProgress::GetBestAccuracy(ScoreType s, Difficulty d) const { return mBestAccuracy[s][d]; }

int AccomplishmentProgress::GetBestHoposPercent(ScoreType s, Difficulty d) const { return mBestHoposPercent[s][d]; }

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

int AccomplishmentProgress::GetTotalDrumRollCount(Difficulty d) const { return mTotalDrumRollCount[d]; }

int AccomplishmentProgress::GetTotalProDrumRollCount(Difficulty d) const { return mTotalProDrumRollCount[d]; }

int AccomplishmentProgress::GetBestKickPercent(Difficulty d) const { return mBestKickPercent[d]; }

int AccomplishmentProgress::GetBestProKickPercent(Difficulty d) const { return mBestProKickPercent[d]; }

int AccomplishmentProgress::GetBestDrumRollPercent(Difficulty d) const { return mBestDrumRollPercent[d]; }

int AccomplishmentProgress::GetBestSoloButtonPercent(Difficulty d) const { return mBestSoloButtonPercent[d]; }

void AccomplishmentProgress::ClearStepTrackingMap(){ mStepTrackingMap.clear(); }