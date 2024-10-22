#include "meta_band/FaceHairProvider.h"
#include "meta_band/AssetMgr.h"
#include "os/Debug.h"
#include "ui/UIListLabel.h"
#include "utl/Symbol.h"
#include "utl/Symbols4.h"

FaceHairProvider::FaceHairProvider() : mFaceHair(0) {
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x13);
    const std::map<Symbol, Asset*>& assets = pAssetMgr->GetAssets();
    mMaleFaceHair.push_back(none_facehair);
    mFemaleFaceHair.push_back(none_facehair);
    for(std::map<Symbol, Asset*>::const_iterator it = assets.begin(); it != assets.end(); ++it){
        Asset* pAsset = it->second;
        MILO_ASSERT(pAsset, 0x20);
        Symbol name = pAsset->mName;
        int type = pAsset->mType;
        int gender = pAsset->mGender;
        if(type == 6){
            if(gender == 1){
                mMaleFaceHair.push_back(name);
            }
            else if(gender == 2){
                mFemaleFaceHair.push_back(name);
            }
        }
    }
    mFaceHair = &mMaleFaceHair;
}

void FaceHairProvider::Text(int, int idx, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(slot, 0x47);
    MILO_ASSERT(label, 0x48);
    if(slot->Matches("option")){
        label->SetTextToken(DataSymbol(idx));
    }
    else label->SetTextToken(gNullStr);
}

Symbol FaceHairProvider::DataSymbol(int data) const {
    MILO_ASSERT_RANGE(data, 0, NumData(), 0x56);
    return mFaceHair->at(data);
}

int FaceHairProvider::NumData() const {
    if(mFaceHair) return mFaceHair->size();
    else return 0;
}
