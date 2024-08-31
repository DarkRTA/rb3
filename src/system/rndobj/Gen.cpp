#include "rndobj/Gen.h"
#include "math/Rot.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Anim.h"
#include "rndobj/Cam.h"
#include "rndobj/Draw.h"
#include "rndobj/Part.h"
#include "rndobj/Trans.h"
#include "types.h"
#include "utl/Symbols.h"

static int GENERATOR_REV = 11;

RndGenerator::RndGenerator() : mPath(this, 0), mPathStartFrame(0.0f), mPathEndFrame(0.0f), mMesh(this, 0), mMultiMesh(this, 0), mParticleSys(this, 0), 
    mNextFrameGen(-9999999.0f), mRateGenLow(100.0f), mRateGenHigh(100.0f), mScaleGenLow(1.0f), mScaleGenHigh(1.0f),
    mPathVarMaxX(0.0f), mPathVarMaxY(0.0f), mPathVarMaxZ(0.0f), mCurMultiMesh(0) {

}

RndGenerator::~RndGenerator(){
    ResetInstances();
}

BEGIN_COPYS(RndGenerator)
    CREATE_COPY_AS(RndGenerator, d)
    MILO_ASSERT(d, 48);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(RndAnimatable)
    ResetInstances();
    if (ty == kCopyFromMax) return;
    COPY_MEMBER_FROM(d, mMesh)
    COPY_MEMBER_FROM(d, mPath)
    COPY_MEMBER_FROM(d, mRateGenLow)
    COPY_MEMBER_FROM(d, mRateGenHigh)
    COPY_MEMBER_FROM(d, mScaleGenLow)
    COPY_MEMBER_FROM(d, mScaleGenHigh)
    COPY_MEMBER_FROM(d, mPathVarMaxX)
    COPY_MEMBER_FROM(d, mPathVarMaxY)
    COPY_MEMBER_FROM(d, mPathVarMaxZ)
    COPY_MEMBER_FROM(d, mPathEndFrame)
    COPY_MEMBER_FROM(d, mPathStartFrame)
    COPY_MEMBER_FROM(d, mMultiMesh)
    COPY_MEMBER_FROM(d, mParticleSys)
END_COPYS

void RndGenerator::Print() {
    TextStream& ts = TheDebug;
    ts << "   path: " << mPath << "\n";
    ts << "   mesh: " << mMesh << "\n";
    ts << "   rateGenLow: " << mRateGenLow << "\n";
    ts << "   rateGenHigh: " << mRateGenHigh << "\n";
    ts << "   scaleGenLow: " << mScaleGenLow << "\n";
    ts << "   scaleGenHigh:" << mScaleGenHigh << "\n";
    ts << "   pathVarMax: (" << mPathVarMaxX << ", " << mPathVarMaxY << ", " << mPathVarMaxZ << ")\n";
    ts << "   multiMesh: " << mMultiMesh << "\n";
    ts << "   particleSys: " << mParticleSys << "\n";
}

SAVE_OBJ(RndGenerator, 98)

BEGIN_LOADS(RndGenerator)
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, GENERATOR_REV);
    if (rev > 9) Hmx::Object::Load(bs);
    if (rev > 1) {
        RndTransformable::Load(bs);
        RndDrawable::Load(bs);
        RndAnimatable::Load(bs);
    }
    ResetInstances();
    bs >> mMesh >> mPath;
    if (rev < 7) { u8 x; bs >> x; if (!x) MILO_WARN("%s no longer supports childOfGen", mName); }
    if (rev < 1) {
        bs >> mRateGenHigh;
        bs >> mScaleGenHigh;
    }
    if (rev < 8) {
        ObjPtr<RndCam, ObjectDir> cam(this, NULL);
        bool a; int b;
        bs >> a; bs >> b;
        bs >> cam;
    }
    if (rev > 0) {
        bs >> mRateGenLow; 
        bs >> mRateGenHigh;
        bs >> mScaleGenLow;
        bs >> mScaleGenHigh;
        bs >> mPathVarMaxX;
        bs >> mPathVarMaxY;
        bs >> mPathVarMaxZ;
        if (rev < 9) {
            mPathVarMaxX *= DEG2RAD;
            mPathVarMaxY *= DEG2RAD;
            mPathVarMaxZ *= DEG2RAD;
        }
    } else {
        mRateGenLow = mRateGenHigh;
        mScaleGenLow = mScaleGenHigh;
        mPathVarMaxZ = 0;
        mPathVarMaxY = 0;
        mPathVarMaxX = 0;
    }

    if (rev == 3) {
        int x;
        ObjPtr<Hmx::Object, ObjectDir> obj(this, NULL);
        bs >> obj >> x;
    }
    if (u32(rev - 4) <= 6) {
        ObjPtr<Hmx::Object, ObjectDir> obj(this, NULL);
        bs >> obj;
    }
    if (u32(rev - 5) <= 5) {
        bool x; bs >> x;
    }
    if (rev > 5) {
        bs >> mPathEndFrame;
        bs >> mPathStartFrame;
    } else {
        if (mPath) mPathEndFrame = mPath->EndFrame();
        mPathStartFrame = 0;
    }
    if (rev > 6) {
        bs >> mMultiMesh >> mParticleSys;
    }
END_LOADS

void RndGenerator::ResetInstances() {
    mInstances.clear();
    if (mParticleSys) mParticleSys->Exit();
    if (mMultiMesh) mMultiMesh->mInstances.clear();
}

void RndGenerator::SetPath(RndTransAnim* path, float start, float end) {
    mPath = path;
    if (mPath && start == -1) {
        mPathStartFrame = mPath->StartFrame();
    } else mPathStartFrame = start;
    if (mPath && end == -1) {
        mPathEndFrame = mPath->EndFrame();
    } else mPathEndFrame = end;
}

void RndGenerator::Generate(float frame) {
    if (mParticleSys) {
        RndParticle* p = RndParticleSys::AllocParticle();
        mCurParticle = p;
        mParticleSys->InitParticle(p, NULL);
    }
}

float RndGenerator::StartFrame() {
    if (mPath) return mPath->StartFrame();
    return 0;
}

float RndGenerator::EndFrame() {
    if (mPath) return mPath->EndFrame();
    return 0;
}

void RndGenerator::ListAnimChildren(std::list<RndAnimatable*>& list) const {
    if (mPath) list.push_back(mPath);
}

void RndGenerator::DrawMesh(Transform& t, float) {
    mMesh->SetWorldXfm(t);
    mMesh->Draw();
}

void RndGenerator::DrawMultiMesh(Transform& t, float f) {
    t.v.x = mCurMultiMesh->pad[0];
}

void RndGenerator::DrawParticleSys(Transform&, float) {
    
}

void RndGenerator::ListDrawChildren(std::list<RndDrawable*>& list) {
    if (mMesh) list.push_back(mMesh);
    if (mMultiMesh) list.push_back(mMultiMesh);
    if (mParticleSys) list.push_back(mParticleSys);
}

BEGIN_HANDLERS(RndGenerator)
    HANDLE(set_path, OnSetPath)
    HANDLE(set_ratevar, OnSetRateVar)
    HANDLE(set_scalevar,OnSetScaleVar)
    HANDLE(set_pathvar,OnSetPathVar)
    HANDLE(generate,OnGenerate)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(572)
END_HANDLERS

DataNode RndGenerator::OnSetPath(const DataArray* da) {
    SetPath(da->Obj<RndTransAnim>(2), -1, -1);
    return DataNode(0);
}

DataNode RndGenerator::OnSetRateVar(const DataArray* da) {
    SetRateVar(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndGenerator::OnSetScaleVar(const DataArray* da) {
    SetScaleVar(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndGenerator::OnSetPathVar(const DataArray* da) {
    SetPathVar(da->Float(2), da->Float(3), da->Float(4));
    return DataNode(0);
}

DataNode RndGenerator::OnGenerate(const DataArray* da) {
    Generate(GetFrame());
    return DataNode(0);
}

BEGIN_PROPSYNCS(RndGenerator)
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
