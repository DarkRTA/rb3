#include "os/User.h"
#include "os/Debug.h"
#include "obj/MessageTimer.h"
#include "utl/Symbols.h"
#include "os/Joypad.h"
#include "os/Joypad_Wii.h"
#include "os/PlatformMgr.h"
#include "meta/WiiProfileMgr.h"

User::User() : mOnlineID(new OnlineID()), mUserGuid(), mMachineID(-1) {
    mUserGuid.Generate();
}

void User::Reset(){
    mMachineID = -1;
}

void User::SetUserGuid(const UserGuid& id){
    MILO_ASSERT(!IsLocal(), 0x2F);
    mUserGuid = id;
}

void User::SyncSave(BinStream& bs, unsigned int ui) const {
    bs << mMachineID;
    bs << UserName();
    bs << *mOnlineID;
}

BEGIN_HANDLERS(User);
    HANDLE_EXPR(is_local, IsLocal());
    HANDLE_EXPR(get_player_name, UserName());
    HANDLE_ACTION(reset, Reset());
    HANDLE_EXPR(comes_before, ComesBefore(_msg->Obj<User>(2)));
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x47);
END_HANDLERS;

bool User::SyncProperty(DataNode& _val, DataArray* _prop, int _i, PropOp _op){
    if(_prop->Size() == _i){
        return true;
    }
    else {
        Symbol b = _prop->Sym(_i);
        return false;
    }
}

LocalUser::LocalUser() : mHasOnlineID(0) {

}

bool LocalUser::IsLocal() const { return true; }

LocalUser* LocalUser::GetLocalUser(){ return this; }
const LocalUser* LocalUser::GetLocalUser() const { return this; }

RemoteUser* LocalUser::GetRemoteUser(){
    MILO_FAIL("Bad Conversion");
    return 0;
}

const RemoteUser* LocalUser::GetRemoteUser() const {
    MILO_FAIL("Bad Conversion");
    return 0;
}

int LocalUser::GetPadNum() const {
    return JoypadGetUsersPadNum((LocalUser*)this);
}

int LocalUser::GetPadType() const {
    return GetWiiJoypadType(GetPadNum());
}

void LocalUser::UpdateOnlineID(){
    mHasOnlineID = ThePlatformMgr.IsUserSignedIn((LocalUser*)this);
    mOnlineID->SetPrincipalID(
        TheWiiProfileMgr.GetIdForIndex(
            TheWiiProfileMgr.GetIndexForUser((LocalUser*)this)
        )
    );
}

bool LocalUser::IsJoypadConnected() const {
    static DataNode& fake_controllers = DataVariable("fake_controllers");
    int pad = fake_controllers.Int(0);
    if(pad) return true;
    else return JoypadIsConnectedPadNum(GetPadNum());
}

bool LocalUser::HasOnlinePrivilege() const {
    return ThePlatformMgr.UserHasOnlinePrivilege((LocalUser*)this);
}

bool LocalUser::IsGuest() const {
    return ThePlatformMgr.IsUserAGuest((LocalUser*)this);
}

bool LocalUser::IsSignedIn() const {
    return ThePlatformMgr.IsUserSignedIn((LocalUser*)this);
}

bool LocalUser::IsSignedInOnline() const {
    return ThePlatformMgr.IsUserSignedIntoLive((LocalUser*)this);
}

bool LocalUser::CanSaveData() const {
    bool check = IsSignedIn() && !IsGuest();
    if(check){
        return TheWiiProfileMgr.IsIndexValid(
            TheWiiProfileMgr.GetIndexForUser((LocalUser*)this)
        );
    }
    else return check;
}

const char* LocalUser::UserName() const {
    return ThePlatformMgr.GetName(GetPadNum());
}

BEGIN_HANDLERS(LocalUser)
    HANDLE_EXPR(get_pad_num, GetPadNum());
    HANDLE_EXPR(get_pad_type, GetPadType());
    HANDLE_EXPR(has_online_privilege, HasOnlinePrivilege());
    HANDLE_EXPR(is_signed_in_online, IsSignedInOnline());
    HANDLE_CHECK(0xDE);
END_HANDLERS

RemoteUser::RemoteUser() : mUserName() {

}

bool RemoteUser::IsLocal() const { return false; }

LocalUser* RemoteUser::GetLocalUser() {
    MILO_FAIL("Bad Conversion");
    return 0;
}

const LocalUser* RemoteUser::GetLocalUser() const {
    MILO_FAIL("Bad Conversion");
    return 0;
}

RemoteUser* RemoteUser::GetRemoteUser(){ return this; }
const RemoteUser* RemoteUser::GetRemoteUser() const { return this; }

const char* RemoteUser::UserName() const { return mUserName.c_str(); }

void RemoteUser::SyncLoad(BinStream& bs, unsigned int ui){
    bs >> mMachineID >> mUserName;
    bs >> *mOnlineID;
}
