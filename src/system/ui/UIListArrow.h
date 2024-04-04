#ifndef UI_UILISTARROW_H
#define UI_UILISTARROW_H
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
    virtual ~UIListArrow();
    OBJ_CLASSNAME(UIListArrow);
    OBJ_SET_TYPE(UIListArrow);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    // Draw
    // StartScroll

    ObjPtr<RndMesh, ObjectDir> mMesh;
    ObjPtr<RndAnimatable, ObjectDir> mScrollAnim;
    UIListArrowPosition mPosition;
    bool mShowOnlyScroll;
    bool mOnHighlight;
};


#endif
