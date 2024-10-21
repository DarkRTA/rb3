#pragma once
#include "meta_band/UIEvent.h"
#include "obj/Data.h"
#include "obj/MsgSource.h"
#include <vector>

class UIEventQueue {
public:
    UIEventQueue();
    ~UIEventQueue();
    void Poll();
    void DismissEvent();
    void CheckActivateEvent();
    void TriggerEvent(UIEvent*);
    UIEvent* CurrentEvent() const;
    bool HasEvent(Symbol) const;

    std::vector<UIEvent*> mEventQueue; // 0x0
};

class UIEventMgr : public MsgSource {
public:
    UIEventMgr(){}
    virtual DataNode Handle(DataArray*, bool);
    virtual ~UIEventMgr();

    void Poll();
    void DismissDialogEvent();
    void DismissTransitionEvent();
    void TriggerEvent(Symbol, DataArray*);
    void TriggerEvent(UIEvent*);
    bool HasActiveEvent() const;
    bool HasActiveDialogEvent() const;
    bool HasActiveTransitionEvent() const;
    bool HasActiveDestructiveEvent() const;
    bool HasTransitionEvent(Symbol) const;
    bool HasDialogEvent(Symbol) const;
    Symbol CurrentDialogEvent() const;
    Symbol CurrentTransitionEvent() const;
    bool IsTransitionEventFinished() const;

    DataNode OnTriggerEvent(DataArray*);

    static void Init();
    static void Terminate();

    UIEventQueue mTransitionEventQueue; // 0x1c
    UIEventQueue mDialogEventQueue; // 0x24
};

extern UIEventMgr* TheUIEventMgr;