#pragma once
#include "game/BandUser.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandNetGameData.h"
#include "obj/MsgSource.h"
#include "os/User.h"

class SessionMsg : public NetMessage {
public:
    SessionMsg(){}
    virtual ~SessionMsg(){}
    virtual void Dispatch();
};

enum JoinResponseError {
    kSuccess = 0,
    kNotHosting = 1,
    kBusy = 2,
    kNoRoom = 3,
    kWrongMode = 4,
    kTimeout = 5,
    kNoSelfJoin = 6,
    kAlreadyHosting = 7,
    kCannotConnect = 8,
    kSameGuid = 9,
    kCustomJoinResponseError = 10
};

class JoinResponseMsg : public SessionMsg {
public:
    JoinResponseMsg(){}
    JoinResponseMsg(JoinResponseError, int);
    virtual ~JoinResponseMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    virtual void Print(TextStream&) const;
    NETMSG_BYTECODE(JoinResponseMsg);
    NETMSG_NAME(JoinResponseMsg);

    NETMSG_NEWNETMSG(JoinResponseMsg);

    JoinResponseError mError; // 0x4
    int mCustomError; // 0x8
};

class VoiceDataMsg : public SessionMsg {
public:
    VoiceDataMsg(){}
    virtual ~VoiceDataMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual bool VoiceData() const { return true; }
    virtual unsigned char ByteCode() const;
    virtual const char* Name() const;
};

enum PacketType {
    kUnreliable = 0,
    kReliable = 1
};

class Friend;

class NetSession : public MsgSource {
public:
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

    int unk1c; // session data
    std::vector<int> unk20; // 0x20
};

extern NetSession* TheNetSession;