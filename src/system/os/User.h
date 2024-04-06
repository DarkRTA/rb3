#ifndef OS_USER_H
#define OS_USER_H
#include "obj/Object.h"
#include "utl/HxGuid.h"
#include "os/OnlineID.h"
#include "utl/Str.h"

// forward decs
class LocalUser;
class RemoteUser;

class User : public Hmx::Object {
public:
    User();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~User(){}
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Reset();
    virtual void SyncSave(BinStream&, unsigned int) const;
    virtual bool IsLocal() const = 0;
    virtual LocalUser* GetLocalUser() = 0;
    virtual const LocalUser* GetLocalUser() const = 0;
    virtual RemoteUser* GetRemoteUser() = 0;
    virtual const RemoteUser* GetRemoteUser() const = 0;
    virtual const char* UserName() const = 0;

    void SetUserGuid(const UserGuid&);
    bool ComesBefore(const User* u){
        return (mUserGuid < u->mUserGuid);
    }

    OnlineID* mOnlineID;
    UserGuid mUserGuid;
    unsigned int mMachineID;
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
    virtual LocalUser* GetLocalUser();
    virtual const LocalUser* GetLocalUser() const;
    virtual RemoteUser* GetRemoteUser();
    virtual const RemoteUser* GetRemoteUser() const;

    void UpdateOnlineID();

    bool mHasOnlineID;
};

class RemoteUser : public virtual User {
public:
    RemoteUser();
    virtual ~RemoteUser(){}
    virtual bool IsLocal() const;
    virtual LocalUser* GetLocalUser();
    virtual const LocalUser* GetLocalUser() const;
    virtual RemoteUser* GetRemoteUser();
    virtual const RemoteUser* GetRemoteUser() const;
    virtual const char* UserName() const;
    virtual void SyncLoad(BinStream&, unsigned int);

    class String mUserName;
};

#endif
