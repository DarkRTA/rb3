#include "Campaign.h"
#include "BandProfile.h"
#include "CampaignLevel.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/GameMode.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/BandMachineMgr.h"
#include "meta_band/CampaignKey.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/ProfileSwappedMsg.h"
#include "tour/Tour.h"
#include "tour/TourDesc.h"
#include "tour/TourProgress.h"
#include "utl/Symbol.h"

Campaign* TheCampaign;

Campaign::Campaign(DataArray* arr) : m_pAccomplishmentMgr(new AccomplishmentManager()), m_symCurrentAccomplishment(""), m_bWasLaunchedIntoMusicLibrary(0),
    unk25(0), unk28(gNullStr), unk84(0), unk88(-1) {
    MILO_ASSERT(!TheCampaign, 0x34);
    TheCampaign = this;
    SetName("campaign", ObjectDir::Main());
    DataArray* accArr = arr->FindArray("accomplishment_info", true);
    m_pAccomplishmentMgr->Init(accArr);
    Init(arr);
    m_pAccomplishmentMgr->SanityCheckAwards();
    TheProfileMgr.AddSink(this, PrimaryProfileChangedMsg::Type());
    ThePlatformMgr.AddSink(this, ProfileSwappedMsg::Type());
}

Campaign::~Campaign(){
    TheProfileMgr.RemoveSink(this, PrimaryProfileChangedMsg::Type());
    ThePlatformMgr.RemoveSink(this, ProfileSwappedMsg::Type());
    TheCampaign = nullptr;
    Cleanup();
    RELEASE(m_pAccomplishmentMgr);
}

void Campaign::Cleanup(){
    for(std::map<Symbol, CampaignLevel*>::iterator it = m_mapCampaignLevels.begin(); it != m_mapCampaignLevels.end(); ++it){
        RELEASE(it->second);
    }
    m_mapCampaignLevels.clear();
    m_vCampaignLevels.clear();
    unk4c.clear();
    unk64.clear();
}

void Campaign::Init(DataArray* arr){
    ConfigureCampaignLevelData(arr->FindArray("campaign_levels", true));
    ConfigureCampaignKeyData(arr->FindArray("campaign_keys", true));
}

void Campaign::ConfigureCampaignLevelData(DataArray* arr){
    int i6 = -1;
    Symbol s = gNullStr;
    for(int i = 1; i < arr->Size(); i++){
        CampaignLevel* pCampaignLevel = new CampaignLevel(arr->Array(i), i - 1);
        MILO_ASSERT(pCampaignLevel, 0x70);

        Symbol levelname = pCampaignLevel->GetName();
        if(GetCampaignLevel(levelname)){
            MILO_WARN("%s campaign level already exists, skipping", levelname);
            delete pCampaignLevel;
        }
        else {
            int value = pCampaignLevel->GetValue();
            if(value <= i6){
                MILO_WARN("%s campaign level has decreasing value from last one", levelname);
            }
            if(pCampaignLevel->HasAward()){
                Symbol campaignAward = pCampaignLevel->GetAward();
                if(!TheAccomplishmentMgr->HasAward(campaignAward)){
                    MILO_WARN("%s campaign level  is using unknown award: %s!", levelname.Str(), campaignAward.Str());
                    delete pCampaignLevel;
                    goto lol;
                }
                TheAccomplishmentMgr->AddAwardSource(pCampaignLevel->GetAward(), pCampaignLevel->GetName());
            }
            m_mapCampaignLevels[levelname] = pCampaignLevel;
            m_vCampaignLevels.push_back(levelname);
            if(pCampaignLevel->IsMajorLevel()){
                s = levelname;
                unk64.push_back(s);
            }
            unk4c[levelname] = s;
lol:
            i6 = value;
        }
    }
}

void Campaign::ConfigureCampaignKeyData(DataArray* arr){
    for(int i = 1; i < arr->Size(); i++){
        CampaignKey* pCampaignKey = new CampaignKey(arr->Array(i));
        MILO_ASSERT(pCampaignKey, 0xA7);
        Symbol name = pCampaignKey->GetName();
        if(GetCampaignKey(name)){
            MILO_WARN("%s campaign key already exists, skipping", name);
        }
        else {
            m_mapCampaignKeys[name] = pCampaignKey;
        }
    }
    if((int)m_mapCampaignKeys.size() > 20){
        MILO_WARN("There are too many campaign keys! Key count = %i, Max = %i", m_mapCampaignKeys.size(), 20);
    }
}

bool Campaign::HasCampaignKey(Symbol s) const {
    return GetCampaignKey(s);
}

CampaignKey* Campaign::GetCampaignKey(Symbol s) const {
    std::map<Symbol, CampaignKey*>::const_iterator it = m_mapCampaignKeys.find(s);
    if(it != m_mapCampaignKeys.end()) return it->second;
    else return nullptr;
}

bool Campaign::HasCampaignLevel(Symbol s) const {
    return GetCampaignLevel(s);
}

CampaignLevel* Campaign::GetCampaignLevel(Symbol s) const {
    std::map<Symbol, CampaignLevel*>::const_iterator it = m_mapCampaignLevels.find(s);
    if(it != m_mapCampaignLevels.end()) return it->second;
    else return nullptr;
}

String Campaign::GetCampaignLevelIconForUser(LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0xE8);
    CampaignLevel* pCampaignLevel = GetCampaignLevel(GetCampaignLevelForUser(i_pUser));
    MILO_ASSERT(pCampaignLevel, 0xED);
    return pCampaignLevel->GetIconArt();
}

bool Campaign::HasScoreReachedCampaignLevel(int i, Symbol s) const {
    CampaignLevel* pCampaignLevel = GetCampaignLevel(s);
    MILO_ASSERT(pCampaignLevel, 0xF7);
    return pCampaignLevel->GetValue() <= i;
}

bool Campaign::HasReachedCampaignLevel(LocalBandUser* user, Symbol s) const {
    int score = GetCampaignMetaScoreForUser(user);
    return HasScoreReachedCampaignLevel(score, s);
}

bool Campaign::HasReachedCampaignLevel(Symbol s) const {
    BandProfile* profile = TheProfileMgr.GetPrimaryProfile();
    if(!profile) return false;
    CampaignLevel* pCampaignLevel = GetCampaignLevel(s);
    MILO_ASSERT(pCampaignLevel, 0x10E);
    TourProgress* tourprog;
    if(TheGameMode->InMode("tour") && (tourprog = TheTour->GetTourProgress(), tourprog) && tourprog->IsOnTour()){
        TourDesc* pTourDesc = TheTour->GetTourDesc(tourprog->GetTourDesc());
        MILO_ASSERT(pTourDesc, 0x118);
        CampaignLevel* pTourCampaignLevel = GetCampaignLevel(pTourDesc->GetRequiredCampaignLevel());
        MILO_ASSERT(pTourCampaignLevel, 0x11C);
        return pTourCampaignLevel->GetValue() >= pCampaignLevel->GetValue();
    }
    else {
        LocalBandUser* pUser = profile->GetAssociatedLocalBandUser();
        MILO_ASSERT(pUser, 0x125);
        CampaignLevel* pUserCampaignLevel = GetCampaignLevel(GetCampaignLevelForUser(pUser));
        MILO_ASSERT(pUserCampaignLevel, 0x128);
        return pUserCampaignLevel->GetValue() >= pCampaignLevel->GetValue();
    }
}

DECOMP_FORCEACTIVE(Campaign, "profile")

int Campaign::GetCampaignMetaScoreForProfile(BandProfile* i_pProfile) const {
    MILO_ASSERT(i_pProfile, 0x14B);
    int meta = i_pProfile->GetAccomplishmentProgress()->GetMetaScore();
    if(unk88 != -1) meta = unk88;
    return meta;
}

Symbol Campaign::GetCampaignLevelForMetaScore(int val) const {
    Symbol ret("");
    for(std::vector<Symbol>::const_reverse_iterator it = m_vCampaignLevels.rbegin(); it != m_vCampaignLevels.rend(); ++it){
        Symbol cur = *it;
        CampaignLevel* pCampaignLevel = GetCampaignLevel(cur);
        MILO_ASSERT(pCampaignLevel, 0x16A);
        if(val >= pCampaignLevel->GetValue()){
            ret = cur;
            break;
        }
    }
    return ret;
}

int Campaign::GetCampaignFanCountForUser(LocalBandUser* i_pUser) const {
    MILO_ASSERT(i_pUser, 0x17B);
    return TheAccomplishmentMgr->GetScaledFanValue(GetCampaignMetaScoreForUser(i_pUser));
}

int Campaign::GetPrimaryCampaignFanCount() const {
    BandMachineMgr* pMachineMgr = TheSessionMgr->mMachineMgr;
    MILO_ASSERT(pMachineMgr, 0x187);
    return TheAccomplishmentMgr->GetScaledFanValue(pMachineMgr->GetLeaderPrimaryMetaScore());
}

int Campaign::GetCampaignMetaScoreForUser(LocalBandUser* i_pUser) const {
    MILO_ASSERT(i_pUser, 0x192);
    int score = 0;
    BandProfile* profile = TheProfileMgr.GetProfileForUser(i_pUser);
    if(profile) score = GetCampaignMetaScoreForProfile(profile);
    return score;
}

Symbol Campaign::GetPrimaryCampaignLevel() const {
    BandMachineMgr* pMachineMgr = TheSessionMgr->mMachineMgr;
    MILO_ASSERT(pMachineMgr, 0x1A3);
    return GetCampaignLevelForMetaScore(pMachineMgr->GetLeaderPrimaryMetaScore());
}

DECOMP_FORCEACTIVE(Campaign, "iNumLevels > 0", "pLevel")

Symbol Campaign::GetCampaignLevelForUser(LocalBandUser* i_pUser) const {
    MILO_ASSERT(i_pUser, 0x1AF);
    return GetCampaignLevelForMetaScore(GetCampaignMetaScoreForUser(i_pUser));
}

bool Campaign::IsUserOnLastCampaignLevel(LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0x1CA);
    return IsLastCampaignLevel(GetCampaignLevelForUser(i_pUser));
}

bool Campaign::IsPrimaryUserOnLastCampaignLevel(){
    return IsLastCampaignLevel(GetPrimaryCampaignLevel());
}

bool Campaign::IsLastCampaignLevel(Symbol level) const {
    int iNumLevels = m_vCampaignLevels.size();
    for(int i = 0; i < iNumLevels; i++){
        if(level == m_vCampaignLevels[i]){
            return i == iNumLevels - 1;
        }
    }
    MILO_ASSERT(false, 0x1E7);
    return false;
}

Symbol Campaign::GetNextCampaignLevel(Symbol i_symCampaignLevel) const {
    MILO_ASSERT(!IsLastCampaignLevel( i_symCampaignLevel ), 0x1EF);
    int iNumLevels = m_vCampaignLevels.size();
    for(int iIndex = 0; iIndex < iNumLevels; iIndex++){
        if(i_symCampaignLevel == m_vCampaignLevels[iIndex]){
            MILO_ASSERT(iIndex < ( iNumLevels - 1 ), 0x1F8);
            return m_vCampaignLevels[iIndex + 1];
        }
    }
    MILO_ASSERT(false, 0x1FF);
    return Symbol("");
}

String Campaign::GetCurrentMajorLevelIcon(LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0x206);
    CampaignLevel* level = GetCampaignLevel(GetMajorLevelForMetaScore(GetCampaignMetaScoreForUser(i_pUser)));
    if(level) return level->GetIconArt();
    else return "";
}

String Campaign::GetNextMajorLevelIcon(LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0x216);
    CampaignLevel* level = GetCampaignLevel(GetNextMajorLevelForMetaScore(GetCampaignMetaScoreForUser(i_pUser)));
    if(level) return level->GetIconArt();
    else return "";
}

String Campaign::GetPrimaryCurrentMajorLevelIcon(){
    BandMachineMgr* pMachineMgr = TheSessionMgr->mMachineMgr;
    MILO_ASSERT(pMachineMgr, 0x227);
    CampaignLevel* level = GetCampaignLevel(GetMajorLevelForMetaScore(pMachineMgr->GetLeaderPrimaryMetaScore()));
    if(level) return level->GetIconArt();
    else return "";
}

String Campaign::GetPrimaryNextMajorLevelIcon(){
    BandMachineMgr* pMachineMgr = TheSessionMgr->mMachineMgr;
    MILO_ASSERT(pMachineMgr, 0x238);
    CampaignLevel* level = GetCampaignLevel(GetNextMajorLevelForMetaScore(pMachineMgr->GetLeaderPrimaryMetaScore()));
    if(level) return level->GetIconArt();
    else return "";
}

void Campaign::UpdatePrimaryCurrentMajorLevelIcon(UIPicture* i_pPicture){
    MILO_ASSERT(i_pPicture, 0x248);
    String icon = GetPrimaryCurrentMajorLevelIcon();
    const char* iconstr = icon.c_str();
    if(strcmp(iconstr, "") == 0){
        i_pPicture->SetShowing(false);
    }
    else {
        i_pPicture->SetTex(FilePath(iconstr));
        i_pPicture->SetShowing(true);
    }
}

void Campaign::UpdatePrimaryNextMajorLevelIcon(UIPicture* i_pPicture){
    MILO_ASSERT(i_pPicture, 0x259);
    String icon = GetPrimaryNextMajorLevelIcon();
    const char* iconstr = icon.c_str();
    if(strcmp(iconstr, "") == 0){
        i_pPicture->SetShowing(false);
    }
    else {
        i_pPicture->SetTex(FilePath(iconstr));
        i_pPicture->SetShowing(true);
    }
}

void Campaign::UpdateCurrentMajorLevelIcon(LocalBandUser* i_pUser, UIPicture* i_pPicture){
    MILO_ASSERT(i_pUser, 0x26A);
    MILO_ASSERT(i_pPicture, 0x26B);
    String icon = GetCurrentMajorLevelIcon(i_pUser);
    const char* iconstr = icon.c_str();
    if(strcmp(iconstr, "") == 0){
        i_pPicture->SetShowing(false);
    }
    else {
        i_pPicture->SetTex(FilePath(iconstr));
        i_pPicture->SetShowing(true);
    }
}

void Campaign::UpdateNextMajorLevelIcon(LocalBandUser* i_pUser, UIPicture* i_pPicture){
    MILO_ASSERT(i_pUser, 0x27C);
    MILO_ASSERT(i_pPicture, 0x27D);
    String icon = GetNextMajorLevelIcon(i_pUser);
    const char* iconstr = icon.c_str();
    if(strcmp(iconstr, "") == 0){
        i_pPicture->SetShowing(false);
    }
    else {
        i_pPicture->SetTex(FilePath(iconstr));
        i_pPicture->SetShowing(true);
    }
}

int Campaign::GetTotalPointsForNextCampaignLevelForUser(LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0x28E);
    Symbol level = GetCampaignLevelForUser(i_pUser);
    if(IsLastCampaignLevel(level)) return 0;
    else {
        Symbol next = GetNextCampaignLevel(level);
        CampaignLevel* pCampaignLevel = GetCampaignLevel(level);
        MILO_ASSERT(pCampaignLevel, 0x29B);
        CampaignLevel* pNextCampaignLevel = GetCampaignLevel(next);
        MILO_ASSERT(pNextCampaignLevel, 0x29E);
        int iCampaignLevel = pCampaignLevel->GetValue();
        int iNextCampaignLevel = pNextCampaignLevel->GetValue();
        MILO_ASSERT(iNextCampaignLevel >= iCampaignLevel, 0x2A2);
        return iNextCampaignLevel - iCampaignLevel;
    }
}

int Campaign::GetCurrentPointsForNextCampaignLevelForUser(LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0x2AA);
    Symbol level = GetCampaignLevelForUser(i_pUser);
    if(IsLastCampaignLevel(level)) return 0;
    else {
        BandProfile* pProfile = TheProfileMgr.GetProfileForUser(i_pUser);
        MILO_ASSERT(pProfile, 0x2B5);
        int iCurrentMetaScore = GetCampaignMetaScoreForProfile(pProfile);
        CampaignLevel* pCampaignLevel = GetCampaignLevel(level);
        MILO_ASSERT(pCampaignLevel, 0x2BA);
        int iCampaignLevel = pCampaignLevel->GetValue();
        MILO_ASSERT(iCurrentMetaScore >= iCampaignLevel, 0x2BE);
        return iCurrentMetaScore - iCampaignLevel;
    }
}

int Campaign::GetTotalPointsForNextMajorCampaignLevelForMetaScore(int i_iMetaScore){
    int iCurrentMajorLevel = 0;
    int iNextMajorLevel = 0;
    CampaignLevel* cur = GetCampaignLevel(GetMajorLevelForMetaScore(i_iMetaScore));
    if(cur) iCurrentMajorLevel = cur->GetValue();
    CampaignLevel* next = GetCampaignLevel(GetNextMajorLevelForMetaScore(i_iMetaScore));
    if(next) iNextMajorLevel = next->GetValue();
    MILO_ASSERT(iNextMajorLevel >= iCurrentMajorLevel, 0x2D7);
    MILO_ASSERT(i_iMetaScore >= iCurrentMajorLevel, 0x2D8);
    return iNextMajorLevel - iCurrentMajorLevel;
}

int Campaign::GetTotalPointsForNextMajorCampaignLevelForPrimary(){
    if(IsPrimaryUserOnLastCampaignLevel()) return 0;
    else {
        BandMachineMgr* pMachineMgr = TheSessionMgr->mMachineMgr;
        MILO_ASSERT(pMachineMgr, 0x2E8);
        return GetTotalPointsForNextMajorCampaignLevelForMetaScore(pMachineMgr->GetLeaderPrimaryMetaScore());
    }
}

int Campaign::GetTotalPointsForNextMajorCampaignLevelForUser(LocalBandUser* user){
    if(IsUserOnLastCampaignLevel(user)) return 0;
    else {
        return GetTotalPointsForNextMajorCampaignLevelForMetaScore(GetCampaignMetaScoreForUser(user));
    }
}

int Campaign::GetCurrentPointsForNextMajorCampaignLevelForMetaScore(int i_iMetaScore){
    int iCurrentMajorLevel = 0;
    int iNextMajorLevel = 0;
    CampaignLevel* cur = GetCampaignLevel(GetMajorLevelForMetaScore(i_iMetaScore));
    if(cur) iCurrentMajorLevel = cur->GetValue();
    CampaignLevel* next = GetCampaignLevel(GetNextMajorLevelForMetaScore(i_iMetaScore));
    if(next) iNextMajorLevel = next->GetValue();
    MILO_ASSERT(iNextMajorLevel >= iCurrentMajorLevel, 0x30E);
    MILO_ASSERT(i_iMetaScore >= iCurrentMajorLevel, 0x30F);
    return i_iMetaScore - iCurrentMajorLevel;
}

int Campaign::GetCurrentPointsForNextMajorCampaignLevelForPrimary(){
    if(IsPrimaryUserOnLastCampaignLevel()) return 0;
    else {
        BandMachineMgr* pMachineMgr = TheSessionMgr->mMachineMgr;
        MILO_ASSERT(pMachineMgr, 0x31E);
        return GetCurrentPointsForNextMajorCampaignLevelForMetaScore(pMachineMgr->GetLeaderPrimaryMetaScore());
    }
}

int Campaign::GetCurrentPointsForNextMajorCampaignLevelForUser(LocalBandUser* user){
    if(IsUserOnLastCampaignLevel(user)) return 0;
    else {
        return GetCurrentPointsForNextMajorCampaignLevelForMetaScore(GetCampaignMetaScoreForUser(user));
    }
}

void Campaign::ClearCurrentGoal(){
    m_symCurrentAccomplishment = "";
    m_bWasLaunchedIntoMusicLibrary = false;
}

bool Campaign::HasCurrentGoal() const {
    return m_symCurrentAccomplishment != "";
}

Symbol Campaign::GetCurrentGoal() const { return m_symCurrentAccomplishment; }

Symbol Campaign::GetCurrentGoalDescription() const {
    Symbol ret = gNullStr;
    if(m_symCurrentAccomplishment != gNullStr){
        Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(m_symCurrentAccomplishment);
        MILO_ASSERT(pAccomplishment, 0x34B);
        ret = pAccomplishment->GetDescription();
    }
    return ret;
}

String Campaign::GetCurrentGoalIcon() const {
    if(m_symCurrentAccomplishment != gNullStr){
        Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(m_symCurrentAccomplishment);
        MILO_ASSERT(pAccomplishment, 0x359);
        return pAccomplishment->GetIconArt();
    }
    else return "";
}

void Campaign::SetupLaunchedAccomplishmentInfo(Symbol acc){
    m_symCurrentAccomplishment = acc;
    m_bWasLaunchedIntoMusicLibrary = false;
    unk25 = false;
}

void Campaign::SetWasLaunchedIntoMusicLibrary(bool b){ m_bWasLaunchedIntoMusicLibrary = b; }

Difficulty Campaign::GetMinimumDifficultyForCurrentAccomplishment() const {
    if(m_symCurrentAccomplishment == "") return kDifficultyEasy;
    else {
        Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(m_symCurrentAccomplishment);
        MILO_ASSERT(pAccomplishment, 0x37A);
        return pAccomplishment->GetRequiredDifficulty();
    }
}