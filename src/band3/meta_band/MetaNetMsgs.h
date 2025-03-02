#pragma once
#include "net/NetMessage.h"

class BandUser;

void InitJunkMsg();
void SendJunkPatchesToUser(BandUser *);
void SendJunkPatchesToAll();

class VerifyBuildVersionMsg : public NetMessage {
public:
    VerifyBuildVersionMsg();
    virtual ~VerifyBuildVersionMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(LockResponseMsg);
    NETMSG_NAME(LockResponseMsg);

    // NETMSG_NEWNETMSG(LockResponseMsg);

    String unk4;
};