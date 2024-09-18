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

    RndMesh* mMesh; // 0x0
    RndGroup* mParent; // 0x4
    int mAllocationCount; // 0x8
    f32 unk_0xC, unk_0x10;
    u8 unk_0x14;
    f32 unk_0x18, unk_0x1C, unk_0x20;
    u8 unk_0x24;
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
    void SetDeployTiming(float, float);
    void SetMeshVert(RndMesh::Vert&, float, float, float, float);

    bool mPitched; // 0x1c
    int mPart; // 0x20
    bool unk_0x24;
    int mGlowLevel; // 0x28 
    u8 unk_0x2C, unk_0x2D;
    float unk_0x30, unk_0x34, unk_0x38;
    RndMat* mBackMat; // 0x3c
    RndMat* mFrontMat; // 0x40
    TubePlate* mBackPlate; // 0x44
    TubePlate* mFrontPlate; // 0x48
    RndGroup* mBackParent; // 0x4c
    RndGroup* mFrontParent; // 0x50
    float mXPos; // 0x54
    std::vector<Vector3> mPoints; // 0x58
    float unk_0x60;
};

#endif // BANDOBJ_NOTETUBE_H