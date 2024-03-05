#ifndef UI_UILISTWIDGET_H
#define UI_UILISTWIDGET_H
#include "obj/Object.h"
#include "math/Color.h"
#include "obj/ObjPtr_p.h"
#include <vector>

class UIList;

enum UIListWidgetDrawType {
    kUIListWidgetDrawAlways,
    kUIListWidgetDrawOnlyFocused,
    kUIListWidgetDrawNever,
    kNumUIListWidgetDrawTypes
};

class UIListWidget : public Hmx::Object {
public:
    UIListWidget();
    virtual ~UIListWidget();
    OBJ_CLASSNAME(UIListWidget);
    OBJ_SET_TYPE(UIListWidget);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual int SubList(int){ return 0; }
    virtual void ResourceCopy(const UIListWidget*);
    virtual void CreateElements(UIList*, int){}
    // there's a few more

    float mDrawOrder;
    ObjPtr<Hmx::Color, ObjectDir> mDefaultColor;
    std::vector<ObjPtr<Hmx::Color, ObjectDir> > mColors;
    UIListWidgetDrawType mWidgetDrawType;
    UIList* mParentList;
};

#endif
