#ifndef UI_UILISTSLOT_H
#define UI_UILISTSLOT_H
#include "UIListWidget.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "utl/MemMgr.h"
#include "utl/Str.h"
#include <vector>

enum UIListSlotDrawType {
    kUIListSlotDrawAlways,
    kUIListSlotDrawHighlight,
    kUIListSlotDrawNoHighlight
};

class UIListSlotElement {
public:
    UIListSlotElement() {}
    virtual ~UIListSlotElement() {}
    virtual void Fill(const UIListProvider&, int, int) = 0;
    virtual void Draw(const Transform&, float, UIColor*, Box*) = 0;
    virtual void Poll() {}
};

class UIListSlot : public UIListWidget {
public:
    UIListSlot();
    virtual ~UIListSlot();
    OBJ_CLASSNAME(UIListSlot)
    OBJ_SET_TYPE(UIListSlot)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void ResourceCopy(const UIListWidget*);
    virtual void CreateElements(UIList*, int);
    virtual void Draw(const UIListWidgetDrawState&, const UIListState&, const Transform&, UIComponent::State, Box*, DrawCommand);
    virtual void Fill(const class UIListProvider&, int, int, int);
    virtual void StartScroll(int, bool);
    virtual void CompleteScroll(const UIListState&, int);
    virtual void Poll();
    virtual UIListSlotElement* CreateElement(UIList*){ return 0; }
    virtual RndTransformable* RootTrans(){ return 0; }

    void ClearElements();
    bool Matches(const char*) const;
    const char* MatchName() const;

    std::vector<UIListSlotElement*> mElements; // 0x40
    UIListSlotDrawType mSlotDrawType; // 0x48
    UIListSlotElement* mNextElement; // 0x4c
    String mMatchName; // 0x50

    DECLARE_REVS
    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(UIListSlot)
    static void Init(){
        REGISTER_OBJ_FACTORY(UIListSlot)
    }
};

#endif // UI_UILISTSLOT_H
