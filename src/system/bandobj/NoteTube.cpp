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
    MILO_ASSERT_RANGE(mGlowLevel, 0, NumGlowLevels(), 73);
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
    mesh->SetMutable(0x3F);
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

void NoteTube::DrawToPlate(TubePlate* plate){
    MILO_ASSERT(plate, 0xB4);
    RndMesh* mesh = plate->mMesh;
    MILO_ASSERT(mesh, 0xB7);
    MILO_ASSERT(!mesh->Showing(), 0xB8);
}

DECOMP_FORCEACTIVE(NoteTube, "mWidth > 0.0f")

void NoteTube::LookupPitchedUVCoordinates(float& f1, float& f2, float& f3, float& f4, bool b){
    f1 = 1.0f;
    f2 = 0.0f;
    f3 = 0.0f;
    f4 = 1.0f;
    MILO_ASSERT(mPitched, 0x1A8);
    MILO_ASSERT(mGlowLevel != -1, 0x1A9);
    int column, i2;
    if(b){
        MILO_ASSERT((mPart == 0) || (mPart == 1), 0x1AF);
        i2 = 0;
        column = (mPart == 0) + 2;
    }
    else {
        column = mGlowLevel;
        i2 = mPart + (unk_0x2C > 0) + 1;
    }
    if(i2 != -1){
        MILO_ASSERT(column != -1, 0x1C0);
        f2 = column * 0.25f;
        f1 = column * 0.25f + 0.25f;
        f3 = i2 * 0.125f;
        f4 = i2 * 0.125f + 0.125f;
    }
}

TubePlate::TubePlate(int i) : mMesh(Hmx::Object::New<RndMesh>()), mParent(0), mAllocationCount(i),
    mBeginX(3.40282346638528859812e38), mWidthX(0), mBaked(0), mActiveMs(3.40282346638528859812e38),
    mInvalidateMs(3.40282346638528859812e38), mMatSize(0), mDeploy(0) {
    mMesh->Verts().reserve(mAllocationCount, true);
    mMesh->Faces().reserve(mAllocationCount);
    Reset();
}

TubePlate::~TubePlate() { RELEASE(mMesh); }

void TubePlate::AllocateVerts(int num, bool warn){
    RndMesh::VertVector& verts = mMesh->Verts();
    int newsize = num + verts.size();
    int cap = verts.capacity();
    if(newsize > cap){
        int count = mAllocationCount;
        float ceiled = std::ceil((float)(newsize - cap) / (float)count);
        verts.reserve((int)ceiled * count + cap, true);
        if(warn) MILO_WARN("TubePlate: Reallocating verts from %d to %d; please alert HUD/Track owner", cap, verts.capacity());
    }
    verts.resize(newsize, true);
    unk28 += num;
}

void TubePlate::AllocateFaces(int num, bool warn){
    std::vector<RndMesh::Face>& faces = mMesh->Faces();
    int newsize = num + faces.size();
    int cap = faces.capacity();
    if(newsize > cap){
        int count = mAllocationCount;
        float ceiled = std::ceil((float)(newsize - cap) / (float)count);
        faces.reserve((int)ceiled * count + cap);
        if(warn) MILO_WARN("TubePlate: Reallocating faces from %d to %d; please alert HUD/Track owner", cap, faces.capacity());
    }
    faces.resize(newsize);
}

void TubePlate::Bake(){
    if(!mBaked){
        MILO_ASSERT(mMesh, 0x21A);
        RndMesh::VertVector& verts = mMesh->Verts();
        if(mDeploy){
            mMatSize = verts[verts.size() - 2].uv.x;
        }
        if(!mDeploy) mMesh->SetMutable(0);
        mMesh->Sync(0x2BF);
        mMesh->SetShowing(true);
        mBaked = true;
    }
}

void TubePlate::SetShowing(bool b){
    mMesh->SetShowing(b && mBaked);
}

float TubePlate::CurrentStartX(float f) const { return mBeginX + f; }
float TubePlate::CurrentEndX(float f) const { return mBeginX + mWidthX + f; }

void TubePlate::Reset(){
    mMesh->SetShowing(false);
    if(mParent) mParent->RemoveObject(mMesh);
    mMesh->SetMutable(0x3F);
    mMesh->Verts().clear();
    mMesh->Faces().clear();
    mWidthX = 0;
    mBaked = false;
    mBeginX = 3.4028235E+38f;
    mActiveMs = 3.4028235E+38f;
    mInvalidateMs = 3.4028235E+38f;
    mMatSize = 0;
    mDeploy = false;
    unk28 = 0;
}

String TubePlate::GetMatName(){
    if(mMesh && mMesh->Mat()){
        return String(mMesh->Mat()->Name());
    }
    else return String("<no mat>");
}

void TubePlate::SetDeployTiming(float f1, float f2){
    mActiveMs = f1;
    mInvalidateMs = f2;
    mDeploy = true;
}

void TubePlate::PollDeploy(float f){
    if(mBaked && mActiveMs < f && f < mInvalidateMs){
        RndMesh::VertVector& verts = mMesh->Verts();
        float f1 = mWidthX;
        float f2 = mMatSize;
        float f3 = (mInvalidateMs - f) / (mInvalidateMs - mActiveMs);
        for(int i = verts.size() - 2; i < verts.size(); i++){
            RndMesh::Vert& curvert = verts[i];
            curvert.pos.x = f1 * f3;
            curvert.uv.x = f2 * f3;
        }
    }
}
