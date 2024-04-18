#ifndef OS_USERMGR_H
#define OS_USERMGR_H
#include "obj/Object.h"
#include "os/User.h"
#include "utl/HxGuid.h"
#include <vector>

class UserMgr : public Hmx::Object {
public:
    UserMgr();
    virtual ~UserMgr(){}
    virtual DataNode Handle(DataArray*, bool);
    virtual void GetUsers(std::vector<User*>&) const = 0;
    virtual User* GetUser(const UserGuid&, bool) const = 0;
    virtual LocalUser* GetLocalUser(const UserGuid&, bool) const;
    virtual RemoteUser* GetRemoteUser(const UserGuid&, bool) const;

    void GetLocalUsers(std::vector<LocalUser*>&) const;
    void GetRemoteUsers(std::vector<RemoteUser*>&) const;
    LocalUser* GetLocalUserFromPadNum(int) const;
};

void SetTheUserMgr(UserMgr*);
extern UserMgr* TheUserMgr;

#endif
