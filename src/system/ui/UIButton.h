#pragma once
#include "obj/Object.h"
#include "ui/UILabel.h"
#include "os/JoypadMsgs.h"

/**
 * @brief A base implementation of a button.
 * Original _objects description:
 * "Simple button, basically just a
 * label that can be selected"
 */
class UIButton : public UILabel {
public:
    UIButton();
    OBJ_CLASSNAME(UIButton);
    OBJ_SET_TYPE(UIButton);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~UIButton() {}
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual bool CanHaveFocus() { return true; }

    DataNode OnMsg(const ButtonDownMsg &);

    NEW_OVERLOAD
    DELETE_OVERLOAD
    DECLARE_REVS
    static void Register() { REGISTER_OBJ_FACTORY(UIButton); }
    static void Init();
    static Hmx::Object *NewObject();
};
