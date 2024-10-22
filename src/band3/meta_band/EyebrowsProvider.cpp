#include "meta_band/EyebrowsProvider.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/TexLoadPanel.h"
#include "os/Debug.h"
#include "ui/UIListMesh.h"
#include "utl/Symbol.h"
#include "utl/Symbols4.h"

EyebrowsProvider::EyebrowsProvider(const std::vector<DynamicTex*>& vec) : mIcons(vec), mGender(gNullStr) {

}

void EyebrowsProvider::Update(Symbol s){
    mGender = s;
    mEyebrows.clear();
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x1C);
    pAssetMgr->GetEyebrows(mEyebrows, mGender);
    mEyebrows.push_back(none_eyebrows);
}

RndMat* EyebrowsProvider::Mat(int, int data, UIListMesh* mesh) const {
    MILO_ASSERT(data < NumData(), 0x26);
    if(mesh->Matches("icon")){
        String str(MakeString("%s_eyebrows_%d", mGender.Str(), data));
        std::vector<DynamicTex*>::const_iterator it = std::find(mIcons.begin(), mIcons.end(), str);
        if(it != mIcons.end()) return (*it)->mMat;
    }
    return nullptr;
}

Symbol EyebrowsProvider::DataSymbol(int idx) const {
    int data = NumData() - 1;
    data = Clamp(0, data, idx);
    MILO_ASSERT_RANGE(data, 0, NumData(), 0x41);
    return mEyebrows[data];
}

int EyebrowsProvider::NumData() const { return mEyebrows.size(); }
