#ifndef RB3_USERMGR_HPP
#define RB3_USERMGR_HPP
#include "os/User.h"

class UserMgr : public User {
public:
    UserMgr();
    virtual ~UserMgr();
    virtual DataNode Handle(DataArray*, bool);
};

#endif
