#include "tour/Tour.h"
#include "QuestManager.h"
#include "TourPerformer.h"
#include "TourProperty.h"
#include "game/BandUser.h"
#include "meta_band/BandProfile.h"
#include "meta_band/ProfileMgr.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/System.h"
#include "tour/TourDesc.h"
#include "tour/TourProgress.h"
#include "utl/Symbols.h"

Tour::Tour(DataArray*, const SongMgr& smgr, BandUserMgr& umgr, bool b) : mSongMgr(smgr), mBandUserMgr(umgr), m_pTourPerformer(0), m_pTourProgress(0), m_pProfile(0), mTourShowPostSeldiffScreen(0) {
    MILO_ASSERT(!TheTour, 0x3B);
    TheTour = this;
    SetName("tour", ObjectDir::Main());
    Init(SystemConfig("tour"));
}

Tour::~Tour(){

}

void Tour::Cleanup(){
    for(std::map<Symbol, TourProperty*>::iterator it = m_mapTourProperties.begin(); it != m_mapTourProperties.end(); ++it){
        TourProperty* pProperty = it->second;
        MILO_ASSERT(pProperty, 100);
        delete pProperty;
    }
    m_mapTourProperties.clear();
    for(std::map<Symbol, TourDesc*>::iterator it = m_mapTourDesc.begin(); it != m_mapTourDesc.end(); ++it){
        TourDesc* pTourDesc = it->second;
        MILO_ASSERT(pTourDesc, 0x6F);
        delete pTourDesc;
    }
    m_mapTourDesc.clear();
    m_vTourStatus.clear();
}

void Tour::Init(DataArray* arr){
    ConfigureTourPropertyData(arr->FindArray("tour_properties", true));
    ConfigureTourStatusData(arr->FindArray("tour_status_info", true));
    ConfigureTourDescData(arr->FindArray("tour_desc_info", true));
    mWeightManager.Init(arr->FindArray("tour_weight_info", true));
    arr->FindData(tour_show_post_seldiff_screen, mTourShowPostSeldiffScreen, false);
}

void Tour::ConfigureTourStatusData(DataArray* arr){
    for(int i = 1; i < arr->Size(); i++){
        DataArray* pStatusEntry = arr->Array(i);
        MILO_ASSERT(pStatusEntry->Size() == 2, 0x8A);
        TourStatusEntry entry;
        entry.mStatus = pStatusEntry->Sym(0);
        entry.mStars = pStatusEntry->Int(1);
        m_vTourStatus.push_back(entry);
    }
    for(int i = 1; i < m_vTourStatus.size(); i++){
        if(m_vTourStatus[i - 1].mStars >= m_vTourStatus[i].mStars)
        MILO_WARN("Tour status fan requirement values are not increasing!");
    }
}

Symbol Tour::GetTourStatusForStarCount(int i, int j) const {
    int iStatusIndex = j + GetTourStatusIndexForFanCount(i);
    MILO_ASSERT(iStatusIndex >= 0, 0xCC);
    MILO_ASSERT(iStatusIndex < m_vTourStatus.size(), 0xCD);
    return m_vTourStatus[iStatusIndex].mStatus;
}

int Tour::GetStarsForTourStatus(Symbol s) const {
    for(int i = 0; i < m_vTourStatus.size(); i++){
        if(m_vTourStatus[i].mStatus == s) return m_vTourStatus[i].mStars;
    }
    MILO_ASSERT(false, 0xDD);
    return 0;
}

bool Tour::HasTourProperty(Symbol s) const {
    return m_mapTourProperties.find(s) != m_mapTourProperties.end();
}

TourProperty* Tour::GetTourProperty(Symbol s) const {
    std::map<Symbol, TourProperty*>::const_iterator it = m_mapTourProperties.find(s);
    if(it != m_mapTourProperties.end()) return it->second;
    else return nullptr;
}

bool Tour::HasTourDesc(Symbol s) const {
    return m_mapTourDesc.find(s) != m_mapTourDesc.end();
}

TourDesc* Tour::GetTourDesc(Symbol s) const {
    std::map<Symbol, TourDesc*>::const_iterator it = m_mapTourDesc.find(s);
    if(it != m_mapTourDesc.end()) return it->second;
    else return nullptr;
}

TourProgress* Tour::GetTourProgress() const { return m_pTourProgress; }

BandProfile* Tour::GetProfile() const { return m_pProfile; }

LocalBandUser* Tour::GetUser() const {
    return !m_pProfile ? nullptr : m_pProfile->GetAssociatedLocalBandUser();
}

void Tour::ClearPerformer(){
    if(m_pTourPerformer){
        if(!m_pTourPerformer->IsLocal()){
            RELEASE(m_pTourProgress);
        }
        RELEASE(m_pTourPerformer);
        m_pTourProgress = 0;
    }
}

void Tour::UseUsersProgress(){
    MILO_ASSERT(m_pProfile, 0x173);
    m_pTourProgress = m_pProfile->GetTourProgress();
}

void Tour::ResetTourData(BandProfile* i_pProfile){
    MILO_ASSERT(i_pProfile, 0x17C);
    TourProgress* pProgress = i_pProfile->GetTourProgress();
    MILO_ASSERT(pProgress, 0x180);
    pProgress->ResetTourData();
}

bool Tour::IsUnderway(BandProfile* i_pProfile) const {
    MILO_ASSERT(i_pProfile, 0x1A5);
    TourProgress* pProgress = i_pProfile->GetTourProgress();
    MILO_ASSERT(pProgress, 0x1A9);
    return pProgress->IsOnTour();
}

bool Tour::HasGigSpecificIntro() const {
    MILO_ASSERT(m_pTourPerformer, 0x1B1);
    Quest* quest = TheQuestMgr.GetQuest(m_pTourPerformer->GetCurrentQuest());
    if(quest) return quest->HasCustomIntro();
    else return false;
}

bool Tour::HasGigSpecificOutro() const {
    MILO_ASSERT(m_pTourPerformer, 0x1C3);
    Quest* quest = TheQuestMgr.GetQuest(m_pTourPerformer->GetCurrentQuest());
    if(quest) return quest->HasCustomOutro();
    else return false;
}

Symbol Tour::GetGigSpecificIntro() const {
    MILO_ASSERT(m_pTourPerformer, 0x1D4);
    Quest* pQuest = TheQuestMgr.GetQuest(m_pTourPerformer->GetCurrentQuest());
    MILO_ASSERT(pQuest, 0x1D9);
    return pQuest->GetCustomIntro();
}

Symbol Tour::GetGigSpecificOutro() const {
    MILO_ASSERT(m_pTourPerformer, 0x1E1);
    Quest* pQuest = TheQuestMgr.GetQuest(m_pTourPerformer->GetCurrentQuest());
    MILO_ASSERT(pQuest, 0x1E6);
    return pQuest->GetCustomOutro();
}

Quest* Tour::GetQuest(){
    Quest* ret = 0;
    if(m_pTourPerformer){
        ret = TheQuestMgr.GetQuest(m_pTourPerformer->GetCurrentQuest());
    }
    return ret;
}

TourPerformerImpl* Tour::GetPerformer() const { return m_pTourPerformer; }

bool Tour::HasAnnouncement() const {
    return GetAnnouncement() != "";
}

Symbol Tour::GetGigFlavor() const {
    if(m_pTourProgress){
        TourDesc* pTourDesc = GetTourDesc(m_pTourProgress->GetTourDesc());
        MILO_ASSERT(pTourDesc, 0x226);
        return pTourDesc->GetFlavorForGigNum(m_pTourProgress->GetNumCompletedGigs());
    }
    else return "";
}

Symbol Tour::GetTourGigGuideMap() const {
    if(m_pTourProgress){
        TourDesc* pTourDesc = GetTourDesc(m_pTourProgress->GetTourDesc());
        if(pTourDesc) return pTourDesc->GetGigGuideMap();
    }
    return "";
}

Symbol Tour::GetConclusionText() const {
    if(m_pTourProgress){
        TourDesc* pTourDesc = GetTourDesc(m_pTourProgress->GetTourDesc());
        MILO_ASSERT(pTourDesc, 0x226);
        return pTourDesc->GetConclusionText();
    }
    else return "";
}

Symbol Tour::GetAnnouncement() const {
    if(m_pTourProgress){
        TourDesc* pTourDesc = GetTourDesc(m_pTourProgress->GetTourDesc());
        MILO_ASSERT(pTourDesc, 0x255);
        int gigs = m_pTourProgress->GetNumCompletedGigs();
        if(pTourDesc->HasAnnouncementScreen(gigs)){
            return pTourDesc->GetAnnouncementScreenForGigNum(gigs);
        }
    }
    return "";
}

Symbol Tour::GetMapScreen() const {
    if(m_pTourProgress){
        TourDesc* pTourDesc = GetTourDesc(m_pTourProgress->GetTourDesc());
        MILO_ASSERT(pTourDesc, 0x255);
        return pTourDesc->GetMapScreenForGigNum(m_pTourProgress->GetNumCompletedGigs());
    }
    return "";
}

const char* Tour::GetProgressOwnerName(){
    MILO_ASSERT(m_pTourProgress, 0x274);
    BandProfile* pProfile = TheProfileMgr.FindTourProgressOwner(m_pTourProgress);
    MILO_ASSERT(pProfile, 0x277);
    return pProfile->GetName();
}

int Tour::GetBronzeMedalGoalInCurrentTour() const {
    TourProgress* pProgress = m_pTourProgress;
    MILO_ASSERT(pProgress, 0x3A1);
    TourDesc* pTourDesc = GetTourDesc(pProgress->GetTourDesc());
    MILO_ASSERT(pTourDesc, 0x3A6);
    return pTourDesc->GetTourStarsBronzeGoalValue();
}

int Tour::GetSilverMedalGoalInCurrentTour() const {
    TourProgress* pProgress = m_pTourProgress;
    MILO_ASSERT(pProgress, 0x3AF);
    TourDesc* pTourDesc = GetTourDesc(pProgress->GetTourDesc());
    MILO_ASSERT(pTourDesc, 0x3B4);
    return pTourDesc->GetTourStarsSilverGoalValue();
}

int Tour::GetGoldMedalGoalInCurrentTour() const {
    TourProgress* pProgress = m_pTourProgress;
    MILO_ASSERT(pProgress, 0x3BD);
    TourDesc* pTourDesc = GetTourDesc(pProgress->GetTourDesc());
    MILO_ASSERT(pTourDesc, 0x3C2);
    return pTourDesc->GetTourStarsGoldGoalValue();
}

bool Tour::HasBronzeMedalInCurrentTour() const {
    TourProgress* pProgress = m_pTourProgress;
    MILO_ASSERT(pProgress, 0x3CB);
    return HasBronzeMedal(pProgress->GetTourDesc());
}

bool Tour::HasSilverMedalInCurrentTour() const {
    TourProgress* pProgress = m_pTourProgress;
    MILO_ASSERT(pProgress, 0x3D6);
    return HasSilverMedal(pProgress->GetTourDesc());
}

bool Tour::HasGoldMedalInCurrentTour() const {
    TourProgress* pProgress = m_pTourProgress;
    MILO_ASSERT(pProgress, 0x3E1);
    return HasGoldMedal(pProgress->GetTourDesc());
}

bool Tour::HasBronzeMedal(Symbol s) const {
    TourProgress* pProgress = m_pTourProgress;
    MILO_ASSERT(pProgress, 0x3EC);
    int stars = pProgress->GetTourMostStars(s);
    TourDesc* pTourDesc = GetTourDesc(s);
    MILO_ASSERT(pTourDesc, 0x3C2);
    int goal = pTourDesc->GetTourStarsBronzeGoalValue();
    return goal <= stars;
}

bool Tour::HasSilverMedal(Symbol s) const {
    TourProgress* pProgress = m_pTourProgress;
    MILO_ASSERT(pProgress, 0x3FA);
    int stars = pProgress->GetTourMostStars(s);
    TourDesc* pTourDesc = GetTourDesc(s);
    MILO_ASSERT(pTourDesc, 0x3FF);
    int goal = pTourDesc->GetTourStarsSilverGoalValue();
    return goal <= stars;
}

bool Tour::HasGoldMedal(Symbol s) const {
    TourProgress* pProgress = m_pTourProgress;
    MILO_ASSERT(pProgress, 0x408);
    int stars = pProgress->GetTourMostStars(s);
    TourDesc* pTourDesc = GetTourDesc(s);
    MILO_ASSERT(pTourDesc, 0x40D);
    int goal = pTourDesc->GetTourStarsGoldGoalValue();
    return goal <= stars;
}