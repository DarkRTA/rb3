#include "meta_band/ClosetMgr.h"
#include "bandobj/BandCharDesc.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/CharCache.h"
#include "meta_band/CharSync.h"
#include "meta_band/ProfileMgr.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/User.h"
#include "tour/TourCharLocal.h"
#include "utl/Symbol.h"

namespace {
    ClosetMgr* TheClosetMgr;
}

ClosetMgr::ClosetMgr() : mUser(0), mSlot(-1), mNoUserMode(0), unk28(0), mCurrentCharacter(0), unk30(0), mBandCharacter(0), mBandCharDesc(0), unk40(0), unk44(gNullStr), unk48(0), unk4c(0),
    unk50(0), unk54(0), unk5c(gNullStr), unk60(0), unk61(0) {
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
    if(unk60){
        int slot = GetUserSlot();
        MILO_ASSERT(slot != -1, 0x60);
        mBandCharacter = TheCharCache->GetCharacter(slot);
        MILO_ASSERT(mBandCharacter, 0x62);
        if(!mBandCharacter->IsLoading()){
            unk60 = false;
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
        oldUser->SetChar(unk30);
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
    unk30 = 0;
    mBandCharacter = 0;
    mBandCharDesc = 0;
    unk40 = 0;
    unk44 = gNullStr;
    unk48 = 0;
    unk4c = 0;
    unk5c = gNullStr;
    unk60 = 0;
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
    unk5c = mBandCharDesc->mGender;
}

bool ClosetMgr::IsCurrentCharacterFinalized(){ return mCurrentCharacter->IsFinalized(); }

void ClosetMgr::UpdateBandCharDesc(BandCharDesc* pBandCharDesc){
    MILO_ASSERT(pBandCharDesc, 0xE2);
    mBandCharDesc->CopyCharDesc(pBandCharDesc);
    MILO_ASSERT(mBandCharDesc, 0xE4);
    unk3c->CopyCharDesc(mBandCharDesc);
    unk5c = mBandCharDesc->mGender;
}

Symbol ClosetMgr::GetAssetFromAssetType(AssetType ty){
    BandCharDesc* desc = mBandCharDesc;
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0xF0);
    Symbol ret =  gNullStr;
    switch(ty){
        case 0:
            break;
        case 1:
            ret = desc->mOutfit.mFaceHair.mName;
            break;
        case 2:
            ret = pAssetMgr->StripFinish(desc->mInstruments.mBass.mName);
            break;
        case 3:
            ret = pAssetMgr->StripFinish(desc->mInstruments.mDrum.mName);
            break;
        case 4:
            ret = desc->mOutfit.mEarrings.mName;
            break;
        case 5:
            ret = desc->mOutfit.mEyebrows.mName;
            break;
        case 6:
            ret = desc->mOutfit.mFaceHair.mName;
            break;
        case 7:
            ret = desc->mOutfit.mFeet.mName;
            break;
        case 8:
            ret = desc->mOutfit.mGlasses.mName;
            break;
        case 9:
            ret = desc->mOutfit.mHands.mName;
            break;
        case 10:
            ret = pAssetMgr->StripFinish(desc->mInstruments.mGuitar.mName);
            break;
        case 11:
            ret = desc->mOutfit.mHair.mName;
            break;
        case 12:
            ret = desc->mOutfit.mHair.mName;
            break;
        case 13:
            ret = desc->mInstruments.mKeyboard.mName;
            break;
        case 14:
            ret = desc->mOutfit.mLegs.mName;
            break;
        case 15:
            ret = desc->mInstruments.mMic.mName;
            break;
        case 16:
            ret = desc->mOutfit.mPiercings.mName;
            break;
        case 17:
            ret = desc->mOutfit.mRings.mName;
            break;
        case 18:
            ret = desc->mOutfit.mTorso.mName;
            break;
        case 19:
            ret = desc->mOutfit.mWrist.mName;
            break;
        default:
            MILO_ASSERT(false, 0x131);
            break;
    }
    return ret;
}