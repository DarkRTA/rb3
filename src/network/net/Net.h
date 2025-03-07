#pragma once
#include "meta_band/BandNetGameData.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/SessionSearcher.h"
#include "net/SyncStore.h"
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
    NetGameData *GetGameData();
    NetSession *GetNetSession() const { return mSession; }
    Server *GetServer() const { return mServer; }
    SessionSearcher *GetSearcher() const { return unk24; }

    NetGameData *mGameData; // 0x1c
    NetSession *mSession; // 0x20
    SessionSearcher *unk24; // 0x24
    Server *mServer; // 0x28
    int unk2c; // NetworkEmulator*
    int unk30; // VoiceChatMgr*
    SyncStore *mSyncStore; // 0x34
    unsigned char *mThreadStack; // 0x38
    int unk3c;
    int unk40;
    int unk44;
    OSThread mThread; // 0x48
    RndOverlay *mNetOverlay; // 0x360
};

extern Net TheNet;