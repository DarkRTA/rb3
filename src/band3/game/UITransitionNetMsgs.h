#pragma once
#include "meta_band/LockMessages.h"
#include "ui/UIScreen.h"

class StartTransitionMsg : public StartLockMsg, public LockData {
public:
    StartTransitionMsg() {}
    StartTransitionMsg(UIScreen *);
    virtual ~StartTransitionMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    virtual LockData *GetLockData();

    UIScreen *GetScreen() const;

    String mScreenName; // 0x1c
};

class NetGotoScreenMsg : public StartTransitionMsg {
public:
    NetGotoScreenMsg() {}
    NetGotoScreenMsg(UIScreen *, bool, bool);
    virtual ~NetGotoScreenMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(NetGotoScreenMsg);
    NETMSG_NAME(NetGotoScreenMsg);
    NETMSG_NEWNETMSG(NetGotoScreenMsg);

    bool mForce; // 0x28
    bool mBack; // 0x29
};

class NetSyncScreenMsg : public StartTransitionMsg {
public:
    NetSyncScreenMsg() {}
    NetSyncScreenMsg(UIScreen *, int);
    virtual ~NetSyncScreenMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(NetSyncScreenMsg);
    NETMSG_NAME(NetSyncScreenMsg);
    NETMSG_NEWNETMSG(NetSyncScreenMsg);

    bool mDepth; // 0x28
};

class NetPushScreenMsg : public StartTransitionMsg {
public:
    NetPushScreenMsg() {}
    NetPushScreenMsg(UIScreen *s) : StartTransitionMsg(s) {}
    virtual ~NetPushScreenMsg() {}
    NETMSG_BYTECODE(NetPushScreenMsg);
    NETMSG_NAME(NetPushScreenMsg);
    NETMSG_NEWNETMSG(NetPushScreenMsg);
};

class NetPopScreenMsg : public StartTransitionMsg {
public:
    NetPopScreenMsg() : StartTransitionMsg(nullptr) {}
    NetPopScreenMsg(UIScreen *s) : StartTransitionMsg(s) {}
    virtual ~NetPopScreenMsg() {}
    NETMSG_BYTECODE(NetPopScreenMsg);
    NETMSG_NAME(NetPopScreenMsg);
    NETMSG_NEWNETMSG(NetPopScreenMsg);
};