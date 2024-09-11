#include "bandobj/PatchDir.h"

std::vector<Symbol> PatchLayer::sCategoryNames;

PatchSticker::PatchSticker() : unk18(1.0f), unk1c(1.0f), unk20(0), unk24(1), unk28(0), unk2c(0), unk30(0) {

}

PatchLayer::PatchLayer() : unk1c(gNullStr), unk20(0), unk28(0) {
    Reset();
}

PatchDir::PatchDir() : unk1c0(0) {
    mSaveSizeMethod = &SaveSize;
    unk194.resize(50);
    unk1bc = Hmx::Object::New<RndTex>();
    unk1bc->SetMipMapK(666.0f);
    if(TheLoadMgr.EditMode()) LoadStickerData();
}

PatchDir::~PatchDir(){

}