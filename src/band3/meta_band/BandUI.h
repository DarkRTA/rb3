#pragma once
#include "WaitingUserGate.h"
#include "meta_band/InterstitialMgr.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/ShellInputInterceptor.h"
#include "obj/Msg.h"
#include "os/ContentMgr.h"
#include "rndobj/Overlay.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"

enum UIFlowType {
    kUIFlowType_None,
    kUIFlowType_Main,
    kUIFlowType_MusicLibrary,
    kUIFlowType_InGame
};

class BandUI : public UIManager, public MsgSource {
public:
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

    DataNode OnMsg(const ContentReadFailureMsg &);
    DataNode OnMsg(const UITransitionCompleteMsg &);

    bool unkd4; // 0xd4
    RndOverlay *mVignetteOverlay; // 0xd8
    RndOverlay *mUIOverlay; // 0xdc
    bool unke0; // 0xe0
    int unke4; // 0xe4
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