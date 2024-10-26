#pragma once
#include "BandMachineMgr.h"
#include "game/NetGameMsgs.h"
#include "net/Synchronize.h"
#include "obj/MsgSource.h"
#include "game/BandUser.h"

class BandUserMgr;
class MatchMaker;

enum PacketType {

};

class SessionMgr : public MsgSource, public Synchronizable {
public:
    SessionMgr(BandUserMgr*, MatchMaker*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~SessionMgr();
    virtual void RegisterOnline();
    virtual void Disconnect();
    virtual bool IsOnlineEnabled() const;
    virtual bool IsLocal() const;
    virtual bool HasRemoteUsers() const;
    virtual LocalBandUser* GetLocalHost() const;
    virtual bool HasUser(const User*) const;
    virtual bool IsBusy() const;
    virtual int NumOpenSlots() const;
    virtual bool AreInvitesAllowed() const;
    virtual void SyncSave(BinStream&, unsigned int) const;
    virtual void SyncLoad(BinStream&, unsigned int);
    virtual bool HasSyncPermission() const;
    virtual void OnSynchronized(unsigned int);
    virtual void AddLocalUserImpl(LocalBandUser*);
    virtual void RemoveLocalUserImpl(LocalBandUser*);
    virtual void GetLocalUserListImpl(std::vector<LocalUser*>&) const;

    bool IsLeaderLocal() const;
    void SendMsg(const std::vector<RemoteBandUser*>&, NetMessage&, PacketType);
    void SendMsg(BandUser*, NetMessage&, PacketType);
    void SendMsgToAll(NetMessage&, PacketType);
    BandUser* GetLeaderUser() const;
    bool HasLeaderUser() const;

    int unk38;
    int unk3c;
    int unk40;
    int unk44;
    int unk48;
    int unk4c;
    BandMachineMgr* unk50;
};

extern SessionMgr* TheSessionMgr;