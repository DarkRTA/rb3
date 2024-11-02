#pragma once
#include "meta_band/BandNetGameData.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/SyncStore.h"
#include "obj/Object.h"
#include "revolution/os/OSThread.h"

class Net : public Hmx::Object {
public:
    Net();
    virtual ~Net(){}
    virtual DataNode Handle(DataArray*, bool);

    void Init();
    void Terminate();
    NetGameData* GetGameData();
    Server* GetServer() const { return mServer; }

    NetGameData* mGameData; // 0x1c
    NetSession* mSession; // 0x20
    int unk24; // SessionSearcher*
    Server* mServer; // 0x28
    int unk2c; // NetworkEmulator*
    int unk30; // VoiceChatMgr*
    SyncStore* mSyncStore; // 0x34
    unsigned char* mThreadStack; // 0x38
    int unk3c;
    int unk40;
    int unk44;
    OSThread mThread; // 0x48
    RndOverlay* mNetOverlay; // 0x360
};

extern Net TheNet;