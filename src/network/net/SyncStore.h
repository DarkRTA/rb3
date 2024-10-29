#pragma once
#include "NetMessage.h"
#include "net/Synchronize.h"
#include "utl/HxGuid.h"
#include "utl/MemStream.h"
#include <vector>

class SyncObjMsg : public NetMessage {
public:
    SyncObjMsg() : mObjData(false) {}
    SyncObjMsg(String&, unsigned int, Synchronizable*);
    virtual ~SyncObjMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    virtual void Print(TextStream&) const;
    NETMSG_BYTECODE(SyncObjMsg);
    NETMSG_NAME(SyncObjMsg);

    NETMSG_NEWNETMSG(SyncObjMsg);

    String mObjTag; // 0x4
    unsigned int mDirtyMask; // 0x10
    MemStream mObjData; // 0x14
};

class SyncUserMsg : public NetMessage {
public:
    SyncUserMsg(){}
    virtual ~SyncUserMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(SyncUserMsg);
    NETMSG_NAME(SyncUserMsg);

    NETMSG_NEWNETMSG(SyncUserMsg);

    UserGuid mUserGuid; // 0x4
};

class SyncAllMsg : public NetMessage {
public:
    SyncAllMsg(){}
    virtual ~SyncAllMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(SyncAllMsg);
    NETMSG_NAME(SyncAllMsg);

    NETMSG_NEWNETMSG(SyncAllMsg);
};

class SyncStore {
public:
    SyncStore();
    void Poll();

    std::vector<Synchronizable*> mSyncObjs; // 0x0
};

extern SyncStore* TheSyncStore;