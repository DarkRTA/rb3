#pragma once
#include "ui/UIListSlot.h"
#include "ui/UIList.h"

/** "Custom slot for use with UIList" */
class UIListSubList : public UIListSlot {
public:
    UIListSubList();
    virtual ~UIListSubList() {}
    OBJ_CLASSNAME(UIListSubList)
    OBJ_SET_TYPE(UIListSubList)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual void Load(BinStream &);
    virtual UIList *SubList(int);
    virtual void Draw(
        const UIListWidgetDrawState &,
        const UIListState &,
        const Transform &,
        UIComponent::State,
        Box *,
        DrawCommand
    );
    virtual UIListSlotElement *CreateElement(UIList *);
    virtual RndTransformable *RootTrans();

    DECLARE_REVS;
    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(UIListSubList)
    static void Init() { REGISTER_OBJ_FACTORY(UIListSubList) }

    static int sNextFillSelection;

    /** "sub list template" */
    ObjPtr<UIList> mList; // 0x5c
};

class UIListSubListElement : public UIListSlotElement {
public:
    UIListSubListElement(UIListSubList *sl, UIList *l) : mSlot(sl), mList(l) {}
    virtual ~UIListSubListElement() { delete mList; }
    virtual void Fill(const UIListProvider &, int, int);
    virtual void Draw(const Transform &, float, UIColor *, Box *);
    virtual void Poll() { mList->Poll(); }
    virtual UIList *List() { return mList; }

    UIListSubList *mSlot;
    UIList *mList;
};
