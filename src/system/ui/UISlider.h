#ifndef UI_UISLIDER_H
#define UI_UISLIDER_H
#include "ui/UIComponent.h"
#include "ui/ScrollSelect.h"
#include "os/JoypadMsgs.h"

class UISlider : public UIComponent, public ScrollSelect {
public:
    UISlider();
    OBJ_CLASSNAME(UISlider)
    OBJ_SET_TYPE(UISlider)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual ~UISlider(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Update();
    virtual void SetCurrent(int);
    virtual int SelectedAux() const;
    virtual void SetSelectedAux(int);

    DataNode OnMsg(const ButtonDownMsg&);

    void SyncSlider();
    float Frame() const;
    void SetNumSteps(int);
    void SetFrame(float);

#ifdef VERSION_SZBE69_B8
    int Current() const;
#else
    int Current() const { return mCurrent; }
#endif

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(UISlider);
    }
    NEW_OBJ(UISlider);

    DECLARE_REVS;
    DELETE_OVERLOAD;

    int mCurrent; // 0x118
    int mNumSteps; // 0x11c
    bool mVertical; // 0x120
};

#endif // UI_UISLIDER_H
