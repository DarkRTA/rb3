#ifndef OS_USER_H
#define OS_USER_H
#include "obj/Object.h"
#include "utl/HxGuid.h"
#include "os/OnlineID.h"
#include "utl/Str.h"

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
    virtual const char* UserName() const = 0;

    void SetUserGuid(const UserGuid&);
    bool ComesBefore(const User* u){
        return (mUserGuid < u->mUserGuid);
    }

    OnlineID* mOnlineID;
    UserGuid mUserGuid;
    int unk30;
};

class LocalUser : public virtual User {
public:
    LocalUser();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~LocalUser(){}
    virtual int GetPadNum() const;
    virtual int GetPadType() const;
    virtual bool IsJoypadConnected() const;
    virtual bool HasOnlinePrivilege() const;
    virtual bool IsGuest() const;
    virtual bool IsSignedIn() const;
    virtual bool IsSignedInOnline() const;
    virtual bool CanSaveData() const;
    virtual const char* UserName() const;
    virtual bool IsLocal() const;
    virtual void GetLocalUser();
    virtual void GetLocalUser() const;
    virtual User* GetRemoteUser();
    virtual User* GetRemoteUser() const;

    bool idk;
};

class RemoteUser : public virtual User {
public:
    RemoteUser();
    virtual ~RemoteUser(){}
    virtual bool IsLocal() const;
    virtual void GetLocalUser();
    virtual void GetLocalUser() const;
    virtual User* GetRemoteUser();
    virtual User* GetRemoteUser() const;
    virtual const char* UserName() const;
    virtual void SyncLoad(BinStream&, unsigned int);

    String str;
};

#endif
