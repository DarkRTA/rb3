#pragma once
#include "game/NetGameMsgs.h"
#include "utl/BinStream.h"
#include "utl/HxGuid.h"
#include "utl/MemStream.h"

class SessionMsg : public NetMessage {
public:
    SessionMsg(){}
    virtual ~SessionMsg(){}
    virtual void Dispatch();
};

class JoinRequestMsg : public SessionMsg {
public:
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

class NewUserMsg : public SessionMsg {
public:
    NewUserMsg(const User*);
    virtual ~NewUserMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(NewUserMsg);
    NETMSG_NAME(NewUserMsg);

    NETMSG_NEWNETMSG(NewUserMsg);

    void GetUserData(BinStream&) const;

    UserGuid mUserGuid; // 0x4
    MemStream mUserData; // 0x14
};

class UserLeftMsg : public SessionMsg {
public:
    UserLeftMsg(User*);
    virtual ~UserLeftMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(UserLeftMsg);
    NETMSG_NAME(UserLeftMsg);

    NETMSG_NEWNETMSG(UserLeftMsg);

    UserGuid mUserGuid; // 0x4
};

class AddUserRequestMsg : public SessionMsg {
public:
    AddUserRequestMsg(const User*);
    virtual ~AddUserRequestMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(AddUserRequestMsg);
    NETMSG_NAME(AddUserRequestMsg);

    NETMSG_NEWNETMSG(AddUserRequestMsg);

    void GetUserData(BinStream&) const;
    void GetAuthenticationData(BinStream&) const;
    
    UserGuid mUserGuid; // 0x4
    MemStream mUserData; // 0x14
    MemStream mAuthData; // 0x34
};

class AddUserResponseMsg : public SessionMsg {
public:
    AddUserResponseMsg(User*);
    virtual ~AddUserResponseMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(AddUserResponseMsg);
    NETMSG_NAME(AddUserResponseMsg);

    NETMSG_NEWNETMSG(AddUserResponseMsg);

    bool mSuccess; // 0x4
    UserGuid mUserGuid; // 0x8
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