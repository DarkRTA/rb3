#pragma once
#include "Services/Data.h"
#include "obj/Msg.h"
#include "os/CritSec.h"
#include "os/OnlineID.h"
#include "network/Services/AccountManagementClient.h"
#include "network/Services/ServiceClient.h"
#include "network/Platform/Holder.h"

class Server : public MsgSource {
public:
    Server();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~Server() {}
    virtual void Init();
    virtual void Terminate() {}
    virtual void Poll() = 0;
    virtual void Login() = 0;
    virtual void Logout() = 0;
    virtual bool IsConnected() { return mLoginState == 2; }
    virtual bool IsLoggingIn() { return mLoginState == 1; }
    virtual int GetPlayerID(int) {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    // fix all of these return types
    virtual int GetFriendsClient() {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    virtual int GetMessagingClient() {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    virtual int GetMatchMakingClient() {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    virtual int GetCustomMatchMakingClient() {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    virtual Quazal::ServiceClient *GetPersistentStoreClient() {
        MILO_FAIL("not implemented for this platform");
        return nullptr;
    }
    virtual int GetCompetitionClient() {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    virtual int GetSecureConnectionClient() {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    virtual Quazal::AccountManagementClient *GetAccountManagementClient() {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    virtual int GetMasterProfileID() {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    virtual int CreateProfile(String) {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    virtual int DeleteProfile(OnlineID &) {
        MILO_FAIL("not implemented for this platform");
        return 0;
    }
    virtual Quazal::Data *GetCustomAuthData() {
        MILO_FAIL("not implemented for this platform");
        static Quazal::AnyObjectHolder<Quazal::Data, Quazal::String> emptyDataHolder;
        return emptyDataHolder.mPtr;
    }

    CriticalSection mLogoutCritSec; // 0x1c
    int mLoginState; // 0x38 - enum
    const char *mKey; // 0x3c
    String mAddress; // 0x40
    int mPort; // 0x4c
    int mPadLoggingIn; // 0x50
    unsigned int mPlayerIDLoggingIn; // 0x54
    unsigned int mPlayerIDs[4]; // 0x58
};

extern Server &TheServer;

DECLARE_MESSAGE(ServerStatusChangedMsg, "server_status_changed");
bool Success() const { return mData->Int(2); }
END_MESSAGE