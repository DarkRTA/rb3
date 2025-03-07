#pragma once
#include "WaitingUserGate.h"
#include "game/BandUser.h"
#include "game/GameMic.h"
#include "meta/ConnectionStatusPanel.h"
#include "meta_band/InterstitialMgr.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/ShellInputInterceptor.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "obj/Msg.h"
#include "os/ContentMgr.h"
#include "os/JoypadMsgs.h"
#include "os/PlatformMgr.h"
#include "rndobj/Overlay.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "meta_band/EventDialogPanel.h"

enum UIFlowType {
    kUIFlowType_None,
    kUIFlowType_Main,
    kUIFlowType_MusicLibrary,
    kUIFlowType_InGame
};

class BandUI : public UIManager, public MsgSource {
public:
    enum DisbandStatus {
        kDisbandsDisabled,
        kDisbandsMessageOnly,
        kDisbandsEnabled
    };
    enum DisbandError {
        kNoLeader,
        kKicked,
        kAbandoned,
        kBadConfiguration
    };
    BandUI();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~BandUI();
    virtual void Init();
    virtual void Terminate();
    virtual void Poll();
    virtual void Draw();
    virtual void GotoScreen(UIScreen *, bool, bool);
    virtual void PushScreen(UIScreen *);
    virtual void PopScreen(UIScreen *);
    virtual bool InComponentSelect();
    virtual bool IsBlockingTransition();
    virtual bool IsTimelineResetAllowed() const;
    virtual void SendTransitionComplete(UIScreen *, UIScreen *);

    void GetCurrentScreenState(std::vector<UIScreen *> &);
    void WriteToVignetteOverlay(const char *);
    void InitPanels();
    void TriggerDisbandEvent(DisbandError);
    UIScreen *GetJoinEntryPointForFlowType(UIFlowType) const;
    void TriggerOnFinishedJoin(UIFlowType);
    void WipeOnNextTransition(bool);
    void WipeInIfNecessary();
    void WipeOutIfNecessary();
    bool WipingIn() const;
    bool WipingOut() const;
    void UpdateUIOverlay();
    UIScreen *GetTargetScreen(UIScreen *);
    void UpdateInputPerformanceMode();

    DataNode OnMsg(const ContentReadFailureMsg &);
    DataNode OnMsg(const UITransitionCompleteMsg &);
    DataNode OnMsg(const UIScreenChangeMsg &);
    DataNode OnMsg(const ProcessedJoinRequestMsg &);
    DataNode OnMsg(const ConnectionStatusChangedMsg &);
    DataNode OnMsg(const ServerStatusChangedMsg &);
    DataNode OnMsg(const DiskErrorMsg &);
    DataNode OnMsg(const JoypadConnectionMsg &);
    DataNode OnMsg(const ButtonDownMsg &);
    DataNode OnMsg(const ButtonUpMsg &);
    DataNode OnMsg(const UIComponentSelectMsg &);
    DataNode OnMsg(const UIComponentSelectDoneMsg &);
    DataNode OnMsg(const UIComponentFocusChangeMsg &);
    DataNode OnMsg(const UIComponentScrollMsg &);
    DataNode OnMsg(const GameMicsChangedMsg &);
    DataNode OnOvershellMsgCommon(const Message &, bool);
    DataNode OnMsg(const NetErrorMsg &);
    DataNode OnMsg(const OvershellActiveStatusChangedMsg &);
    DataNode OnMsg(const OvershellAllowingInputChangedMsg &);
    DataNode OnMsg(const EventDialogStartMsg &);
    DataNode OnMsg(const EventDialogDismissMsg &);
    DataNode OnMsg(const LocalUserLeftMsg &);

    UIPanel *EventDialog() const { return mEventDialog; }
    void SetInviteAccepted(bool b) { mInviteAccepted = b; }
    bool GetInviteAccepted() const { return mInviteAccepted; }
    void SetDisbandStatus(DisbandStatus s) { mDisbandStatus = s; }
    OvershellPanel *GetOvershell() { return mOvershell; }

    bool mShowVignettes; // 0xd4
    RndOverlay *mVignetteOverlay; // 0xd8
    RndOverlay *mUIOverlay; // 0xdc
    bool mInviteAccepted; // 0xe0 - invite accepted
    DisbandStatus mDisbandStatus; // 0xe4 - disband status
    OvershellPanel *mOvershell; // 0xe8
    UIPanel *mEventDialog; // 0xec
    UIPanel *mContentLoadingPanel; // 0xf0
    UIPanel *mPassiveMessagesPanel; // 0xf4
    UIPanel *mSaveLoadStatusPanel; // 0xf8
    WaitingUserGate *mWaitingUserGate; // 0xfc
    InterstitialMgr *mInterstitialMgr; // 0x100
    ShellInputInterceptor *mInputInterceptor; // 0x104
    UIPanel *mAbstractWipePanel; // 0x108
    bool unk10c; // 0x10c
    bool unk10d; // 0x10d
};

extern BandUI TheBandUI;