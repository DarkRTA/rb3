#ifndef RB3_LOCALUSER_HPP
#define RB3_LOCALUSER_HPP
#include "user.hpp"

class LocalUser : public virtual User {
public:
    LocalUser();
    virtual ~LocalUser();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool IsLocal() const; // fn_80311AD8
    virtual void GetLocalUser();
    virtual void GetLocalUser() const;
    virtual User* GetRemoteUser();
    virtual User* GetRemoteUser() const;
    virtual char* UserName() const;

    char idk;
};

#endif
