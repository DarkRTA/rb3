#include "ProfileAssets.h"

#include "system/utl/MakeString.h"
#include "AssetMgr.h"
#include "os/Debug.h"
#include "AccomplishmentManager.h"

ProfileAssets::ProfileAssets(BandProfile* profile) : mParentProfile(profile) {
    Clear();
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
        MILO_WARN("Could not find asset %s", asset);
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
    TheAccomplishmentMgr->DoesAssetHaveSource(asset);
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

}

void ProfileAssets::LoadFixed(FixedSizeSaveableStream& stream, int) {

}

void ProfileAssets::FakeFill() {
    for (int i = 0; i < 3000; i++) {
        Symbol s = MakeString("fake_asset_%i", i);
        mAssets.insert(s);
    }
}