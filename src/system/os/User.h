#ifndef OS_USER_H
#define OS_USER_H
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

#endif


// class User : public Object {
//     // total size: 0x48
// protected:
//     class String mUserName; // offset 0x28, size 0xC
// private:
//     int mUserNum; // offset 0x34, size 0x4
//     unsigned int mMachineID; // offset 0x38, size 0x4
//     unsigned char mReady; // offset 0x3C, size 0x1
//     class OnlineID * mOnlineID; // offset 0x40, size 0x4
//     unsigned char mHasOnlineID; // offset 0x44, size 0x1
// };
