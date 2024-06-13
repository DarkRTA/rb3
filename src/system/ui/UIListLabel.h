#ifndef UI_UILISTLABEL_H
#define UI_UILISTLABEL_H
#include "ui/UIListSlot.h"
#include "ui/UILabel.h"
#include "obj/ObjPtr_p.h"

class UIListLabelElement;

class UIListLabel : public UIListSlot {
public:
    UIListLabel();
    virtual ~UIListLabel();
    OBJ_CLASSNAME(UIListLabel)
    OBJ_SET_TYPE(UIListLabel)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void ResourceCopy(const UIListWidget*);
    virtual void CreateElements(UIList*, int);
    virtual void Draw(const UIListWidgetDrawState&, const UIListState&, const Transform&, UIComponent::State, Box*, DrawCommand);
    virtual void Fill(const class UIListProvider&, int, int, int);
    virtual void StartScroll(int, bool);
    virtual void CompleteScroll(const UIListState&, int);
    virtual void Poll();    
    virtual UIListSlotElement* CreateElement(UIList*);
    virtual RndTransformable* RootTrans();

    const char* GetDefaultText() const;

    ObjPtr<UILabel, ObjectDir> mLabel; // 0x5c
};

class UIListLabelElement : public UIListSlotElement {
public:
    UIListLabelElement(UIListLabel* ll, UILabel* l) : mListLabel(ll), mLabel(l) {}
    virtual ~UIListLabelElement(){}
    virtual void Fill(const UIListProvider&, int, int);
    virtual void Draw(const Transform&, float, UIColor*, Box*);

    // two word params
    UIListLabel* mListLabel;
    UILabel* mLabel;
};

#endif
