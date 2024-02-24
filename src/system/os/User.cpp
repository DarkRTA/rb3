#include "os/User.h"
#include "os/Debug.h"

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

RemoteUser::RemoteUser() : str() {
    
}
