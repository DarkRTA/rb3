#include "rndobj/Flare.h"
#include "math/Rot.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/Rnd.h"
#include "rndobj/Trans.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"
#include "utl/TextStream.h"

INIT_REVS(RndFlare)

BEGIN_COPYS(RndFlare)
    CREATE_COPY_AS(RndFlare, f)
    MILO_ASSERT(f, 25);
    Hmx::Object::Copy(o, ty);
    RndTransformable::Copy(o, ty);
    RndDrawable::Copy(o, ty);
    mSizes = f->mSizes;
    mMat = f->mMat;
    mVisible = f->mVisible;
    bool td = f->mLastDone; // ???
    mLastDone = false;
    mRange = f->mRange;
    mOffset = f->mOffset;
    mSteps = f->mSteps;
    mPointTest = f->mPointTest;
    mTestDone = td;
END_COPYS

void RndFlare::Print() {
    TextStream& ts = TheDebug;
    ts << "   mat: " << mMat << "\n";
    ts << "   sizes: " << mSizes << "\n";
    ts << "   range: " << mRange << "\n";
    ts << "   offset:" << mOffset << "\n";
    ts << "   steps: " << mSteps << "\n";
    ts << "   point test: " << mPointTest << "\n";
}

SAVE_OBJ(RndFlare, 60)

BEGIN_LOADS(RndFlare)
    LOAD_REVS(bs)
    ASSERT_REVS(7, 0)
    if (gRev > 3) Hmx::Object::Load(bs);
    RndTransformable::Load(bs);
    RndDrawable::Load(bs);
    if (gRev != 0) {
        bs >> mMat;
    }
    if (gRev > 2)
        bs >> mSizes;
    else {
        bs >> mSizes.x;
        mSizes.y = mSizes.x;
    }
    if (gRev > 1) {
        bs >> mRange;
        bs >> mSteps;
    }
    if (gRev > 4) {
        bool b; bs >> b;
        mPointTest = b;
    }
    if (gRev > 6) bs >> mOffset;
    mTestDone = 0;
    mLastDone = unk8p7;
    CalcScale();
END_LOADS

RndFlare::RndFlare() : mPointTest(1), mAreaTest(1), mVisible(0), mSizes(0.1f, 0.1f), mMat(this, 0), 
    mRange(0.0f, 0.0f), mOffset(0.0f), mSteps(1), mStep(0), unkec(0.0f), unk114(1.0f, 1.0f) {
    mTestDone = 0;
    mLastDone = 0;
    mMatrix.Identity();
}

RndFlare::~RndFlare() {
    if (!gSuppressPointTest) MILO_FAIL("Async point tests not disabled while destroying flares!\n"); 
    TheRnd->RemovePointTest(this);
}

void RndFlare::SetPointTest(bool b) {
    if (!b && mPointTest) TheRnd->RemovePointTest(this);
    mPointTest = b; 
}

void RndFlare::Mats(std::list<RndMat*>& list, bool) {
    if (mMat) {
        mMat.mPtr->mShaderOptions = GetDefaultMatShaderOpts(this, mMat);
        list.push_back(mMat);
    }
}

void RndFlare::SetMat(RndMat* m) { mMat = m; }

BEGIN_HANDLERS(RndFlare)
    HANDLE_ACTION(set_steps, SetSteps(_msg->Int(2)))
    HANDLE_ACTION(set_point_test, SetPointTest(_msg->Int(2)))
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(373)
END_HANDLERS

BEGIN_PROPSYNCS(RndFlare)
    SYNC_PROP(mat, mMat)
    SYNC_PROP(sizes, mSizes)
    SYNC_PROP(steps, mSteps)
    SYNC_PROP(range, mRange)
    SYNC_PROP(offset, mOffset)
    SYNC_PROP_MODIFY(point_test, mPointTest, TheRnd->RemovePointTest(this))
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
