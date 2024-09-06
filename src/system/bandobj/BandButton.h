#pragma once
#include "ui/UIButton.h"

class BandButton : public UIButton {
public:
    BandButton();
    OBJ_CLASSNAME(BandButton);
    OBJ_SET_TYPE(BandButton);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~BandButton();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SetState(UIComponent::State);
    virtual void Update();

    static void LoadOldBandTextComp(BinStream&);

    DECLARE_REVS;
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(BandButton)
    }
    NEW_OBJ(BandButton)
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    RndAnimatable* mFocusAnim; // 0x1bc - RndAnimatable*
    RndAnimatable* mPulseAnim; // 0x1c0 - RndAnimatable*
    Task* mAnimTask; // 0x1c4 - Task*
    float mStartTime; // 0x1c8
};