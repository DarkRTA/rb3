#ifndef BANDOBJ_NOTETUBE_H
#define BANDOBJ_NOTETUBE_H
#include "rndobj/Group.h"
#include "rndobj/Mesh.h"
#include "obj/Object.h"
#include <vector>

class TubePlate {
public:
    TubePlate(int);
    ~TubePlate();
    void Bake();
    void Reset();
    void SetDeployTiming(float, float);
    void SetShowing(bool);
    float CurrentStartX(float) const;
    float CurrentEndX(float) const;
    String GetMatName();
    void AllocateVerts(int, bool);
    void SetParent(RndGroup* grp){ mParent = grp; }
    void SetBeginX(float x){ mBeginX = x; }
    void SetWidthX(float x){ mWidthX = x; }

    RndMesh* mMesh; // 0x0
    RndGroup* mParent; // 0x4
    int mAllocationCount; // 0x8
    float mBeginX; // 0xc
    float mWidthX; // 0x10
    bool mBaked; // 0x14
    float mActiveMs; // 0x18 
    float mInvalidateMs; // 0x1c 
    float mMatSize; // 0x20
    bool mDeploy; // 0x24
    int unk28; // 0x28
};

class NoteTube : public Hmx::Object {
public:
    NoteTube();
    virtual ~NoteTube(){}

    void SetNumPoints(int);
    void SetPointPos(int, Vector3);
    void SetGlowLevel(int);
    int NumGlowLevels() const { return 4; }
    void BakePlates();
    void CreateMeshes();
    void SetDeployTiming(float, float);
    void SetMeshVert(RndMesh::Vert&, float, float, float, float);
    void InitializePlate(TubePlate*, RndMat*, RndGroup*);
    void DrawToPlate(TubePlate*);

    bool mPitched; // 0x1c
    int mPart; // 0x20
    bool unk_0x24;
    int mGlowLevel; // 0x28 
    u8 unk_0x2C, unk_0x2D;
    float unk_0x30, unk_0x34;
    float mEndX; // 0x38
    RndMat* mBackMat; // 0x3c
    RndMat* mFrontMat; // 0x40
    TubePlate* mBackPlate; // 0x44
    TubePlate* mFrontPlate; // 0x48
    RndGroup* mBackParent; // 0x4c
    RndGroup* mFrontParent; // 0x50
    float mXPos; // 0x54
    std::vector<Vector3> mPoints; // 0x58
    float mAlpha; // 0x60
};

#endif // BANDOBJ_NOTETUBE_H