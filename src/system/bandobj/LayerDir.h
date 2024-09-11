#pragma once
#include "rndobj/Dir.h"

class LayerDir : public RndDir {
public:
    LayerDir();
    OBJ_CLASSNAME(LayerDir);
    OBJ_SET_TYPE(LayerDir);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~LayerDir(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void DrawShowing();
    virtual RndCam* CamOverride();

    ObjList<int> unk18c; // 0x18c
    bool unk198; // 0x198
};