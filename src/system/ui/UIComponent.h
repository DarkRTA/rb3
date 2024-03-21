#ifndef UI_UICOMPONENT_H
#define UI_UICOMPONENT_H

#include "obj/Dir.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Trans.h"

class UIComponent : public RndTransformable, public RndDrawable, public RndPollable {
    public:
    UIComponent();
    virtual ~UIComponent();
    OBJ_CLASSNAME(UIComponent)
    OBJ_SET_TYPE(UIComponent)
    virtual void SetTypeDef(DataArray *);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Poll();
    virtual void Exit();
    virtual void Highlight();
    ObjPtr<UIComponent, ObjectDir> mNavRight;
    ObjPtr<UIComponent, ObjectDir> mNavDown;
};

#endif // UI_UICOMPONENT_H
