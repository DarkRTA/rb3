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
    virtual void SetFrame(float, float){}
    virtual void Poll();
    virtual void Enter();

    void SyncScores();

    ObjPtr<RndAnimatable, ObjectDir> mNeedleAnim; // 0x18c
    ObjPtr<RndAnimatable, ObjectDir> mLogoGlowAnim; // 0x198
    ObjPtr<RndMesh, ObjectDir> mGlowMesh1; // 0x1a4
    ObjPtr<RndMesh, ObjectDir> mGlowMesh2; // 0x1b0
    ObjPtr<RndAnimatable, ObjectDir> mPeggedAnim1; // 0x1bc
    ObjPtr<RndAnimatable, ObjectDir> mPeggedAnim2; // 0x1c8
    ObjPtr<RndMesh, ObjectDir> mLensMesh; // 0x1d4
    ObjPtr<RndMat, ObjectDir> mLensMatNeutral; // 0x1e0
    ObjPtr<RndMat, ObjectDir> mLensMat1; // 0x1ec
    ObjPtr<RndMat, ObjectDir> mLensMat2; // 0x1f8
    int unk204; // 0x204
    int mScoreDiff; // 0x208
};