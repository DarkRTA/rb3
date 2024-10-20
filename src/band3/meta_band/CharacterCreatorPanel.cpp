#include "meta_band/CharacterCreatorPanel.h"
#include "CharacterCreatorPanel.h"
#include "FaceHairProvider.h"
#include "FaceOptionsProvider.h"
#include "OutfitProvider.h"
#include "PrefabMgr.h"
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandHeadShaper.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "math/Rand.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AppLabel.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/BandProfile.h"
#include "meta_band/CharData.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/EyebrowsProvider.h"
#include "meta_band/FaceTypeProvider.h"
#include "meta_band/NameGenerator.h"
#include "meta_band/ProfileAssets.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/TexLoadPanel.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include "tour/TourCharLocal.h"
#include "ui/UIComponent.h"
#include "ui/UIGridProvider.h"
#include "ui/UIList.h"
#include "ui/UIListMesh.h"
#include "ui/UIPanel.h"
#include "utl/Locale.h"
#include "utl/Messages3.h"
#include "utl/Messages4.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

CharacterCreatorPanel::CharCreatorState CharacterCreatorPanel::sCancelStates[18] = {
    kCharCreatorState_Invalid, kCharCreatorState_Invalid, kCharCreatorState_CharacterOptions, kCharCreatorState_CharacterOptions,
    kCharCreatorState_ModifyFace, kCharCreatorState_FaceMakerMenu, kCharCreatorState_FaceMakerMenu, kCharCreatorState_FaceMakerChooseChin,
    kCharCreatorState_FaceMakerMenu, kCharCreatorState_FaceMakerMenu, kCharCreatorState_FaceMakerChooseEyes, kCharCreatorState_FaceMakerModifyEyes,
    kCharCreatorState_FaceMakerMenu, kCharCreatorState_FaceMakerChooseBrows, kCharCreatorState_FaceMakerMenu, kCharCreatorState_FaceMakerChooseNose,
    kCharCreatorState_FaceMakerMenu, kCharCreatorState_FaceMakerChooseMouth
};

CharacterCreatorPanel::CharacterCreatorPanel() : mCharCreatorState(kCharCreatorState_Invalid), mClosetMgr(0), mCharacter(0), mPreviewDesc(0), mFaceTypeProvider(0), mOutfitProvider(0), mFaceHairProvider(0),
    mFaceOptionsProvider(0), mFaceOptionsGridProvider(0), mEyebrowsProvider(0), mEyebrowsGridProvider(0), mGender(gNullStr), mOutfit(gNullStr), mGenderChanged(0), mWaitingToFinalize(0) {

}

CharacterCreatorPanel::~CharacterCreatorPanel(){
    mFocusComponents.clear();
}

void CharacterCreatorPanel::Load(){
    TexLoadPanel::Load();
    mClosetMgr = ClosetMgr::GetClosetMgr();
    LocalBandUser* closetUser = mClosetMgr->mUser;
    BandProfile* profile = TheProfileMgr.GetProfileForUser(closetUser);
    if(profile && closetUser && mClosetMgr && profile == mClosetMgr->unk28){
        CreateNewCharacter();
        AddGridThumbnails(male);
        AddGridThumbnails(female);
        SetGender(male);
        MILO_ASSERT(!mOutfitProvider, 0xA7);
        mOutfitProvider = new OutfitProvider();
        MILO_ASSERT(!mFaceTypeProvider, 0xAA);
        mFaceTypeProvider = new FaceTypeProvider();
        MILO_ASSERT(!mFaceHairProvider, 0xAD);
        mFaceHairProvider = new FaceHairProvider();
        MILO_ASSERT(!mFaceOptionsProvider, 0xB0);
        mFaceOptionsProvider = new FaceOptionsProvider(mTexs);
        MILO_ASSERT(!mFaceOptionsGridProvider, 0xB3);
        mFaceOptionsGridProvider = new UIGridProvider(mFaceOptionsProvider, 3);
        MILO_ASSERT(!mEyebrowsProvider, 0xB6);
        mEyebrowsProvider = new EyebrowsProvider(mTexs);
        MILO_ASSERT(!mEyebrowsGridProvider, 0xB9);
        mEyebrowsGridProvider = new UIGridProvider(mEyebrowsProvider, 3);
    }
}

void CharacterCreatorPanel::FinishLoad(){
    TexLoadPanel::FinishLoad();
}

void CharacterCreatorPanel::Enter(){
    UIPanel::Enter();
    if(mCharacter){
        mClosetMgr->PreviewCharacter(true, false);
        SetProviders();
        if(!mClosetMgr->IsCurrentCharacterFinalized()) HandleGenderChanged();
        SetCharCreatorState(kCharCreatorState_CharacterOptions);
    }
}

void CharacterCreatorPanel::Poll(){
    UIPanel::Poll();
    if(GetState() == kUp) mClosetMgr->Poll();
}

void CharacterCreatorPanel::Exit(){
    UIPanel::Exit();
    if(mCharacter) SetCharCreatorState(kCharCreatorState_Invalid);
}

DECOMP_FORCEACTIVE(CharacterCreatorPanel, "mClosetMgr", "pUser", "pPreviousCharacter")

void CharacterCreatorPanel::Unload(){
    RELEASE(mEyebrowsGridProvider);
    RELEASE(mEyebrowsProvider);
    RELEASE(mFaceOptionsGridProvider);
    RELEASE(mFaceOptionsProvider);
    RELEASE(mFaceHairProvider);
    RELEASE(mFaceTypeProvider);
    RELEASE(mOutfitProvider);
}

LocalBandUser* CharacterCreatorPanel::GetUser(){
    return mClosetMgr->mUser;
}

void CharacterCreatorPanel::AddGridThumbnails(Symbol s){
    AddGridThumbnails(s, shape);
    AddGridThumbnails(s, chin);
    AddGridThumbnails(s, eye);
    AddGridThumbnails(s, eyebrows);
    AddGridThumbnails(s, nose);
    AddGridThumbnails(s, mouth);
}

DECOMP_FORCEACTIVE(CharacterCreatorPanel, "ui/character_creator/image/%s_keep.png")

void CharacterCreatorPanel::AddGridThumbnails(Symbol s1, Symbol s2){
    int count;
    if(s2 == eyebrows){
        AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x144);
        count = pAssetMgr->GetEyebrowsCount(s1) + 1;
    }
    else {
        count = BandHeadShaper::GetCount(s2);
    }
    for(int i = 0; i < count; i++){
        const char* str = MakeString("%s_%s_%d", s1.Str(), s2.Str(), i);
        const char* charstr = MakeString("ui/character_creator/image/%s_keep.png", str);
        AddTex(charstr, str, true, true);
    }
}

void CharacterCreatorPanel::CreateNewCharacter(){
    mCharacter = new TourCharLocal();
    mCharacter->GenerateGUID();
    LocalBandUser* pUser = mClosetMgr->mUser;
    MILO_ASSERT(pUser, 0x161);
    pUser->SetChar(mCharacter);
    mClosetMgr->UpdateCurrentCharacter();
    mCharacter->SetCharacterName(gNullStr);
}

void CharacterCreatorPanel::SetName(const char* name){
    mCharacter->SetCharacterName(name);
    UpdateNameLabel();
}

const char* CharacterCreatorPanel::GetName(){
    return mCharacter->GetCharacterName();
}

const char* CharacterCreatorPanel::GetDefaultVKName(){
    GetName();
    if(mGender == male){
        Symbol random_name = TheNameGenerator->GetRandomNameFromList(character_names_male);
        return Localize(random_name, 0);
    }
    else {
        Symbol random_name = TheNameGenerator->GetRandomNameFromList(character_names_female);
        return Localize(random_name, 0);
    }
}

void CharacterCreatorPanel::SetGender(Symbol gender){
    MILO_ASSERT(gender == male || gender == female, 0x195);
    mGender = gender;
}

void CharacterCreatorPanel::HandleGenderChanged(){
    mGenderChanged = true;
    mFaceTypeProvider->Update(mGender);
    mEyebrowsProvider->Update(mGender);
    mFaceOptionsProvider->mGender = mGender;
    PrefabMgr* pPrefabMgr = PrefabMgr::GetPrefabMgr();
    MILO_ASSERT(pPrefabMgr, 0x1A3);
    PrefabMgr::CharCreatorPrefab* pCharCreatorPrefab = pPrefabMgr->GetRandomCharCreatorPrefab(mGender);
    MILO_ASSERT(pCharCreatorPrefab, 0x1A7);
    mOutfit = pCharCreatorPrefab->unk4;
    PrefabChar* pPrefabChar = pCharCreatorPrefab->unk0;
    MILO_ASSERT(pPrefabChar, 0x1AE);
    BandCharDesc* pPrefabCharDesc = pPrefabChar->GetBandCharDesc();
    MILO_ASSERT(pPrefabCharDesc, 0x1B1);
    mClosetMgr->UpdateBandCharDesc(pPrefabCharDesc);
    mPreviewDesc = mClosetMgr->unk3c;
    MILO_ASSERT(mPreviewDesc, 0x1B5);
    mClosetMgr->PreviewCharacter(true, true);
}

void CharacterCreatorPanel::SetOutfit(Symbol outfit){
    mOutfit = outfit;
    PrefabMgr* pPrefabMgr = PrefabMgr::GetPrefabMgr();
    MILO_ASSERT(pPrefabMgr, 0x1C0);
    PrefabMgr::CharCreatorPrefab* pCharCreatorPrefab = pPrefabMgr->GetCharCreatorPrefab(mGender, mOutfit);
    MILO_ASSERT(pCharCreatorPrefab, 0x1C4);
    PrefabChar* pPrefabChar = pCharCreatorPrefab->unk0;
    MILO_ASSERT(pPrefabChar, 0x1C7);
    BandCharDesc* pPrefabBandCharDesc = pPrefabChar->GetBandCharDesc();
    MILO_ASSERT(pPrefabBandCharDesc, 0x1CA);
    BandCharDesc* target = mPreviewDesc;
    target->mOutfit.mTorso = pPrefabBandCharDesc->mOutfit.mTorso;
    target->mOutfit.mLegs = pPrefabBandCharDesc->mOutfit.mLegs;
    target->mOutfit.mFeet = pPrefabBandCharDesc->mOutfit.mFeet;
    target->mOutfit.mEarrings = pPrefabBandCharDesc->mOutfit.mEarrings;
    target->mOutfit.mHands = pPrefabBandCharDesc->mOutfit.mHands;
    target->mOutfit.mPiercings = pPrefabBandCharDesc->mOutfit.mPiercings;
    target->mOutfit.mRings = pPrefabBandCharDesc->mOutfit.mRings;
    target->mOutfit.mWrist = pPrefabBandCharDesc->mOutfit.mWrist;
    mClosetMgr->PreviewCharacter(true, true);
    UpdateOutfitList();
}

void CharacterCreatorPanel::SetEyeColor(int color){
    if(mPreviewDesc){
        mPreviewDesc->mHead.mEyeColor = color;
        mClosetMgr->PreviewCharacter(true, false);
    }
}

int CharacterCreatorPanel::GetEyeColor(){
    if(mPreviewDesc) return mPreviewDesc->mHead.mEyeColor;
    else return 0;
}

void CharacterCreatorPanel::SetGlasses(Symbol s){
    BandCharDesc* desc = mPreviewDesc;
    if(desc){
        if(s != none_glasses) desc->mOutfit.mGlasses.mName = s;
        else desc->mOutfit.mGlasses.mName = gNullStr;
        mClosetMgr->SetCurrentOutfitPiece(glasses);
        mClosetMgr->PreviewCharacter(true, false);
    }
}

Symbol CharacterCreatorPanel::GetGlasses(){
    if(!mPreviewDesc) return gNullStr;
    Symbol glassesName = mPreviewDesc->mOutfit.mGlasses.mName;
    if(glassesName == gNullStr) return none_glasses;
    else return mPreviewDesc->mOutfit.mHair.mName;
}

void CharacterCreatorPanel::SetHair(Symbol s){
    BandCharDesc* desc = mPreviewDesc;
    if(desc){
        if(s != none_hair) desc->mOutfit.mHair.mName = s;
        else desc->mOutfit.mHair.mName = gNullStr;
        mClosetMgr->SetCurrentOutfitPiece(hair);
        mClosetMgr->PreviewCharacter(true, false);
    }
}

Symbol CharacterCreatorPanel::GetHair(){
    if(!mPreviewDesc) return gNullStr;
    Symbol hairName = mPreviewDesc->mOutfit.mHair.mName;
    if(hairName == gNullStr) return none_hair;
    else return mPreviewDesc->mOutfit.mHair.mName;
}

void CharacterCreatorPanel::SetFaceHair(Symbol s){
    BandCharDesc* desc = mPreviewDesc;
    if(desc){
        if(s != none_facehair) desc->mOutfit.mFaceHair.mName = s;
        else desc->mOutfit.mFaceHair.mName = gNullStr;
        mClosetMgr->SetCurrentOutfitPiece(facehair);
        mClosetMgr->PreviewCharacter(true, false);
    }
}

Symbol CharacterCreatorPanel::GetFaceHair(){
    if(!mPreviewDesc) return gNullStr;
    Symbol facehairName = mPreviewDesc->mOutfit.mFaceHair.mName;
    if(facehairName == gNullStr) return none_facehair;
    else return facehairName;
}

void CharacterCreatorPanel::SetHeight(int height){
    if(mPreviewDesc){
        MILO_ASSERT(( 0) <= (height) && (height) <= ( 10), 0x268);
        mPreviewDesc->SetHeight(height / 10.0f);
        mClosetMgr->PreviewCharacter(true, false);
    }
}

int CharacterCreatorPanel::GetHeight(){
    if(!mPreviewDesc) return 0;
    else {
        float fHeight = mPreviewDesc->mHeight;
        MILO_ASSERT(( 0.0f) <= (fHeight) && (fHeight) <= ( 1.0f), 0x276);
        return fHeight * 10.0f;
    }
}

void CharacterCreatorPanel::SetWeight(int weight){
    if(mPreviewDesc){
        MILO_ASSERT(( 0) <= (weight) && (weight) <= ( 10), 0x282);
        mPreviewDesc->SetWeight(weight / 10.0f);
        mClosetMgr->PreviewCharacter(true, false);
    }
}

int CharacterCreatorPanel::GetWeight(){
    if(!mPreviewDesc) return 0;
    else {
        float fWeight = mPreviewDesc->mWeight;
        MILO_ASSERT(( 0.0f) <= (fWeight) && (fWeight) <= ( 1.0f), 0x290);
        return fWeight * 10.0f;
    }
}

void CharacterCreatorPanel::SetBuild(int build){
    if(mPreviewDesc){
        MILO_ASSERT(( 0) <= (build) && (build) <= ( 10), 0x29C);
        mPreviewDesc->SetMuscle(build / 10.0f);
        mClosetMgr->PreviewCharacter(true, false);
    }
}

int CharacterCreatorPanel::GetBuild(){
    if(!mPreviewDesc) return 0;
    else {
        float fBuild = mPreviewDesc->mMuscle;
        MILO_ASSERT(( 0.0f) <= (fBuild) && (fBuild) <= ( 1.0f), 0x2AA);
        return fBuild * 10.0f;
    }
}

void CharacterCreatorPanel::SetSkinTone(int tone){
    if(mPreviewDesc){
        mPreviewDesc->SetSkinColor(tone);
        mClosetMgr->PreviewCharacter(true, false);
    }
}

int CharacterCreatorPanel::GetSkinTone(){
    if(mPreviewDesc) return mPreviewDesc->mSkinColor;
    else return 0;
}

void CharacterCreatorPanel::RandomizeFace(){
    BandCharDesc* desc = mPreviewDesc;
    desc->mHead.mShape = RandomInt(0, BandHeadShaper::GetCount(shape));
    desc->mHead.mChin = RandomInt(0, BandHeadShaper::GetCount(chin));
    desc->mHead.mEye = RandomInt(0, BandHeadShaper::GetCount(eye));
    desc->mHead.mNose = RandomInt(0, BandHeadShaper::GetCount(nose));
    desc->mHead.mMouth = RandomInt(0, BandHeadShaper::GetCount(mouth));
    desc->mHead.mBrowHeight = 0.5f;
    desc->mHead.mBrowSeparation = 0.5f;
    desc->mHead.mChinHeight = 0.5f;
    desc->mHead.mChinWidth = 0.5f;
    desc->mHead.mEyeHeight = 0.5f;
    desc->mHead.mEyeRotation = 0.5f;
    desc->mHead.mEyeSeparation = 0.5f;
    desc->mHead.mJawHeight = 0.5f;
    desc->mHead.mJawWidth = 0.5f;
    desc->mHead.mMouthHeight = 0.5f;
    desc->mHead.mMouthWidth = 0.5f;
    desc->mHead.mNoseHeight = 0.5f;
    desc->mHead.mNoseWidth = 0.5f;
    desc->mOutfit.mEyebrows.mName = GetRandomEyebrows();
    mClosetMgr->PreviewCharacter(true, false);
    mClosetMgr->FinalizeCharCreatorChanges();
}

void CharacterCreatorPanel::SetFaceType(Symbol s){
    PrefabMgr* pPrefabMgr = PrefabMgr::GetPrefabMgr();
    MILO_ASSERT(pPrefabMgr, 0x2EC);
    BandCharDesc* pFaceTypeDesc = pPrefabMgr->GetFaceType(s);
    MILO_ASSERT(pFaceTypeDesc, 0x2EF);
    BandCharDesc* desc = mPreviewDesc;
    desc->mHead.mBrowHeight = pFaceTypeDesc->mHead.mBrowHeight;
    desc->mHead.mBrowSeparation = pFaceTypeDesc->mHead.mBrowSeparation;
    desc->mHead.mChin = pFaceTypeDesc->mHead.mChin;
    desc->mHead.mChinHeight = pFaceTypeDesc->mHead.mChinHeight;
    desc->mHead.mChinWidth = pFaceTypeDesc->mHead.mChinWidth;
    desc->mHead.mEye = pFaceTypeDesc->mHead.mEye;
    desc->mHead.mEyeHeight = pFaceTypeDesc->mHead.mEyeHeight;
    desc->mHead.mEyeRotation = pFaceTypeDesc->mHead.mEyeRotation;
    desc->mHead.mEyeSeparation = pFaceTypeDesc->mHead.mEyeSeparation;
    desc->mHead.mJawHeight = pFaceTypeDesc->mHead.mJawHeight;
    desc->mHead.mJawWidth = pFaceTypeDesc->mHead.mJawWidth;
    desc->mHead.mMouth = pFaceTypeDesc->mHead.mMouth;
    desc->mHead.mMouthHeight = pFaceTypeDesc->mHead.mMouthHeight;
    desc->mHead.mMouthWidth = pFaceTypeDesc->mHead.mMouthWidth;
    desc->mHead.mNose = pFaceTypeDesc->mHead.mNose;
    desc->mHead.mNoseHeight = pFaceTypeDesc->mHead.mNoseHeight;
    desc->mHead.mNoseWidth = pFaceTypeDesc->mHead.mNoseWidth;
    desc->mHead.mShape = pFaceTypeDesc->mHead.mShape;
    BandCharDesc* eyebrowdesc = mPreviewDesc;
    eyebrowdesc->mOutfit.mEyebrows = pFaceTypeDesc->mOutfit.mEyebrows;
    mClosetMgr->PreviewCharacter(true, false);
}

Symbol CharacterCreatorPanel::GetRandomEyebrows(){
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x312);
    std::vector<Symbol> eyebrows;
    pAssetMgr->GetEyebrows(eyebrows, mGender);
    return eyebrows[RandomInt(0, eyebrows.size())];
}

void CharacterCreatorPanel::SetFaceOption(int option){
    BandCharDesc* desc = mPreviewDesc;
    switch(mCharCreatorState){
        case kCharCreatorState_FaceMakerChooseCheeks:
            desc->mHead.mShape = option;
            break;
        case kCharCreatorState_FaceMakerChooseChin:
            desc->mHead.mChin = option;
            break;
        case kCharCreatorState_FaceMakerChooseEyes:
            desc->mHead.mEye = option;
            break;
        case kCharCreatorState_FaceMakerChooseNose:
            desc->mHead.mNose = option;
            break;
        case kCharCreatorState_FaceMakerChooseMouth:
            desc->mHead.mMouth = option;
            break;
        default:
            break;
    }
    mClosetMgr->PreviewCharacter(true, false);
}

void CharacterCreatorPanel::SetEyebrows(Symbol brows){
    BandCharDesc* desc = mPreviewDesc;
    if(desc){
        desc->mOutfit.mEyebrows.mName = brows;
        if(brows != none_eyebrows) desc->mOutfit.mEyebrows.mName = brows;
        else desc->mOutfit.mEyebrows.mName = gNullStr;
        mClosetMgr->SetCurrentOutfitPiece(eyebrows);
        mClosetMgr->PreviewCharacter(true, false);
    }
}

Symbol CharacterCreatorPanel::GetEyebrows(){
    if(mPreviewDesc) return mPreviewDesc->mOutfit.mEyebrows.mName;
    else return gNullStr;
}

int CharacterCreatorPanel::GetFeatureIndex(Symbol s){
    if(!mPreviewDesc) return 0;
    else {
        DataArrayPtr ptr(head, s);
        DataNode* featureIndex = mPreviewDesc->Property(ptr, true);
        MILO_ASSERT(featureIndex, 0x36D);
        return featureIndex->Int();
    }
}

void CharacterCreatorPanel::ModifyFeature(Symbol s, float f){
    if(mPreviewDesc){
        DataArrayPtr ptr(head, s);
        float prop = mPreviewDesc->Property(ptr, true)->Float();
        float newfloat = prop + f;
        ClampEq(newfloat, 0.0f, 1.0f);
        if(newfloat != prop){
            mPreviewDesc->SetProperty(ptr, newfloat);
            mClosetMgr->PreviewCharacter(true, false);
        }
    }
}

void CharacterCreatorPanel::SetProviders(){
    Handle(set_providers_msg, true);
}

void CharacterCreatorPanel::UpdateNameLabel(){
    if(mCharacter){
        static Message msg("get_name_label", 0);
        DataNode handled = Handle(msg, true);
        AppLabel* pAppLabel = handled.Obj<AppLabel>();
        MILO_ASSERT(pAppLabel, 0x395);
        pAppLabel->SetFromCharacter(mCharacter);
    }
}

void CharacterCreatorPanel::UpdateOutfitList(){
    Handle(update_outfit_list_msg, true);
}

void CharacterCreatorPanel::RefreshFaceOptionsList(){
    Handle(refresh_face_options_list_msg, true);
}

void CharacterCreatorPanel::FinalizeCharacter(){
    CheckCharacterAssets();
    mCharacter->SetFinalized(true);
    BandProfile* pProfile = mClosetMgr->unk28;
    MILO_ASSERT(pProfile, 0x3B1);
    pProfile->AddNewChar(mCharacter);
    mClosetMgr->FinalizeChanges(true, false);
    LocalBandUser* pUser = mClosetMgr->mUser;
    MILO_ASSERT(pUser, 0x3B9);
    TheAccomplishmentMgr->EarnAccomplishment(pUser, acc_charactercreate);
}

void CharacterCreatorPanel::SetIsWaitingToFinalize(bool b){ mWaitingToFinalize = b; }

void CharacterCreatorPanel::CheckCharacterAssets(){
    BandProfile* pProfile = mClosetMgr->unk28;
    MILO_ASSERT(pProfile, 0x3C9);
    Symbol syms[17] = {
        "eyebrows", "facehair", "hair", "earrings", "glasses", "piercings", "feet", "hands",
        "legs", "rings", "torso", "wrist", "guitar", "bass", "drum", "mic", "keyboard"
    };
    const ProfileAssets& assets = pProfile->mProfileAssets;
    BandCharDesc::Outfit& outfit = mPreviewDesc->mOutfit;
    BandCharDesc::InstrumentOutfit& ioutfit = mPreviewDesc->mInstruments;
    for(int i = 0; i < 17; i++){
        Symbol curSym = syms[i];
        BandCharDesc::OutfitPiece* curPiece;
        if(curSym == "guitar" || curSym == "bass" || curSym == "drum" || curSym == "mic" || curSym == "keyboard"){
            curPiece = ioutfit.GetPiece(curSym);
        }
        else curPiece = outfit.GetPiece(curSym);
        Symbol piecename = curPiece->mName;
        if(!assets.HasAsset(piecename)){
            MILO_WARN("Character has unsafe asset: (%s) in char/main/shared/nonselectable_prefabs.milo.", piecename.Str());
        }
    }
}

void CharacterCreatorPanel::SetCharCreatorState(CharCreatorState state){
    Symbol bodypart = gNullStr;
    switch(state){
        case kCharCreatorState_FaceMakerChooseCheeks:
            bodypart = shape;
            break;
        case kCharCreatorState_FaceMakerChooseChin:
            bodypart = chin;
            break;
        case kCharCreatorState_FaceMakerChooseEyes:
            bodypart = eye;
            break;
        case kCharCreatorState_FaceMakerChooseNose:
            bodypart = nose;
            break;
        case kCharCreatorState_FaceMakerChooseMouth:
            bodypart = mouth;
            break;
        default:
            break;
    }
    if(bodypart != gNullStr){
        mFaceOptionsProvider->Update(bodypart);
        RefreshFaceOptionsList();
    }
    static Message msg("update_state", 0, 0);
    msg[0] = state;
    msg[1] = mCharCreatorState;
    mCharCreatorState = state;
    HandleType(msg);
}

void CharacterCreatorPanel::SetFocusComponent(CharCreatorState state, Symbol s){
    UIComponent* pComponent = mDir->Find<UIComponent>(s.Str(), true);
    MILO_ASSERT(pComponent, 0x42E);
    mFocusComponents[state] = pComponent;
}

void CharacterCreatorPanel::StoreFocusComponent(){
    UIComponent* pFocusComponent = FocusComponent();
    MILO_ASSERT(pFocusComponent, 0x438);
    mFocusComponents[mCharCreatorState] = pFocusComponent;
}

UIComponent* CharacterCreatorPanel::GetFocusComponent(){
    return mFocusComponents[mCharCreatorState];
}

DataNode CharacterCreatorPanel::OnMsg(const ButtonDownMsg& msg){
    if(mWaitingToFinalize) return 1;
    JoypadAction act = msg.GetAction();
    if(mCharCreatorState == kCharCreatorState_FaceMakerModifyChin){
        switch(act){
            case kAction_Up:
                ModifyFeature("chin_height", 0.1f);
                break;
            case kAction_Right:
                ModifyFeature("chin_width", 0.1f);
                break;
            case kAction_Down:
                ModifyFeature("chin_height", -0.1f);
                break;
            case kAction_Left:
                ModifyFeature("chin_width", -0.1f);
                break;
            default:
                break;
        }
    }
    else if(mCharCreatorState == kCharCreatorState_FaceMakerModifyJaw){
        switch(act){
            case kAction_Up:
                ModifyFeature("jaw_height", 0.1f);
                break;
            case kAction_Right:
                ModifyFeature("jaw_width", 0.1f);
                break;
            case kAction_Down:
                ModifyFeature("jaw_height", -0.1f);
                break;
            case kAction_Left:
                ModifyFeature("jaw_width", -0.1f);
                break;
            default:
                break;
        }
    }
    else if(mCharCreatorState == kCharCreatorState_FaceMakerModifyEyes){
        switch(act){
            case kAction_Up:
                ModifyFeature("eye_height", 0.1f);
                break;
            case kAction_Right:
                ModifyFeature("eye_separation", 0.1f);
                break;
            case kAction_Down:
                ModifyFeature("eye_height", -0.1f);
                break;
            case kAction_Left:
                ModifyFeature("eye_separation", -0.1f);
                break;
            default:
                break;
        }
    }
    else if(mCharCreatorState == kCharCreatorState_FaceMakerRotateEyes){
        switch(act){
            case kAction_Up:
                ModifyFeature("eye_rotation", 0.1f);
                break;
            case kAction_Down:
                ModifyFeature("eye_rotation", -0.1f);
                break;
            default:
                break;
        }
    }
    else if(mCharCreatorState == kCharCreatorState_FaceMakerModifyBrows){
        switch(act){
            case kAction_Up:
                ModifyFeature("brow_height", 0.1f);
                break;
            case kAction_Right:
                ModifyFeature("brow_separation", 0.1f);
                break;
            case kAction_Down:
                ModifyFeature("brow_height", -0.1f);
                break;
            case kAction_Left:
                ModifyFeature("brow_separation", -0.1f);
                break;
            default:
                break;
        }
    }
    else if(mCharCreatorState == kCharCreatorState_FaceMakerModifyNose){
        switch(act){
            case kAction_Up:
                ModifyFeature("nose_height", 0.1f);
                break;
            case kAction_Right:
                ModifyFeature("nose_width", 0.1f);
                break;
            case kAction_Down:
                ModifyFeature("nose_height", -0.1f);
                break;
            case kAction_Left:
                ModifyFeature("nose_width", -0.1f);
                break;
            default:
                break;
        }
    }
    else if(mCharCreatorState == kCharCreatorState_FaceMakerModifyMouth){
        switch(act){
            case kAction_Up:
                ModifyFeature("mouth_height", 0.1f);
                break;
            case kAction_Right:
                ModifyFeature("mouth_width", 0.1f);
                break;
            case kAction_Down:
                ModifyFeature("mouth_height", -0.1f);
                break;
            case kAction_Left:
                ModifyFeature("mouth_width", -0.1f);
                break;
            default:
                break;
        }
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode CharacterCreatorPanel::LeaveState(){
    LocalBandUser* pUser = mClosetMgr->mUser;
    MILO_ASSERT(pUser, 0x4D6);
    static Message msg("handle_sound_back", 0);
    msg[0] = pUser;
    Handle(msg, true);
    mClosetMgr->ResetCharacterPreview();
    SetCharCreatorState(sCancelStates[mCharCreatorState]);
    return 1;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(CharacterCreatorPanel)
    HANDLE_EXPR(get_user, GetUser())
    HANDLE_ACTION(set_name, SetName(_msg->Str(2)))
    HANDLE_EXPR(get_name, GetName())
    HANDLE_EXPR(get_default_vk_name, GetDefaultVKName())
    HANDLE_ACTION(update_name_label, UpdateNameLabel())
    HANDLE_ACTION(set_gender, SetGender(_msg->Sym(2)))
    HANDLE_EXPR(get_gender, GetGender())
    HANDLE_ACTION(handle_gender_changed, HandleGenderChanged())
    HANDLE_ACTION(set_outfit, SetOutfit(_msg->Sym(2)))
    HANDLE_EXPR(get_outfit, GetOutfit())
    HANDLE_ACTION(set_facetype, SetFaceType(_msg->Sym(2)))
    HANDLE_ACTION(set_eye_color, SetEyeColor(_msg->Int(2)))
    HANDLE_EXPR(get_eye_color, GetEyeColor())
    HANDLE_ACTION(set_glasses, SetGlasses(_msg->Sym(2)))
    HANDLE_EXPR(get_glasses, GetGlasses())
    HANDLE_ACTION(set_hair, SetHair(_msg->Sym(2)))
    HANDLE_EXPR(get_hair, GetHair())
    HANDLE_ACTION(set_facehair, SetFaceHair(_msg->Sym(2)))
    HANDLE_EXPR(get_facehair, GetFaceHair())
    HANDLE_ACTION(set_eyebrows, SetEyebrows(_msg->Sym(2)))
    HANDLE_EXPR(get_eyebrows, GetEyebrows())
    HANDLE_ACTION(set_height, SetHeight(_msg->Int(2)))
    HANDLE_EXPR(get_height, GetHeight())
    HANDLE_ACTION(set_weight, SetWeight(_msg->Int(2)))
    HANDLE_EXPR(get_weight, GetWeight())
    HANDLE_ACTION(set_build, SetBuild(_msg->Int(2)))
    HANDLE_EXPR(get_build, GetBuild())
    HANDLE_ACTION(set_skin_tone, SetSkinTone(_msg->Int(2)))
    HANDLE_EXPR(get_skin_tone, GetSkinTone())
    HANDLE_ACTION(randomize_face, RandomizeFace())
    HANDLE_ACTION(set_face_option, SetFaceOption(_msg->Int(2)))
    HANDLE_EXPR(get_feature_index, GetFeatureIndex(_msg->Sym(2)))
    HANDLE_ACTION(set_focus_component, SetFocusComponent((CharCreatorState)_msg->Int(2), _msg->Sym(3)))
    HANDLE_ACTION(store_focus_component, StoreFocusComponent())
    HANDLE_EXPR(get_focus_component, GetFocusComponent())
    HANDLE_ACTION(finalize_character, FinalizeCharacter())
    HANDLE_ACTION(set_is_waiting_to_finalize, SetIsWaitingToFinalize(_msg->Int(2)))
    HANDLE_EXPR(is_waiting_to_finalize, mWaitingToFinalize)
    HANDLE_ACTION(set_state, SetCharCreatorState((CharCreatorState)_msg->Int(2)))
    HANDLE_EXPR(get_state, GetCharCreatorState())
    HANDLE_ACTION(leave_state, LeaveState())
    HANDLE_EXPR(outfit_provider, mOutfitProvider)
    HANDLE_EXPR(facetype_provider, mFaceTypeProvider)
    HANDLE_EXPR(facehair_provider, mFaceHairProvider)
    HANDLE_ACTION(set_face_options_provider, _msg->Obj<UIList>(2)->SetProvider(mFaceOptionsGridProvider))
    HANDLE_ACTION(set_eyebrows_provider, _msg->Obj<UIList>(2)->SetProvider(mEyebrowsGridProvider))
    HANDLE_EXPR(get_face_options_selected, mFaceOptionsGridProvider->GetDataFromList(_msg->Obj<UIList>(2)))
    HANDLE_ACTION(set_face_options_selected, mFaceOptionsGridProvider->SetListToData(_msg->Obj<UIList>(2), _msg->Int(3)))
    HANDLE_EXPR(get_eyebrows_selected, mEyebrowsGridProvider->GetSymbolFromList(_msg->Obj<UIList>(2)))
    HANDLE_ACTION(set_eyebrows_selected, mEyebrowsGridProvider->SetListToSymbol(_msg->Obj<UIList>(2), _msg->Sym(3)))
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_SUPERCLASS(TexLoadPanel)
    HANDLE_CHECK(0x556)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(CharacterCreatorPanel)
    SYNC_PROP(gender_changed, mGenderChanged)
END_PROPSYNCS

inline int FaceOptionsProvider::NumData() const { return mFaceOptionCount; }

inline RndMat* FaceOptionsProvider::Mat(int, int data, UIListMesh* mesh) const {
    MILO_ASSERT(data < NumData(), 0x59);
    if(mesh->Matches("icon")){
        const char* genderStr = mGender.Str();
        String str(MakeString("%s_%s_%d", genderStr, mFaceOption, data));
        std::vector<DynamicTex*>::const_iterator it = std::find(mIcons.begin(), mIcons.end(), str);
        if(it != mIcons.end()) return (*it)->mMat;
    }
    return nullptr;
}