#pragma once
#include "rndobj/Draw.h"
#include "obj/Object.h"
#include "utl/FilePath.h"

class RndTex;
class RndMat;

/** "Object to draw a screensot in Milo, to help with positioning.
 *  The screenshot will not be drawn or even loaded in-game." */
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
    NEW_OBJ(Screenshot);
    static void Init(){
        REGISTER_OBJ_FACTORY(Screenshot);
    }

    void Sync();

    DECLARE_REVS

    /** "File containing the screenshot to display.  This file will only be loaded in Milo, not in game." */
    FilePath mTexPath; // 0x20
    RndTex* mTex; // 0x2c
    RndMat* mMat; // 0x30
};
