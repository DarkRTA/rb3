#pragma once
#include "rndobj/TexRenderer.h"
#include "rndobj/Mat.h"

class PatchRenderer : public RndTexRenderer {
public:
    PatchRenderer();
    OBJ_CLASSNAME(PatchRenderer);
    OBJ_SET_TYPE(PatchRenderer);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~PatchRenderer(){}
    virtual void DrawBefore();
    virtual void DrawAfter();

    ObjPtr<RndMat, ObjectDir> unk78; // 0x78
    ObjPtr<RndMat, ObjectDir> unk84; // 0x84
    int unk90; // 0x90
    Symbol unk94; // 0x94
    Symbol unk98; // 0x98
};