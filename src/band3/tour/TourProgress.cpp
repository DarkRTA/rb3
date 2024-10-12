#include "TourProgress.h"
#include "QuestJournal.h"
#include "Tour.h"
#include "TourDesc.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/BandProfile.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "obj/Object.h"
#include "os/DateTime.h"
#include "os/Debug.h"
#include "stl/pointers/_vector.h"
#include "tour/TourPropertyCollection.h"
#include "utl/BinStream.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

TourProgress::TourProgress() : mQuests(*this), mLastTouchTime(0), mOnTour(0), m_symTourDesc(""), mNumCompletedGigs(0), mCurrentQuest(gNullStr), mMetaScore(0), mNewStars(0), mWonQuest(0), mCurrentGigNum(0) {
    mSaveSizeMethod = &SaveSize;
    ClearQuestFilters();
    unk70.clear();
    unk88.clear();
    unka0.clear();
}

TourProgress::~TourProgress(){

}

void TourProgress::SyncSave(BinStream& bs){
    bs << m_symTourDesc;
    bs << mCurrentQuest;
    bs << mOnTour;
    for(int i = 0; i < 3; i++) bs << mQuestFilters[i];
    bs << mNumCompletedGigs;
    bs << mCurrentGigNum;
    bs << mNewStars;
    bs << unk70;
    bs << mMetaScore;
    bs << unk88;
    bs << unka0;
}

void TourProgress::SyncLoad(BinStream& bs){
    bs >> m_symTourDesc;
    bs >> mCurrentQuest;
    bs >> mOnTour;
    for(int i = 0; i < 3; i++) bs >> mQuestFilters[i];
    bs >> mNumCompletedGigs;
    bs >> mCurrentGigNum;
    bs >> mNewStars;
    bs >> unk70;
    bs >> mMetaScore;
    unk88.clear();
    unka0.clear();
    bs >> unk88;
    bs >> unka0;
}

void TourProgress::HandleTourRewardApplied(){
    HandleDirty(3);
}

void TourProgress::HandleDirty(int i){
    UpdateLastTouchTime();
    SetDirty(true, i);
    MetaPerformer* p = MetaPerformer::Current();
    if(p) p->SetSyncDirty(-1, true);
}

void TourProgress::UpdateLastTouchTime(){
    DateTime dt;
    GetDateAndTime(dt);
    mLastTouchTime = dt.ToCode();
}

String TourProgress::GetLastTouchedDateString() const {
    String ret;
    DateTime dt;
    dt = DateTime(mLastTouchTime);
    dt.ToString(ret);
    return ret;
}

void TourProgress::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << mLastTouchTime;
    stream << mQuests;
    stream << mTourProperties;
    stream << mOnTour;
    FixedSizeSaveable::SaveSymbolID(stream, m_symTourDesc);
    stream << mNumCompletedGigs;
    FixedSizeSaveable::SaveSymbolID(stream, mCurrentQuest);
    for(int i = 0; i < 3; i++) FixedSizeSaveable::SaveFixedSymbol(stream, mQuestFilters[i]);
    FixedSizeSaveable::SaveStd(stream, unk70, 10, 4);
}

int TourProgress::SaveSize(int i){
    int size = QuestJournal::SaveSize(i) + 4;
    size += TourPropertyCollection::SaveSize(i);
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "TourProgress", size + 0xCF);
    }
    return size + 0xCF;
}

void TourProgress::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    stream >> mLastTouchTime;
    stream >> mQuests;
    stream >> mTourProperties;
    stream >> mOnTour;
    FixedSizeSaveable::LoadSymbolFromID(stream, m_symTourDesc);
    stream >> mNumCompletedGigs;
    FixedSizeSaveable::LoadSymbolFromID(stream, mCurrentQuest);
    for(int i = 0; i < 3; i++) FixedSizeSaveable::LoadFixedSymbol(stream, mQuestFilters[i]);
    FixedSizeSaveable::LoadStd(stream, unk70, 10, 4);
}

const TourPropertyCollection& TourProgress::GetTourProperties() const { return mTourProperties; }
TourPropertyCollection& TourProgress::GetTourProperties() { return mTourProperties; }
const TourPropertyCollection& TourProgress::GetPerformanceProperties() const { return mPerformanceProperties; }
TourPropertyCollection& TourProgress::GetPerformanceProperties(){ return mPerformanceProperties; }

void TourProgress::ClearPerformanceState(){ ClearPeformanceProperties(); }
void TourProgress::ClearPeformanceProperties(){ mPerformanceProperties.Clear(); }

void TourProgress::UpdateMostStars(){
    BandProfile* owner = TheProfileMgr.FindTourProgressOwner(this);
    if(owner){
        owner->AccessAccomplishmentProgress();
        int stars = GetNumStars();
        TheAccomplishmentMgr->UpdateMostStarsForAllParticipants(m_symTourDesc, stars);
        TheTour->UpdateProgressWithCareerData();
    }
}

void TourProgress::HandleQuestFinished(){
    SetCurrentQuest(gNullStr);
    ClearQuestFilters();
}

void TourProgress::SetOnTour(bool b){
    mOnTour = b;
    HandleDirty(3);
}

bool TourProgress::IsOnTour() const { return mOnTour; }
Symbol TourProgress::GetTourDesc() const { return m_symTourDesc; }

void TourProgress::SetTourDesc(Symbol s){
    m_symTourDesc = s;
    HandleDirty(3);
}

Symbol TourProgress::GetFilterForCurrentGig() const {
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return gNullStr;
    else {
        MILO_ASSERT(pTourDesc, 0x13F);
        return pTourDesc->GetFilterForGigNum(mCurrentGigNum);
    }
}

Symbol TourProgress::GetSetlistTypeForCurrentGig(int i) const {
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return gNullStr;
    else {
        MILO_ASSERT(pTourDesc, 0x14E);
        return pTourDesc->GetSetlistTypeForGigNum(mCurrentGigNum, i);
    }
}

int TourProgress::GetNumSongsForCurrentGig() const {
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return 0;
    else {
        MILO_ASSERT(pTourDesc, 0x15D);
        return pTourDesc->GetNumSongsForGigNum(mCurrentGigNum);
    }
}

Symbol TourProgress::GetVenueForCurrentGig() const {
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return gNullStr;
    else {
        MILO_ASSERT(pTourDesc, 0x16C);
        return pTourDesc->GetVenueForGigNum(mCurrentGigNum);
    }
}

bool TourProgress::IsTourComplete() const {
    if(!mOnTour) return false;
    else return GetNumTotalGigs() <= mNumCompletedGigs;
}

bool TourProgress::AreAllTourGigsComplete() const {
    return GetNumTotalGigs() <= mNumCompletedGigs;
}

Symbol TourProgress::GetTourLeaderboardGoal() const {
    MILO_ASSERT(m_symTourDesc != "", 0x18E);
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return gNullStr;
    else {
        MILO_ASSERT(pTourDesc, 0x196);
        return pTourDesc->GetLeaderboardGoal();
    }
}

bool TourProgress::DoesTourHaveLeaderboard() const {
    MILO_ASSERT(m_symTourDesc != "", 0x19E);
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return false;
    else {
        MILO_ASSERT(pTourDesc, 0x1A6);
        return pTourDesc->HasLeaderboardGoal();
    }
}

int TourProgress::GetNumTotalGigs() const {
    MILO_ASSERT(m_symTourDesc != "", 0x1AE);
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return 0;
    else {
        MILO_ASSERT(pTourDesc, 0x1B6);
        return pTourDesc->GetNumGigs();
    }
}

void TourProgress::SetNumCompletedGigs(int num){
    mNumCompletedGigs = num;
    HandleDirty(3);
}

int TourProgress::GetCurrentGigNum() const { return mCurrentGigNum; }

int TourProgress::GetNumStarsForGig(int gig) const {
    if(gig >= unk70.size()) return 0;
    else return unk70[gig];
}

int TourProgress::GetNumCompletedGigs() const { return mNumCompletedGigs; }

void TourProgress::SetCurrentGigNum(int num){
    mCurrentGigNum = num;
    HandleDirty(3);
}

void TourProgress::SetCurrentQuest(Symbol q){
    mCurrentQuest = q;
    HandleDirty(3);
}

void TourProgress::ResetTourData(){
    mQuests.Clear();
    mTourProperties.Clear();
    unk70.clear();
    mNewStars = 0;
    mWonQuest = false;
    mCurrentGigNum = 0;
    mOnTour = false;
    mCurrentQuest = gNullStr;
    mMetaScore = 0;
    unk88.clear();
    unka0.clear();
    m_symTourDesc = gNullStr;
    ClearQuestFilters();
    ClearPerformanceState();
    SetNumCompletedGigs(0);
    HandleDirty(3);
}

float TourProgress::GetTourPropertyValue(Symbol s) const {
    return mTourProperties.GetPropertyValue(s);
}

void TourProgress::RemoveStars(int i){
    mNewStars -= i;
    HandleDirty(2);
}

void TourProgress::EarnStars(int i){
    mNewStars += i;
    HandleDirty(2);
}

bool TourProgress::GetWonQuest() const { return mWonQuest; }
void TourProgress::SetWonQuest(bool won){ mWonQuest = won; }

int TourProgress::GetTotalStarsForTour() const {
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return 0;
    else {
        MILO_ASSERT(pTourDesc, 0x22D);
        return pTourDesc->GetNumStarsPossibleForTour();
    }
}

int TourProgress::GetNumStars() const {
    int num = mNewStars;
    for(std::vector<int>::const_iterator it = unk70.begin(); it != unk70.end(); ++it){
        num += *it;
    }
    return num;
}

Symbol TourProgress::GetTourStatus(int i) const {
    return TheTour->GetTourStatusForStarCount(GetNumStars(), i);
}

int TourProgress::GetNumStarsForTourStatus(int i) const {
    return TheTour->GetStarsForTourStatus(GetTourStatus(i));
}

bool TourProgress::DoesTourStatusExist(int i) const {
    return TheTour->DoesTourStatusExist(GetNumStars(), i);
}

void TourProgress::FinalizeNewStars(){
    unk70.push_back(mNewStars);
    ClearNewStars();
    HandleDirty(2);
}

void TourProgress::ClearNewStars(){
    mNewStars = 0;
    HandleDirty(2);
}

Symbol TourProgress::GetNextCity() const {
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return gNullStr;
    else {
        MILO_ASSERT(pTourDesc, 0x270);
        return pTourDesc->GetCityForGigNum(mNumCompletedGigs);
    }
}

Symbol TourProgress::GetTourName() const {
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return gNullStr;
    else {
        MILO_ASSERT(pTourDesc, 0x27E);
        return pTourDesc->GetName();
    }
}

Symbol TourProgress::GetTourWelcome() const {
    TourDesc* pTourDesc = TheTour->GetTourDesc(m_symTourDesc);
    if(!pTourDesc) return gNullStr;
    else {
        MILO_ASSERT(pTourDesc, 0x28C);
        return pTourDesc->GetWelcome();
    }
}

bool TourProgress::AreQuestFiltersEmpty() const {
    for(int i = 0; i < 3; i++){
        if(mQuestFilters[i] != gNullStr) return false;
    }
    return true;
}

Symbol TourProgress::GetQuestFilter(int i_iIndex) const {
    MILO_ASSERT(( 0) <= ( i_iIndex) && ( i_iIndex) < ( kTour_NumQuestFilters), 0x2A2);
    return mQuestFilters[i_iIndex];
}

// undefined4 __thiscall TourProgress::GetQuestFilter(TourProgress *this,int param_1)

// {
//   bool bVar1;
//   char *pcVar2;
  
//   bVar1 = false;
//   if ((param_1 > -1) && (param_1 < 3)) {
//     bVar1 = true;
//   }
//   if (!bVar1) {
//     pcVar2 = ::MakeString(kAssertStr,s_TourProgress.cpp_80bacbf1,0x2a2,
//                           s_(_0)_<=_(_i_iIndex)_&&_(_i_iInde_80bacc20);
//     Debug::Fail((Debug *)TheDebug,pcVar2);
//   }
//   return *(undefined4 *)(this + param_1 * 4 + 0x7c);
// }

BEGIN_HANDLERS(TourProgress)
    HANDLE_ACTION(set_on_tour, SetOnTour(_msg->Int(2)))
END_HANDLERS