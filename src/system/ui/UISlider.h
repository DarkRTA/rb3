#ifndef UI_UISLIDER_H
#define UI_UISLIDER_H
#include "ui/UIComponent.h"
#include "ui/ScrollSelect.h"

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

    static void Init();
    NEW_OBJ(UISlider);

    DECLARE_REVS;
    DELETE_OVERLOAD;

    int unk118; // 0x118
    int unk11c; // 0x11c
    bool unk120; // 0x120
};

#endif // UI_UISLIDER_H
