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
    virtual int SubList(int);
    virtual void Draw(const UIListWidgetDrawState&, const UIListState&, const Transform&, UIComponent::State, Box*, DrawCommand);
    virtual UIListSlotElement* CreateElement(UIList*);
    virtual RndTransformable* RootTrans();
    
    ObjPtr<UIList, ObjectDir> mList; // 0x5c
};

class UIListSubListElement : public UIListSlotElement {
public:
    UIListSubListElement(){}
    virtual ~UIListSubListElement(){}
    virtual void Fill(const UIListProvider&, int, int);
    virtual void Draw(const Transform&, float, UIColor*, Box*);
    virtual void Poll();
    virtual UIList* List();

    UIListSubList* mSlot;
    UIList* mList;
};

#endif
