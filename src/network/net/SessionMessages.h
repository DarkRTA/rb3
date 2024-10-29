#pragma once
#include "game/NetGameMsgs.h"
#include "utl/BinStream.h"
#include "utl/MemStream.h"

class SessionMsg : public NetMessage {
public:
    SessionMsg(){}
    virtual ~SessionMsg(){}
    virtual void Dispatch();
};

class JoinRequestMsg : public SessionMsg {
public:
    JoinRequestMsg() : mAuthData(false) {}
    JoinRequestMsg(const std::vector<User*>&, int);
    virtual ~JoinRequestMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(JoinRequestMsg);
    NETMSG_NAME(JoinRequestMsg);

    NETMSG_NEWNETMSG(JoinRequestMsg);

    int NumUsers() const { return mUserDatas.size(); }
    void GetUserData(int, BinStream&) const;
    const UserGuid& GetUserGuid(int) const;
    void GetAuthenticationData(BinStream&) const;

    int mGameMode; // 0x4
    std::vector<UserGuid> mUserGuids; // 0x8
    std::vector<MemStream> mUserDatas; // 0x10
    MemStream mAuthData; // 0x18
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

    bool Joined() const;

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