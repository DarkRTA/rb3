#pragma once
#include "game/BandUser.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandNetGameData.h"
#include "obj/MsgSource.h"
#include "os/User.h"

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