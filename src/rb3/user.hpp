#ifndef RB3_USER_HPP
#define RB3_USER_HPP
#include "hmx/object.hpp"
#include "hxguid.hpp"
#include "onlineid.hpp"

class User : public Hmx::Object {
public:
    User();
    virtual ~User();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Reset();
    virtual void SyncSave(BinStream&, unsigned int) const;
    virtual bool IsLocal() const = 0;
    virtual void GetLocalUser() = 0;
    virtual void GetLocalUser() const = 0;
    virtual User* GetRemoteUser() = 0;
    virtual User* GetRemoteUser() const = 0;
    virtual char* UserName() const = 0;

    bool ComesBefore(const User*);

    OnlineID* id;
    UserGuid guid;
    int unk30;
};

User* GetUser(DataNode*, DataArray*);
User* GetUserAtIndex(DataArray*, int);

#endif
