#include "NoteTube.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "decomp.h"

NoteTube::NoteTube() : mPitched(false), mPart(-1), unk_0x24(false), mGlowLevel(-1), unk_0x2C(0), unk_0x2D(0), 
    unk_0x30(0), unk_0x34(0), unk_0x38(0), mBackMat(0), mFrontMat(0), mBackPlate(0), mFrontPlate(0), mBackParent(0), 
    mFrontParent(0), mXPos(0), unk_0x60(1) { mPoints.reserve(100); }

void NoteTube::SetNumPoints(int i) { 
    if (i > mPoints.capacity()) MILO_WARN("Reallocating NoteTube point buffer to %d; please alert HUD/Track owner!", i);
    mPoints.resize(i);
}

void NoteTube::SetPointPos(int i, Vector3 v) {
    if (i < mPoints.size() ) mPoints[i] = v;
    else MILO_WARN("note tube has too few points\n");
}

DECOMP_FORCEACTIVE(NoteTube, "point pos query out of bounds\n")

void NoteTube::SetGlowLevel(int i) {
    mGlowLevel = 3 - i;
    MILO_ASSERT(( 0) <= (mGlowLevel) && (mGlowLevel) < ( NumGlowLevels()), 73);
}

void NoteTube::BakePlates() {
    if(mBackPlate) mBackPlate->Bake();
    if(mFrontPlate) mFrontPlate->Bake();
}

void NoteTube::SetDeployTiming(float f1, float f2){
    if(mBackPlate) mBackPlate->SetDeployTiming(f1, f2);
    if(mFrontPlate) mFrontPlate->SetDeployTiming(f1, f2);
}

void NoteTube::SetMeshVert(RndMesh::Vert& v, float f1, float f2, float f3, float f4){
    v.pos.Set(f1, 0, f2);
    v.uv.Set(f3, f4);
    v.color.SetAlpha(unk_0x60);
    unk_0x38 = std::max(unk_0x38, f1);
}

TubePlate::TubePlate(int i) : mMesh(Hmx::Object::New<RndMesh>()), mParent(0), mAllocationCount(i), 
    unk_0xC(3.40282346638528859812e38), unk_0x10(0), unk_0x14(0), unk_0x18(3.40282346638528859812e38), 
    unk_0x1C(3.40282346638528859812e38), unk_0x20(0), unk_0x24(0) {
    mMesh->mOwner->mVerts.reserve(mAllocationCount, true);
    mMesh->mOwner->mFaces.reserve(mAllocationCount); // evil regswap
    Reset();
}

TubePlate::~TubePlate() { RELEASE(mMesh); }