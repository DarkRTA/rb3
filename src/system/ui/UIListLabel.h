#ifndef UI_UILISTLABEL_H
#define UI_UILISTLABEL_H
#include "ui/UIListSlot.h"
#include "ui/UILabel.h"
#include "obj/ObjPtr_p.h"

class UIListLabelElement;

class UIListLabel : public UIListSlot {
public:
    UIListLabel();
    virtual ~UIListLabel(){}
    OBJ_CLASSNAME(UIListLabel)
    OBJ_SET_TYPE(UIListLabel)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);   
    virtual UIListSlotElement* CreateElement(UIList*);
    virtual RndTransformable* RootTrans();

    const char* GetDefaultText() const;
    UILabel* ElementLabel(int) const;

    DECLARE_REVS
    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(UIListLabel)
    static void Init(){
        REGISTER_OBJ_FACTORY(UIListLabel)
    }

    ObjPtr<UILabel, ObjectDir> mLabel; // 0x5c
};

class UIListLabelElement : public UIListSlotElement {
public:
    UIListLabelElement(UIListLabel* ll, UILabel* l) : mListLabel(ll), mLabel(l) {}
    virtual ~UIListLabelElement(){ delete mLabel; }
    virtual void Fill(const UIListProvider& prov, int i, int j){
        prov.Text(i, j, mListLabel, mLabel);
    }
    virtual void Draw(const Transform&, float, UIColor*, Box*);

    UIListLabel* mListLabel;
    UILabel* mLabel;
};

#endif
