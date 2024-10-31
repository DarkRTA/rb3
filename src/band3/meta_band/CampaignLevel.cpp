#include "meta_band/CampaignLevel.h"
#include "decomp.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

CampaignLevel::CampaignLevel(DataArray* arr, int i) : mName(""), unk8(i), mPointValue(0), mAward(""), mAdvertisement(""), mRequirementToken(""), mIsMajorLevel(0) {
    Configure(arr);
}

CampaignLevel::~CampaignLevel(){

}

void CampaignLevel::Configure(DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x1F);
    mName = i_pConfig->Sym(0);
    i_pConfig->FindData(point_value, mPointValue, true);
    i_pConfig->FindData(advertisement, mAdvertisement, true);
    i_pConfig->FindData(requirement_token, mRequirementToken, false);
    i_pConfig->FindData(award, mAward, false);
    i_pConfig->FindData(is_major_level, mIsMajorLevel, false);
}

DECOMP_FORCEACTIVE(CampaignLevel, "%s_desc")

Symbol CampaignLevel::GetName() const { return mName; }
Symbol CampaignLevel::GetEarnedText() const { return MakeString("%s_earned", mName); }
String CampaignLevel::GetIconArt() const { return MakeString("ui/accomplishments/campaignlevel_art/%s_keep.bmp", mName.Str()); }
int CampaignLevel::GetValue() const { return mPointValue; }
Symbol CampaignLevel::GetAward() const { return mAward; }
bool CampaignLevel::HasAward() const { return mAward != ""; }
Symbol CampaignLevel::GetAdvertisement() const { return mAdvertisement; }
Symbol CampaignLevel::GetRequirementToken() const { return mRequirementToken; }
bool CampaignLevel::IsMajorLevel() const { return mIsMajorLevel; }