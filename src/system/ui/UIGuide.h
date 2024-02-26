#ifndef UI_UIGUIDE_H
#define UI_UIGUIDE_H
#include "obj/Object.h"

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

    int mType;
    float mPos;
};

#endif
