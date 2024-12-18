#pragma once
#include "ui/UIListWidget.h"
#include "obj/ObjPtr_p.h"

/**
 * @brief Highlighter object for UILists.
 * Original _objects description:
 * "Highlight widget for use with UIList"
 */
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
    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(UIListHighlight)
    static void Init(){
        REGISTER_OBJ_FACTORY(UIListHighlight)
    }

    /** "arrow mesh to draw/transform" */
    ObjPtr<RndMesh, ObjectDir> mMesh; // 0x40
};
