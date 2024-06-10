#ifndef UI_UILISTSLOT_H
#define UI_UILISTSLOT_H

#include "UIListWidget.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "utl/MemMgr.h"
#include "utl/Str.h"
#include <vector>

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
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    OBJ_CLASSNAME(UIListSlot)
    OBJ_SET_TYPE(UIListSlot)
    virtual ~UIListSlot();
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);

    std::vector<int> unk_0x40;
    int unk_0x48, unk_0x4C;
    String unk_0x50;

    DECLARE_REVS
    DELETE_OVERLOAD

    NEW_OBJ(UIListSlot)
};

#endif // UI_UILISTSLOT_H
