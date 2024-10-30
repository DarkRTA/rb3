#pragma once
#include "game/NetGameMsgs.h"
#include "obj/Data.h"
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
    JoinRequestMsg(){}
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
    kCustom = 10
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
    NewUserMsg(){}
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
    UserLeftMsg(){}
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
    AddUserRequestMsg(){}
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
    AddUserResponseMsg(){}
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

class UpdateUserDataMsg : public SessionMsg {
public:
    UpdateUserDataMsg() : mUserData(false) {}
    UpdateUserDataMsg(const User*, unsigned int);
    virtual ~UpdateUserDataMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(UpdateUserDataMsg);
    NETMSG_NAME(UpdateUserDataMsg);

    NETMSG_NEWNETMSG(UpdateUserDataMsg);

    void GetUserData(BinStream&) const;

    UserGuid mUserGuid; // 0x4
    unsigned int mDirtyMask; // 0x14
    MemStream mUserData; // 0x18
};

class BeginArbitrationMsg : public SessionMsg {
public:
    BeginArbitrationMsg(){}
    virtual ~BeginArbitrationMsg(){}
    virtual void Save(BinStream &) const {}
    virtual void Load(BinStream &){}
    NETMSG_BYTECODE(BeginArbitrationMsg);
    NETMSG_NAME(BeginArbitrationMsg);

    NETMSG_NEWNETMSG(BeginArbitrationMsg);
};

class FinishedArbitrationMsg : public SessionMsg {
public:
    FinishedArbitrationMsg(){}
    virtual ~FinishedArbitrationMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(FinishedArbitrationMsg);
    NETMSG_NAME(FinishedArbitrationMsg);

    NETMSG_NEWNETMSG(FinishedArbitrationMsg);

    unsigned int mMachineID; // 0x4
};

class StartGameOnTimeMsg : public SessionMsg {
public:
    StartGameOnTimeMsg(){}
    StartGameOnTimeMsg(unsigned long long);
    virtual ~StartGameOnTimeMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(StartGameOnTimeMsg);
    NETMSG_NAME(StartGameOnTimeMsg);

    NETMSG_NEWNETMSG(StartGameOnTimeMsg);

    unsigned long long mStartTime; // 0x8
};

class EndGameMsg : public SessionMsg {
public:
    EndGameMsg(){}
    EndGameMsg(int, bool, float);
    virtual ~EndGameMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    NETMSG_BYTECODE(EndGameMsg);
    NETMSG_NAME(EndGameMsg);

    NETMSG_NEWNETMSG(EndGameMsg);

    int mResultCode; // 0x4
    bool mReportStats; // 0x8
    float unkc; // 0xc
};

class VoiceDataMsg : public SessionMsg {
public:
    VoiceDataMsg(){}
    virtual ~VoiceDataMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual bool VoiceData() const { return true; }
    NETMSG_BYTECODE(VoiceDataMsg);
    NETMSG_NAME(VoiceDataMsg);

    NETMSG_NEWNETMSG(VoiceDataMsg);

    void GetVoiceData(BinStream&) const;

    UserGuid mUserGuid; // 0x4
    MemStream mVoiceData; // 0x14
};

class DataArrayMsg : public NetMessage {
public:
    DataArrayMsg(){}
    DataArrayMsg(DataArray*);
    virtual ~DataArrayMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    virtual void Print(TextStream&) const;
    NETMSG_BYTECODE(DataArrayMsg);
    NETMSG_NAME(DataArrayMsg);

    NETMSG_NEWNETMSG(DataArrayMsg);

    MemStream mBuffer; // 0x4
};