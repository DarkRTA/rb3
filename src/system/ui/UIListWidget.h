#ifndef UI_UILISTWIDGET_H
#define UI_UILISTWIDGET_H
#include "obj/Object.h"
#include "ui/UIColor.h"
#include "math/Vec.h"
#include "obj/ObjPtr_p.h"
#include <vector>

class UIList;

enum UIListWidgetState {
    kUIListWidgetActive,
    kUIListWidgetHighlight,
    kUIListWidgetInactive,
    kNumUIListWidgetStates
};

enum UIListWidgetDrawType {
    kUIListWidgetDrawAlways,
    kUIListWidgetDrawOnlyFocused,
    kUIListWidgetDrawNever,
    kNumUIListWidgetDrawTypes
};

class UIListWidgetDrawState {
public:
    Vector3 mFirstPos;
    Vector3 mLastPos;
    Vector3 mHighlightPos;
    int mHighlightDisplay;
    UIListWidgetState mHighlightElementState;
    std::vector<int> mElements;
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
    // virtual void Draw(const UIListWidgetDrawState&, const UIListState&, const Transform&, UIComponent::State, Box*, DrawCommand){}
    // virtual void Fill(const UIListProvider&, int, int, int){}
    // virtual void StartScroll(int, bool){}
    // virtual void CompleteScroll(const UIListState&, int){}
    // virtual void Poll(){}

    float DrawOrder() const;
    float DisabledAlphaScale() const;
    UIListWidgetDrawType WidgetDrawType() const;
    UIList* ParentList();
    // void SetColor(UIListWidgetState, UIComponent::State, UIColor*);

    void SetParentList(UIList*);

    float mDrawOrder;
    float mDisabledAlphaScale;
    ObjPtr<UIColor, ObjectDir> mDefaultColor;
    std::vector<ObjPtr<UIColor, ObjectDir> > mColors;
    UIListWidgetDrawType mWidgetDrawType;
    UIList* mParentList;
};

#endif
