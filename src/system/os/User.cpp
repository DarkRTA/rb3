#include "os/User.h"
#include "os/Debug.h"
#include "obj/MessageTimer.h"
#include "utl/Symbols.h"

User::User() : mOnlineID(new OnlineID()), mUserGuid(), unk30(-1) {
    mUserGuid.Generate();
}

void User::Reset(){
    unk30 = -1;
}

void User::SetUserGuid(const UserGuid& id){
    MILO_ASSERT(!IsLocal(), 0x2F);
    mUserGuid = id;
}

void User::SyncSave(BinStream& bs, unsigned int ui) const {
    bs << unk30;
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

LocalUser::LocalUser() : idk(0) {

}

bool LocalUser::IsLocal() const { return true; }

void LocalUser::GetLocalUser(){}
void LocalUser::GetLocalUser() const {}

User* LocalUser::GetRemoteUser(){
    TheDebug.Fail(MakeString("Bad Conversion"));
    return 0;
}

User* LocalUser::GetRemoteUser() const {
    TheDebug.Fail(MakeString("Bad Conversion"));
    return 0;
}

RemoteUser::RemoteUser() : str() {
    
}
