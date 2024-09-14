#pragma once
#include "ui/UIComponent.h"
#include "ui/UIMessages.h"

class BandHighlight : public UIComponent {
public:
    BandHighlight();
    OBJ_CLASSNAME(BandHighlight);
    OBJ_SET_TYPE(BandHighlight);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual ~BandHighlight();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void Update();

    void OnRegisterFocus();
    void OnUnregisterFocus();

    DataNode OnMsg(const UIComponentFocusChangeMsg&);

    char filler[0x3c]; // 0x10c
    int unk148; // 0x148
    std::vector<int> unk14c; // 0x14c
    int unk154; // 0x154
    int unk158; // 0x158
};