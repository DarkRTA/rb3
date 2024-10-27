#pragma once
#include "MetaMessages.h"
#include "game/BandUser.h"
#include "game/GameMessages.h"
#include "obj/Object.h"

class SessionMgr;

class CriticalUserListener : public Hmx::Object {
public:
    CriticalUserListener(SessionMgr*);
    virtual ~CriticalUserListener();
    virtual DataNode Handle(DataArray*, bool);

    void SetCriticalUser(LocalBandUser*);
    void ClearCriticalUser();

    DataNode OnMsg(const LocalUserLeftMsg&);
    DataNode OnMsg(const SigninChangedMsg&);

    LocalBandUser* mCriticalUser; // 0x1c
    SessionMgr* mSessionMgr; // 0x20
    bool mCanSaveData; // 0x24
};