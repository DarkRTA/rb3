#ifndef UI_UILISTSUBLIST_H
#define UI_UILISTSUBLIST_H
#include "ui/UIListSlot.h"
#include "ui/UIList.h"

class UIListSubList : public UIListSlot {
public:
    UIListSubList();
    virtual ~UIListSubList(){}
    OBJ_CLASSNAME(UIListSubList)
    OBJ_SET_TYPE(UIListSubList)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual UIList* SubList(int);
    virtual void Draw(const UIListWidgetDrawState&, const UIListState&, const Transform&, UIComponent::State, Box*, DrawCommand);
    virtual UIListSlotElement* CreateElement(UIList*);
    virtual RndTransformable* RootTrans();

    DECLARE_REVS;

    static int sNextFillSelection;
    
    ObjPtr<UIList, ObjectDir> mList; // 0x5c
};

class UIListSubListElement : public UIListSlotElement {
public:
    UIListSubListElement(UIListSubList* sl, UIList* l) : mSlot(sl), mList(l) {}
    virtual ~UIListSubListElement(){ delete mList; }
    virtual void Fill(const UIListProvider&, int, int);
    virtual void Draw(const Transform&, float, UIColor*, Box*);
    virtual void Poll(){ mList->Poll(); }
    virtual UIList* List(){ return mList; }

    UIListSubList* mSlot;
    UIList* mList;
};

#endif
