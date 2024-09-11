#pragma once
#include "bandobj/BandList.h"
#include "ui/UIComponent.h"

class ScrollbarDisplay : public UIComponent {
public:
    ScrollbarDisplay();
    OBJ_CLASSNAME(ScrollbarDisplay);
    OBJ_SET_TYPE(ScrollbarDisplay);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~ScrollbarDisplay();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void CopyMembers(const UIComponent*, CopyType);
    virtual void Update();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<BandList, ObjectDir> unk10c; // 0x10c
    float unk118; // 0x118
    bool unk11c; // 0x11c
    float unk120; // 0x120
    float unk124; // 0x124
    float unk128; // 0x128
    int unk12c; // 0x12c
    int unk130; // 0x130
    int unk134; // 0x134
    int unk138; // 0x138
    int unk13c; // 0x13c
    int unk140; // 0x140
    int unk144; // 0x144
    int unk148; // 0x148
    int unk14c; // 0x14c
    float unk150; // 0x150
    float unk154; // 0x154
};