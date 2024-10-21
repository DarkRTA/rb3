#pragma once
#include "NetSync.h"
#include "obj/Data.h"
#include "ui/UIScreen.h"

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

class TransitionEvent : public UIEvent {
public:
    TransitionEvent(DataArray*, DataArray*);
    virtual ~TransitionEvent(){}
    virtual bool IsDialogEvent() const { return false; }
    virtual bool IsTransitionEvent() const { return true; }
    virtual bool IsDestructiveEvent() const = 0;
    virtual bool AllowsOverride() const { return false; }
    virtual bool IsDestination(const std::vector<UIScreen*>&) const = 0;
    virtual bool IsTransitionAllowed(UIScreen*) const = 0;
};

class DestructiveTransitionEvent : public TransitionEvent {
public:
    DestructiveTransitionEvent(NetSync*, DataArray*, DataArray*);
    virtual ~DestructiveTransitionEvent(){}
    virtual bool IsDestructiveEvent() const { return true; }
    virtual void OnActivate();
    virtual bool IsDestination(const std::vector<UIScreen*>&) const;
    virtual bool IsTransitionAllowed(UIScreen*) const;

    void SetTransitionAndDestination();

    UIScreen* mTransitionScreen; // 0x10
    UIScreen* mDestinationScreen; // 0x14
    NetSync* mNetSync; // 0x18
};

class NonDestructiveTransitionEvent : public TransitionEvent {
public:
    NonDestructiveTransitionEvent(NetSync*, const std::vector<UIScreen*>&);
    virtual ~NonDestructiveTransitionEvent(){}
    virtual Symbol Type() const;
    virtual bool IsDestructiveEvent() const { return false; }
    virtual void Poll();
    virtual void OnActivate();
    virtual bool IsDestination(const std::vector<UIScreen*>&) const;
    virtual bool IsTransitionAllowed(UIScreen*) const;

    void AttemptNextTransition();

    std::vector<UIScreen*> mDestState; // 0x10
    NetSync* mNetSync; // 0x18
};