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

    void operator delete(void* v){
        _MemFree(v);
    }

    void Sync();

    static unsigned short gRev;
    static unsigned short gAltRev;

    FilePath mTexPath;
    RndTex* mTex;
    RndMat* mMat;
};

#endif
