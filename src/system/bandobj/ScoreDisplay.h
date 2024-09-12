#pragma once
#include "ui/UIComponent.h"
#include "ui/UIListCustom.h"
#include "ui/UIColor.h"
#include "bandobj/BandLabel.h"

class ScoreDisplay : public UIComponent, public UIListCustomTemplate {
public:
    ScoreDisplay();
    OBJ_CLASSNAME(ScoreDisplay);
    OBJ_SET_TYPE(ScoreDisplay);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~ScoreDisplay();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void CopyMembers(const UIComponent*, CopyType);
    virtual void Update();
    virtual void SetAlphaColor(float, UIColor*);
    virtual void GrowBoundingBox(Box&) const;
    virtual void UpdateDisplay();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    BandLabel* unk110; // 0x110
    short unk114; // 0x114
    int unk118; // 0x118
    int unk11c; // 0x11c
    bool unk120; // 0x120
    ObjPtr<UIColor, ObjectDir> unk124; // 0x124
};