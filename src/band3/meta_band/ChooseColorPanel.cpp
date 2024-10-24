#include "meta_band/ChooseColorPanel.h"
#include "bandobj/OutfitConfig.h"
#include "meta_band/ClosetMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "ui/UIPanel.h"
#include "utl/Symbols.h"

ChooseColorPanel::ChooseColorPanel() : mCurrentOutfitConfig(0), mCurrentOutfitPiece(0), mNumOptions(-1), mCurrentOption(-1) {
    mClosetMgr = ClosetMgr::GetClosetMgr();
    MILO_ASSERT(mClosetMgr, 0x19);
}

void ChooseColorPanel::Load(){
    UIPanel::Load();
    mCurrentOutfitConfig = mClosetMgr->mCurrentOutfitConfig;
    MILO_ASSERT(mCurrentOutfitConfig, 0x21);
    mCurrentOutfitPiece = mClosetMgr->mCurrentOutfitPiece;
    MILO_ASSERT(mCurrentOutfitPiece, 0x24);
    mNumOptions = mCurrentOutfitConfig->NumColorOptions();
    OutfitConfig* cfg = mCurrentOutfitConfig;
    for(int i = 0; i < cfg->mMats.size(); i++){
        OutfitConfig::MatSwap* pMatSwap = &cfg->mMats[i];
        MILO_ASSERT(pMatSwap, 0x2C);
        if(pMatSwap->mColor1Option != pMatSwap->mColor2Option){
            AddColorOption(pMatSwap->mColor1Option, pMatSwap->mColor1Palette);
            AddColorOption(pMatSwap->mColor2Option, pMatSwap->mColor2Palette);
        }
        else if(pMatSwap->mColor1Palette) {
            AddColorOption(pMatSwap->mColor1Option, pMatSwap->mColor1Palette);
        }
        else if(pMatSwap->mColor2Palette) {
            AddColorOption(pMatSwap->mColor1Option, pMatSwap->mColor2Palette);
        }
        else {
            MILO_WARN("(%s.milo) OutfitConfig mats[%i] has no color palettes set!", mCurrentOutfitPiece->mName, i);
        }
    }
    MILO_ASSERT(mColorOptions.size() == mNumOptions, 0x49);
    if(mNumOptions >= 1) mCurrentOption = 0;
}

void ChooseColorPanel::Enter(){
    UIPanel::Enter();
}

void ChooseColorPanel::Poll(){
    UIPanel::Poll();
    mClosetMgr->ForceClosetPoll();
}

void ChooseColorPanel::Draw(){
    UIPanel::Draw();
}

void ChooseColorPanel::Exit(){
    UIPanel::Exit();
}

void ChooseColorPanel::Unload(){
    UIPanel::Unload();
    mCurrentOutfitConfig = 0;
    mColorOptions.clear();
    mNumOptions = -1;
    mCurrentOption = -1;
}

void ChooseColorPanel::AddColorOption(int i, ColorPalette* pal){
    if(pal) mColorOptions[i] = pal;
}

int ChooseColorPanel::GetCurrentColor(){
    int color = mCurrentOutfitPiece->mColors[mCurrentOption];
    if(color == -1){
        color = mCurrentOutfitConfig->mColors[mCurrentOption];
    }
    return color;
}

void ChooseColorPanel::PreviewColor(int color){
    mCurrentOutfitPiece->mColors[mCurrentOption] = color;
    mClosetMgr->PreviewCharacter(true, false);
}

BEGIN_HANDLERS(ChooseColorPanel)
    HANDLE_EXPR(get_color_palette, mColorOptions[mCurrentOption])
    HANDLE_EXPR(get_current_color, GetCurrentColor())
    HANDLE_ACTION(preview_color, PreviewColor(_msg->Int(2)))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x9C)
END_HANDLERS

BEGIN_PROPSYNCS(ChooseColorPanel)
    SYNC_PROP(num_options, mNumOptions)
    SYNC_PROP(current_option, mCurrentOption)
END_PROPSYNCS