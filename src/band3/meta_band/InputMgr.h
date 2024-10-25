#pragma once
#include "MetaMessages.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameMessages.h"
#include "meta_band/NetSync.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/UIEventMgr.h"
#include "obj/MsgSource.h"

class InputMgr : public MsgSource {
public:
    InputMgr(BandUserMgr*, UIEventMgr*, NetSync*, SessionMgr*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~InputMgr();

    BandUser* GetUser();
    bool IsActiveAndConnected(ControllerType) const;
    bool AllowRemoteExit() const;
    bool HasValidController(LocalBandUser*, ControllerType) const;
    bool AllowInput(BandUser*) const;
    void CheckTriggerAutoVocalsConfirm();
    void SetUser(BandUser*);
    void ExportStatusChangedMsg();
    LocalBandUser* GetUserWithInvalidController() const;
    void SetInvalidMessageSink(Hmx::Object*);
    void ClearInvalidMessageSink();
    void ExportUserLeftMsg();
    bool IsValidButtonForShell(JoypadButton, LocalBandUser*);

    DataNode OnMsg(const LocalUserLeftMsg&);
    DataNode OnMsg(const SigninChangedMsg&);
    DataNode OnMsg(const JoypadConnectionMsg&);
    DataNode OnMsg(const ButtonDownMsg&);
    DataNode OnMsg(const ButtonUpMsg&);

    static void Init();
    static void Terminate();

    BandUserMgr* mBandUserMgr; // 0x1c
    UIEventMgr* mEventMgr; // 0x20
    NetSync* mNetSync; // 0x24
    SessionMgr* mSessionMgr; // 0x28
    bool mAutoVocalsConfirmAllowed; // 0x2c
    bool unk2d; // 0x2d
    BandUser* mUser; // 0x30
};

extern InputMgr* TheInputMgr;