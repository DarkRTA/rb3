#pragma once
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "meta_band/NetSync.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/UIEventMgr.h"
#include "obj/MsgSource.h"

class InputMgr : public MsgSource {
public:
    InputMgr(BandUserMgr*, UIEventMgr*, NetSync*, SessionMgr*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~InputMgr();

    static void Init();
    static void Terminate();

    BandUserMgr* mBandUserMgr; // 0x1c
    UIEventMgr* mEventMgr; // 0x20
    NetSync* mNetSync; // 0x24
    SessionMgr* mSessionMgr; // 0x28
    bool unk2c; // 0x2c
    bool unk2d; // 0x2d
    BandUser* mUser; // 0x30
};

extern InputMgr* TheInputMgr;