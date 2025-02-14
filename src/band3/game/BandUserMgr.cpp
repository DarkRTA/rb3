#include "game/BandUserMgr.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "meta/Profile.h"
#include "meta_band/BandProfile.h"
#include "meta_band/CharData.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/Matchmaker.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/PlatformMgr.h"
#include "os/User.h"
#include "os/UserMgr.h"
#include "tour/TourCharLocal.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
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

int BandUserMgr::GetLocalBandUsers(std::vector<LocalBandUser *> *users, int mask) const {}

int BandUserMgr::GetRemoteBandUsers(std::vector<RemoteBandUser *> *users, int mask) const {

}

int BandUserMgr::GetParticipatingBandUsers(std::vector<BandUser *> &users) const {
    return GetBandUsers(&users, 8);
}

int BandUserMgr::GetParticipatingBandUsersInSession(std::vector<BandUser *> &users
) const {
    return GetBandUsers(&users, 0x4008);
}

int BandUserMgr::GetBandUsersInSession(std::vector<BandUser *> &users) const {
    return GetBandUsers(&users, 0x4000);
}

int BandUserMgr::GetLocalParticipants(std::vector<LocalBandUser *> &users) const {
    return GetLocalBandUsers(&users, 8);
}

int BandUserMgr::GetLocalBandUsers(std::vector<LocalBandUser *> &users) const {
    return GetLocalBandUsers(&users, 2);
}

int BandUserMgr::GetLocalBandUsersInSession(std::vector<LocalBandUser *> &users) const {
    return GetLocalBandUsers(&users, 0x4000);
}

int BandUserMgr::GetLocalUsersWithAnyController(std::vector<LocalBandUser *> &users
) const {
    return GetLocalBandUsers(&users, 0x80);
}

int BandUserMgr::GetLocalUsersNotInSessionWithAnyController(
    std::vector<LocalBandUser *> &users
) const {
    return GetLocalBandUsers(&users, 0x2082);
}

LocalBandUser *BandUserMgr::GetUserFromPad(int pad) {
    FOREACH (it, mLocalUsers) {
        LocalBandUser *pLocalUser = *it;
        MILO_ASSERT(pLocalUser, 0x23E);
        if (pad == pLocalUser->GetPadNum())
            return pLocalUser;
    }
    return nullptr;
}

DataNode BandUserMgr::ForEachUser(const DataArray *a, int mask) {
    DataNode *var = a->Var(2);
    DataNode tmp = *var;
    std::vector<BandUser *> users;
    TheBandUserMgr->GetBandUsers(&users, mask);
    FOREACH (it, users) {
        BandUser *pUser = *it;
        MILO_ASSERT(pUser, 0x254);
        *var = pUser;
        for (int i = 3; i < a->Size(); i++) {
            a->Command(i)->Execute();
        }
    }
    *var = tmp;
    return 0;
}

DataNode BandUserMgr::OnMsg(const ProfilePreDeleteMsg &msg) {
    BandProfile *p = msg.GetProfile();
    std::vector<LocalBandUser *> users;
    GetLocalParticipants(users);
    FOREACH (it, users) {
        LocalBandUser *cur = *it;
        if (cur->HasChar()) {
            CharData *cd = cur->GetChar();
            if (cd->IsCustomizable() && p->GetCharFromGuid(cd->GetGuid())) {
                int slot = cur->GetSlot();
                if (slot != -1) {
                    cur->SetLoadedPrefabChar(slot);
                }
            }
        }
    }
    return 0;
}

DataNode BandUserMgr::OnMsg(const SigninChangedMsg &msg) {
    std::vector<LocalBandUser *> users;
    GetLocalParticipants(users);
    FOREACH (it, users) {
        LocalBandUser *cur = *it;
        if (ThePlatformMgr.HasUserSigninChanged(cur)) {
            if (ThePlatformMgr.IsUserSignedIn(cur)) {
                TourCharLocal *tChar = dynamic_cast<TourCharLocal *>(cur->GetChar());
                if (tChar) {
                    int slot = cur->GetSlot();
                    if (slot != -1) {
                        cur->SetLoadedPrefabChar(slot);
                    }
                }
            }
        }
    }
    return 0;
}

ControllerType BandUserMgr::DebugGetControllerTypeOverride(int padNum) {
    MILO_ASSERT_RANGE(padNum, 0, kNumJoypads, 0x2B3);
    LocalBandUser *local = GetUserFromPad(padNum);
    MILO_ASSERT(local, 0x2B5);
    return local->DebugGetControllerTypeOverride();
}

void BandUserMgr::DebugSetControllerTypeOverride(int padNum, ControllerType ct) {
    MILO_ASSERT_RANGE_EQ(ct, 0, kNumControllerTypes, 0x2BB);
    MILO_ASSERT_RANGE(padNum, 0, kNumJoypads, 0x2BC);
    LocalBandUser *local = GetUserFromPad(padNum);
    MILO_ASSERT(local, 0x2BE);
    local->DebugSetControllerTypeOverride(ct);
}

bool BandUserMgr::IsCharAvailable(const CharData *cd) const {
    std::vector<LocalBandUser *> users;
    GetLocalBandUsersInSession(users);
    FOREACH (it, users) {
        LocalBandUser *pUser = *it;
        MILO_ASSERT(pUser, 0x2D6);
        if (pUser->GetChar() == cd)
            return false;
    }
    ClosetMgr *mgr = ClosetMgr::GetClosetMgr();
    if (mgr && mgr->mPreviousCharacter == cd)
        return false;
    else
        return true;
}

BandUser *BandUserMgr::GetUserWithChar(const CharData *c) {
    MILO_ASSERT(c, 0x2E9);
    std::vector<BandUser *> users;
    GetBandUsersInSession(users);
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->GetChar() == c) {
            return users[i];
        }
    }
    return nullptr;
}

BEGIN_HANDLERS(BandUserMgr)
    HANDLE_ACTION(set_slot, SetSlot(_msg->Obj<BandUser>(2), _msg->Int(3)))
    HANDLE_EXPR(get_user_from_slot, GetUserFromSlot(_msg->Int(2)))
    HANDLE_EXPR(is_any_user_signed_in_and_connected, GetBandUsers(0x882) != 0)
    HANDLE_EXPR(does_any_user_have_online_privilege, GetBandUsers(0x1082) != 0)
    HANDLE_EXPR(foreach_user, ForEachUser(_msg, 0x4000))
    HANDLE_EXPR(foreach_local_user, ForEachUser(_msg, 0x4002))
    HANDLE_EXPR(get_num_participants, GetNumParticipants())
    HANDLE_EXPR(get_num_local_participants, GetNumLocalParticipants())
    HANDLE_EXPR(debug_get_user_from_pad, GetUserFromPad(_msg->Int(2)))
    HANDLE_EXPR(
        debug_get_controller_type_override, DebugGetControllerTypeOverride(_msg->Int(2))
    )
    HANDLE_ACTION(
        debug_set_controller_type_override,
        DebugSetControllerTypeOverride(_msg->Int(2), (ControllerType)_msg->Int(3))
    )
    HANDLE_MESSAGE(ProfilePreDeleteMsg)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_SUPERCLASS(UserMgr)
    HANDLE_CHECK(0x31F)
END_HANDLERS