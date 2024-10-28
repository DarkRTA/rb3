#pragma once
#include "game/BandUser.h"
#include "game/NetGameMsgs.h"
#include "obj/MsgSource.h"
#include "os/User.h"

enum PacketType {
    kUnreliable = 0,
    kReliable = 1
};

class NetSession : public MsgSource {
public:
    NetSession();
    // virtual methods here

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

    int unk1c; // session data
    std::vector<int> unk20; // 0x20
};

extern NetSession* TheNetSession;