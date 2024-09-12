#pragma once
#include "rndobj/Dir.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"

class BandLeadMeter : public RndDir {
public:
    BandLeadMeter();
    OBJ_CLASSNAME(BandLeadMeter);
    OBJ_SET_TYPE(BandLeadMeter);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~BandLeadMeter(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SetFrame(float, float);
    virtual void Poll();
    virtual void Enter();

    void SyncScores();

    ObjPtr<RndAnimatable, ObjectDir> unk18c; // 0x18c
    ObjPtr<RndAnimatable, ObjectDir> unk198; // 0x198
    ObjPtr<RndMesh, ObjectDir> unk1a4; // 0x1a4
    ObjPtr<RndMesh, ObjectDir> unk1b0; // 0x1b0
    ObjPtr<RndAnimatable, ObjectDir> unk1bc; // 0x1bc
    ObjPtr<RndAnimatable, ObjectDir> unk1c8; // 0x1c8
    ObjPtr<RndMesh, ObjectDir> unk1d4; // 0x1d4
    ObjPtr<RndMat, ObjectDir> unk1e0; // 0x1e0
    ObjPtr<RndMat, ObjectDir> unk1ec; // 0x1ec
    ObjPtr<RndMat, ObjectDir> unk1f8; // 0x1f8
    int unk204; // 0x204
    int unk208; // 0x208
};