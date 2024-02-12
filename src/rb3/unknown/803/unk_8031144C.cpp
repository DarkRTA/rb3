#include "os/User.h"
#include "common.hpp"
#include "localuser.hpp"

User::User() : id(new OnlineID()), guid(), unk30(-1) {
    guid.Generate();
}

void User::Reset(){
    unk30 = -1;
}


bool User::ComesBefore(const User* u){
    return guid < u->guid;
}


extern Symbol SymComesBefore, SymGetPlayerName, SymIsLocal, SymReset;
extern char* PathName(const Hmx::Object*);

DataNode User::Handle(DataArray* da, bool b){
    Symbol toMatch = da->GetSymAtIndex(1);
    if(toMatch == SymIsLocal){
        return DataNode(IsLocal());
    }
    if(toMatch == SymGetPlayerName){
        return DataNode(UserName());
    }
    if(toMatch == SymReset){
        Reset();
        return DataNode(0);
    }
    if(toMatch == SymComesBefore){
        return DataNode(ComesBefore(GetUserAtIndex(da, 2)));
    }
    {
    DataNode node = Hmx::Object::Handle(da, false);
    if(node.GetType() != kDataUnhandled) return DataNode(node);
    }
    if(b) PathName(this);
    return DataNode(kDataUnhandled, 0);
}

bool User::SyncProperty(DataNode& dn, DataArray* da, int i, PropOp op){
    int cnt = da->GetNodeCount();
    bool ret;
    if(i == cnt) ret = true;
    else {
        Symbol lol = da->GetSymAtIndex(cnt);
        ret = false;
    }
    return ret;
}

LocalUser::LocalUser(){
    idk = 0;
}

bool LocalUser::IsLocal() const { return true; }
void LocalUser::GetLocalUser(){}
void LocalUser::GetLocalUser() const { }
User* LocalUser::GetRemoteUser() { return nullptr; }
User* LocalUser::GetRemoteUser() const { return nullptr; }
