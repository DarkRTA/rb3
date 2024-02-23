#ifndef OS_USER_H
#define OS_USER_H
#include "obj/Object.h"
#include "utl/HxGuid.h"
#include "os/OnlineID.h"

class User : public Hmx::Object {
public:
    User();
    virtual ~User(){}
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

    void SetUserGuid(const UserGuid&);
    bool ComesBefore(const User*);

    OnlineID* mOnlineID;
    UserGuid mUserGuid;
    int unk30;
};

#endif
