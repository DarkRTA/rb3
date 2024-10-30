#pragma once
#include "game/BandUser.h"
#include "game/GameMessages.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandNetGameData.h"
#include "net/SessionMessages.h"
#include "obj/Data.h"
#include "obj/MsgSource.h"
#include "os/User.h"
#include "utl/JobMgr.h"

enum PacketType {
    kUnreliable = 0,
    kReliable = 1
};

class Friend;
class SessionSettings;

class NetSession : public MsgSource {
public:
    enum SessionState {
        kIdle = 0,
        kCreatingHostSession = 1,
        kRegisteringHostSession = 2,
        kCreatingJoinSession = 3,
        kConnectingToSession = 4,
        kRequestingJoin = 5,
        kRevertingToHost = 6,
        kRequestingNewUser = 7,
        kClientsArbitrating = 8,
        kHostArbitrating = 9
    };

    enum GameState {
        kInLobby = 0,
        kGameNeedIntro = 0,
        kStartingGame = 1,
        kGameNeedStart = 1,
        kInOnlineGame = 2,
        kGamePlaying = 2,
        kGameOver = 3,
        kInLocalGame = 3
    };

    NetSession();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~NetSession();
    virtual void Poll();
    virtual void WriteStats(const std::vector<UserStat>&) = 0;
    virtual void SetInvitesAllowed(bool) = 0;
    virtual void InviteFriend(Friend*, const char*, const char*);
    virtual void PrepareRegisterHostSessionJob() = 0;
    virtual void AddLocalToSession(LocalUser*);
    virtual void AddRemoteToSession(RemoteUser*);
    virtual void RemoveLocalFromSession(LocalUser*);
    virtual void RemoveRemoteFromSession(RemoteUser*);
    virtual void StartSession() = 0;
    virtual void EndSession(bool) = 0;
    virtual void DeleteSession() = 0;
    virtual void PrepareConnectSessionJob() = 0;
    virtual void FinishJoin(const JoinResponseMsg&) = 0;
    virtual int PrepareRegisterArbitrationJob() = 0;
    virtual void UpdateSettings() = 0;
    virtual void OnSetPublic(bool){}
    virtual int OnMsg(const VoiceDataMsg&){ return 0; }

    bool IsLocal() const;
    void AddLocalUser(LocalUser*);
    void RemoveLocalUser(LocalUser*);
    void RegisterOnline();
    void Disconnect();
    bool IsOnlineEnabled() const;
    LocalUser* GetLocalHost() const;
    void SendMsg(User*, NetMessage&, PacketType);
    void SendMsg(const std::vector<RemoteUser*>&, NetMessage&, PacketType);
    void SendMsgToAll(NetMessage&, PacketType);
    bool IsJoining() const;
    bool HasUser(const User*) const;
    bool IsBusy() const;
    int NumOpenSlots() const;
    void GetLocalUserList(std::vector<LocalUser*>&) const;
    void AssignLocalOwner();
    void OnCreateSessionJobComplete(bool);
    void SetState(SessionState);
    void OnRegisterSessionJobComplete(bool);
    void OnConnectSessionJobComplete(bool);
    void Clear();
    void EnterInGameState();
    bool IsHost() const;

    int OnMsg(const JoinResponseMsg&);

    DataNode OnSendMsg(DataArray*);
    DataNode OnSendMsgToAll(DataArray*);

    int unk1c; // session data
    std::vector<User*> unk20; // 0x20
    LocalUser* mLocalHost; // 0x28
    int unk2c;
    SessionSettings* mSettings; // 0x30
    JobMgr mJobMgr; // 0x34
    int unk44; // 0x44
    GameState mGameState; // 0x48
    JoinResultMsg* mRevertingJoinResult; // 0x4c
    std::vector<int> unk50;
    int unk58;
    int mGameStartDelay; // 0x5c
    SessionState mState; // 0x60
    bool mOnlineEnabled; // 0x64
    int unk68; // 0x68 - QuazalSession
};

extern NetSession* TheNetSession;