#ifndef BANDOBJ_NOTETUBE_H
#define BANDOBJ_NOTETUBE_H
#include "rndobj/Group.h"
#include "rndobj/Mat.h"
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
    void PollDeploy(float);
    void AllocateVerts(int, bool);
    void AllocateFaces(int, bool);
    void SetParent(RndGroup *grp) { mParent = grp; }
    void SetBeginX(float x) { mBeginX = x; }
    void SetWidthX(float x) { mWidthX = x; }
    bool NoVerts() const { return mNumVerts == 0; }
    bool Baked() const { return mBaked; }
    float InvalidateMs() const { return mInvalidateMs; }
    bool Deploy() const { return mDeploy; }
    float GetWidthX() const { return mWidthX; }
    float GetBeginX() const { return mBeginX; }

    RndMesh *mMesh; // 0x0
    RndGroup *mParent; // 0x4
    int mAllocationCount; // 0x8
    float mBeginX; // 0xc
    float mWidthX; // 0x10
    bool mBaked; // 0x14
    float mActiveMs; // 0x18
    float mInvalidateMs; // 0x1c
    float mMatSize; // 0x20
    bool mDeploy; // 0x24
    int mNumVerts; // 0x28
};

class NoteTube : public Hmx::Object {
public:
    NoteTube();
    virtual ~NoteTube() {}

    void SetNumPoints(int);
    void SetPointPos(int, Vector3);
    void SetGlowLevel(int);
    int NumGlowLevels() const { return 4; }
    void BakePlates();
    void CreateMeshes();
    void SetDeployTiming(float, float);
    void SetMeshVert(RndMesh::Vert &, float, float, float, float);
    void InitializePlate(TubePlate *, RndMat *, RndGroup *);
    void DrawToPlate(TubePlate *);
    void LookupPitchedUVCoordinates(float &, float &, float &, float &, bool);
    bool Pitched() const { return mPitched; }
    void SetBackPlate(TubePlate *plate) { mBackPlate = plate; }
    void SetFrontPlate(TubePlate *plate) { mFrontPlate = plate; }
    int Part() const { return mPart; }
    void SetPitched(bool pitched) { mPitched = pitched; }
    void SetPart(int part) { mPart = part; }
    void SetAlpha(float alpha) { mAlpha = alpha; }
    void SetBackMat(RndMat *mat) { mBackMat = mat; }
    void SetBackParent(RndGroup *grp) { mBackParent = grp; }
    void SetFrontMat(RndMat *mat) { mFrontMat = mat; }
    void SetFrontParent(RndGroup *grp) { mFrontParent = grp; }
    void SetXPos(float pos) { mXPos = pos; }

    bool mPitched; // 0x1c
    int mPart; // 0x20
    bool unk_0x24;
    int mGlowLevel; // 0x28
    u8 unk_0x2C, unk_0x2D;
    float unk_0x30, unk_0x34;
    float mEndX; // 0x38
    RndMat *mBackMat; // 0x3c
    RndMat *mFrontMat; // 0x40
    TubePlate *mBackPlate; // 0x44
    TubePlate *mFrontPlate; // 0x48
    RndGroup *mBackParent; // 0x4c
    RndGroup *mFrontParent; // 0x50
    float mXPos; // 0x54
    std::vector<Vector3> mPoints; // 0x58
    float mAlpha; // 0x60
};

#endif // BANDOBJ_NOTETUBE_H