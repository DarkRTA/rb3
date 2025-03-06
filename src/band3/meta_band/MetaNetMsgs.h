#pragma once
#include "net/NetMessage.h"

class BandUser;

void InitJunkMsg();
void SendJunkPatchesToUser(BandUser *);
void SendJunkPatchesToAll();

class BandEventPreviewMsg : public NetMessage {
public:
    BandEventPreviewMsg() {}
    virtual ~BandEventPreviewMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(BandEventPreviewMsg);
    NETMSG_NAME(BandEventPreviewMsg);
    // NETMSG_NEWNETMSG(BandEventPreviewMsg);

    bool unk4;
};

class VerifyBuildVersionMsg : public NetMessage {
public:
    VerifyBuildVersionMsg();
    virtual ~VerifyBuildVersionMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(VerifyBuildVersionMsg);
    NETMSG_NAME(VerifyBuildVersionMsg);

    // NETMSG_NEWNETMSG(VerifyBuildVersionMsg);

    String mVersion; // 0x4
};

class JunkDataMsg : public NetMessage {
public:
    JunkDataMsg() {}
    virtual ~JunkDataMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(JunkDataMsg);
    NETMSG_NAME(JunkDataMsg);
    NETMSG_NEWNETMSG(JunkDataMsg);
};

class TriggerBackSoundMsg : public NetMessage {
public:
    TriggerBackSoundMsg() {}
    virtual ~TriggerBackSoundMsg() {}
    virtual void Save(BinStream &) const {}
    virtual void Load(BinStream &) {}
    virtual void Dispatch();
    NETMSG_BYTECODE(TriggerBackSoundMsg);
    NETMSG_NAME(TriggerBackSoundMsg);
};

class AppendSongToSetlistMsg : public NetMessage {
public:
    AppendSongToSetlistMsg() {}
    virtual ~AppendSongToSetlistMsg() {}
    virtual void Save(BinStream &bs) const { bs << unk4; }
    virtual void Load(BinStream &bs) { bs >> unk4; }
    virtual void Dispatch();
    NETMSG_BYTECODE(AppendSongToSetlistMsg);
    NETMSG_NAME(AppendSongToSetlistMsg);

    int unk4;
};

class RemoveLastSongFromSetlistMsg : public NetMessage {
public:
    RemoveLastSongFromSetlistMsg() {}
    virtual ~RemoveLastSongFromSetlistMsg() {}
    virtual void Save(BinStream &) const {}
    virtual void Load(BinStream &) {}
    virtual void Dispatch();
    NETMSG_BYTECODE(RemoveLastSongFromSetlistMsg);
    NETMSG_NAME(RemoveLastSongFromSetlistMsg);
};