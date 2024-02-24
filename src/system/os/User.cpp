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

DataNode User::Handle(DataArray* _msg, bool _warn){
    Symbol sym = _msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? this : 0, sym);
    if(sym == is_local){
        return DataNode(IsLocal());
    }
    if(sym == get_player_name){
        return DataNode(UserName());
    }
    if(sym == reset){
        Reset();
        return DataNode(0);
    }
    if(sym == comes_before){
        return DataNode(ComesBefore(_msg->Obj<User>(2)));
    }
    {
        DataNode handled = Hmx::Object::Handle(_msg, false);
        if(handled.Type() != kDataUnhandled){
            return DataNode(handled);
        }
    }
    if(_warn) MILO_WARN("%s(%d): %s unhandled msg: %s", __FILE__, 0x47, PathName(this), sym);
    return DataNode(kDataUnhandled, 0);
}

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
