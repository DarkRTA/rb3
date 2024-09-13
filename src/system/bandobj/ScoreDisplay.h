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

    DataNode OnSetValues(const DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    BandLabel* unk110; // 0x110
    short unk114; // 0x114
    int mScore; // 0x118
    int mRank; // 0x11c
    bool mGlobally; // 0x120
    ObjPtr<UIColor, ObjectDir> mTextColor; // 0x124
};