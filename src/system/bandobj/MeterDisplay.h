#pragma once
#include "ui/UIComponent.h"

class MeterDisplay : public UIComponent {
public:
    MeterDisplay();
    OBJ_CLASSNAME(MeterDisplay);
    OBJ_SET_TYPE(MeterDisplay);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~MeterDisplay();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Poll();
    virtual void Update();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int unk10c; // 0x10c
    float unk110; // 0x110
    float unk114; // 0x114
    int unk118; // 0x118
    int unk11c; // 0x11c
    bool unk120; // 0x120
    bool unk121; // 0x121
    bool unk122; // 0x122
    Symbol unk124; // 0x124
    int unk128; // 0x128
    int unk12c; // 0x12c
};