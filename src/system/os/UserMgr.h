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
    virtual void GetUsers(User*, std::vector<User*>&) const = 0;
    virtual User* GetUser(const UserGuid&, bool) const = 0;
    virtual User* GetLocalUser(const UserGuid&, bool) const;
    virtual User* GetRemoteUser(const UserGuid&, bool) const;
};

#endif
