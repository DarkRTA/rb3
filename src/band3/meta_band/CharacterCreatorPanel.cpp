#include "meta_band/CharacterCreatorPanel.h"
#include "FaceHairProvider.h"
#include "FaceOptionsProvider.h"
#include "OutfitProvider.h"
#include "PrefabMgr.h"
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandHeadShaper.h"
#include "game/BandUser.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/BandProfile.h"
#include "meta_band/CharData.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/EyebrowsProvider.h"
#include "meta_band/FaceTypeProvider.h"
#include "meta_band/NameGenerator.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/TexLoadPanel.h"
#include "os/Debug.h"
#include "tour/TourCharLocal.h"
#include "ui/UIGridProvider.h"
#include "ui/UIPanel.h"
#include "utl/Locale.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

CharacterCreatorPanel::CharacterCreatorPanel() : mCharCreatorState(kCharCreatorState_Invalid), mClosetMgr(0), mCharacter(0), mPreviewDesc(0), mFaceTypeProvider(0), mOutfitProvider(0), mFaceHairProvider(0),
    mFaceOptionsProvider(0), mFaceOptionsGridProvider(0), mEyebrowsProvider(0), mEyebrowsGridProvider(0), mGender(gNullStr), mOutfit(gNullStr), unk98(0), unk99(0) {

}

CharacterCreatorPanel::~CharacterCreatorPanel(){
    unk50.clear();
}

void CharacterCreatorPanel::Load(){
    TexLoadPanel::Load();
    mClosetMgr = ClosetMgr::GetClosetMgr();
    LocalBandUser* closetUser = mClosetMgr->mUser;
    BandProfile* profile = TheProfileMgr.GetProfileForUser(closetUser);
    if(profile && closetUser && mClosetMgr){
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
        SetCharCreatorState((CharCreatorState)1);
    }
}

void CharacterCreatorPanel::Poll(){
    UIPanel::Poll();
    if(GetState() == kUp) mClosetMgr->Poll();
}

void CharacterCreatorPanel::Exit(){
    UIPanel::Exit();
    if(mCharacter) SetCharCreatorState((CharCreatorState)0);
}

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
    unk98 = true;
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
    BandCharDesc* pPrefabCharDesc = pPrefabChar->GetBandCharDesc();
    MILO_ASSERT(pPrefabCharDesc, 0x1CA);
    mPreviewDesc->mOutfit = pPrefabCharDesc->mOutfit;
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
    if(mPreviewDesc){
        if(s == none_glasses) mPreviewDesc->mOutfit.mGlasses.mName = s;
        else mPreviewDesc->mOutfit.mGlasses.mName = gNullStr;
        mClosetMgr->SetCurrentOutfitPiece(glasses);
        mClosetMgr->PreviewCharacter(true, false);
    }
}

Symbol CharacterCreatorPanel::GetGlasses(){
    if(!mPreviewDesc) return gNullStr;
    Symbol glassesname = mPreviewDesc->mOutfit.mGlasses.mName;
    if(glassesname != gNullStr) return glassesname;
    else return none_glasses;
}