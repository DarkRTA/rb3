#include "game/BandUserMgr.h"
#include "game/BandUser.h"
#include "meta_band/Matchmaker.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/User.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

BandUserMgr *TheBandUserMgr;

#define kGameNumSlots 4

void BandUserMgrTerminate() {
    MILO_ASSERT(TheBandUserMgr, 0x20);
    RELEASE(TheBandUserMgr);
}

void BandUserMgrInit() {
    MILO_ASSERT(!TheBandUserMgr, 0x26);
    TheBandUserMgr = new BandUserMgr(4, 3);
    SetTheUserMgr(TheBandUserMgr);
    TheDebug.AddExitCallback(BandUserMgrTerminate);
}

BandUserMgr::BandUserMgr(int num_local, int num_remote) : mNullUser(0), mSessionMgr(0) {
    mUsers.reserve(num_local + num_remote);
    mLocalUsers.reserve(num_local);
    mRemoteUsers.reserve(num_remote);
    for (int i = 0; i < num_local; i++) {
        LocalBandUser *u = BandUser::NewLocalBandUser();
        mUsers.push_back(u);
        mLocalUsers.push_back(u);
    }
    for (int i = 0; i < num_remote; i++) {
        RemoteBandUser *u = BandUser::NewRemoteBandUser();
        mUsers.push_back(u);
        mRemoteUsers.push_back(u);
    }
    mNullUser = BandUser::NewNullLocalBandUser();
    for (int i = 0; i < 4; i++)
        mSlotMap[i].Clear();

    TheProfileMgr.AddSink(this, profile_pre_delete_msg);
    ThePlatformMgr.AddSink(this, signin_changed);
}

BandUserMgr::~BandUserMgr() {
    TheProfileMgr.RemoveSink(this, profile_pre_delete_msg);
    ThePlatformMgr.RemoveSink(this, signin_changed);
    TheBandUserMgr = nullptr;
    mLocalUsers.clear();
    mRemoteUsers.clear();
    DeleteAll(mUsers);
    RELEASE(mNullUser);
}

User *BandUserMgr::GetUser(const UserGuid &guid, bool fail) const {
    return GetBandUser(guid, fail);
}

LocalUser *BandUserMgr::GetLocalUser(const UserGuid &guid, bool fail) const {
    return GetLocalBandUser(guid, fail);
}

RemoteUser *BandUserMgr::GetRemoteUser(const UserGuid &guid, bool fail) const {
    return GetRemoteBandUser(guid, fail);
}

BandUser *BandUserMgr::GetBandUser(User *u) { return dynamic_cast<BandUser *>(u); }
LocalBandUser *BandUserMgr::GetLocalBandUser(LocalUser *u) {
    return dynamic_cast<LocalBandUser *>(u);
}
RemoteBandUser *BandUserMgr::GetRemoteBandUser(RemoteUser *u) {
    return dynamic_cast<RemoteBandUser *>(u);
}

BandUser *BandUserMgr::GetBandUser(const UserGuid &guid, bool fail) const {
    for (int i = 0; i < mUsers.size(); i++) {
        if (mUsers[i]->mUserGuid == guid) {
            return mUsers[i];
        }
    }
    if (fail) {
        MILO_FAIL("No BandUser exists with guid %s\n", guid.ToString());
    }
    return 0;
}

LocalBandUser *BandUserMgr::GetLocalBandUser(const UserGuid &guid, bool fail) const {
    int size = mLocalUsers.size();
    for (int i = 0; i < size; i++) {
        if (mLocalUsers[i]->mUserGuid == guid) {
            return mLocalUsers[i];
        }
    }
    if (fail) {
        MILO_FAIL("No LocalBandUser exists with guid %s\n", guid.ToString());
    }
    return 0;
}

RemoteBandUser *BandUserMgr::GetRemoteBandUser(const UserGuid &guid, bool fail) const {
    int size = mRemoteUsers.size();
    for (int i = 0; i < size; i++) {
        if (mRemoteUsers[i]->mUserGuid == guid) {
            return mRemoteUsers[i];
        }
    }
    if (fail) {
        MILO_FAIL("No RemoteBandUser exists with guid %s\n", guid.ToString());
    }
    return 0;
}

NullLocalBandUser *BandUserMgr::GetNullUser() const { return mNullUser; }

void BandUserMgr::GetUsers(std::vector<User *> &users) const {
    for (int i = 0; i < mUsers.size(); i++) {
        users.push_back(mUsers[i]);
    }
}

std::vector<BandUser *> &BandUserMgr::GetBandUsers() { return mUsers; }
std::vector<LocalBandUser *> &BandUserMgr::GetLocalBandUsers() { return mLocalUsers; }

void BandUserMgr::ResetSlots() {
    for (int i = 0; i < 4; i++)
        mSlotMap[i].Clear();
}

int BandUserMgr::GetSlot(const UserGuid &userGuid) const {
    MILO_ASSERT(!userGuid.IsNull(), 0xD4);
    for (int i = 0; i < 4; i++) {
        if (mSlotMap[i] == userGuid)
            return i;
    }
    return -1;
}

void BandUserMgr::SetSlot(BandUser *pUser, int slot) {
    MILO_ASSERT(( -1) <= (slot) && (slot) < ( kGameNumSlots), 0xE1);
    MILO_ASSERT(pUser, 0xE2);
    const UserGuid &userGuid = pUser->GetUserGuid();
    if (slot == -1) {
        slot = GetSlot(userGuid);
        if (slot != -1) {
            mSlotMap[slot].Clear();
        }
    } else
        mSlotMap[slot] = userGuid;
    if (mSessionMgr && mSessionMgr->HasSyncPermission()) {
        mSessionMgr->SetSyncDirty(-1, false);
        mSessionMgr->GetMatchmaker()->UpdateMatchmakingSettings();
    }
}

void BandUserMgr::ClearSlot(BandUser *u) { SetSlot(u, -1); }

const UserGuid &BandUserMgr::GetUserGuidFromSlot(int slotNum) const {
    MILO_ASSERT(0 <= slotNum && slotNum < kGameNumSlots, 0x101);
    return mSlotMap[slotNum];
}

BandUser *BandUserMgr::GetUserFromSlot(int slot) const {
    const UserGuid &guid = GetUserGuidFromSlot(slot);
    if (!guid.IsNull())
        return GetBandUser(guid, true);
    else
        return 0;
}

int BandUserMgr::MaxSlot() const {
    int slot = -1;
    for (int i = 0; i < 4; i++) {
        if (!mSlotMap[i].IsNull())
            slot = i;
    }
    return slot;
}

int BandUserMgr::GetNumParticipants() const {
    int num = 0;
    for (int i = 0; i < mUsers.size(); i++) {
        if (mUsers[i]->IsParticipating())
            num++;
    }
    return num;
}

int BandUserMgr::GetNumLocalParticipants() const {
    std::vector<LocalBandUser *> users;
    GetLocalParticipants(users);
    return users.size();
}

bool BandUserMgr::IsMultiplayerGame() const { return GetNumParticipants() > 1; }

int BandUserMgr::GetNumLocalPlayers() const {
    int num = 0;
    for (int i = 0; i < 4; i++) {
        if (!mSlotMap[i].IsNull()) {
            BandUser *u = TheBandUserMgr->GetBandUser(mSlotMap[i], true);
            if (u && u->IsLocal())
                num++;
        }
    }
    return num;
}

bool BandUserMgr::AllLocalUsersInSessionAreGuests() const {
    std::vector<LocalBandUser *> users;
    GetLocalBandUsersInSession(users);
    for (int i = 0; i < users.size(); i++) {
        if (!users[i]->IsGuest())
            return false;
    }
    return true;
}

int BandUserMgr::GetBandUsers(std::vector<BandUser *> *users, int mask) const {
    int ret = 0;
    if (!(mask & 1U)) {
        std::vector<LocalBandUser *> localUsers;
        ret = GetLocalBandUsers(!users ? nullptr : &localUsers, mask);
        if (users) {
            FOREACH (it, localUsers) {
                users->push_back(*it);
            }
        }
    }
    if (!(mask & 2U)) {
        std::vector<RemoteBandUser *> remoteUsers;
        ret += GetRemoteBandUsers(!users ? nullptr : &remoteUsers, mask);
        if (users) {
            FOREACH (it, remoteUsers) {
                users->push_back(*it);
            }
        }
    }
    return ret;
}

BEGIN_HANDLERS(BandUserMgr)
    HANDLE_ACTION(set_slot, SetSlot(_msg->Obj<BandUser>(2), _msg->Int(3)))
    HANDLE_EXPR(get_user_from_slot, GetUserFromSlot(_msg->Int(2)))

END_HANDLERS