#include "os/UserMgr.h"
#include "os/Joypad.h"
#include "obj/Dir.h"
#include "utl/Symbols.h"

UserMgr* TheUserMgr = 0;

void SetTheUserMgr(UserMgr* mgr){
    TheUserMgr = mgr;
    JoypadReset();
}

UserMgr::UserMgr(){
    SetName("user_mgr", ObjectDir::sMainDir);
}

LocalUser* UserMgr::GetLocalUser(const UserGuid& ug, bool b) const { return 0; }
RemoteUser* UserMgr::GetRemoteUser(const UserGuid& ug, bool b) const { return 0; }

void UserMgr::GetLocalUsers(std::vector<LocalUser*>& lUsers) const {
    std::vector<User*> users;
    GetUsers(users);
    for(int i = 0; i < users.size(); i++){
        if(users[i]->IsLocal()){
            lUsers.push_back(users[i]->GetLocalUser());
        }
    }
}

void UserMgr::GetRemoteUsers(std::vector<RemoteUser*>& rUsers) const {
    std::vector<User*> users;
    GetUsers(users);
    for(int i = 0; i < users.size(); i++){
        if(!users[i]->IsLocal()){
            rUsers.push_back(users[i]->GetRemoteUser());
        }
    }
}

LocalUser* UserMgr::GetLocalUserFromPadNum(int padnum) const {
    return JoypadGetUserFromPadNum(padnum);
}

BEGIN_HANDLERS(UserMgr)
    HANDLE_EXPR(get_user_from_pad_num, JoypadGetUserFromPadNum(_msg->Int(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x47)
END_HANDLERS
