#ifndef UI_UILISTWIDGET_H
#define UI_UILISTWIDGET_H
#include "obj/Object.h"
#include "ui/UIColor.h"
#include "math/Vec.h"
#include "ui/UIComponent.h"
#include "ui/UIListState.h"
#include "ui/UIListElementDrawState.h"
#include "ui/UIEnums.h"
#include "obj/ObjPtr_p.h"
#include "utl/MemMgr.h"
#include <vector>

class UIList;

class UIListWidgetDrawState {
public:
    Vector3 mFirstPos; // 0x0
    Vector3 mLastPos; // 0xc
    Vector3 mHighlightPos; // 0x18
    int mHighlightDisplay; // 0x24
    UIListWidgetState mHighlightElementState; // 0x28
    std::vector<UIListElementDrawState> mElements; // 0x2c
};

class UIListWidget : public Hmx::Object {
public:
    UIListWidget();
    virtual ~UIListWidget(){}
    OBJ_CLASSNAME(UIListWidget);
    OBJ_SET_TYPE(UIListWidget);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual UIList* SubList(int){ return 0; }
    virtual void ResourceCopy(const UIListWidget*);
    virtual void CreateElements(UIList*, int){}
    virtual void Draw(const UIListWidgetDrawState&, const UIListState&, const Transform&, UIComponent::State, Box*, DrawCommand){}
    virtual void Fill(const class UIListProvider&, int, int, int){}
    virtual void StartScroll(int, bool){}
    virtual void CompleteScroll(const UIListState&, int){}
    virtual void Poll(){}

    float DrawOrder() const;
    float DisabledAlphaScale() const;
    UIListWidgetDrawType WidgetDrawType() const;
    UIList* ParentList();
    void DrawMesh(RndMesh*, UIListWidgetState, UIComponent::State, const Transform&, Box*);
    UIColor* DisplayColor(UIListWidgetState, UIComponent::State) const;
    void SetColor(UIListWidgetState, UIComponent::State, UIColor*);
    void SetParentList(UIList*);
    void CalcXfm(const Transform&, const Vector3&, Transform&);

    DECLARE_REVS
    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(UIListWidget)
    static void Init(){
        REGISTER_OBJ_FACTORY(UIListWidget)
    }

    float mDrawOrder; // 0x1c
    float mDisabledAlphaScale; // 0x20
    ObjPtr<UIColor, class ObjectDir> mDefaultColor; // 0x24
    std::vector< std::vector<ObjPtr<UIColor, class ObjectDir> > > mColors; // 0x30 - a vector of vectors of ObjPtrs...wonderful
    UIListWidgetDrawType mWidgetDrawType; // 0x38
    UIList* mParentList; // 0x3c
};

#endif
