#pragma once
#include "BandMachineMgr.h"
#include "BandNetGameData.h"
#include "game/NetGameMsgs.h"
#include "meta_band/CriticalUserListener.h"
#include "net/NetSession.h"
#include "net/Synchronize.h"
#include "obj/MsgSource.h"
#include "game/BandUser.h"

class BandUserMgr;
class Matchmaker;

enum PacketType {
    kUnreliable = 0,
    kReliable = 1
};

class SessionMgr : public MsgSource, public Synchronizable {
public:
    SessionMgr(BandUserMgr*, Matchmaker*);
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

    NetSession* mSession; // 0x38
    BandUserMgr* mBandUserMgr; // 0x3c
    int unk40; // 0x40
    int unk44; // 0x44
    int unk48; // 0x48
    Matchmaker* mMatchMaker; // 0x4c
    BandMachineMgr* mMachineMgr; // 0x50
    CriticalUserListener* mCritUserListener; // 0x54
    BandNetGameData* mBandNetGameData; // 0x58
    int unk5c; // 0x5c
    std::vector<int> unk60; // 0x60
    bool unk68; // 0x68
    int mNetRandomSeed; // 0x6c
    bool unk70; // 0x70
};

extern SessionMgr* TheSessionMgr;