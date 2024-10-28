#pragma once
#include "BandMachineMgr.h"
#include "BandNetGameData.h"
#include "game/Defines.h"
#include "game/GameMessages.h"
#include "game/NetGameMsgs.h"
#include "meta_band/CriticalUserListener.h"
#include "net/NetSession.h"
#include "net/Synchronize.h"
#include "obj/MsgSource.h"
#include "game/BandUser.h"

class BandUserMgr;
class Matchmaker;

class SavePlayer {
public:
    LocalBandUser* mUser; // 0x0
    ControllerType mCt; // 0x4
    int mSlot; // 0x8
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
    void SendMsg(RemoteBandMachine*, NetMessage&, PacketType);
    void SendMsg(BandUser*, NetMessage&, PacketType);
    void SendMsgToAll(NetMessage&, PacketType);
    BandUser* GetLeaderUser() const;
    bool HasLeaderUser() const;
    void Poll();
    void AddLocalUser(LocalBandUser*);
    void SetLeaderUser(BandUser*);
    void RemoveLocalUser(LocalBandUser*);
    void UpdateLeader();
    void ClearLeader();
    bool IsLocalToLeader(const BandUser*) const;

    static void Init();

    DataNode OnMsg(const LocalUserLeftMsg&);
    DataNode OnMsg(const SessionReadyMsg&);
    DataNode OnMsg(const SessionDisconnectedMsg&);
    DataNode OnMsg(const SessionBusyMsg&);
    DataNode OnMsg(const AddUserResultMsg&);
    DataNode OnMsg(const SigninChangedMsg&);
    DataNode OnMsg(const ModeChangedMsg&);
    DataNode OnMsg(const NewRemoteUserMsg&);
    DataNode OnMsg(const RemoteUserLeftMsg&);
    DataNode OnMsg(const JoinResultMsg&);
    DataNode OnMsg(const ProcessedJoinRequestMsg&);

    NetSession* mSession; // 0x38
    BandUserMgr* mBandUserMgr; // 0x3c
    SavePlayer mNewPlayer; // 0x40
    Matchmaker* mMatchMaker; // 0x4c
    BandMachineMgr* mMachineMgr; // 0x50
    CriticalUserListener* mCritUserListener; // 0x54
    BandNetGameData* mBandNetGameData; // 0x58
    BandUser* mUserLeader; // 0x5c
    std::vector<int> unk60; // 0x60
    bool unk68; // 0x68
    int mNetRandomSeed; // 0x6c
    bool unk70; // 0x70
};

extern SessionMgr* TheSessionMgr;