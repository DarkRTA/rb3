#include "ProfileAssets.h"

#include "system/utl/MakeString.h"
#include "AssetMgr.h"
#include "os/Debug.h"
#include "AccomplishmentManager.h"
#include "MetaPanel.h"

ProfileAssets::ProfileAssets(BandProfile* profile) : mParentProfile(profile) {
    Clear();
    mSaveSizeMethod = SaveSize;
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
            mNewAssets.insert(asset);
            MILO_ASSERT(mParentProfile, 0x37);
            mParentProfile->MakeDirty();
        }
    }
}

bool ProfileAssets::HasAsset(Symbol asset) const {
    bool returnValue;

    if (MetaPanel::sUnlockAll) {
        return true;
    }

    bool hasSource = TheAccomplishmentMgr->DoesAssetHaveSource(asset);
    if (!hasSource) {
        return true;
    }

    return mAssets.find(asset) != mAssets.end();    
}

bool ProfileAssets::IsNew(Symbol name) const {
    MILO_ASSERT(HasAsset(name), 0x53);

    return mNewAssets.find(name) != mNewAssets.end();
}

void ProfileAssets::SetOld(Symbol name) {
    std::set<Symbol>::iterator it = mNewAssets.find(name);
    if (it != mNewAssets.end()) {
        mNewAssets.erase(it);
        MILO_ASSERT(mParentProfile, 0x66);
        mParentProfile->MakeDirty();
    }
}

void ProfileAssets::GetNewAssets(std::vector<Symbol>& assets, AssetGender gender) const {
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x6e);
    for (std::set<Symbol>::const_iterator it = mNewAssets.begin(); it != mNewAssets.end(); it++) {
        Symbol assetName = *it;
        Asset* pAsset = pAssetMgr->GetAsset(assetName);
        MILO_ASSERT(pAsset, 0x75);
        AssetGender assetGender = (AssetGender)pAsset->mGender;
        if (assetGender == gender || assetGender == 0) {
            assets.push_back(assetName);
        }
    }
    
}

int ProfileAssets::GetNumNewAssets(AssetGender gender) const {
    std::vector<Symbol> assets;
    GetNewAssets(assets, gender);
    return assets.size();
}

int ProfileAssets::SaveSize(int) {
    if (sPrintoutsEnabled != '\0') {
        TheDebug << MakeString("* %s = %i\n", "ProfileAssets", 0x5dc8);
    }
    return 0x5dc8;
}

void ProfileAssets::SaveFixed(FixedSizeSaveableStream& stream) const {
    FixedSizeSaveable::SaveStd(stream, mAssets, 0xbb8);
    FixedSizeSaveable::SaveStd(stream, mNewAssets, 0xbb8);
}

void ProfileAssets::LoadFixed(FixedSizeSaveableStream& stream, int param_2) {
    FixedSizeSaveable::LoadStd(stream, mAssets, 0xbb8);
    FixedSizeSaveable::LoadStd(stream, mNewAssets, 0xbb8);
}

void ProfileAssets::FakeFill() {
    for (int i = mAssets.size(); i < 3000; i++) {
        Symbol s = MakeString("fake_asset_%i", i);
        mAssets.insert(s);
    }
}