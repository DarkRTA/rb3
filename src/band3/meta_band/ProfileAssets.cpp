#include "ProfileAssets.h"

#include "system/utl/MakeString.h"
#include "AssetMgr.h"
#include "os/Debug.h"
#include "AccomplishmentManager.h"

ProfileAssets::ProfileAssets(BandProfile* profile) : mParentProfile(profile) {
    Clear();
    // profile->SaveSize = SaveSize;
}

ProfileAssets::~ProfileAssets() {

}

void ProfileAssets::Clear() {
    mAssets.clear();
}

void ProfileAssets::AddAsset(Symbol asset) {
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x27);
    if (!pAssetMgr->HasAsset(asset)) {
        MILO_WARN("Could not find asset %s", asset.Str());
    } else {
        if (!HasAsset(asset)) {
            if (3000 <= (int)mAssets.size()) {
                TheDebug.Fail(MakeString(kAssertStr, __FILE__, 0x32, "GetNumAssets() < kMaxSymbols_Assets"));
            }
            mAssets.insert(asset);
            mAssets2.insert(asset);
            MILO_ASSERT(mParentProfile, 0x37);
            mParentProfile->MakeDirty();
        }
    }
}

bool ProfileAssets::HasAsset(Symbol asset) const {
    bool hasSource = TheAccomplishmentMgr->DoesAssetHaveSource(asset);
    if (!hasSource) {
        return true;
    }
    std::set<Symbol>::const_iterator iter = mAssets.begin();
    while (*iter != NULL) {

    }

    return true;
}

bool ProfileAssets::IsNew(Symbol name) const {
    MILO_ASSERT(HasAsset(name), 0x53);
}

void ProfileAssets::SetOld(Symbol) {

}

void ProfileAssets::GetNewAssets(std::vector<Symbol>&, AssetGender) const {

}

void ProfileAssets::GetNumNewAssets(AssetGender) const {

}

void ProfileAssets::SaveSize(int) {
    if (sPrintoutsEnabled != '\0') {
        TheDebug << "* %s = %i\n";
    }
    // return 0x5dc8;
}

void ProfileAssets::SaveFixed(FixedSizeSaveableStream& stream) const {
    FixedSizeSaveable::SaveStd(stream, mAssets, 0xbb8);
    FixedSizeSaveable::SaveStd(stream, mAssets2, 0xbb8);
}

void ProfileAssets::LoadFixed(FixedSizeSaveableStream& stream, int param_2) {
    FixedSizeSaveable::LoadStd(stream, mAssets, 0xbb8);
    FixedSizeSaveable::LoadStd(stream, mAssets2, 0xbb8);
}

void ProfileAssets::FakeFill() {
    for (int i = mAssets.size(); i < 3000; i++) {
        Symbol s = MakeString("fake_asset_%i", i);
        mAssets.insert(s);
    }
}