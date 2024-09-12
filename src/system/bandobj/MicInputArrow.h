#pragma once
#include "ui/UIComponent.h"

class MicInputArrow : public UIComponent {
public:
    MicInputArrow();
    OBJ_CLASSNAME(MicInputArrow);
    OBJ_SET_TYPE(MicInputArrow);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~MicInputArrow(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Update();

    int unk10c; // 0x10c
    int unk110; // 0x110
    std::vector<char> unk114; // 0x114
    std::vector<bool> unk11c; // 0x11c
    std::vector<int> unk124; // 0x124
    std::vector<int> unk12c; // 0x12c
    std::vector<int> unk134; // 0x134
    std::vector<int> unk13c; // 0x13c
    std::vector<int> unk144; // 0x144
    std::vector<int> unk14c; // 0x14c
    std::vector<int> unk154; // 0x154
    float unk15c; // 0x15c
    bool unk160; // 0x160
    float unk164[3]; // 0x164
};