#include "char/CharServoBone.h"
#include "char/CharClipDriver.h"
#include "char/Character.h"
#include "char/CharBoneDir.h"
#include "char/CharDriver.h"
#include "char/Waypoint.h"
#include "char/CharUtl.h"
#include "math/Mtx.h"
#include "math/Rot.h"
#include "math/Vec.h"
#include "obj/Task.h"
#include "utl/Symbols.h"

DECOMP_FORCEACTIVE(
    CharServoBone, ".cb", "bone_facing_delta.pos", "bone_facing.pos", "bone_pelvis"
)

INIT_REVS(CharServoBone)

CharServoBone::CharServoBone()
    : mPelvis(0), mFacingRotDelta(0), mFacingPosDelta(0), mFacingRot(0), mFacingPos(0),
      mMoveSelf(0), mDeltaChanged(0), mRegulate(this) {}

CharServoBone::~CharServoBone() {}

void CharServoBone::Highlight() {}

void CharServoBone::SetName(const char *cc, ObjectDir *dir) {
    Hmx::Object::SetName(cc, dir);
    mMe = dynamic_cast<Character *>(Dir());
}

void CharServoBone::SetClipType(Symbol sym) {
    if (sym != mClipType) {
        mClipType = sym;
        ClearBones();
        CharBoneDir::StuffBones(*this, mClipType);
    }
}

void CharServoBone::Poll() {
    if (!mMeshes.empty()) {
        PoseMeshes();
        if (mFacingPosDelta) {
            if (!mMoveSelf) {
                if (mDeltaChanged) {
                    Transform tf48 = mMe->mLocalXfm;
                    MoveToDeltaFacing(tf48);
                    Transform tf78;
                    Multiply(mPelvis->mLocalXfm, tf48, tf78);
                    MoveToFacing(mPelvis->DirtyLocalXfm());
                    Transform tfa8;
                    FastInvert(mPelvis->DirtyLocalXfm(), tfa8);
                    Multiply(tfa8, tf78, mMe->DirtyLocalXfm());
                } else {
                    MoveToFacing(mPelvis->DirtyLocalXfm());
                }
                for (ObjDirItr<CharBone> it(
                         CharBoneDir::FindResourceFromClipType(mClipType), false
                     );
                     it != nullptr;
                     ++it) {
                    if (it->BakeOutAsTopLevel()) {
                        String str(it->Name());
                        if (str.find(".cb") != String::npos) {
                            str = str.substr(0, str.length() - 3);
                        }
                        RndTransformable *boneTrans =
                            CharUtlFindBoneTrans(str.c_str(), Dir());
                        if (mDeltaChanged) {
                            MoveToDeltaFacing(boneTrans->DirtyLocalXfm());
                            MoveToFacing(boneTrans->DirtyLocalXfm());
                        } else {
                            MoveToFacing(boneTrans->DirtyLocalXfm());
                        }
                    }
                }
            } else {
                if (mDeltaChanged) {
                    Transform tfd8(mPelvis->mLocalXfm);
                    MoveToFacing(tfd8);
                    Multiply(tfd8, mMe->mLocalXfm, tfd8);
                    Transform tf108;
                    FastInvert(mPelvis->mLocalXfm, tf108);
                    Multiply(tf108, tfd8, mMe->DirtyLocalXfm());
                } else {
                    MoveToDeltaFacing(mMe->DirtyLocalXfm());
                }
                Regulate();
            }
            mDeltaChanged = false;
        }
        ZeroDeltas();
    }
}

void CharServoBone::ReallocateInternal() {
    CharBonesMeshes::ReallocateInternal();
    mFacingRotDelta = 0;
    mFacingPosDelta = (Vector3 *)FindPtr("bone_facing_delta.pos");
    if (mFacingPosDelta) {
        mFacingPos = (Vector3 *)FindPtr("bone_facing.pos");
        mPelvis = CharUtlFindBoneTrans("bone_pelvis", Dir());
        MILO_ASSERT(mFacingPos && mPelvis, 0xB3);
        mFacingRot = (float *)FindPtr("bone_facing.rotz");
        mFacingRotDelta = (float *)FindPtr("bone_facing_delta.rotz");
    }
}

void CharServoBone::Enter() {
    ZeroDeltas();
    SetRegulateWaypoint(nullptr);
    mDeltaChanged = false;
    mMoveSelf = mFacingPosDelta;
}

void CharServoBone::ZeroDeltas() {
    if (mFacingPosDelta)
        mFacingPosDelta->Zero();
    if (!mFacingRotDelta)
        return;
    *mFacingRotDelta = 0.0f;
}

void CharServoBone::SetMoveSelf(bool b) {
    if (mMoveSelf == b)
        return;
    mMoveSelf = b;
    mDeltaChanged = true;
}

void CharServoBone::MoveToFacing(Transform &tf) {
    if (mFacingRot) {
        RotateAboutZ(tf.m, *mFacingRot, tf.m);
        RotateAboutZ(tf.v, *mFacingRot, tf.v);
        Normalize(tf.m, tf.m);
    }
    tf.v += *mFacingPos;
}

void CharServoBone::MoveToDeltaFacing(Transform &tf) {
    Vector3 v18;
    Multiply(*mFacingPosDelta, tf.m, v18);
    tf.v += v18;
    if (mFacingRotDelta) {
        RotateAboutZ(tf.m, *mFacingRotDelta, tf.m);
        Normalize(tf.m, tf.m);
    }
}

void CharServoBone::Regulate() {
    if (mRegulate) {
        CharClipDriver *driver = mMe->GetDriver()->Before(mMe->GetDriver()->Last());
        CharClipDriver *next = driver && driver->mRampIn > 0 ? driver->Next() : nullptr;
        if (next) {
            DoRegulate(
                mRegulate, next, driver->mRampIn, Max(2.0f, driver->mRampIn / 1.5f)
            );
        }
        mRegulate->Constrain(mMe->DirtyLocalXfm());
    }
}

void CharServoBone::DoRegulate(
    Waypoint *waypoint, CharClipDriver *driver, float f3, float f4
) {
    Transform &myxfm = mMe->DirtyLocalXfm();
    ClipPredict pred(driver->GetClip(), myxfm.v, GetZAngle(myxfm.m));
    pred.Predict(driver->mBeat, driver->mBeat + f3);
    pred.mPos = pred.mLastPos;

    float ang = pred.Angle();
    float deltaBeat = TheTaskMgr.DeltaBeat() / f4;
    waypoint->ShapeDelta(pred.mPos, pred.mLastPos);
    ScaleAddEq(myxfm.v, pred.mPos, deltaBeat);
    RotateAboutZ(myxfm.m, waypoint->ShapeDelta(ang) * deltaBeat, myxfm.m);
}

void CharServoBone::PollDeps(
    std::list<Hmx::Object *> &changedBy, std::list<Hmx::Object *> &change
) {
    StuffMeshes(change);
}

SAVE_OBJ(CharServoBone, 0x14A)

BEGIN_LOADS(CharServoBone)
    LOAD_REVS(bs)
    ASSERT_REVS(2, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    Symbol s;
    if (gRev > 1)
        bs >> s;
    SetClipType(s);
END_LOADS

BEGIN_COPYS(CharServoBone)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharServoBone)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mMoveSelf)
        SetClipType(c->mClipType);
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharServoBone)
    HANDLE_SUPERCLASS(CharPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x16E)
END_HANDLERS

BEGIN_PROPSYNCS(CharServoBone)
    SYNC_PROP_SET(clip_type, mClipType, SetClipType(_val.Sym()))
    SYNC_PROP_SET(move_self, mMoveSelf, SetMoveSelf(_val.Int()))
    SYNC_PROP(delta_changed, mDeltaChanged)
    SYNC_PROP(regulate, mRegulate)
    SYNC_SUPERCLASS(CharBonesMeshes)
END_PROPSYNCS
