#include "Award.h"
#include "os/Debug.h"
#include "system/utl/Symbols.h"
#include "system/utl/Symbols2.h"
#include "ProfileAssets.h"
#include "AccomplishmentManager.h"

Award::Award(DataArray* configure, int index) : mName(gNullStr), mIconArt(gNullStr), mIndex(index) {

}

Award::~Award() {

}

void Award::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x0a);

    mName = i_pConfig->Sym(0);
    i_pConfig->FindData(is_secret, mIsSecret, false);
    i_pConfig->FindData(is_bonus, mIsBonus, false);
    i_pConfig->FindData(icon, mIcon, false);
    DataArray* pAwardArray = i_pConfig->FindArray(awards, false);

    MILO_ASSERT(pAwardArray->Size() > 1, 0x39);

    pAwardArray->Node(0);

    TheAccomplishmentMgr.AddAssetAward(Symbol(), Symbol());
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
    // These are likely part of configuration
    "pAwardEntryArray", 
    "pAwardEntryArray->Size() >= 1", 
    "pAssetMgr", 
    "Award: %s is granting unknown asset: %s.", 
    "AWARD: %s is awarding too many assets! count = %i.", 
    // Likely in description
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
