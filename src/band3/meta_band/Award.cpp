#include "Award.h"
#include "os/Debug.h"
#include "system/utl/Symbols2.h"
#include "ProfileAssets.h"

Award::Award(DataArray* configure, int index) : mName(""), mIconArt(""), mIndex(index), mDescription("") {
    Configure(configure);
}

Award::~Award() {

}

void Award::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x0a);

    mName = i_pConfig->Sym(0);
}

Symbol Award::GetName() const{
    return mName;
}

Symbol Award::GetDescription() const{
    if (HasAssets()) {
        return award_genericdesc;
    }
    return MakeString("", mDescription);
}

Symbol Award::GetDisplayName() const{
    bool hasAssets = HasAssets();

    if (hasAssets) {
        return Symbol(award_generic);
    }
    return Symbol(award_generic);
}

bool Award::HasIconArt() const {
    bool noIcon;

    if (gNullStr) {
        noIcon = !strcmp(mIconArt.Str(), gNullStr);
    } else {
        noIcon = (mIconArt.Str() == gNullStr);
    }

    return !noIcon;
}

Symbol Award::GetIconArt() const{
    return mIconArt;
}

bool Award::IsBonus() const{
    return mIsBonus;
}

static const char* unusedAwardStrings[] = {
    "pAwardArray->Size() > 1", 
    "pAwardEntryArray", 
    "pAwardEntryArray->Size() >= 1", 
    "pAssetMgr", 
    "Award: %s is granting unknown asset: %s.", 
    "AWARD: %s is awarding too many assets! count = %i.", 
    "%s_desc", 
    "%s_howto", 
    "%s_gray"
};

void Award::GrantAward(const AwardEntry& awardEntry, BandProfile* i_pProfile) {
    MILO_ASSERT(i_pProfile, 0xbd);

    ProfileAssets::AddAsset(asset);

    BandProfile::GrantCampaignKey(asset);
}

static const char* unusedAwardStrings2[] = {
    "pPerformer", 
    "Award Category is not currently supported: %s .", 
};

void Award::InqAssets(std::vector<Symbol>& o_rAssets) {
    MILO_ASSERT(o_rAssets.empty(), 0xe5);
}

bool Award::HasAssets() const {
    return !pAwardEntryArray.empty();
}

void Award::GrantAwards(BandProfile* bandProfile) {
    for (int i = 0; i < pAwardEntryArray.size(); i++) {
        AwardEntry& entry = pAwardEntryArray.at(i);
        GrantAward(entry, bandProfile);
    }
}
