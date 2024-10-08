#include "meta_band/CharData.h"

CharData::CharData(){

}

CharData::~CharData(){

}

BEGIN_HANDLERS(CharData)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x20)
END_HANDLERS

const char* GetPrefabPortraitPath(PrefabChar* pPrefab){
    MILO_ASSERT(pPrefab, 0x29);
}

PrefabChar::PrefabChar(BandCharDesc* desc) : mBandCharDesc(desc), mPortraitTex(0), unk20(0) {
    MILO_ASSERT(mBandCharDesc, 0x3F);
    unk24 = GetPrefabPortraitPath(this);
}

PrefabChar::~PrefabChar(){
    RELEASE(mPortraitTex);
}

RndTex* PrefabChar::GetPortraitTex() const { return mPortraitTex; }

void PrefabChar::CachePortraitTex(RndTex* tex){
    MILO_ASSERT(tex->Width() > 0 && tex->Height() > 0, 0x5A);
    tex->SaveBitmap(unk24.c_str());
}

bool PrefabChar::IsFinalized() const { return true; }

RndTex* PrefabChar::GetTexAtPatchIndex(int, bool) const { return 0; }