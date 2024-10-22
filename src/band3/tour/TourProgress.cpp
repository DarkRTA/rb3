#include "TourProgress.h"
#include "QuestJournal.h"
#include "Tour.h"
#include "TourDesc.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/BandProfile.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/DateTime.h"
#include "os/Debug.h"
#include "stl/pointers/_vector.h"
#include "tour/TourProperty.h"
#include "tour/TourPropertyCollection.h"
#include "tour/TourSavable.h"
#include "utl/BinStream.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

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
    return !mOnTour ? false : GetNumTotalGigs() <= mNumCompletedGigs;
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
    MILO_ASSERT_RANGE( i_iIndex, 0, kTour_NumQuestFilters, 0x2A2);
    return mQuestFilters[i_iIndex];
}

bool TourProgress::HasQuestFilter(Symbol s) const {
    bool isdynamic = s == filter_dynamic_artist;
    for(int i = 0; i < 3; i++){
        Symbol filt = GetQuestFilter(i);
        if(filt == s) return true;
        if(isdynamic && strncmp("filter_artist_", filt.Str(), 0xE) == 0) return true;
    }
    return false;
}

void TourProgress::SetQuestFilter(int i_iIndex, Symbol s){
    MILO_ASSERT_RANGE( i_iIndex, 0, kTour_NumQuestFilters, 0x2C2);
    mQuestFilters[i_iIndex] = s;
    HandleDirty(3);
}

void TourProgress::ClearQuestFilters(){
    for(int i = 0; i < 3; i++){
        SetQuestFilter(i, gNullStr);
    }
}

int TourProgress::GetToursPlayed(Symbol s) const {
    int ret = 0;
    std::map<Symbol, int>::const_iterator it = unka0.find(s);
    if(it != unka0.end()) ret = it->second;
    return ret;
}

int TourProgress::GetTourMostStars(Symbol s) const {
    int ret = 0;
    std::map<Symbol, int>::const_iterator it = unk88.find(s);
    if(it != unk88.end()) ret = it->second;
    return ret;
}

void TourProgress::SetMetaScore(int i){
    mMetaScore = i;
    HandleDirty(3);
}

void TourProgress::SetToursPlayedMap(const std::map<Symbol, int>& map){
    unka0 = map;
    HandleDirty(3);
}

void TourProgress::SetTourMostStarsMap(const std::map<Symbol, int>& map){
    unk88 = map;
    HandleDirty(3);
}

void TourProgress::FakeFill(){
    mQuests.FakeFill();
    mTourProperties.FakeFill();
    mPerformanceProperties.FakeFill();
}

void TourProgress::DumpProperties(){
    MILO_LOG("\n***** Tour Property Dump *****\n\n");
    const std::map<Symbol, TourProperty*>& propmap = TheTour->TourProperties();
    for(std::map<Symbol, TourProperty*>::const_iterator it = propmap.begin(); it != propmap.end(); ++it){
        Symbol name = it->first;
        MILO_LOG("%s = %f\n", name.Str(), mTourProperties.GetPropertyValue(name));
    }
    MILO_LOG("\n******************************\n");
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(TourProgress)
    HANDLE_ACTION(set_on_tour, SetOnTour(_msg->Int(2)))
    HANDLE_EXPR(is_on_tour, IsOnTour())
    HANDLE_EXPR(is_tour_complete, IsTourComplete())
    HANDLE_ACTION(set_tour_desc, SetTourDesc(_msg->Sym(2)))
    HANDLE_EXPR(get_total_gigs, GetNumTotalGigs())
    HANDLE_EXPR(get_current_gig_num, GetCurrentGigNum() + 1)
    HANDLE_EXPR(get_num_completed_gigs, GetNumCompletedGigs())
    HANDLE_EXPR(get_stars_for_gig, GetNumStarsForGig(_msg->Int(2)))
    HANDLE_EXPR(are_all_tour_gigs_complete, AreAllTourGigsComplete())
    HANDLE_ACTION(reset_tour_data, ResetTourData())
    HANDLE_EXPR(get_property_value, GetTourPropertyValue(_msg->Sym(2)))
    HANDLE_EXPR(is_quest_won, GetWonQuest())
    HANDLE_EXPR(get_tour_status, GetTourStatus(_msg->Int(2)))
    HANDLE_EXPR(does_tour_status_exist, DoesTourStatusExist(_msg->Int(2)))
    HANDLE_EXPR(get_num_stars_for_tour_status, GetNumStarsForTourStatus(_msg->Int(2)))
    HANDLE_EXPR(get_num_stars, GetNumStars())
    HANDLE_EXPR(get_total_stars_for_tour, GetTotalStarsForTour())
    HANDLE_EXPR(get_last_touched_date_string, GetLastTouchedDateString())
    HANDLE_ACTION(clear_new_stars, ClearNewStars())
    HANDLE_ACTION(handle_quest_finished, HandleQuestFinished())
    HANDLE_ACTION(update_most_stars, UpdateMostStars())
    HANDLE_EXPR(get_tour_welcome, GetTourWelcome())
    HANDLE_EXPR(get_tour_name, GetTourName())
    HANDLE_EXPR(get_next_city, GetNextCity())
    HANDLE_EXPR(does_tour_have_leaderboard, DoesTourHaveLeaderboard())
    HANDLE_EXPR(get_tour_leaderboard_goal, GetTourLeaderboardGoal())
    HANDLE_ACTION(dump_properties, DumpProperties())
    HANDLE_SUPERCLASS(TourSavable)
    HANDLE_CHECK(0x373)
END_HANDLERS
#pragma pop

