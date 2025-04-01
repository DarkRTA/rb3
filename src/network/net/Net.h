#pragma once
#include "NetworkEmulator.h"
#include "meta_band/BandNetGameData.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/SessionSearcher.h"
#include "net/SyncStore.h"
#include "net/VoiceChatMgr.h"
#include "obj/Object.h"
#include "rndobj/Overlay.h"
#include "revolution/os/OSThread.h"

class Net : public Hmx::Object {
public:
    Net();
    virtual ~Net() {}
    virtual DataNode Handle(DataArray *, bool);

    void Init();
    void Terminate();
    void Poll();
    NetGameData *GetGameData();
    void UpdateNetOverlay();
    void SetGameData(NetGameData *);
    void ToggleLogging();
    NetSession *GetNetSession() const { return mSession; }
    Server *GetServer() const { return mServer; }
    SessionSearcher *GetSearcher() const { return mSearcher; }

    static void SystemCheckCallback(char const *, char const *, unsigned int);

    NetGameData *mGameData; // 0x1c
    NetSession *mSession; // 0x20
    SessionSearcher *mSearcher; // 0x24
    Server *mServer; // 0x28
    NetworkEmulator *mEmulator; // 0x2c
    VoiceChatMgr *mVoiceChatMgr; // 0x30
    SyncStore *mSyncStore; // 0x34
    unsigned char *mThreadStack; // 0x38
    int unk3c;
    int unk40;
    int unk44;
    OSThread mThread; // 0x48
    RndOverlay *mNetOverlay; // 0x360
};

void TerminateTheNet();

extern Net TheNet;