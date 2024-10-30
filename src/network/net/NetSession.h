#pragma once
#include "Platform/Time.h"
#include "game/BandUser.h"
#include "game/GameMessages.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandNetGameData.h"
#include "net/NetMessage.h"
#include "net/SessionMessages.h"
#include "obj/Data.h"
#include "obj/MsgSource.h"
#include "os/User.h"
#include "utl/BinStream.h"
#include "utl/HxGuid.h"
#include "utl/JobMgr.h"

enum PacketType {
    kUnreliable = 0,
    kReliable = 1
};

class Friend;
class SessionSettings;
class RVSessionData;

class SessionData {
public:
    SessionData(){}
    virtual ~SessionData(){}
    virtual void CopyInto(const SessionData*) = 0;
    virtual void Save(BinStream&) const = 0;
    virtual void Load(BinStream&) = 0;
    virtual bool Equals(const SessionData*) const  = 0;

    static RVSessionData* New();
};

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
    virtual void InviteFriend(Friend*, const char*, const char*){}
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
    virtual bool OnMsg(const VoiceDataMsg&){ return false; }

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
    void AssignLocalOwner();
    void OnCreateSessionJobComplete(bool);
    void SetState(SessionState);
    void OnRegisterSessionJobComplete(bool);
    void OnConnectSessionJobComplete(bool);
    void Clear();
    void EnterInGameState();
    bool IsHost() const;
    void ProcessUserLeftMsg(const UserLeftMsg&);
    void UpdateSyncStore(const User*);
    void SendToAllClientsExcept(const NetMessage&, PacketType, unsigned int);
    void RemoveClient(unsigned int);
    void SetDoneArbitrating(int);
    void HandleSessionMsg(SessionMsg*);
    RemoteUser* GetNewRemoteUser();
    bool CheckJoinable(JoinResponseError&, int&, std::vector<UserGuid>, BinStream&);
    void StartGame();
    void StartArbitration();
    void BeginGameStartCountdown();
    void EndGame(int, bool, float);
    void LeaveInGameState(int, bool, float);
    void GetLocalUserList(std::vector<LocalUser*>&) const;
    void GetRemoteUserList(std::vector<RemoteUser*>&) const;
    void GetUserList(std::vector<User*>&) const;

    bool OnMsg(const JoinRequestMsg&);
    bool OnMsg(const JoinResponseMsg&);
    bool OnMsg(const NewUserMsg&);
    bool OnMsg(const AddUserRequestMsg&);
    bool OnMsg(const AddUserResponseMsg&);
    bool OnMsg(const UserLeftMsg&);
    bool OnMsg(const UpdateUserDataMsg&);
    bool OnMsg(const BeginArbitrationMsg&);
    bool OnMsg(const FinishedArbitrationMsg&);
    bool OnMsg(const StartGameOnTimeMsg&);
    bool OnMsg(const EndGameMsg&);

    DataNode OnSendMsg(DataArray*);
    DataNode OnSendMsgToAll(DataArray*);

    SessionData* mData; // 0x1c
    std::vector<User*> mUsers; // 0x20
    LocalUser* mLocalHost; // 0x28
    SessionData* mJoinData; // 0x2c
    SessionSettings* mSettings; // 0x30
    JobMgr mJobMgr; // 0x34
    int unk44; // 0x44
    GameState mGameState; // 0x48
    JoinResultMsg* mRevertingJoinResult; // 0x4c
    std::vector<int> mStillArbitrating; // 0x50
    Quazal::Time* mGameStartTime; // 0x58
    int mGameStartDelay; // 0x5c
    SessionState mState; // 0x60
    bool mOnlineEnabled; // 0x64
    int mQNet; // 0x68 - QuazalSession
};

extern NetSession* TheNetSession;