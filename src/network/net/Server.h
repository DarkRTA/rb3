#pragma once
#include "obj/MsgSource.h"
#include "os/CritSec.h"
#include "os/OnlineID.h"

class Server : public MsgSource {
public:
    Server();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~Server();
    virtual void Init();
    virtual void Terminate();
    virtual void Poll() = 0;
    virtual void Login() = 0;
    virtual void Logout() = 0;
    virtual bool IsConnected();
    virtual bool IsLoggingIn();
    // fix all of these return types
    virtual int GetPlayerID();
    virtual int GetFriendsClient();
    virtual int GetMessagingClient();
    virtual int GetMatchMakingClient();
    virtual int GetCustomMatchMakingClient();
    virtual int GetPersistentStoreClient();
    virtual int GetCompetitionClient();
    virtual int GetSecureConnectionClient();
    virtual int GetAccountManagementClient();
    virtual int GetMasterProfileID();
    virtual int CreateProfile(String);
    virtual int DeleteProfile(OnlineID&);
    virtual int GetCustomAuthData();

    CriticalSection mLogoutCritSec; // 0x1c
    int mLoginState; // 0x38 - enum
    const char* mKey; // 0x3c
    String mAddress; // 0x40
    int mPort; // 0x4c
    int mPadLoggingIn; // 0x50
    unsigned int mPlayerIDLoggingIn; // 0x54
    unsigned int mPlayerIDs[4]; // 0x58
};