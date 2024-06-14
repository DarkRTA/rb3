#ifndef UI_UILISTHIGHLIGHT_H
#define UI_UILISTHIGHLIGHT_H
#include "ui/UIListWidget.h"
#include "obj/ObjPtr_p.h"

class UIListHighlight : public UIListWidget {
public:
    UIListHighlight();
    virtual ~UIListHighlight(){}
    OBJ_CLASSNAME(UIListHighlight);
    OBJ_SET_TYPE(UIListHighlight);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Draw(const UIListWidgetDrawState&, const UIListState&, const Transform&, UIComponent::State, Box*, DrawCommand);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<RndMesh, ObjectDir> mMesh; // 0x40
};

#endif
