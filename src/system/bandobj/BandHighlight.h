#pragma once
#include "bandobj/BandLabel.h"
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
    void UpdateTargetEdge(RndTransformable*);
    void SyncDir();
    void SetTarget(UIComponent*, bool);

    DataNode OnMsg(const UIComponentFocusChangeMsg&);

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(BandHighlight);
    }
    NEW_OBJ(BandHighlight);
    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    Vector3 unk10c; // 0x10c
    Vector3 unk118; // 0x118
    float unk124;
    float mAnimDuration; // 0x128
    BandLabel* mHelpTextLabel; // 0x12c
    Vector3 unk130; // 0x130
    Vector3 unk13c; // 0x13c
    RndTransformable* unk148; // 0x148
    std::vector<RndMat*> mMirrorMats; // 0x14c
    UIComponent* unk154; // 0x154
    int unk158; // 0x158
};