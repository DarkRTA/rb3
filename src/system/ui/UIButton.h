#ifndef UI_UIBUTTON_H
#define UI_UIBUTTON_H

#include "obj/Object.h"
#include "ui/UILabel.h"
#include "os/JoypadMsgs.h"

class UIButton : public UILabel {
    UIButton();
    virtual ~UIButton() {}
    OBJ_CLASSNAME(UIButton);
    OBJ_SET_TYPE(UIButton);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    DataNode OnMsg(const ButtonDownMsg&);

    NEW_OVERLOAD
    DELETE_OVERLOAD

    static void Init();
    static Hmx::Object* NewObject();

    DECLARE_REVS
};

#endif // UI_UIBUTTON_H
