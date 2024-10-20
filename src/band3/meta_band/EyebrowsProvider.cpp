#include "meta_band/EyebrowsProvider.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/TexLoadPanel.h"
#include "os/Debug.h"
#include "ui/UIListMesh.h"
#include "utl/Symbol.h"
#include "utl/Symbols4.h"

EyebrowsProvider::EyebrowsProvider(const std::vector<DynamicTex*>& vec) : unk28(vec), unk2c(gNullStr) {

}

void EyebrowsProvider::Update(Symbol s){
    unk2c = s;
    unk20.clear();
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x1C);
    pAssetMgr->GetEyebrows(unk20, unk2c);
    unk20.push_back(none_eyebrows);
}

RndMat* EyebrowsProvider::Mat(int, int data, UIListMesh* mesh) const {
    MILO_ASSERT(data < NumData(), 0x26);
    if(mesh->Matches("icon")){
        String str(MakeString("%s_eyebrows_%d", unk2c.Str(), data));
        std::vector<DynamicTex*>::const_iterator it = std::find(unk28.begin(), unk28.end(), str);
        if(it != unk28.end()) return (*it)->mMat;
    }
    return nullptr;
}

Symbol EyebrowsProvider::DataSymbol(int idx) const {
    int data = NumData() - 1;
    if(idx <= data) data = idx & ~(idx >> 0x1F);
    MILO_ASSERT(( 0) <= (data) && (data) < ( NumData()), 0x41);
    return unk20[data];
}