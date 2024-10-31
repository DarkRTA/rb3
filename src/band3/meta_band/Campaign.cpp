#include "Campaign.h"
#include "BandProfile.h"
#include "CampaignLevel.h"
#include "bandobj/MeterDisplay.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameMode.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentCategory.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/BandMachineMgr.h"
#include "meta_band/CampaignKey.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/UIEventMgr.h"
#include "obj/Data.h"
#include "obj/DataFile.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/ProfileSwappedMsg.h"
#include "os/User.h"
#include "tour/Tour.h"
#include "tour/TourDesc.h"
#include "tour/TourProgress.h"
#include "ui/UIPicture.h"
#include "utl/FilePath.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

DataArray* s_pReloadedCampaignData;
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

ScoreType Campaign::GetRequiredScoreTypeForGoal(Symbol s) const {
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(s);
    MILO_ASSERT(pAccomplishment, 0x383);
    return pAccomplishment->GetRequiredScoreType();
}

ScoreType Campaign::GetRequiredScoreTypeForCurrentAccomplishment() const {
    if(m_symCurrentAccomplishment == "") return kScoreBand;
    else return GetRequiredScoreTypeForGoal(m_symCurrentAccomplishment);
}

TrackType Campaign::GetRequiredTrackTypeForGoal(Symbol goal) const {
    return ScoreTypeToTrackType(GetRequiredScoreTypeForGoal(goal));
}

TrackType Campaign::GetRequiredTrackTypeForCurrentAccomplishment() const {
    if(m_symCurrentAccomplishment == "") return kTrackNone;
    else return GetRequiredTrackTypeForGoal(m_symCurrentAccomplishment);
}

bool Campaign::HasValidUser() const {
    LocalBandUser* u = GetUser();
    if(!u) return false;
    else return TheProfileMgr.GetProfileForUser(u);
}

LocalBandUser* Campaign::GetLaunchUser() const {
    LocalBandUser* u = GetUser();
    if(u) return u;
    else return nullptr;
}

LocalBandUser* Campaign::GetUser() const {
    return !unk84 ? nullptr : unk84->GetAssociatedLocalBandUser();
}

BandProfile* Campaign::GetProfile() const { return unk84; }

Symbol Campaign::GetMajorLevelForMetaScore(int score){
    Symbol key = GetCampaignLevelForMetaScore(score);
    std::map<Symbol, Symbol>::iterator it = unk4c.find(key);
    if(it != unk4c.end()) return it->second;
    else return gNullStr;
}

Symbol Campaign::GetNextMajorLevelForMetaScore(int score){
    Symbol symCurrentMajorLevel = GetMajorLevelForMetaScore(score);
    MILO_ASSERT(!IsLastCampaignLevel( symCurrentMajorLevel ), 0x410);
    int num = unk64.size();
    for(int i = 0; i < num; i++){
        if(unk64[i] == symCurrentMajorLevel){
            if(i < num - 1){
                return unk64[i + 1];
            }
            else return gNullStr;
        }
    }
    MILO_ASSERT(false, 0x425);
    return gNullStr;
}

void Campaign::UpdateProgressMeter(MeterDisplay* i_pMeter, LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0x42C);
    MILO_ASSERT(i_pMeter, 0x42D);
    int current = GetCurrentPointsForNextMajorCampaignLevelForUser(i_pUser);
    int total = GetTotalPointsForNextMajorCampaignLevelForUser(i_pUser);
    i_pMeter->SetValues(current, total);
}

void Campaign::UpdatePrimaryProgressMeter(MeterDisplay* i_pMeter){
    MILO_ASSERT(i_pMeter, 0x436);
    int current = GetCurrentPointsForNextMajorCampaignLevelForPrimary();
    int total = GetTotalPointsForNextMajorCampaignLevelForPrimary();
    i_pMeter->SetValues(current, total);
}

DataNode Campaign::OnMsg(const ProfileSwappedMsg& msg){
    LocalUser* pUser1 = msg.GetUser1();
    MILO_ASSERT(pUser1, 0x441);
    MILO_ASSERT(pUser1->IsLocal(), 0x442);
    LocalBandUser* pLocalUser1 = BandUserMgr::GetLocalBandUser(pUser1);
    MILO_ASSERT(pLocalUser1, 0x444);
    LocalUser* pUser2 = msg.GetUser2();
    MILO_ASSERT(pUser2, 0x446);
    MILO_ASSERT(pUser2->IsLocal(), 0x447);
    LocalBandUser* pLocalUser2 = BandUserMgr::GetLocalBandUser(pUser2);
    MILO_ASSERT(pLocalUser2, 0x449);
    LocalBandUser* launchUser = GetLaunchUser();
    if(launchUser == pLocalUser1 || launchUser == pLocalUser2){
        ClearCurrentGoal();
    }
    return 1;
}

DataNode Campaign::OnMsg(const PrimaryProfileChangedMsg& msg){
    BandProfile* profile = TheProfileMgr.GetPrimaryProfile();
    if(profile) unk84 = profile;

    if(!TheGameMode->InMode(campaign) && !TheGameMode->InMode(qp_career_songinfo)){
        return 1;
    }
    else if(!profile){
        m_symCurrentAccomplishment = gNullStr;
        static Message init("init", 0);
        init[0] = 3;
        TheUIEventMgr->TriggerEvent(sign_out, init);
    }
    return 1;
}

bool Campaign::CanSkipSongs(){
    if(m_symCurrentAccomplishment != gNullStr){
        Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(m_symCurrentAccomplishment);
        MILO_ASSERT(pAccomplishment, 0x480);
        if(pAccomplishment->GetType() == kAccomplishmentTypeSetlist) return false;
    }
    return true;
}

bool Campaign::CanResumeSongs(){
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(m_symCurrentAccomplishment);
    MILO_ASSERT(pAccomplishment, 0x490);
    if(pAccomplishment->GetType() == kAccomplishmentTypeSetlist) return false;
    else return true;
}

bool Campaign::CanSaveSetlists(){
    return m_symCurrentAccomplishment == acc_createsetlist;
}

Symbol Campaign::GetNextHintToShow() const {
    BandProfile* profile = TheProfileMgr.GetPrimaryProfile();
    if(profile){
        if(!profile->HasSeenHint(hint_goalcomplete_screen)){
            if(profile->GetAccomplishmentProgress()->GetNumCompleted() > 0){
                return hint_goalcomplete_screen;
            }
        }
    }
    return gNullStr;
}

bool Campaign::HasHintsToShow() const {
    Symbol hint = GetNextHintToShow();
    return hint != gNullStr;
}

Symbol Campaign::GetCampaignLevelAdvertisement(Symbol level) const {
    CampaignLevel* pCampaignLevel = GetCampaignLevel(level);
    MILO_ASSERT(pCampaignLevel, 0x4E2);
    return pCampaignLevel->GetAdvertisement();
}

bool Campaign::GetWasLaunchedIntoMusicLibrary() const { return m_bWasLaunchedIntoMusicLibrary; }

bool Campaign::DidUserMakeProgressOnGoal(LocalBandUser* i_pUser, Symbol goal){
    MILO_ASSERT(i_pUser, 0x4F0);
    return TheAccomplishmentMgr->DidUserMakeProgressOnGoal(i_pUser, goal);
}

void Campaign::UpdateEndGameInfoForCurrentCampaignGoal(UILabel* i_pUserLabel, UILabel* i_pStatusLabel, UIPicture* i_pPicture){
    MILO_ASSERT(i_pUserLabel, 0x53E);
    MILO_ASSERT(i_pStatusLabel, 0x53F);
    MILO_ASSERT(i_pPicture, 0x540);
    LocalBandUser* pUser = GetUser();
    MILO_ASSERT(pUser, 0x54D);
    Symbol goal = m_symCurrentAccomplishment;
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(goal);
    MILO_ASSERT(pAccomplishment, 0x552);
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(pUser);
    if(!pProfile){
        i_pPicture->SetTex(FilePath(pAccomplishment->GetIconArt()));
        i_pUserLabel->SetTokenFmt(campaign_endgame_user_noprogress, pUser->Name());
        i_pStatusLabel->SetTokenFmt(campaign_endgame_goal_noprogress, goal);
    }
    else {
        MILO_ASSERT(pProfile, 0x560);
        AccomplishmentProgress* prog = pProfile->GetAccomplishmentProgress();
        unk28 = goal;
        if(prog->IsAccomplished(goal)){
            int othergoals = TheAccomplishmentMgr->GetNumOtherGoalsAcquired(pUser->Name(), goal);
            i_pPicture->SetTex(FilePath(pAccomplishment->GetIconArt()));
            i_pUserLabel->SetTokenFmt(campaign_endgame_user_congrats, pUser->Name());
            if(othergoals == 0){
                i_pStatusLabel->SetTokenFmt(campaign_endgame_goal_complete, goal);
            }
            else if(othergoals == 1){
                i_pStatusLabel->SetTokenFmt(campaign_endgame_goal_complete_and1more, goal);
            }
            else {
                i_pStatusLabel->SetTokenFmt(campaign_endgame_goal_complete_andmore, goal, othergoals);
            }
        }
        else {
            if(DidUserMakeProgressOnGoal(pUser, goal)){
                i_pPicture->SetTex(FilePath(pAccomplishment->GetIconArt()));
                i_pUserLabel->SetTokenFmt(campaign_endgame_user_progress, pUser->Name());
                int iCurrent = 0;
                int iMax = 0;
                pAccomplishment->InqProgressValues(pProfile, iCurrent, iMax);
                MILO_ASSERT(iMax > iCurrent, 0x584);
                int diff = iMax - iCurrent;
                if(pAccomplishment->HasAward()){
                    i_pStatusLabel->SetTokenFmt(campaign_endgame_goal_progress_reward, goal, diff, pAccomplishment->GetUnitsToken(diff));
                }
                else {
                    i_pStatusLabel->SetTokenFmt(campaign_endgame_goal_progress, goal, diff, pAccomplishment->GetUnitsToken(diff));
                }
            }
            else {   
                i_pPicture->SetTex(FilePath(pAccomplishment->GetIconArt()));
                i_pUserLabel->SetTokenFmt(campaign_endgame_user_noprogress, pUser->Name());
                i_pStatusLabel->SetTokenFmt(campaign_endgame_goal_noprogress, goal);             
            }
        }
    }
}

DECOMP_FORCEACTIVE(Campaign, "iNumUsersWithGoals > 0", "pSelectedUser")

void Campaign::UpdateEndGameInfo(UILabel* i_pUserLabel, UILabel* i_pStatusLabel, UIPicture* i_pPicture){
    MILO_ASSERT(i_pUserLabel, 0x61F);
    MILO_ASSERT(i_pStatusLabel, 0x620);
    MILO_ASSERT(i_pPicture, 0x621);
    bool show = true;
    if(TheGameMode->InMode("campaign") && m_symCurrentAccomplishment != ""){
        UpdateEndGameInfoForCurrentCampaignGoal(i_pUserLabel, i_pStatusLabel, i_pPicture);
    }
    else {
        i_pUserLabel->SetTextToken(gNullStr);
        i_pStatusLabel->SetTextToken(gNullStr);
        show = false;
        unk28 = gNullStr;
    }
    i_pPicture->SetShowing(show);
}

bool Campaign::HasDisplayGoal(){
    return unk28 != gNullStr;
}

Symbol Campaign::GetCategoryGroup(Symbol s){
    AccomplishmentCategory* pAccomplishmentCategory = TheAccomplishmentMgr->GetAccomplishmentCategory(s);
    MILO_ASSERT(pAccomplishmentCategory, 0x64D);
    return pAccomplishmentCategory->GetGroup();
}

Symbol Campaign::GetGoalCategory(Symbol s){
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(s);
    MILO_ASSERT(pAccomplishment, 0x656);
    return pAccomplishment->GetCategory();
}

Symbol Campaign::GetDisplayGoal(){ return unk28; }
bool Campaign::ShouldReturnToCategoryScreen(){ return unk25; }

void Campaign::HandleLaunchedGoalComplete(){
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(m_symCurrentAccomplishment);
    MILO_ASSERT(pAccomplishment, 0x66C);
    LocalBandUser* pUser = GetUser();
    MILO_ASSERT(pUser, 0x66E);
    BandProfile* pUserProfile = TheProfileMgr.GetProfileForUser(pUser);
    MILO_ASSERT(pUserProfile, 0x670);
    unk25 = TheAccomplishmentMgr->IsCategoryComplete(pUserProfile, pAccomplishment->GetCategory());
}

RndTex* Campaign::GetPrimaryBandLogoTex(){
    BandMachineMgr* pMachineMgr = TheSessionMgr->mMachineMgr;
    MILO_ASSERT(pMachineMgr, 0x67B);
    if(pMachineMgr->IsLeaderMachineLocal()){
        BandProfile* pProfile = TheProfileMgr.GetPrimaryProfile();
        MILO_ASSERT(pProfile, 0x681);
        return pProfile->GetBandLogoTex();
    }
    else return nullptr;
}

void Campaign::CheatNextMetaLevel(){
    BandMachineMgr* pMachineMgr = TheSessionMgr->mMachineMgr;
    MILO_ASSERT(pMachineMgr, 0x68F);
    if(unk88 == -1){
        unk88 = 0;
        pMachineMgr->RefreshPrimaryProfileInfo();
    }
    else {
        Symbol level = GetCampaignLevelForMetaScore(unk88);
        if(IsLastCampaignLevel(level)){
            unk88 = -1;
            pMachineMgr->RefreshPrimaryProfileInfo();
        }
        else {
            Symbol nextlevel = GetNextCampaignLevel(level);
            CampaignLevel* pNextCampaignLevel = GetCampaignLevel(nextlevel);
            MILO_ASSERT(pNextCampaignLevel, 0x6A9);
            unk88 = pNextCampaignLevel->GetValue();
            pMachineMgr->RefreshPrimaryProfileInfo();
        }
    }
}

const char* Campaign::GetCheatMetaLevel(){
    if(unk88 == -1) return "Campaign Level Cheat Disabled";
    else return GetCampaignLevelForMetaScore(unk88).Str();
}

void Campaign::CheatReloadCampaignData(){
    if(s_pReloadedCampaignData) s_pReloadedCampaignData->Release();
    s_pReloadedCampaignData = DataReadFile("config/campaign.dta", true);
    m_pAccomplishmentMgr->CheatReloadData(s_pReloadedCampaignData);
    Cleanup();
    Init(s_pReloadedCampaignData);
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(Campaign)
    HANDLE_EXPR(get_fan_count, GetCampaignFanCountForUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(get_primary_fan_count, GetPrimaryCampaignFanCount())
    HANDLE_EXPR(get_campaign_level, GetCampaignLevelForUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(get_primary_campaign_level, GetPrimaryCampaignLevel())
    HANDLE_EXPR(get_next_campaign_level, GetNextCampaignLevel(_msg->Sym(2)))
    HANDLE_EXPR(is_last_campaign_level, IsLastCampaignLevel(_msg->Sym(2)))
    HANDLE_EXPR(get_campaign_level_icon, GetCampaignLevelIconForUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(get_total_points_for_next_campaign_level, GetTotalPointsForNextCampaignLevelForUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(get_current_points_for_next_campaign_level, GetCurrentPointsForNextCampaignLevelForUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(get_campaign_level_advertisement, GetCampaignLevelAdvertisement(_msg->Sym(2)))
    HANDLE_EXPR(is_user_on_last_campaign_level, IsUserOnLastCampaignLevel(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(is_primary_user_on_last_campaign_level, IsPrimaryUserOnLastCampaignLevel())
    HANDLE_EXPR(has_reached_campaign_level, HasReachedCampaignLevel(_msg->Sym(2)))
    HANDLE_EXPR(has_score_reached_campaign_level, HasScoreReachedCampaignLevel(_msg->Int(2), _msg->Sym(3)))
    HANDLE_ACTION(update_current_major_level_icon, UpdateCurrentMajorLevelIcon(_msg->Obj<LocalBandUser>(2), _msg->Obj<UIPicture>(3)))
    HANDLE_ACTION(update_next_major_level_icon, UpdateNextMajorLevelIcon(_msg->Obj<LocalBandUser>(2), _msg->Obj<UIPicture>(3)))
    HANDLE_ACTION(update_primary_current_major_level_icon, UpdatePrimaryCurrentMajorLevelIcon(_msg->Obj<UIPicture>(2)))
    HANDLE_ACTION(update_primary_next_major_level_icon, UpdatePrimaryNextMajorLevelIcon(_msg->Obj<UIPicture>(2)))
    HANDLE_EXPR(get_current_goal, GetCurrentGoal())
    HANDLE_EXPR(get_current_goal_description, GetCurrentGoalDescription())
    HANDLE_EXPR(get_current_goal_icon, GetCurrentGoalIcon())
    HANDLE_EXPR(has_current_goal, HasCurrentGoal())
    HANDLE_ACTION(clear_current_goal, ClearCurrentGoal())
    HANDLE_EXPR(get_user, GetUser())
    HANDLE_EXPR(get_profile, GetProfile())
    HANDLE_EXPR(can_skip_songs, CanSkipSongs())
    HANDLE_EXPR(can_resume_songs, CanResumeSongs())
    HANDLE_EXPR(can_save_setlists, CanSaveSetlists())
    HANDLE_EXPR(get_next_hint_to_show, GetNextHintToShow())
    HANDLE_EXPR(has_hints_to_show, HasHintsToShow())
    HANDLE_ACTION(update_progress_meter, UpdateProgressMeter(_msg->Obj<MeterDisplay>(2), _msg->Obj<LocalBandUser>(3)))
    HANDLE_ACTION(update_primary_progress_meter, UpdatePrimaryProgressMeter(_msg->Obj<MeterDisplay>(2)))
    HANDLE_EXPR(has_valid_user, HasValidUser())
    HANDLE_EXPR(get_was_launched_into_musiclibrary, GetWasLaunchedIntoMusicLibrary())
    HANDLE_ACTION(update_endgame_info, UpdateEndGameInfo(_msg->Obj<UILabel>(2), _msg->Obj<UILabel>(3), _msg->Obj<UIPicture>(4)))
    HANDLE_EXPR(has_display_goal, HasDisplayGoal())
    HANDLE_EXPR(get_display_goal, GetDisplayGoal())
    HANDLE_EXPR(get_goal_category, GetGoalCategory(_msg->Sym(2)))
    HANDLE_EXPR(get_category_group, GetCategoryGroup(_msg->Sym(2)))
    HANDLE_EXPR(should_return_to_category_screen, ShouldReturnToCategoryScreen())
    HANDLE_EXPR(get_primary_band_logo_tex, GetPrimaryBandLogoTex())
    HANDLE_ACTION(cheat_next_campaign_level, CheatNextMetaLevel())
    HANDLE_EXPR(get_cheat_meta_level, GetCheatMetaLevel())
    HANDLE_ACTION(cheat_reload_data, CheatReloadCampaignData())
    HANDLE_MESSAGE(ProfileSwappedMsg)
    HANDLE_MESSAGE(PrimaryProfileChangedMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x747)
END_HANDLERS
#pragma pop