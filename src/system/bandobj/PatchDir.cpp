#include "bandobj/PatchDir.h"
#include "utl/Symbols.h"

std::vector<Symbol> PatchLayer::sCategoryNames;

PatchSticker::PatchSticker() : unk18(1.0f), unk1c(1.0f), unk20(0), unk24(1), unk28(0), unk2c(0), unk30(0) {

}

PatchSticker::~PatchSticker(){
    Unload();
}

PatchLayer::PatchLayer() : mStickerCategory(gNullStr), mStickerIdx(0), unk28(0) {
    Reset();
}

BEGIN_HANDLERS(PatchLayer)
    HANDLE_EXPR(color_palette, sColorPalette)
    HANDLE_EXPR(has_sticker, !mStickerCategory.Null())
    HANDLE_ACTION(set_scale, SetScale(_msg->Float(2), _msg->Float(3)))
    HANDLE_EXPR(allow_color, AllowColor())
    HANDLE_ACTION(set_default_color, SetDefaultColor())
    HANDLE_ACTION(select_fx, SelectFX())
    HANDLE_ACTION(flip_x, FlipX())
    HANDLE_ACTION(flip_y, FlipY())
    HANDLE_ACTION(clear_sticker, ClearSticker())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x185)
END_HANDLERS

BEGIN_PROPSYNCS(PatchLayer)
    SYNC_PROP_MODIFY(sticker_category, mStickerCategory, mStickerIdx = 0)
    SYNC_PROP(sticker_idx, mStickerIdx)
    SYNC_PROP(color_idx, mColorIdx)
END_PROPSYNCS

PatchDir::PatchDir() : unk1c0(0) {
    mSaveSizeMethod = &SaveSize;
    unk194.resize(50);
    mTex = Hmx::Object::New<RndTex>();
    mTex->SetMipMapK(666.0f);
    if(TheLoadMgr.EditMode()) LoadStickerData();
}

PatchDir::~PatchDir(){

}

BEGIN_HANDLERS(PatchDir)
    HANDLE_EXPR(has_layers, HasLayers())
    HANDLE_ACTION(clear, Clear())
    HANDLE_EXPR(is_loading_stickers, !unk1b4.empty())
    HANDLE_EXPR(get_tex, mTex)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x544)
END_HANDLERS