#ifndef UI_UILISTARROW_H
#define UI_UILISTARROW_H
#include "obj/Object.h"
#include "ui/UIColor.h"
#include "ui/UIListWidget.h"
#include "obj/ObjPtr_p.h"

class RndMesh;
class RndAnimatable;

enum UIListArrowPosition {
    kUIListArrowBack,
    kUIListArrowNext
};

class UIListArrow : public UIListWidget {
public:
    UIListArrow();
    virtual ~UIListArrow(){}
    OBJ_CLASSNAME(UIListArrow);
    OBJ_SET_TYPE(UIListArrow);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Draw(const UIListWidgetDrawState&, const UIListState&, const Transform&, UIComponent::State, Box*, DrawCommand);
    void StartScroll(int, bool);

    ObjPtr<RndMesh, class ObjectDir> mMesh; // 0x40
    ObjPtr<RndAnimatable, class ObjectDir> mScrollAnim; // 0x4c
    UIListArrowPosition mPosition; // 0x58
    bool mShowOnlyScroll; // 0x5c
    bool mOnHighlight; // 0x5d

    DECLARE_REVS
    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(UIListArrow)
    static void Init(){
        REGISTER_OBJ_FACTORY(UIListArrow)
    }
};


#endif
