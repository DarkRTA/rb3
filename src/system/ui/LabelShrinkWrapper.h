#ifndef UI_LABELSHRINKWRAPPER_H
#define UI_LABELSHRINKWRAPPER_H
#include "ui/UIComponent.h"
#include "obj/ObjPtr_p.h"

class UILabel;

class LabelShrinkWrapper : public UIComponent {
public:
    LabelShrinkWrapper();
    OBJ_CLASSNAME(LabelShrinkWrapper)
    OBJ_SET_TYPE(LabelShrinkWrapper)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~LabelShrinkWrapper();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Poll();
    virtual void Update();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(LabelShrinkWrapper)
    static void Init();

    static void Register(){ REGISTER_OBJ_FACTORY(LabelShrinkWrapper); }

    ObjPtr<UILabel, ObjectDir> mLabel; // 0x10c
    bool mShow; // 0x118
    int unk11c; // 0x11c
    int unk120; // 0x120
    int unk124; // 0x124
    int unk128; // 0x128
};

#endif
