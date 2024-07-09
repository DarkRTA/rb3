#ifndef UI_SCREENSHOT_H
#define UI_SCREENSHOT_H
#include "rndobj/Draw.h"
#include "obj/Object.h"
#include "utl/FilePath.h"

class RndTex;
class RndMat;

class Screenshot : public RndDrawable {
public:
    Screenshot();
    OBJ_CLASSNAME(Screenshot);
    OBJ_SET_TYPE(Screenshot);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~Screenshot();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    void Sync();

    DECLARE_REVS

    FilePath mTexPath; // 0x20
    RndTex* mTex; // 0x2c
    RndMat* mMat; // 0x30
};

#endif
