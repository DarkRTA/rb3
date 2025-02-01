#include "char/CharMirror.h"
#include "char/CharBones.h"
#include "char/CharWeightable.h"
#include "math/Mtx.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "utl/Symbols.h"

INIT_REVS(CharMirror)

CharMirror::CharMirror() : mServo(this), mMirrorServo(this), mBones(), mOps() {}

void CharMirror::Poll() {
    float weight = Weight();
    if (weight == 0 || mBones.TotalSize() == 0)
        return;
    mBones.ScaleDown(*mServo, 1.0f - weight);
    MirrorOp *curMirrorOp = &mOps[0];
    for (Vector3 *it = (Vector3 *)mBones.Start(); it < (Vector3 *)mBones.ScaleOffset();
         curMirrorOp++, it++) {
        *it = *(Vector3 *)curMirrorOp->ptr;
        if (!curMirrorOp->op.Null() && curMirrorOp->op == x) {
            it->x = -it->x;
        }
    }
    for (Hmx::Quat *it = (Hmx::Quat *)mBones.QuatOffset();
         it < (Hmx::Quat *)mBones.RotXOffset();
         curMirrorOp++, it++) {
        *it = *(Hmx::Quat *)curMirrorOp->ptr;
        if (!curMirrorOp->op.Null()) {
            if (curMirrorOp->op == zw) {
                it->w = -it->w;
                it->z = -it->z;
            } else if (curMirrorOp->op == xy) {
                it->x = -it->x;
                it->y = -it->y;
            } else if (curMirrorOp->op == mirror_x) {
                it->Set(it->z, it->w, it->x, it->y);
            } else
                MILO_WARN("Unknown operation %s", curMirrorOp->op);
        }
    }
    for (float *it = (float *)mBones.RotXOffset(); it < (float *)mBones.EndOffset();
         curMirrorOp++, it++) {
        *it = *(float *)curMirrorOp->ptr;
    }
    mBones.ScaleAdd(*mServo, weight);
}

void CharMirror::SetServo(CharServoBone *bone) {
    if (bone != mServo) {
        mServo = bone;
        SyncBones();
    }
}

void CharMirror::SetMirrorServo(CharServoBone *bone) {
    if (bone != mMirrorServo) {
        mMirrorServo = bone;
        SyncBones();
    }
}

void CharMirror::SyncBones() {
    mBones.ClearBones();
    if (!mServo || !mMirrorServo || !TypeDef())
        return;
    else {
        std::list<CharBones::Bone> bones;
        DataArray *mapArr = TypeDef()->FindArray("mappings", true);
        for (int i = 1; i < mapArr->Size(); i++) {
            bones.push_back(CharBones::Bone(mapArr->Array(i)->Sym(0), 1));
        }
        mBones.AddBones(bones);
        int numBones = mBones.mBones.size();
        mOps.resize(numBones);
        for (int i = 0; i < mOps.size(); i++) {
            Symbol boneName = mBones.mBones[i].name;
            DataArray *boneArr = mapArr->FindArray(boneName, true);
            mOps[i].ptr = mMirrorServo->FindPtr(boneArr->Sym(1));
            mOps[i].op = boneArr->Size() > 2 ? boneArr->Sym(2) : Symbol();
        }
    }
}

void CharMirror::PollDeps(
    std::list<Hmx::Object *> &changedBy, std::list<Hmx::Object *> &change
) {
    change.push_back(mServo);
}

SAVE_OBJ(CharMirror, 0x90)

BEGIN_LOADS(CharMirror)
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(CharWeightable)
    bs >> mMirrorServo;
    bs >> mServo;
    SyncBones();
END_LOADS

BEGIN_COPYS(CharMirror)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharMirror)
    BEGIN_COPYING_MEMBERS
        SetMirrorServo(c->mMirrorServo);
        SetServo(c->mServo);
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharMirror)
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xB8)
END_HANDLERS

BEGIN_PROPSYNCS(CharMirror)
    SYNC_PROP_SET(servo, (Hmx::Object *)mServo, SetServo(_val.Obj<CharServoBone>()));
    SYNC_PROP_SET(
        mirror_servo,
        (Hmx::Object *)mMirrorServo,
        SetMirrorServo(_val.Obj<CharServoBone>())
    );
    SYNC_SUPERCLASS(CharWeightable);
END_PROPSYNCS
