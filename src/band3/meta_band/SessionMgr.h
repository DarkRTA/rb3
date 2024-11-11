#pragma once
#include "BandMachineMgr.h"
#include "BandNetGameData.h"
#include "game/Defines.h"
#include "game/NetGameMsgs.h"
#include "game/GameMode.h"
#include "meta_band/CriticalUserListener.h"
#include "net/NetSession.h"
#include "net/Synchronize.h"
#include "obj/MsgSource.h"
#include "game/BandUser.h"
#include "os/Debug.h"

class BandUserMgr;
class Matchmaker;

DECLARE_MESSAGE(SessionMgrUpdatedMsg, "session_mgr_updated_msg")
    SessionMgrUpdatedMsg() : Message(Type()) {}
END_MESSAGE;

DECLARE_MESSAGE(AddLocalUserResultMsg, "add_local_user_result_msg")
    AddLocalUserResultMsg(int i, LocalUser* u) : Message(Type(), i, u) {}
    bool Success() const { return mData->Int(2); }
    BandUser* GetBandUser() const {
        MILO_ASSERT(Success(), 0x33);
        return mData->Obj<BandUser>(3);
    }
END_MESSAGE;

DECLARE_MESSAGE(SessionDisconnectedMsg, "session_disconnected")
    SessionDisconnectedMsg() : Message(Type()) {}
END_MESSAGE;

DECLARE_MESSAGE(SessionBusyMsg, "session_busy")
    SessionBusyMsg() : Message(Type()) {}
END_MESSAGE;

DECLARE_MESSAGE(SessionReadyMsg, "session_ready")
    SessionReadyMsg(int i) : Message(Type(), i) {}
END_MESSAGE;

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
    void UpdateInvitesAllowed();
    void GetWaitingUsers(std::vector<RemoteBandUser*>&);
    void ClearWaitingUsers();
    void SetActiveRoster(bool);
    void ChangeRandomSeed();

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
    std::vector<RemoteBandUser*> mWaitingUsers; // 0x60
    bool mActiveRosterSet; // 0x68
    int mNetRandomSeed; // 0x6c
    bool mInvitesAllowed; // 0x70
};

extern SessionMgr* TheSessionMgr;