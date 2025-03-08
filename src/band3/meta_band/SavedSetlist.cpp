#include "meta_band/SavedSetlist.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/UIEventMgr.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/ObjMacros.h"
#include "os/DateTime.h"
#include "os/Debug.h"
#include "os/OnlineID.h"
#include "rndobj/Tex.h"
#include "tour/TourSavable.h"
#include "utl/HxGuid.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

Symbol SavedSetlist::SetlistTypeToSym(SetlistType ty) {
    switch (ty) {
    case kSetlistInternal:
        return setlist_internal;
    case kSetlistLocal:
        return setlist_local;
    case kSetlistFriend:
        return setlist_friend;
    case kSetlistHarmonix:
        return setlist_harmonix;
    case kBattleHarmonix:
        return battle_harmonix;
    case kBattleHarmonixArchived:
        return battle_harmonix_archived;
    case kBattleFriend:
        return battle_friend;
    case kBattleFriendArchived:
        return battle_friend_archived;
    default:
        MILO_FAIL("bad SetlistType");
        return gNullStr;
    }
}

int SavedSetlist::GetLengthMs() const {
    int ms = 0;
    FOREACH (it, mSongs) {
        BandSongMetadata *data = (BandSongMetadata *)TheSongMgr.Data(*it);
        if (data) {
            ms += data->LengthMs();
        }
    }
    return ms;
}

void SavedSetlist::AddSong(int id) {
    MILO_ASSERT(id != kSongID_Invalid && id != kSongID_Any && id != kSongID_Random, 0x4D);
    mSongs.push_back(id);
}

void SavedSetlist::SetSongs(const std::vector<int> &songs) { mSongs = songs; }

LocalSavedSetlist::LocalSavedSetlist()
    : SavedSetlist(gNullStr, gNullStr), mOwnerProfile(0) {
    mSaveSizeMethod = &SaveSize;
}

LocalSavedSetlist::LocalSavedSetlist(
    BandProfile *owner, const char *title, const char *desc, bool b
)
    : SavedSetlist(title, desc), mOwnerProfile(owner), mIsShared(b), mNeedsUpload(true),
      unk68(0) {
    mSaveSizeMethod = &SaveSize;
    mGuid.Generate();
}

int LocalSavedSetlist::SaveSize(int) {
    int size = HxGuid::SaveSize();
    REPORT_SIZE("SavedSetlist", size + 0x2A6);
}

Symbol LocalSavedSetlist::GetIdentifyingToken() const { return mGuid.ToString(); }

RndTex *LocalSavedSetlist::GetArtTex() const {
    RndTex *ret = nullptr;
    if (mArt.patchType == 1) {
        MILO_ASSERT(mOwnerProfile, 0x91);
        ret = mOwnerProfile->GetTexAtPatchIndex(mArt.patchIndex);
    }
    return ret;
}

void LocalSavedSetlist::SaveFixed(FixedSizeSaveableStream &fs) const {
    FixedSizeSaveable::SaveFixedString(fs, mTitle);
    FixedSizeSaveable::SaveStd(fs, mSongs, 100, 4);
    fs << mDateTime.ToCode();
    FixedSizeSaveable::SaveFixedString(fs, mDescription);
    fs << mIsShared;
    fs << mNeedsUpload;
    fs << mGuid;
    fs << mArt;
    fs << unk68;
}

void LocalSavedSetlist::LoadFixed(FixedSizeSaveableStream &fs, int rev) {
    FixedSizeSaveable::LoadFixedString(fs, mTitle);
    FixedSizeSaveable::LoadStd(fs, mSongs, 100, 4);
    unsigned int dtCode = 0;
    fs >> dtCode;
    mDateTime = DateTime(dtCode);
    FixedSizeSaveable::LoadFixedString(fs, mDescription);
    fs >> mIsShared;
    fs >> mNeedsUpload;
    fs >> mGuid;
    fs >> mArt;
    fs >> unk68;
}

void LocalSavedSetlist::ProcessRetCode(int ret) {
    static Message msg("init", 0);
    bool b2 = false;
    if (ret == 15) {
        msg[0] = Symbol("error_setlist_title_profane");
        TheUIEventMgr->TriggerEvent(error_message, msg);
        b2 = true;
    } else if (ret == 16) {
        msg[0] = Symbol("error_setlist_description_profane");
        TheUIEventMgr->TriggerEvent(error_message, msg);
        b2 = true;
    }
    if (b2) {
        mIsShared = false;
        mNeedsUpload = true;
    }
}

void LocalSavedSetlist::UploadComplete() {
    mNeedsUpload = false;
    TourSavable::UploadComplete();
}

DataNode LocalSavedSetlist::OnMsg(const RockCentralOpCompleteMsg &msg) {
    msg.Arg1();
    msg.Arg0();
    return 1;
}

BEGIN_HANDLERS(LocalSavedSetlist)
    HANDLE_EXPR(get_title, GetTitle())
    HANDLE_EXPR(get_description, GetDescription())
    HANDLE_EXPR(is_shared, GetShared())
    HANDLE_ACTION(set_title, SetTitle(_msg->Str(2)))
    HANDLE_ACTION(set_description, SetDescription(_msg->Str(2)))
    HANDLE_ACTION(set_shared, SetShared(_msg->Int(2)))
    HANDLE_EXPR(get_owner_profile, mOwnerProfile)
    HANDLE_EXPR(get_art_tex, GetArtTex())
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_SUPERCLASS(TourSavable)
    HANDLE_CHECK(0xFE)
END_HANDLERS

Symbol NetSavedSetlist::GetIdentifyingToken() const {
    switch (mSetlistType) {
    case 2:
        MILO_ASSERT(!mGuid.empty(), 0x107);
        return MakeString("fnd_%s", mGuid.c_str());
        break;
    case 3:
        MILO_ASSERT(mGuid.empty(), 0x10B);
        return MakeString("hmx_%s", GetTitle());
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        MILO_FAIL("Battles should have their own identifying token!\n");
        break;
    default:
        MILO_FAIL("Bad NetSavedSetlist SetlistType %i!\n", mSetlistType);
        break;
    }
    return gNullStr;
}

const char *NetSavedSetlist::GetOwner() const {
    return !mOwner.empty() ? mOwner.c_str() : nullptr;
}

const OnlineID *NetSavedSetlist::GetOwnerOnlineID() const { return &mOID; }

const char *NetSavedSetlist::GetArtUrl() const { return unk48.c_str(); }

const char *NetSavedSetlist::GetSongTitle(int i) const {
    MILO_ASSERT_RANGE(i, 0, mSongTitles.size(), 0x12F);
    return mSongTitles[i].c_str();
}

void NetSavedSetlist::AddSongTitle(const char *song) { mSongTitles.push_back(song); }

Symbol BattleSavedSetlist::GetIdentifyingToken() const {
    return MakeString("btl_%i", mID);
}