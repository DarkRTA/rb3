#pragma once
#include "ui/UIComponent.h"

class ReviewDisplay : public UIComponent {
public:
    ReviewDisplay();
    OBJ_CLASSNAME(ReviewDisplay);
    OBJ_SET_TYPE(ReviewDisplay);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~ReviewDisplay();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void CopyMembers(const UIComponent*, CopyType);
    virtual void Update();
    virtual void UpdateDisplay();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int unk10c; // 0x10c
    int unk110; // 0x110
    int unk114; // 0x114
};