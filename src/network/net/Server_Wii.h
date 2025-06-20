#pragma once
#include "Server.h"
#include "os/Timer.h"

class WiiServer : public Server {
public:
    WiiServer();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~WiiServer() {}
    virtual void Init();
    virtual void Terminate();
    virtual void Poll();
    virtual void Login();
    virtual void Logout();
    // fix all of these return types
    virtual int GetPlayerID(int);
    virtual int GetFriendsClient();
    virtual int GetMessagingClient();
    virtual Quazal::MatchMakingClient *GetMatchMakingClient();
    virtual Quazal::CustomMatchMakingClient *GetCustomMatchMakingClient();
    virtual Quazal::ServiceClient *GetPersistentStoreClient();
    virtual int GetCompetitionClient();
    virtual Quazal::SecureConnectionClient *GetSecureConnectionClient();
    virtual Quazal::AccountManagementClient *GetAccountManagementClient();
    virtual unsigned int GetMasterProfileID();
    virtual int CreateProfile(String);
    virtual int DeleteProfile(OnlineID &);
    virtual Quazal::Data *GetCustomAuthData();

    bool unk68;
    bool unk69;
    bool unk6a;
    bool unk6b;
    int unk6c;
    int unk70;
    int unk74;
    int unk78;
    int unk7c;
    int unk80;
    int unk84;
    int unk88;
    int unk8c;
    int unk90;
    int unk94;
    int unk98;
    int unk9c;
    int unka0;
    int unka4;
    int unka8;
    bool unkac;
    bool unkad;
    Timer unkb0;
    bool unke0;
};

extern WiiServer gWiiServer;