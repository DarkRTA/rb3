#include "Campaign.h"
#include "CampaignLevel.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/CampaignKey.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/ProfileSwappedMsg.h"
#include "utl/Symbol.h"

Campaign* TheCampaign;

Campaign::Campaign(DataArray* arr) : m_pAccomplishmentMgr(new AccomplishmentManager()), m_symCurrentAccomplishment(""), unk24(0), unk25(0), unk28(gNullStr), unk84(0), unk88(-1) {
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
    for(std::map<Symbol, CampaignLevel*>::iterator it = unk34.begin(); it != unk34.end(); ++it){
        RELEASE(it->second);
    }
    unk34.clear();
    unk2c.clear();
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
            unk34[levelname] = pCampaignLevel;
            unk2c.push_back(levelname);
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
            unk6c[name] = pCampaignKey;
        }
    }
    if((int)unk6c.size() > 20){
        MILO_WARN("There are too many campaign keys! Key count = %i, Max = %i", unk6c.size(), 20);
    }
}

bool Campaign::HasCampaignKey(Symbol s) const {
    return GetCampaignKey(s);
}

CampaignKey* Campaign::GetCampaignKey(Symbol s) const {
    std::map<Symbol, CampaignKey*>::const_iterator it = unk6c.find(s);
    if(it != unk6c.end()) return it->second;
    else return nullptr;
}

bool Campaign::HasCampaignLevel(Symbol s) const {
    return GetCampaignLevel(s);
}

CampaignLevel* Campaign::GetCampaignLevel(Symbol s) const {
    std::map<Symbol, CampaignLevel*>::const_iterator it = unk34.find(s);
    if(it != unk34.end()) return it->second;
    else return nullptr;
}

String Campaign::GetCampaignLevelIconForUser(LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0xE8);
    CampaignLevel* pCampaignLevel = GetCampaignLevel(GetCampaignLevelForUser(i_pUser));
    MILO_ASSERT(pCampaignLevel, 0xED);
    return pCampaignLevel->GetIconArt();
}