#ifndef UI_UIGUIDE_H
#define UI_UIGUIDE_H
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "utl/MemMgr.h"

class UIGuide : public Hmx::Object {
public:
    UIGuide();
    virtual ~UIGuide();
    OBJ_CLASSNAME(UIGuide);
    OBJ_SET_TYPE(UIGuide);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD
    NEW_OBJ(UIGuide);
    static void Init(){
        REGISTER_OBJ_FACTORY(UIGuide);
    }

    int mType;
    float mPos;
};

#endif
