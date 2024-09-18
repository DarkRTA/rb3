#include "NoteTube.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "decomp.h"

NoteTube::NoteTube() : mPitched(false), mPart(-1), unk_0x24(false), mGlowLevel(-1), unk_0x2C(0), unk_0x2D(0), 
    unk_0x30(0), unk_0x34(0), mEndX(0), mBackMat(0), mFrontMat(0), mBackPlate(0), mFrontPlate(0), mBackParent(0), 
    mFrontParent(0), mXPos(0), mAlpha(1) { mPoints.reserve(100); }

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

void NoteTube::CreateMeshes(){
    int numpoints = mPoints.size();
    if(numpoints >= 2){
        if(mPitched){
            if(numpoints == 2){
                float segmentLength = mPoints[1].x - mPoints[0].x;
                MILO_ASSERT(segmentLength > 0.0f, 0x67);
                segmentLength = Min(segmentLength * 0.5f, unk_0x34);
                mPoints[0].x += segmentLength;
                mPoints[1].x -= segmentLength;
            }
            else {
                float segmentLength = mPoints[1].x - mPoints[0].x;
                MILO_ASSERT(segmentLength > 0.0f, 0x75);
                segmentLength = Min(segmentLength, unk_0x34);
                mPoints[0].x += segmentLength;

                segmentLength = mPoints[numpoints - 1].x - mPoints[numpoints - 2].x;
                MILO_ASSERT(segmentLength > 0.0f, 0x79);
                segmentLength = Min(segmentLength, unk_0x34);
                mPoints[numpoints - 1].x -= segmentLength;
            }
        }
        if(mFrontPlate && mFrontMat){
            if(!mFrontPlate->unk28) InitializePlate(mFrontPlate, mFrontMat, mFrontParent);
            DrawToPlate(mFrontPlate);
        }
        if(mBackPlate && mBackMat){
            if(!mBackPlate->unk28) InitializePlate(mBackPlate, mBackMat, mBackParent);
            DrawToPlate(mBackPlate);
        }
    }
}

void NoteTube::SetMeshVert(RndMesh::Vert& v, float f1, float f2, float f3, float f4){
    v.pos.Set(f1, 0, f2);
    v.uv.Set(f3, f4);
    v.color.SetAlpha(mAlpha);
    mEndX = std::max(mEndX, f1);
}

void NoteTube::InitializePlate(TubePlate* plate, RndMat* mat, RndGroup* parent){
    MILO_ASSERT(plate, 0x99);
    MILO_ASSERT(parent, 0x9A);
    RndMesh* mesh = plate->mMesh;
    MILO_ASSERT(mesh, 0x9D);
    mesh->mOwner->unk_0xF0 = 0x3F; // TODO: this should be inlined
    mesh->SetGeomOwner(mesh);
    mesh->SetMat(mat);
    mesh->SetTransParent(parent, false);
    mesh->SetShowing(false);
    plate->SetParent(parent);
    parent->AddObject(mesh, 0);
    Transform& xfm = mesh->DirtyLocalXfm();
    xfm.Reset();
    xfm.v.x = mXPos;
    plate->SetBeginX(mXPos);
    plate->SetWidthX(0);
}

TubePlate::TubePlate(int i) : mMesh(Hmx::Object::New<RndMesh>()), mParent(0), mAllocationCount(i), 
    mBeginX(3.40282346638528859812e38), mWidthX(0), mBaked(0), mActiveMs(3.40282346638528859812e38), 
    mInvalidateMs(3.40282346638528859812e38), mMatSize(0), mDeploy(0) {
    mMesh->Verts().reserve(mAllocationCount, true);
    mMesh->Faces().reserve(mAllocationCount);
    Reset();
}

TubePlate::~TubePlate() { RELEASE(mMesh); }

void TubePlate::AllocateVerts(int, bool){
    mMesh->Verts().Capacity();
}

void TubePlate::SetShowing(bool b){
    mMesh->SetShowing(b && mBaked);
}

float TubePlate::CurrentStartX(float f) const { return mBeginX + f; }
float TubePlate::CurrentEndX(float f) const { return mBeginX + mWidthX + f; }

String TubePlate::GetMatName(){
    if(mMesh && mMesh->GetMat()){
        return String(mMesh->GetMat()->Name());
    }
    else return String("<no mat>");
}

void TubePlate::SetDeployTiming(float f1, float f2){
    mActiveMs = f1;
    mInvalidateMs = f2;
    mDeploy = true;
}