#pragma once
#include "rndobj/TexRenderer.h"
#include "rndobj/Mat.h"
#include "rndobj/Dir.h"

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

    void SetPatch(RndDir*);

    static RndDir* sBlankPatch;
    static RndDir* sTestPatch;
    static void Init();
    static void InitResources();
    static void Terminate();
    static void Register(){
        REGISTER_OBJ_FACTORY(PatchRenderer);
    }
    NEW_OBJ(PatchRenderer);
    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<RndMat, ObjectDir> mBackMat; // 0x78
    ObjPtr<RndMat, ObjectDir> mOverlayMat; // 0x84
    RndEnviron* unk90; // 0x90
    Symbol mTestMode; // 0x94
    Symbol mPosition; // 0x98
};