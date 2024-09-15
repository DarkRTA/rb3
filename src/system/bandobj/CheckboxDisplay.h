#pragma once
#include "ui/UIComponent.h"

class CheckboxDisplay : public UIComponent {
public:
    CheckboxDisplay();
    OBJ_CLASSNAME(CheckboxDisplay);
    OBJ_SET_TYPE(CheckboxDisplay);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~CheckboxDisplay();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void CopyMembers(const UIComponent*, CopyType);
    virtual void Update();

    void SetChecked(bool);

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(CheckboxDisplay);
    }
    NEW_OBJ(CheckboxDisplay);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    RndMesh* mCheckMesh; // 0x10c
    bool mChecked; // 0x110
};