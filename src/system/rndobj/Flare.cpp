#include "rndobj/Flare.h"
#include "math/Rot.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Cam.h"
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
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    COPY_SUPERCLASS(RndDrawable)
    COPY_MEMBER_FROM(f, mSizes)
    COPY_MEMBER_FROM(f, mMat)
    COPY_MEMBER_FROM(f, mVisible)
    COPY_MEMBER_FROM(f, mRange)
    COPY_MEMBER_FROM(f, mOffset)
    COPY_MEMBER_FROM(f, mSteps)
    COPY_MEMBER_FROM(f, mPointTest)
    mLastDone = false;
    mTestDone = mLastDone;
END_COPYS

void RndFlare::Print() {
    TextStream &ts = TheDebug;
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
    if (gRev > 3)
        LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    LOAD_SUPERCLASS(RndDrawable)
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
        bs >> mRange >> mSteps;
    }
    if (gRev > 4) {
        bs >> mPointTest;
    }
    if (gRev > 6)
        bs >> mOffset;
    mLastDone = 0;
    mTestDone = mLastDone;
    CalcScale();
END_LOADS

RndFlare::RndFlare()
    : mPointTest(1), mAreaTest(1), mVisible(0), mSizes(0.1f, 0.1f), mMat(this),
      mRange(0, 0), mOffset(0), mSteps(1), mStep(0), unkec(0), unk114(1, 1) {
    mTestDone = 0;
    mLastDone = 0;
    mMatrix.Identity();
}

RndFlare::~RndFlare() {
    if (!gSuppressPointTest)
        MILO_FAIL("Async point tests not disabled while destroying flares!\n");
    TheRnd->RemovePointTest(this);
}

void RndFlare::CalcScale() {
    if (mMatrix != WorldXfm().m) {
        Vector3 v28;
        mMatrix = WorldXfm().m;
        float len = Length(mMatrix.z);
        Cross(mMatrix.x, mMatrix.y, v28);
        unk114.Set(Length(mMatrix.x), Dot(v28, mMatrix.z) > 0.0f ? len : -len);
    }
}

void RndFlare::SetPointTest(bool b) {
    if (!b && mPointTest)
        TheRnd->RemovePointTest(this);
    mPointTest = b;
}

void RndFlare::DrawShowing() {}

Hmx::Rect &RndFlare::CalcRect(Vector2 &vref, float &fref) {
    float f9 = mSizes.x;
    if (f9 != mSizes.y) {
        RndCam *cam = RndCam::sCurrent;
        float dot = Dot(cam->WorldXfm().m.y, WorldXfm().m.y);
        float max = Max(0.0f, -dot);
        f9 = Interp(mSizes.x, mSizes.y, max);
    }
    int width = TheRnd->Width();
    int height = TheRnd->Height();
    CalcScale();
    mArea.w = f9 * width * unk114.x;
    mArea.h = (height * f9 * width * unk114.y) / (width * TheRnd->YRatio());
    mArea.x = vref.x * width - mArea.w * 0.5f;
    mArea.y = vref.y * height - mArea.h * 0.5f;
    float f1 = Min<float>(width, mArea.x + mArea.w) - Max(0.0f, mArea.x);
    float f2 = Min<float>(height, mArea.y + mArea.h) - Max(0.0f, mArea.y);
    fref = f1 * f2;
    return mArea;
}

bool RndFlare::RectOffscreen(const Hmx::Rect &r) const {
    if (r.x + r.w < 0)
        return true;
    else if (r.y + r.h < 0)
        return true;
    else if (r.x > TheRnd->Width())
        return true;
    else if (r.y > TheRnd->Height())
        return true;
    else
        return false;
}

void RndFlare::Mats(std::list<RndMat *> &list, bool) {
    if (mMat) {
        mMat->mShaderOptions = GetDefaultMatShaderOpts(this, mMat);
        list.push_back(mMat);
    }
}

void RndFlare::SetMat(RndMat *m) { mMat = m; }

void RndFlare::SetSteps(int i1) {
    int max = Max(1, i1);
    if (mStep == mSteps) {
        mStep = max;
    } else
        mStep *= ((float)max / mSteps);
    mSteps = max;
}

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
