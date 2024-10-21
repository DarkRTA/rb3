#pragma once
#include "obj/Data.h"

class UIEvent {
public:
    UIEvent(DataArray*, DataArray*);
    virtual ~UIEvent();
    virtual Symbol Type() const;
    virtual bool IsDialogEvent() const = 0;
    virtual bool IsTransitionEvent() const = 0;
    virtual bool IsDestructiveEvent() const = 0;
    virtual bool AllowsOverride() const = 0;
    virtual void Poll(){}
    virtual void OnActivate(){}
    virtual void OnDismiss(){}

    void Activate();
    void Dismiss();

    DataArray* mEventDef; // 0x4
    DataArrayPtr mEventInit; // 0x8
    bool mActive; // 0xc
};

class DialogEvent : public UIEvent {
public:
    DialogEvent(DataArray*, DataArray*);
    virtual ~DialogEvent(){}
    virtual bool IsDialogEvent() const { return true; }
    virtual bool IsTransitionEvent() const { return false; }
    virtual bool IsDestructiveEvent() const { return false; }
    virtual bool AllowsOverride() const;
    virtual void OnActivate();
    virtual void OnDismiss();
};