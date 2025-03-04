#include "meta_band/CustomizePanel.h"
#include "AssetTypes.h"
#include "BandProfile.h"
#include "CustomizePanel.h"
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandCharacter.h"
#include "meta/Profile.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/AssetProvider.h"
#include "meta_band/AssetTypes.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/CharCache.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/CurrentOutfitProvider.h"
#include "meta_band/InstrumentFinishProvider.h"
#include "meta_band/MakeupProvider.h"
#include "meta_band/NewAssetProvider.h"
#include "meta_band/PrefabMgr.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/UIEventMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include "ui/UIComponent.h"
#include "ui/UIPanel.h"
#include "utl/Messages3.h"
#include "utl/NetCacheMgr.h"
#include "utl/Messages.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

CustomizePanel::CustomizeState CustomizePanel::sBackStates[] = { (CustomizeState)0,
                                                                 (CustomizeState)0 };

CustomizePanel::CustomizePanel()
    : mCustomizeState(kCustomizeState_Invalid), mPendingState(kCustomizeState_Invalid),
      mPatchMenuReturnState(kCustomizeState_Invalid), mClosetMgr(0), mUser(0),
      mProfile(0), mCharData(0), mPreviewDesc(0), mNewAssetProvider(0),
      mCurrentOutfitProvider(0), mAssetProvider(0), mPremiumAssetProvider(0),
      mMakeupProvider(0), mInstrumentFinishProvider(0),
      mCurrentBoutique(kAssetBoutique_None), unk90(gNullStr), mCurrentMakeupIndex(-1),
      mRefreshingContent(0), mWaitingToLeave(0),
      mPatchCategory((BandCharDesc::Patch::Category)0), mPatchName(gNullStr),
      mShowAssetTokens(0) {}

CustomizePanel::~CustomizePanel() { mFocusComponents.clear(); }

void CustomizePanel::Load() {
    UIPanel::Load();
    mClosetMgr = ClosetMgr::GetClosetMgr();
    MILO_ASSERT(mClosetMgr, 0x82);
    mUser = mClosetMgr->GetUser();
    MILO_ASSERT(mUser, 0x85);
    mCharData = mUser->GetChar();
    MILO_ASSERT(mCharData, 0x88);
    if (PrefabMgr::PrefabIsCustomizable()) {
        mProfile = TheProfileMgr.GetProfileForUser(mUser);
    } else
        mProfile = mClosetMgr->GetProfile();
    mPreviewDesc = mClosetMgr->GetPreviewDesc();
    MILO_ASSERT(mPreviewDesc, 0x93);
    Symbol genderSym = mClosetMgr->GetGender();
    AssetGender assetGender = GetAssetGenderFromSymbol(genderSym);
    MILO_ASSERT(!mNewAssetProvider, 0x98);
    mNewAssetProvider = new NewAssetProvider(mProfile, assetGender);
    MILO_ASSERT(!mCurrentOutfitProvider, 0x9B);
    mCurrentOutfitProvider = new CurrentOutfitProvider();
    MILO_ASSERT(!mAssetProvider, 0x9E);
    mAssetProvider = new AssetProvider(mProfile, assetGender);
    MILO_ASSERT(!mMakeupProvider, 0xA6);
    mMakeupProvider = new MakeupProvider(genderSym);
    MILO_ASSERT(!mInstrumentFinishProvider, 0xA9);
    mInstrumentFinishProvider = new InstrumentFinishProvider();
    mUnlockedFacePaint = mProfile->HasCampaignKey(key_unlocked_face_paint);
    mUnlockedTattoos = mProfile->HasCampaignKey(key_unlocked_tattoos);
}

bool CustomizePanel::IsLoaded() const {
    return !UIPanel::IsLoaded() ? false : !TheContentMgr->RefreshInProgress();
}

void CustomizePanel::FinishLoad() {
    UIPanel::FinishLoad();
    if (mClosetMgr->GetGender() == female)
        DisableFaceHair();
    else
        EnableFaceHair();
}

void CustomizePanel::Enter() {
    UIPanel::Enter();
    mClosetMgr->PreviewCharacter(true, false);
    mRefreshingContent = TheContentMgr->RefreshInProgress();
    TheContentMgr->RegisterCallback(this, false);
    TheSessionMgr->AddSink(this, SigninChangedMsg::Type());
}

void CustomizePanel::Poll() {
    UIPanel::Poll();
    if (GetState() == kUp) {
        mClosetMgr->Poll();
    }
}

void CustomizePanel::Exit() {
    UIPanel::Exit();
    TheContentMgr->UnregisterCallback(this, true);
    TheSessionMgr->RemoveSink(this, SigninChangedMsg::Type());
}

void CustomizePanel::Unload() {
    UIPanel::Unload();
    SetCustomizeState(kCustomizeState_Invalid);
    mUser->UpdateData(2);
    MILO_ASSERT(mClosetMgr, 0x10A);
    MILO_ASSERT(mUser, 0x10B);
    MILO_ASSERT(mProfile, 0x10C);
    MILO_ASSERT(mCharData, 0x10D);
    MILO_ASSERT(mPreviewDesc, 0x10E);
    mClosetMgr->PreviewCharacter(false, false);
    mClosetMgr = nullptr;
    mUser = nullptr;
    mProfile = nullptr;
    mCharData = nullptr;
    mPreviewDesc = nullptr;
    RELEASE(mInstrumentFinishProvider);
    RELEASE(mMakeupProvider);
    RELEASE(mPremiumAssetProvider);
    RELEASE(mAssetProvider);
    RELEASE(mCurrentOutfitProvider);
    RELEASE(mNewAssetProvider);
}

bool CustomizePanel::Unloading() const { return !TheNetCacheMgr->IsUnloaded(); }
void CustomizePanel::ContentStarted() { mRefreshingContent = true; }
void CustomizePanel::ContentDone() { mRefreshingContent = false; }

void CustomizePanel::SetCustomizeState(CustomizeState state) {
    static Message msg("update_state", 0, 0);
    msg[0] = state;
    msg[1] = mCustomizeState;
    mCustomizeState = state;
    HandleType(msg);
}

void CustomizePanel::SetPendingState(CustomizeState state) { mPendingState = state; }
void CustomizePanel::SetPatchMenuReturnState(CustomizeState state) {
    mPatchMenuReturnState = state;
}

bool CustomizePanel::InPreviewState() const {
    switch (mCustomizeState) {
    case 2:
    case kCustomizeState_BrowseTorso:
    case kCustomizeState_BrowseLegs:
    case kCustomizeState_BrowseFeet:
    case kCustomizeState_BrowseHats:
    case kCustomizeState_BrowseEarrings:
    case kCustomizeState_BrowsePiercings:
    case kCustomizeState_BrowseGlassesAndMasks:
    case kCustomizeState_BrowseBandanas:
    case kCustomizeState_BrowseWrists:
    case kCustomizeState_BrowseRings:
    case kCustomizeState_BrowseGloves:
    case kCustomizeState_BrowseHair:
    case kCustomizeState_BrowseEyebrows:
    case kCustomizeState_BrowseFaceHair:
    case kCustomizeState_BrowseEyeMakeup:
    case kCustomizeState_BrowseLipMakeup:
    case kCustomizeState_BrowseGuitars:
    case kCustomizeState_BrowseBasses:
    case kCustomizeState_BrowseDrums:
    case kCustomizeState_BrowseMicrophones:
    case kCustomizeState_BrowseKeyboards:
    case 0x1d:
    case 0x1e:
    case 0x24:
        return true;
    default:
        return false;
    }
}

bool CustomizePanel::InClothingState() const {
    return mCustomizeState == kCustomizeState_BrowseTorso
        || mCustomizeState == kCustomizeState_BrowseLegs
        || mCustomizeState == kCustomizeState_BrowseFeet;
}

void CustomizePanel::UpdateNewAssetProvider() {
    mNewAssetProvider->Update();
    RefreshNewAssetsList();
}

void CustomizePanel::UpdateCurrentOutfitProvider() {
    mCurrentOutfitProvider->Update();
    RefreshCurrentOutfitList();
}

void CustomizePanel::UpdateAssetProvider() {
    AssetType ty = GetAssetTypeFromCurrentState();
    if (ty != kAssetType_None) {
        mAssetProvider->Update(ty, mCurrentBoutique);
        RefreshAssetsList();
    }
}

void CustomizePanel::UpdateMakeupProvider(Symbol type) {
    MILO_ASSERT(type == eyes || type == lips, 0x1A9);
    mMakeupProvider->Update(type);
}

void CustomizePanel::SetCurrentBoutique(Symbol s) {
    mCurrentBoutique = GetAssetBoutiqueFromSymbol(s);
    UpdateAssetProvider();
}

Symbol CustomizePanel::GetCurrentBoutique() {
    return GetSymbolFromAssetBoutique(mCurrentBoutique);
}

void CustomizePanel::ClearCurrentBoutique() { mCurrentBoutique = kAssetBoutique_None; }

Symbol CustomizePanel::GetWearing() {
    BandCharDesc *desc = mPreviewDesc;
    AssetType ty = GetAssetTypeFromCurrentState();
    Symbol ret(gNullStr);
    switch (ty) {
    case kAssetType_None:
    case kAssetType_Feet:
    case kAssetType_Legs:
    case kAssetType_Torso:
        break;
    case kAssetType_Bandana:
        ret = desc->mOutfit.mFaceHair.mName;
        break;
    case kAssetType_Bass:
        ret = StripFinish(desc->mInstruments.mBass.mName);
        break;
    case kAssetType_Drum:
        ret = StripFinish(desc->mInstruments.mDrum.mName);
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
    case kAssetType_GlassesAndMasks:
        ret = desc->mOutfit.mGlasses.mName;
        break;
    case kAssetType_Gloves:
        ret = desc->mOutfit.mHands.mName;
        break;
    case kAssetType_Guitar:
        ret = StripFinish(desc->mInstruments.mGuitar.mName);
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
    case kAssetType_Mic:
        ret = desc->mInstruments.mMic.mName;
        break;
    case kAssetType_Piercings:
        ret = desc->mOutfit.mPiercings.mName;
        break;
    case kAssetType_Rings:
        ret = desc->mOutfit.mRings.mName;
        break;
    case kAssetType_Wrists:
        ret = desc->mOutfit.mWrist.mName;
        break;
    default:
        MILO_ASSERT(false, 0x20D);
        break;
    }
    if (ret == gNullStr) {
        ret = GetDefaultAssetFromAssetType(
            ty, GetAssetGenderFromSymbol(mClosetMgr->GetGender())
        );
    }
    return ret;
}

Symbol CustomizePanel::StripFinish(Symbol s) {
    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x21F);
    return pAssetMgr->StripFinish(s);
}

void CustomizePanel::RefreshNewAssetsList() { Handle(refresh_new_assets_list_msg, true); }
void CustomizePanel::RefreshAssetsList() { Handle(refresh_assets_list_msg, true); }
void CustomizePanel::RefreshCurrentOutfitList() {
    Handle(refresh_current_outfit_list_msg, true);
}

void CustomizePanel::PreviewAsset(Symbol s) {
    if (InPreviewState()) {
        BandCharDesc *desc = mPreviewDesc;
        AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x255);
        AssetType ty;
        if (s == none_bandana || s == none_earrings || s == none_eyebrows
            || s == none_facehair || s == none_glasses || s == none_hair || s == none_hat
            || s == none_piercings || s == none_rings || s == none_wrists) {
            ty = pAssetMgr->GetTypeFromName(s);
            s = gNullStr;
        } else {
            Asset *pAsset = pAssetMgr->GetAsset(s);
            MILO_ASSERT(pAsset, 0x269);
            BandProfile *p = mProfile;
            p->mProfileAssets.SetOld(s);
            ty = pAsset->GetType();
            if (pAsset->HasFinishes()) {
                s = MakeString("%s_%s", s.mStr, pAsset->GetFinish(0).mStr);
            }
        }
        Symbol ret = none;
        switch (ty) {
        case kAssetType_None:
            break;
        case kAssetType_Bandana:
            desc->mOutfit.mFaceHair.mName = s;
            ret = facehair;
            break;
        case kAssetType_Bass:
            desc->mInstruments.mBass.mName = s;
            ret = bass;
            break;
        case kAssetType_Drum:
            desc->mInstruments.mDrum.mName = s;
            ret = drum;
            break;
        case kAssetType_Earrings:
            desc->mOutfit.mEarrings.mName = s;
            ret = earrings;
            break;
        case kAssetType_Eyebrows:
            desc->mOutfit.mEyebrows.mName = s;
            ret = eyebrows;
            break;
        case kAssetType_FaceHair:
            desc->mOutfit.mFaceHair.mName = s;
            ret = facehair;
            break;
        case kAssetType_Feet:
            desc->mOutfit.mFeet.mName = s;
            ret = feet;
            break;
        case kAssetType_GlassesAndMasks:
            desc->mOutfit.mGlasses.mName = s;
            ret = glasses;
            break;
        case kAssetType_Gloves:
            desc->mOutfit.mHands.mName = s;
            ret = hands;
            break;
        case kAssetType_Guitar:
            desc->mInstruments.mGuitar.mName = s;
            ret = guitar;
            break;
        case kAssetType_Hair:
            desc->mOutfit.mHair.mName = s;
            ret = hair;
            break;
        case kAssetType_Hat:
            desc->mOutfit.mHair.mName = s;
            ret = hair;
            break;
        case kAssetType_Keyboard:
            desc->mInstruments.mKeyboard.mName = s;
            ret = keyboard;
            break;
        case kAssetType_Legs:
            desc->mOutfit.mLegs.mName = s;
            ret = legs;
            break;
        case kAssetType_Mic:
            desc->mInstruments.mMic.mName = s;
            ret = mic;
            break;
        case kAssetType_Piercings:
            desc->mOutfit.mPiercings.mName = s;
            ret = piercings;
            break;
        case kAssetType_Rings:
            desc->mOutfit.mRings.mName = s;
            ret = rings;
            break;
        case kAssetType_Torso:
            desc->mOutfit.mTorso.mName = s;
            ret = torso;
            break;
        case kAssetType_Wrists:
            desc->mOutfit.mWrist.mName = s;
            ret = wrist;
            break;
        default:
            MILO_ASSERT(false, 0x304);
            break;
        }
        mClosetMgr->SetCurrentOutfitPiece(ret);
        if (IsInstrumentAssetType(ret)) {
            mClosetMgr->SetInstrumentType(ret);
        }
        mClosetMgr->PreviewCharacter(true, false);
    }
}

void CustomizePanel::PreviewFinish(Symbol s) {
    BandCharDesc *desc = mPreviewDesc;
    BandCharDesc::OutfitPiece *pOutfitPiece = mClosetMgr->GetCurrentOutfitPiece();
    MILO_ASSERT(pOutfitPiece, 0x318);
    Symbol outfitName = pOutfitPiece->mName;
    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x31C);
    Symbol stripped = pAssetMgr->StripFinish(outfitName);
    Asset *pAsset = pAssetMgr->GetAsset(stripped);
    MILO_ASSERT(pAsset, 800);
    Symbol s1c = MakeString("%s_%s", stripped.mStr, s.mStr);
    Symbol outfit = none;
    switch (pAsset->GetType()) {
    case kAssetType_Guitar:
        desc->mInstruments.mGuitar.mName = s1c;
        outfit = guitar;
        break;
    case kAssetType_Bass:
        desc->mInstruments.mBass.mName = s1c;
        outfit = bass;
        break;
    case kAssetType_Drum:
        desc->mInstruments.mDrum.mName = s1c;
        outfit = drum;
        break;
    default:
        break;
    }
    mClosetMgr->SetCurrentOutfitPiece(outfit);
    mClosetMgr->PreviewCharacter(true, false);
}

void CustomizePanel::SelectAsset(Symbol s) {
    if (!mClosetMgr->IsCharacterLoading()) {
        if (s == none_bandana || s == none_earrings || s == none_eyebrows
            || s == none_facehair || s == none_glasses || s == none_hair || s == none_hat
            || s == none_piercings || s == none_rings || s == none_wrists) {
            mClosetMgr->FinalizeChanges(true, InClothingState());
            LeaveState(false);
        } else {
            AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
            MILO_ASSERT(pAssetMgr, 0x36A);
            Asset *pAsset = pAssetMgr->GetAsset(s);
            MILO_ASSERT(pAsset, 0x36D);
            BandProfile *p = mProfile;
            if (p->mProfileAssets.HasAsset(s)) {
                if (pAsset->HasFinishes()) {
                    mInstrumentFinishProvider->Update(s);
                    ChooseFinish();
                } else if (pAsset->GetBoutique() != kAssetBoutique_Premium) {
                    ChooseColors();
                }
            } else
                ShowLockedDialog();
        }
    }
}

void CustomizePanel::ShowLockedDialog() { Handle(show_locked_dialog_msg, true); }
void CustomizePanel::ChooseFinish() { Handle(choose_finish_msg, true); }
void CustomizePanel::ChooseColors() { Handle(choose_colors_msg, true); }
void CustomizePanel::GotoCustomizeClothingScreen() {
    Handle(goto_customize_clothing_screen_msg, true);
}

Symbol CustomizePanel::GetCurrentMakeup(Symbol type) {
    MILO_ASSERT(type == eyes || type == lips, 0x3A9);
    BandCharDesc *desc = mPreviewDesc;
    for (int i = 0; i < desc->mPatches.size(); i++) {
        BandCharDesc::Patch &curPatch = desc->mPatches[i];
        if (curPatch.mCategory == BandCharDesc::Patch::kPatchMakeup) {
            String meshName = curPatch.mMeshName;
            Symbol s6;
            std::vector<String> subStrings;
            if (meshName.split("_", subStrings) == 4) {
                s6 = subStrings[2].c_str();
            } else
                MILO_WARN("Invalid makeup mesh: (%s)", meshName);
            if (s6 == type) {
                SetCurrentMakeupIndex(i);
                return meshName.substr(0, meshName.length() - 5).c_str();
            }
        }
    }
    ClearCurrentMakeupIndex();
    return gNullStr;
}

void CustomizePanel::SetCurrentMakeupIndex(int idx) { mCurrentMakeupIndex = idx; }
void CustomizePanel::ClearCurrentMakeupIndex() { mCurrentMakeupIndex = -1; }

void CustomizePanel::PreviewMakeup(Symbol s) {
    if (mCustomizeState != kCustomizeState_BrowseEyeMakeup
        && mCustomizeState != kCustomizeState_BrowseLipMakeup)
        return;
    else {
        std::vector<BandCharDesc::Patch> &rPatches = mPreviewDesc->mPatches;
        if (s == none_makeup) {
            if (mCurrentMakeupIndex != -1) {
                MILO_ASSERT_RANGE(mCurrentMakeupIndex, 0, rPatches.size(), 0x3F3);
                rPatches.erase(rPatches.begin() + mCurrentMakeupIndex);
                ClearCurrentMakeupIndex();
            }
        } else {
            String meshName = MakeString("%s.mesh", s.mStr);
            if (mCurrentMakeupIndex == -1) {
                BandCharDesc::Patch patch;
                patch.mTexture = -1;
                patch.mCategory = BandCharDesc::Patch::kPatchMakeup;
                patch.mMeshName = meshName;
                rPatches.push_back(patch);
                mCurrentMakeupIndex = rPatches.size() - 1;
            } else
                rPatches[mCurrentMakeupIndex].mMeshName = meshName;
        }
        mClosetMgr->RecomposePatches(0x20);
    }
}

bool CustomizePanel::HasNewAssets() {
    return mProfile->mProfileAssets.GetNumNewAssets(
               GetAssetGenderFromSymbol(mClosetMgr->GetGender())
           )
        > 0;
}

bool CustomizePanel::AssetProviderHasAsset(Symbol s) {
    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x42B);
    AssetType nameType = pAssetMgr->GetTypeFromName(s);
    if (nameType != GetAssetTypeFromCurrentState()) {
        return false;
    } else
        return mAssetProvider->HasAsset(s);
}

void CustomizePanel::SetupCurrentOutfit(Symbol s) {
    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x43D);
    if (pAssetMgr->HasAsset(s)) {
        Asset *pAsset = pAssetMgr->GetAsset(s);
        MILO_ASSERT(pAsset, 0x443);
        Symbol assetSym = GetSymbolFromAssetType(pAsset->GetType());
        if (assetSym == bandana) {
            assetSym = facehair;
        } else if (assetSym == hat) {
            assetSym = hair;
        }
        mClosetMgr->SetCurrentOutfitPiece(assetSym);
    }
}

bool CustomizePanel::HasPatch() {
    return mPreviewDesc->FindPatchIndex(
               (BandCharDesc::Patch::Category)mPatchCategory, mPatchName.c_str()
           )
        != -1;
}

void CustomizePanel::EnableFaceHair() { Handle(enable_facehair_msg, true); }
void CustomizePanel::DisableFaceHair() { Handle(disable_facehair_msg, true); }
bool CustomizePanel::HasLicense(Symbol s) { return TheSongMgr.HasLicense(s); }

Symbol CustomizePanel::GetAssetShot(Symbol s) {
    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x4B8);
    AssetType ty = pAssetMgr->GetTypeFromName(s);
    const char *shotstr = gNullStr;
    switch (ty) {
    case kAssetType_None:
        MILO_ASSERT(false, 0x4C0);
        break;
    case kAssetType_Bandana:
        shotstr = "head";
        break;
    case kAssetType_Bass:
        shotstr = "guitar";
        break;
    case kAssetType_Drum:
        shotstr = "drums";
        break;
    case kAssetType_Earrings:
        shotstr = "head";
        break;
    case kAssetType_Eyebrows:
        shotstr = "head";
        break;
    case kAssetType_FaceHair:
        shotstr = "head";
        break;
    case kAssetType_Feet:
        shotstr = "feet";
        break;
    case kAssetType_GlassesAndMasks:
        shotstr = "head";
        break;
    case kAssetType_Gloves:
        shotstr = "gloves";
        break;
    case kAssetType_Guitar:
        shotstr = "guitar";
        break;
    case kAssetType_Hair:
        shotstr = "head";
        break;
    case kAssetType_Hat:
        shotstr = "head";
        break;
    case kAssetType_Keyboard:
        shotstr = "keyboard";
        break;
    case kAssetType_Legs:
        shotstr = "legs";
        break;
    case kAssetType_Mic:
        shotstr = "microphone";
        break;
    case kAssetType_Piercings:
        shotstr = "head";
        break;
    case kAssetType_Rings:
        shotstr = "rings";
        break;
    case kAssetType_Torso:
        shotstr = "torso";
        break;
    case kAssetType_Wrists:
        shotstr = "wrists";
        break;
    default:
        MILO_ASSERT(false, 0x4FC);
        break;
    }
    return MakeString("%s_1.shot", shotstr);
}

AssetType CustomizePanel::GetAssetTypeFromCurrentState() {
    switch (mCustomizeState) {
    case kCustomizeState_Invalid:
        return kAssetType_None;
    case 1:
        return kAssetType_None;
    case 2:
        return kAssetType_None;
    case 3:
        return kAssetType_None;
    case 4:
        return kAssetType_None;
    case kCustomizeState_BrowseTorso:
        return kAssetType_Torso;
    case kCustomizeState_BrowseLegs:
        return kAssetType_Legs;
    case kCustomizeState_BrowseFeet:
        return kAssetType_Feet;
    case 8:
        return kAssetType_None;
    case kCustomizeState_BrowseHats:
        return kAssetType_Hat;
    case kCustomizeState_BrowseEarrings:
        return kAssetType_Earrings;
    case kCustomizeState_BrowsePiercings:
        return kAssetType_Piercings;
    case kCustomizeState_BrowseGlassesAndMasks:
        return kAssetType_GlassesAndMasks;
    case kCustomizeState_BrowseBandanas:
        return kAssetType_Bandana;
    case kCustomizeState_BrowseWrists:
        return kAssetType_Wrists;
    case kCustomizeState_BrowseRings:
        return kAssetType_Rings;
    case kCustomizeState_BrowseGloves:
        return kAssetType_Gloves;
    case kCustomizeState_HairAndMakeup:
        return kAssetType_None;
    case kCustomizeState_BrowseHair:
        return kAssetType_Hair;
    case kCustomizeState_BrowseEyebrows:
        return kAssetType_Eyebrows;
    case kCustomizeState_BrowseFaceHair:
        return kAssetType_FaceHair;
    case kCustomizeState_BrowseEyeMakeup:
        return kAssetType_None;
    case kCustomizeState_BrowseLipMakeup:
        return kAssetType_None;
    case kCustomizeState_Instruments:
        return kAssetType_None;
    case kCustomizeState_BrowseGuitars:
        return kAssetType_Guitar;
    case kCustomizeState_BrowseBasses:
        return kAssetType_Bass;
    case kCustomizeState_BrowseDrums:
        return kAssetType_Drum;
    case kCustomizeState_BrowseMicrophones:
        return kAssetType_Mic;
    case kCustomizeState_BrowseKeyboards:
        return kAssetType_Keyboard;
    case 29:
        return kAssetType_Torso;
    case 30:
        return kAssetType_Torso;
    case 31:
        return kAssetType_None;
    default:
        return kAssetType_None;
    }
}

void CustomizePanel::SetFocusComponent(CustomizeState state, Symbol sym) {
    UIComponent *pComponent = mDir->Find<UIComponent>(sym.mStr, true);
    MILO_ASSERT(pComponent, 0x574);
    mFocusComponents[state] = pComponent;
}

void CustomizePanel::StoreFocusComponent() {
    UIComponent *pFocusComponent = FocusComponent();
    MILO_ASSERT(pFocusComponent, 0x57E);
    mFocusComponents[mCustomizeState] = pFocusComponent;
}

UIComponent *CustomizePanel::GetFocusComponent() {
    return mFocusComponents[mCustomizeState];
}

DataNode CustomizePanel::OnMsg(const SigninChangedMsg &msg) {
    if (mProfile) {
        if (!mProfile->HasValidSaveData()) {
            static Message init("init", 0);
            init[0] = 4;
            TheUIEventMgr->TriggerEvent(sign_out, init);
        }
    }
    return 1;
}

DataNode CustomizePanel::OnMsg(const ButtonDownMsg &msg) {
    if (mWaitingToLeave)
        return 1;
    if (mPendingState != 0)
        return 1;
    JoypadAction action = msg.GetAction();
    if (action == kAction_Cancel)
        return LeaveState(true);
    else if (mCustomizeState == 0x21) {
        switch (action) {
        case kAction_Up:
            MovePatch(0, -0.05f);
            break;
        case kAction_Right:
            MovePatch(0.05f, 0);
            break;
        case kAction_Down:
            MovePatch(0, 0.05f);
            break;
        case kAction_Left:
            MovePatch(-0.05f, 0);
            break;
        default:
            break;
        }
    } else if (mCustomizeState == 0x22) {
        switch (action) {
        case kAction_Right:
            RotatePatch(-10);
            break;
        case kAction_Left:
            RotatePatch(10);
            break;
        default:
            break;
        }
    } else if (mCustomizeState == 0x23) {
        switch (action) {
        case kAction_Up:
            ScalePatch(0, 0.05f);
            break;
        case kAction_Right:
            ScalePatch(0.05f, 0);
            break;
        case kAction_Down:
            ScalePatch(0, -0.05f);
            break;
        case kAction_Left:
            ScalePatch(-0.05f, 0);
            break;
        default:
            break;
        }
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode CustomizePanel::OnMsg(const UIComponentScrollMsg &) {
    if (mPendingState != 0)
        return 1;
    else
        return DataNode(kDataUnhandled, 0);
}

DataNode CustomizePanel::LeaveState(bool b1) {
    if (b1) {
        static Message cMsg("handle_sound_back", 0);
        cMsg[0] = mUser;
        Handle(cMsg, true);
    }
    if (mCustomizeState == kCustomizeState_BrowseTorso
        && mCurrentBoutique == kAssetBoutique_TShirts) {
        mClosetMgr->ResetCharacterPreview();
        SetPendingState((CustomizeState)3);
        return 1;
    } else
        switch (mCustomizeState) {
        case 1:
            return LeaveCustomizePanel();
        case 2:
            mClosetMgr->ClearInstrument();
            mClosetMgr->ResetCharacterPreview();
            SetPendingState((CustomizeState)1);
            return 1;
        case kCustomizeState_HairAndMakeup:
            GotoCustomizeClothingScreen();
            return 1;
        case kCustomizeState_BrowseEyeMakeup:
        case kCustomizeState_BrowseLipMakeup:
            ClearCurrentMakeupIndex();
            mClosetMgr->ResetPatches();
            mClosetMgr->RecomposePatches(0x20);
            SetCustomizeState(kCustomizeState_HairAndMakeup);
            return 1;
        case kCustomizeState_Instruments:
            GotoCustomizeClothingScreen();
            return 1;
        case kCustomizeState_BrowseGuitars:
        case kCustomizeState_BrowseBasses:
        case kCustomizeState_BrowseDrums:
        case kCustomizeState_BrowseMicrophones:
        case kCustomizeState_BrowseKeyboards:
            mClosetMgr->ClearInstrument();
            SetPendingState(kCustomizeState_Instruments);
            return 1;
        case 0x1f:
            mClosetMgr->ResetCharacterPreview();
            GotoCustomizeClothingScreen();
            return 1;
        case 0x20:
            SetCustomizeState(mPatchMenuReturnState);
            return 1;
        case 0x21:
        case 0x22:
        case 0x23:
            mClosetMgr->ResetPatches();
            RefreshPatchEdit();
            SetCustomizeState((CustomizeState)0x20);
            return 1;
        default:
            mClosetMgr->ResetCharacterPreview();
            // SetPendingState(sBackStates[mCustomizeState]);
            return 1;
        }
}

DataNode CustomizePanel::LeaveCustomizePanel() {
    if (mClosetMgr->IsCharacterLoading()) {
        mWaitingToLeave = true;
        return 1;
    } else {
        mClosetMgr->TakePortrait();
        return DataNode(kDataUnhandled, 0);
    }
}

void CustomizePanel::SetIsWaitingToLeave(bool b) { mWaitingToLeave = b; }

void CustomizePanel::ClearAssetPatchData() {
    unk90 = gNullStr;
    mPatchCategory = BandCharDesc::Patch::kPatchNone;
}

bool CustomizePanel::IsCurrentAssetPatchable() {
    if (unk90 != gNullStr && mPatchCategory != 0)
        return true;
    else
        return false;
}

const char *CustomizePanel::GetPlacementMeshFromCurrentCamShot() {
    CamShot *pCurrentShot = mClosetMgr->GetCurrentShot();
    MILO_ASSERT(pCurrentShot, 0x6B6);
    const char *meshStr = pCurrentShot->Property(placement_mesh, true)->Str();
    return MakeString("%s_placement_%s.mesh", mClosetMgr->GetGender().mStr, meshStr);
}

void CustomizePanel::PreparePatchEdit(BandCharDesc::Patch::Category cat) {
    mPatchCategory = cat;
    mPatchName = GetPlacementMeshFromCurrentCamShot();
}

void CustomizePanel::PrepareAssetPatchEdit() {
    switch (mPatchCategory) {
    case BandCharDesc::Patch::kPatchBass:
        mPatchName = "instrument_placement01.mesh";
        break;
    case BandCharDesc::Patch::kPatchGuitar:
        mPatchName = "instrument_placement01.mesh";
        break;
    case BandCharDesc::Patch::kPatchTorso:
        mPatchName = GetPlacementMeshFromCurrentCamShot();
        break;
    default:
        break;
    }
}

void CustomizePanel::SetCurrentCharacterPatch() {
    mClosetMgr->SetCurrentCharacterPatch(mPatchCategory, mPatchName.c_str());
}

void CustomizePanel::FinishPatchEdit() {
    mClosetMgr->UpdateCharacterPatch(mPatchCategory, mPatchName.c_str());
    mClosetMgr->SetPatches();
    RefreshPatchEdit();
}

void CustomizePanel::RefreshPatchEdit() { mClosetMgr->RecomposePatches(mPatchCategory); }

void CustomizePanel::SavePrefab() {
    if (!IsLoaded()) {
        MILO_WARN("Tried to save prefab, but customize_panel is not loaded.\n");
    } else {
        BandCharacter *pBandCharacter = TheCharCache->GetCharacter(mUser->GetSlot());
        MILO_ASSERT(pBandCharacter, 0x6fb);
        pBandCharacter->SavePrefabFromCloset();
    }
}

bool CustomizePanel::CheatToggleAssetTokens() {
    return mShowAssetTokens = !mShowAssetTokens;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(CustomizePanel)
    HANDLE_EXPR(get_character, GetCharData())
    HANDLE_ACTION(set_current_boutique, SetCurrentBoutique(_msg->Sym(2)))
    HANDLE_EXPR(get_current_boutique, GetCurrentBoutique())
    HANDLE_ACTION(clear_current_boutique, ClearCurrentBoutique())
    HANDLE_EXPR(get_wearing, GetWearing())
    HANDLE_ACTION(preview_asset, PreviewAsset(_msg->Sym(2)))
    HANDLE_ACTION(preview_finish, PreviewFinish(_msg->Sym(2)))
    HANDLE_ACTION(select_asset, SelectAsset(_msg->Sym(2)))
    HANDLE_EXPR(asset_provider_has_asset, AssetProviderHasAsset(_msg->Sym(2)))
    HANDLE_EXPR(get_asset_shot, GetAssetShot(_msg->Sym(2)))
    HANDLE_ACTION(
        set_focus_component, SetFocusComponent((CustomizeState)_msg->Int(2), _msg->Sym(3))
    )
    HANDLE_ACTION(store_focus_component, StoreFocusComponent())
    HANDLE_EXPR(get_focus_component, GetFocusComponent())
    HANDLE_ACTION(set_state, SetCustomizeState((CustomizeState)_msg->Int(2)))
    HANDLE_EXPR(get_state, GetCustomizeState())
    HANDLE_EXPR(leave_state, LeaveState(_msg->Int(2)))
    HANDLE_EXPR(in_clothing_state, InClothingState())
    HANDLE_ACTION(
        set_patch_menu_return_state, SetPatchMenuReturnState((CustomizeState)_msg->Int(2))
    )
    HANDLE_EXPR(get_patch_menu_return_state, GetPatchMenuReturnState())
    HANDLE_EXPR(is_refreshing_content, mRefreshingContent)
    HANDLE_EXPR(has_license, HasLicense(_msg->Sym(2)))
    HANDLE_EXPR(new_asset_provider, mNewAssetProvider)
    HANDLE_EXPR(current_outfit_provider, mCurrentOutfitProvider)
    HANDLE_EXPR(asset_provider, mAssetProvider)
    HANDLE_EXPR(premium_asset_provider, mPremiumAssetProvider)
    HANDLE_EXPR(makeup_provider, mMakeupProvider)
    HANDLE_EXPR(instrument_finish_provider, mInstrumentFinishProvider)
    HANDLE_ACTION(update_new_asset_provider, UpdateNewAssetProvider())
    HANDLE_ACTION(update_current_outfit_provider, UpdateCurrentOutfitProvider())
    HANDLE_ACTION(update_asset_provider, UpdateAssetProvider())
    HANDLE_ACTION(update_makeup_provider, UpdateMakeupProvider(_msg->Sym(2)))
    HANDLE_EXPR(get_current_makeup, GetCurrentMakeup(_msg->Sym(2)))
    HANDLE_ACTION(preview_makeup, PreviewMakeup(_msg->Sym(2)))
    HANDLE_EXPR(has_new_assets, HasNewAssets())
    HANDLE_ACTION(setup_current_outfit, SetupCurrentOutfit(_msg->Sym(2)))
    HANDLE_ACTION(setup_asset_patch_data, SetupAssetPatchData(_msg->Sym(2)))
    HANDLE_EXPR(is_asset_patchable, IsAssetPatchable())
    HANDLE_EXPR(is_current_asset_patchable, IsCurrentAssetPatchable())
    HANDLE_ACTION(
        prepare_patch_edit, PreparePatchEdit((BandCharDesc::Patch::Category)_msg->Int(2))
    )
    HANDLE_ACTION(prepare_asset_patch_edit, PrepareAssetPatchEdit())
    HANDLE_ACTION(set_current_character_patch, SetCurrentCharacterPatch())
    HANDLE_ACTION(finish_patch_edit, FinishPatchEdit())
    HANDLE_ACTION(refresh_patch_edit, RefreshPatchEdit())
    HANDLE_EXPR(has_patch, HasPatch())
    HANDLE_ACTION(set_is_waiting_to_leave, SetIsWaitingToLeave(_msg->Int(2)))
    HANDLE_EXPR(is_waiting_to_leave, mWaitingToLeave)
    HANDLE_ACTION(take_portrait, mClosetMgr->TakePortrait())
    HANDLE_ACTION(save_prefab, SavePrefab())
    HANDLE_EXPR(cheat_toggle_asset_tokens, CheatToggleAssetTokens())
    HANDLE_EXPR(show_asset_tokens, mShowAssetTokens)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(UIComponentScrollMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x786)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(CustomizePanel)
    SYNC_PROP_SET(
        pending_state, (int &)mPendingState, SetPendingState((CustomizeState)_val.Int())
    )
    SYNC_PROP(unlocked_face_paint, mUnlockedFacePaint)
    SYNC_PROP(unlocked_tattoos, mUnlockedTattoos)
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS