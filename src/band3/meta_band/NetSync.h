#pragma once
#include "LockStepMgr.h"
#include "game/NetGameMsgs.h"
#include "obj/Object.h"
#include "ui/UIComponent.h"
#include "ui/UIMessages.h"
#include "ui/UIScreen.h"

class NetSync : public Hmx::Object {
public:
    NetSync();
    virtual ~NetSync();
    virtual DataNode Handle(DataArray*, bool);

    bool IsBlockingTransition() const;
    bool IsBlockingEvent(Symbol) const;
    bool IsEnabled() const;
    NetUIState GetUIState() const;
    void Poll();
    void AttemptTransition(UIScreen*, int);
    void Enable();
    void Disable();
    void SetUIState(NetUIState);
    void SyncScreen(UIScreen*, int);
    void SendNetFocus(User*, UIComponent*);

    DataNode OnMsg(const UITransitionCompleteMsg&);
    DataNode OnMsg(const UIComponentFocusChangeMsg&);
    DataNode OnMsg(const UIComponentSelectMsg&);
    DataNode OnMsg(const UIComponentScrollMsg&);
    DataNode OnMsg(const LockStepStartMsg&);
    DataNode OnMsg(const LockStepCompleteMsg&);

    static void Init();
    static void Terminate();

    bool unk1c; // 0x1c
    UIScreen* mDestinationScreen; // 0x20
    int mDestinationDepth; // 0x24
    bool unk28; // 0x28
    bool unk29; // 0x29
    LockStepMgr* mUILockStep; // 0x2c
};

extern NetSync* TheNetSync;