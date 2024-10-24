#include "meta_band/ClosetMgr.h"
#include "bandobj/BandCharDesc.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/AssetTypes.h"
#include "meta_band/CharCache.h"
#include "meta_band/CharData.h"
#include "meta_band/CharSync.h"
#include "meta_band/ClosetPanel.h"
#include "meta_band/MetaMessages.h"
#include "meta_band/ProfileMgr.h"
#include "obj/Dir.h"
#include "obj/MsgSource.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/ProfileSwappedMsg.h"
#include "os/User.h"
#include "synth/Synth.h"
#include "tour/TourCharLocal.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include "world/CameraShot.h"

namespace {
    ClosetMgr* TheClosetMgr;
}

ClosetMgr::ClosetMgr() : mUser(0), mSlot(-1), mNoUserMode(0), unk28(0), mCurrentCharacter(0), mPreviousCharacter(0), mBandCharacter(0), mBandCharDesc(0), mCurrentClosetPanel(0), unk44(gNullStr), mCurrentOutfitPiece(0), mCurrentOutfitConfig(0),
    unk50(0), unk54(0), mGender(gNullStr), mCharacterLoading(0), unk61(0) {
    SetName("closet_mgr", ObjectDir::Main());
    unk3c = dynamic_cast<BandCharDesc*>(BandCharDesc::NewObject());
    ThePlatformMgr.AddSink(this, ProfileSwappedMsg::Type());
}

ClosetMgr::~ClosetMgr(){
    ThePlatformMgr.RemoveSink(this, ProfileSwappedMsg::Type());
    RELEASE(unk3c);
}

void ClosetMgr::Init(){
    MILO_ASSERT(TheClosetMgr == NULL, 0x45);
    TheClosetMgr = new ClosetMgr();
}

ClosetMgr* ClosetMgr::GetClosetMgr(){ return TheClosetMgr; }

void ClosetMgr::Poll(){
    ForceClosetPoll();
    if(mCharacterLoading){
        int slot = GetUserSlot();
        MILO_ASSERT(slot != -1, 0x60);
        mBandCharacter = TheCharCache->GetCharacter(slot);
        MILO_ASSERT(mBandCharacter, 0x62);
        if(!mBandCharacter->IsLoading()){
            mCharacterLoading = false;
            CharacterFinishedLoading();
        }
    }   
}

DataNode ClosetMgr::OnMsg(const ProfileSwappedMsg& msg){
    LocalUser* pUser1 = msg.GetUser1();
    MILO_ASSERT(pUser1, 0x70);
    MILO_ASSERT(pUser1->IsLocal(), 0x71);
    LocalBandUser* pLocalUser1 = BandUserMgr::GetLocalBandUser(pUser1);
    MILO_ASSERT(pLocalUser1, 0x73);
    LocalUser* pUser2 = msg.GetUser2();
    MILO_ASSERT(pUser2, 0x75);
    MILO_ASSERT(pUser2->IsLocal(), 0x76);
    LocalBandUser* pLocalUser2 = BandUserMgr::GetLocalBandUser(pUser2);
    MILO_ASSERT(pLocalUser2, 0x78);
    if(mUser == pLocalUser1) mUser = pLocalUser2;
    else if(mUser == pLocalUser2) mUser = pLocalUser1;
    return 1;
}

bool ClosetMgr::InNoUserMode() const { return mNoUserMode; }
void ClosetMgr::SetNoUserMode(bool mode){ mNoUserMode = mode; }

void ClosetMgr::SetUser(LocalBandUser* pUser){
    MILO_ASSERT(pUser, 0x92);
    LocalBandUser* oldUser = mUser;
    if(oldUser && pUser != oldUser){
        oldUser->SetChar(mPreviousCharacter);
        mUser = pUser;
        UpdatePreviousCharacter();
    }
    else {
        mUser = pUser;
        UpdatePreviousCharacter();
    }
    mSlot = mUser->GetSlot();
    UpdateCurrentCharacter();
}

void ClosetMgr::ClearUser(){
    mUser = 0;
    mSlot = -1;
    mNoUserMode = false;
    unk28 = 0;
    mCurrentCharacter = 0;
    mPreviousCharacter = 0;
    mBandCharacter = 0;
    mBandCharDesc = 0;
    mCurrentClosetPanel = 0;
    unk44 = gNullStr;
    mCurrentOutfitPiece = 0;
    mCurrentOutfitConfig = 0;
    mGender = gNullStr;
    mCharacterLoading = 0;
    unk61 = 0;
    TheCharSync->UpdateCharCache();
}

void ClosetMgr::UpdateCurrentCharacter(){
    mCurrentCharacter = mUser->GetChar();
    MILO_ASSERT(mCurrentCharacter, 0xC5);
    TourCharLocal* local = dynamic_cast<TourCharLocal*>(mCurrentCharacter);
    if(local && local->IsFinalized()){
        unk28 = TheProfileMgr.GetProfileForChar(local);
    }
    else {
        unk28 = TheProfileMgr.GetProfileForUser(mUser);
    }
    mBandCharDesc = mCurrentCharacter->GetBandCharDesc();
    MILO_ASSERT(mBandCharDesc, 0xD4);
    unk3c->CopyCharDesc(mBandCharDesc);
    mGender = mBandCharDesc->mGender;
}

bool ClosetMgr::IsCurrentCharacterFinalized(){ return mCurrentCharacter->IsFinalized(); }

void ClosetMgr::UpdateBandCharDesc(BandCharDesc* pBandCharDesc){
    MILO_ASSERT(pBandCharDesc, 0xE2);
    mBandCharDesc->CopyCharDesc(pBandCharDesc);
    MILO_ASSERT(mBandCharDesc, 0xE4);
    unk3c->CopyCharDesc(mBandCharDesc);
    mGender = mBandCharDesc->mGender;
}

Symbol ClosetMgr::GetAssetFromAssetType(AssetType ty){
    BandCharDesc* desc = mBandCharDesc;
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0xF0);
    Symbol ret =  gNullStr;
    switch(ty){
        case kAssetType_None:
            break;
        case kAssetType_Bandana:
            ret = desc->mOutfit.mFaceHair.mName;
            break;
        case kAssetType_Bass:
            ret = pAssetMgr->StripFinish(desc->mInstruments.mBass.mName);
            break;
        case kAssetType_Drum:
            ret = pAssetMgr->StripFinish(desc->mInstruments.mDrum.mName);
            break;
        case kAssetType_Earrings:
            ret = desc->mOutfit.mEarrings.mName;
            break;
        case kAssetType_Eyebrows:
            ret = desc->mOutfit.mEyebrows.mName;
            break;
        case kAssetType_FaceHair:
            ret = desc->mOutfit.mFaceHair.mName;
            break;
        case kAssetType_Feet:
            ret = desc->mOutfit.mFeet.mName;
            break;
        case kAssetType_GlassesAndMasks:
            ret = desc->mOutfit.mGlasses.mName;
            break;
        case kAssetType_Gloves:
            ret = desc->mOutfit.mHands.mName;
            break;
        case kAssetType_Guitar:
            ret = pAssetMgr->StripFinish(desc->mInstruments.mGuitar.mName);
            break;
        case kAssetType_Hair:
            ret = desc->mOutfit.mHair.mName;
            break;
        case kAssetType_Hat:
            ret = desc->mOutfit.mHair.mName;
            break;
        case kAssetType_Keyboard:
            ret = desc->mInstruments.mKeyboard.mName;
            break;
        case kAssetType_Legs:
            ret = desc->mOutfit.mLegs.mName;
            break;
        case kAssetType_Mic:
            ret = desc->mInstruments.mMic.mName;
            break;
        case kAssetType_Piercings:
            ret = desc->mOutfit.mPiercings.mName;
            break;
        case kAssetType_Rings:
            ret = desc->mOutfit.mRings.mName;
            break;
        case kAssetType_Torso:
            ret = desc->mOutfit.mTorso.mName;
            break;
        case kAssetType_Wrists:
            ret = desc->mOutfit.mWrist.mName;
            break;
        default:
            MILO_ASSERT(false, 0x131);
            break;
    }
    return ret;
}

void ClosetMgr::SetCurrentClosetPanel(ClosetPanel* pClosetPanel){
    MILO_ASSERT(pClosetPanel, 0x13A);
    mCurrentClosetPanel = pClosetPanel;
}

void ClosetMgr::ClearCurrentClosetPanel(){ mCurrentClosetPanel = 0; }

void ClosetMgr::ResetCharacterPreview(){
    unk44 = none;
    mCurrentOutfitPiece = 0;
    mCurrentOutfitConfig = 0;
    unk3c->CopyCharDesc(mBandCharDesc);
    PreviewCharacter(true, false);
}

void ClosetMgr::ResetNewCharacterPreview(Symbol s){
    unk3c->CopyCharDesc(mBandCharDesc);
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x154);
    Symbol assetSym = GetSymbolFromAssetType(pAssetMgr->GetTypeFromName(s));
    if(!IsInstrumentAssetType(assetSym) || assetSym != unk44){
        mBandCharacter->SetInstrumentType(none);
    }
    PreviewCharacter(true, false);
}

void ClosetMgr::PreviewCharacter(bool b1, bool b2){
    if(TheCharCache){
        int slot = GetUserSlot();
        if(slot >= 0){
            std::vector<BandCharDesc*> descs;
            descs.push_back(unk3c);
            TheCharCache->Request(slot, descs, b1, b2);
            mCharacterLoading = true;
            unk61 = true;
        }
    }
}

void ClosetMgr::FinalizeBodyChanges(Symbol s){
    DataNode* prop = unk3c->Property(s, true);
    mBandCharDesc->SetProperty(s, *prop);
    PlayFinalizedSound(false);
}

void ClosetMgr::FinalizeCharCreatorChanges(){
    mBandCharDesc->CopyCharDesc(unk3c);
    PlayFinalizedSound(false);
}

void ClosetMgr::FinalizeChanges(bool b1, bool b2){
    mBandCharDesc->CopyCharDesc(unk3c);
    MakeProfileDirty();
    bool bbb = false;
    if(b1){
        if(!IsInstrumentAssetType(unk44)) bbb = true;
    }
    if(bbb) TakePortrait();
    PlayFinalizedSound(b2);
}

void ClosetMgr::PlayFinalizedSound(bool b){
    ClosetPanel* pClosetPanel = mCurrentClosetPanel;
    MILO_ASSERT(pClosetPanel, 0x198);
    const char* name = pClosetPanel->Name();
    if(strcmp(name, "customize_clothing_panel") == 0){
        if(b){
            TheSynth->Play("finish_clothes.cue", 0, 0, 0);
        }
        else TheSynth->Play("finish_accessories.cue", 0, 0, 0);
    }
    else if(strcmp(name, "customize_salon_panel") == 0){
        TheSynth->Play("finish_hairmakeup.cue", 0, 0, 0);
    }
    else if(strcmp(name, "customize_tattoo_panel") == 0){
        TheSynth->Play("finish_tattoo.cue", 0, 0, 0);
    }
    else if(strcmp(name, "customize_instrument_panel") == 0){
        TheSynth->Play("finish_instrument.cue", 0, 0, 0);
    }
}

DECOMP_FORCEACTIVE(ClosetMgr, "pProfile")

void ClosetMgr::MakeProfileDirty(){
    if(unk28) unk28->MakeDirty();
}

void ClosetMgr::CharacterFinishedLoading(){
    if(mCurrentOutfitPiece && !mCurrentOutfitConfig) UpdateCurrentOutfitConfig();
    static CharacterFinishedLoadingMsg msg;
    Export(msg, true);
}

void ClosetMgr::FinalizedColors(){
    static FinalizedColorsMsg msg;
    Export(msg, true);
}

void ClosetMgr::ForceClosetPoll(){
    if(unk61 && mCurrentClosetPanel){
        mCurrentClosetPanel->Poll();
        unk61 = false;
    }
}

void ClosetMgr::SetCurrentCharacterPatch(BandCharDesc::Patch::Category cat, const char* cc){
    int idx = unk3c->FindPatchIndex(cat, cc);
    if(idx == -1){
        unk3c->AddNewPatch(cat, cc);
        unk50 = 0;
    }
    else {
        unk54 = unk3c->GetPatch(idx)->mTexture;
    }
    PreviewCharacter(true, false);
}

void ClosetMgr::UpdateCharacterPatch(BandCharDesc::Patch::Category cat, const char* cc){
    if(unk50 == 0) unk3c->ClearPatch(cat, cc);
    else {
        int idx = unk3c->FindPatchIndex(cat, cc);
        if(idx != -1){
            BandCharDesc::Patch* patch = unk3c->GetPatch(idx);
            patch->mTexture = unk54;
        }
    }
}

void ClosetMgr::RecomposePatches(int i){
    if(TheCharCache){
        int slot = GetUserSlot();
        MILO_ASSERT(slot != -1, 0x219);
        TheCharCache->RecomposePatches(slot, unk3c, i);
    }
}

void ClosetMgr::SetPatches(){
    mBandCharDesc->mPatches = unk3c->mPatches;
    PlayFinalizedSound(false);
    MakeProfileDirty();
}

void ClosetMgr::ResetPatches(){
    unk3c->mPatches = mBandCharDesc->mPatches;
}

void ClosetMgr::SetCurrentOutfitPiece(Symbol s){
    unk44 = s;
    if(IsInstrumentAssetType(unk44)){
        mCurrentOutfitPiece = unk3c->mInstruments.GetPiece(unk44);
    }
    else mCurrentOutfitPiece = unk3c->mOutfit.GetPiece(unk44);
    MILO_ASSERT(mCurrentOutfitPiece, 0x245);
    if(IsAlreadyLoaded()) UpdateCurrentOutfitConfig();
    else {
        mCurrentOutfitConfig = 0;
        SetDefaultColors();
    }
}

void ClosetMgr::UpdateCurrentOutfitConfig(){
    Symbol name = mCurrentOutfitPiece->mName;
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 599);
    if(unk44 == guitar || unk44 == bass || unk44 == drum){
        name = pAssetMgr->StripFinish(name);
    }
    if(!pAssetMgr->HasAsset(name)) mCurrentOutfitConfig = 0;
    else {
        const char* cfgname = GetConfigNameFromAssetType(pAssetMgr->GetTypeFromName(name));
        mCurrentOutfitConfig = mBandCharacter->GetOutfitConfig(cfgname);
        if(!mCurrentOutfitConfig) MILO_WARN("Could not find (%s) for this asset.", cfgname);
    }
}

void ClosetMgr::HideClothes(){
    BandCharDesc* desc = unk3c;
    desc->mOutfit.mGlasses.mName = gNullStr;
    desc->mOutfit.mWrist.mName = gNullStr;
    if(mGender == male){
        desc->mOutfit.mTorso.mName = male_torso_naked;
        desc->mOutfit.mHands.mName = male_hands_naked;
        desc->mOutfit.mLegs.mName = undies_dirty;
        desc->mOutfit.mFeet.mName = male_feet_naked;
    }
    else {
        desc->mOutfit.mTorso.mName = femalebra_cotton;
        desc->mOutfit.mHands.mName = female_hands_naked;
        desc->mOutfit.mLegs.mName = femaleundies_cotton;
        desc->mOutfit.mFeet.mName = female_feet_naked;
    }
    PreviewCharacter(true, false);
}

void ClosetMgr::ShowClothes(){
    BandCharDesc* desc1 = unk3c;
    BandCharDesc* desc2 = mBandCharDesc;
    desc1->mOutfit.mGlasses.mName = desc2->mOutfit.mGlasses.mName;
    desc1->mOutfit.mWrist.mName = desc2->mOutfit.mWrist.mName;
    desc1->mOutfit.mTorso.mName = desc2->mOutfit.mTorso.mName;
    desc1->mOutfit.mHands.mName = desc2->mOutfit.mHands.mName;
    desc1->mOutfit.mLegs.mName = desc2->mOutfit.mLegs.mName;
    desc1->mOutfit.mFeet.mName = desc2->mOutfit.mFeet.mName;
    PreviewCharacter(true, false);
}

void ClosetMgr::SetDefaultColors(){
    Symbol name = mCurrentOutfitPiece->mName;
    if(name != gNullStr){
        AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x2B3);
        if(unk44 == guitar || unk44 == bass || unk44 == drum){
            name = pAssetMgr->StripFinish(name);
        }
        if(pAssetMgr->GetTypeFromName(name) != kAssetType_Eyebrows){
            for(int i = 0; i < 3; i++)
                mCurrentOutfitPiece->mColors[i] = -1;
        }
    }
}

CamShot* ClosetMgr::GetCurrentShot(){
    CamShot* pCamShot = mCurrentClosetPanel->GetCurrentShot();
    MILO_ASSERT(pCamShot, 0x2CD);
    return pCamShot;
}

void ClosetMgr::CycleCamera(){
    mCurrentClosetPanel->CycleCamera();
}

void ClosetMgr::GotoArtMakerShot(){
    mCurrentClosetPanel->GotoArtMakerShot();
}

void ClosetMgr::LeaveArtMakerShot(){
    mCurrentClosetPanel->LeaveArtMakerShot();
}

void ClosetMgr::SetInstrumentType(Symbol type){
    MILO_ASSERT(type == guitar || type == bass || type == drum || type == mic || type == keyboard, 0x2E8);
    if(type != mBandCharacter->InstrumentType()){
        mBandCharacter->SetInstrumentType(type);
    }
}

void ClosetMgr::ClearInstrument(){
    mBandCharacter->SetInstrumentType(none);
    unk44 = none;
    mCurrentOutfitPiece = 0;
    mCurrentOutfitConfig = 0;
    PreviewCharacter(true, false);
}

void ClosetMgr::TakePortrait(){
    mCurrentClosetPanel->TakePortrait();
}

void ClosetMgr::SetReturnScreen(Symbol screen){
    mReturnScreen = screen;
}

int ClosetMgr::GetUserSlot() const {
    if(mNoUserMode) return 0;
    else return mSlot;
}

bool ClosetMgr::IsAlreadyLoaded(){
    if(IsInstrumentAssetType(unk44)) return false;
    BandCharDesc::OutfitPiece* pLoadedPiece = mBandCharacter->mOutfit.GetPiece(unk44);
    MILO_ASSERT(pLoadedPiece, 0x341);
    if(mCurrentOutfitPiece->mName == pLoadedPiece->mName) return true;
    else return false;
}

void ClosetMgr::UpdatePreviousCharacter(){
    CharData* pCharacter = mUser->GetChar();
    MILO_ASSERT(pCharacter, 0x34C);
    if(pCharacter->IsFinalized()){
        mPreviousCharacter = pCharacter;
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(ClosetMgr)
    HANDLE_ACTION(set_user, SetUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(get_user, GetUser())
    HANDLE_ACTION(clear_user, ClearUser())
    HANDLE_EXPR(get_user_slot, GetUserSlot())
    HANDLE_ACTION(set_no_user_mode, SetNoUserMode(_msg->Int(2)))
    HANDLE_EXPR(is_character_loading, IsCharacterLoading())
    HANDLE_ACTION(set_current_outfit_piece, SetCurrentOutfitPiece(_msg->Sym(2)))
    HANDLE_ACTION(reset_character_preview, ResetCharacterPreview())
    HANDLE_ACTION(reset_new_character_preview, ResetNewCharacterPreview(_msg->Sym(2)))
    HANDLE_ACTION(finalize_body_changes, FinalizeBodyChanges(_msg->Sym(2)))
    HANDLE_ACTION(finalize_char_creator_changes, FinalizeCharCreatorChanges())
    HANDLE_ACTION(finalize_changes, FinalizeChanges(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(finalized_colors, FinalizedColors())
    HANDLE_ACTION(set_patches, SetPatches())
    HANDLE_ACTION(hide_clothes, HideClothes())
    HANDLE_ACTION(show_clothes, ShowClothes())
    HANDLE_ACTION(set_current_closet_panel, SetCurrentClosetPanel(_msg->Obj<ClosetPanel>(2)))
    HANDLE_ACTION(clear_current_closet_panel, ClearCurrentClosetPanel())
    HANDLE_ACTION(cycle_camera, CycleCamera())
    HANDLE_ACTION(goto_art_maker_shot, GotoArtMakerShot())
    HANDLE_ACTION(leave_art_maker_shot, LeaveArtMakerShot())
    HANDLE_ACTION(clear_instrument, ClearInstrument())
    HANDLE_ACTION(set_return_screen, SetReturnScreen(_msg->Sym(2)))
    HANDLE_EXPR(get_return_screen, GetReturnScreen())
    HANDLE_ACTION(has_asset_offer, nullptr)
    HANDLE_ACTION(show_purchase_ui, nullptr)
    HANDLE_ACTION(is_downloading, nullptr)
    HANDLE_MESSAGE(ProfileSwappedMsg)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x3A7)
END_HANDLERS
#pragma pop