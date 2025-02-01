#pragma once
#include "ui/UIComponent.h"
#include "ui/ScrollSelect.h"
#include "os/JoypadMsgs.h"

/** "A component with animatable whose frames correspond to a
 *  range of values. The resources don't have to look like a slider;
 *  they could easily be a knob, dial, etc." */
class UISlider : public UIComponent, public ScrollSelect {
public:
    UISlider();
    OBJ_CLASSNAME(UISlider)
    OBJ_SET_TYPE(UISlider)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void DrawShowing();
    virtual RndDrawable *CollideShowing(const Segment &, float &, Plane &);
    virtual int CollidePlane(const Plane &);
    virtual ~UISlider() {}
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual void Enter();
    virtual void Update();
    virtual void SetCurrent(int);
    virtual int SelectedAux() const;
    virtual void SetSelectedAux(int);

    DataNode OnMsg(const ButtonDownMsg &);

    void SyncSlider();
    float Frame() const;
    void SetNumSteps(int);
    void SetFrame(float);
    int Current() const;

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS;

    static void Init();
    static void Register() { REGISTER_OBJ_FACTORY(UISlider); }
    NEW_OBJ(UISlider);

    int mCurrent; // 0x118
    int mNumSteps; // 0x11c
    bool mVertical; // 0x120
};
