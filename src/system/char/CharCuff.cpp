#include "char/CharCuff.h"
#include "char/FileMerger.h"
#include "decomp.h"
#include "math/Rot.h"
#include "math/Trig.h"
#include "math/Vec.h"
#include "os/Debug.h"
#include "rndobj/Mesh.h"
#include "rndobj/Rnd.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"

INIT_REVS(CharCuff)

CharCuff::CharCuff()
    : mOpenEnd(0), mIgnore(this, kObjListNoNull), mBone(this, 0), mEccentricity(1.0f),
      mCategory() {
    mShape[0].offset = -2.9f;
    mShape[0].radius = 1.9f;

    mShape[1].offset = 0.0f;
    mShape[1].radius = 2.6f;

    mShape[2].offset = 2.0f;
    mShape[2].radius = 3.5f;

    mOuterRadius = mShape[1].radius + 0.5f;
}

CharCuff::~CharCuff() {}

float CharCuff::Eccentricity(const Vector2 &v) const {
    float f1 = v.y * v.y;
    float f2 = v.x * v.x;
    return std::sqrt((f1 + f2) / (f1 * (1.0f / (mEccentricity * mEccentricity)) + f2));
}

// fn_804C3D90 - highlight
void CharCuff::Highlight() {
    Hmx::Color white(1, 1, 1, 1);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 32; j++) {
            float toSine = j * 6.2831855f / 32.0f;
            Vector3 va8(Sine(toSine), Cosine(toSine), mShape[i].offset);
            Vector3 vb4(Sine(toSine), Cosine(toSine), mShape[i + 1].offset);
            (Vector2 &)va8 *= mShape[i].radius * Eccentricity((Vector2 &)va8);
            (Vector2 &)vb4 *= mShape[i + 1].radius * Eccentricity((Vector2 &)vb4);
            Vector3 vc0;
            Multiply(va8, WorldXfm(), vc0);
            Vector3 vcc;
            Multiply(vb4, WorldXfm(), vcc);
            TheRnd->DrawLine(vc0, vcc, white, false);
            if (i < 2) {
                float toSinePlus1 = (j + 1) * 6.2831855f / 32.0f;
                va8.Set(Sine(toSinePlus1), Cosine(toSinePlus1), mShape[i].offset);
                (Vector2 &)va8 *= mShape[i].radius * Eccentricity((Vector2 &)va8);
                Multiply(va8, WorldXfm(), vcc);
                TheRnd->DrawLine(vc0, vcc, white, false);
            }
            if (i == 1) {
                Vector3 vd8(Sine(toSine), Cosine(toSine), mShape[i].offset);
                (Vector2 &)vd8 *= mOuterRadius;
                Multiply(vd8, WorldXfm(), vc0);
                float toSinePlus1 = (j + 1) * 6.2831855f / 32.0f;
                vb4.Set(Sine(toSinePlus1), Cosine(toSinePlus1), mShape[i].offset);
                (Vector2 &)vb4 *= mOuterRadius;
                Multiply(vb4, WorldXfm(), vcc);
                TheRnd->DrawLine(vc0, vcc, white, false);
            }
        }
    }
}

unsigned int BoneMask(std::list<RndTransformable *> &tlist, RndMesh *mesh) {
    unsigned int mask = 0;
    for (int i = 0; i < mesh->NumBones(); i++) {
        if (std::find(tlist.begin(), tlist.end(), mesh->BoneTransAt(i)) != tlist.end()) {
            mask |= 1 << i;
        }
    }
    return mask;
}

void AddBoneChildren(std::list<RndTransformable *> &tlist, RndTransformable *trans) {
    if (trans) {
        if (strncmp(trans->Name(), "bone_", 5) == 0) {
            tlist.push_back(trans);
            for (std::vector<RndTransformable *>::const_iterator it =
                     trans->TransChildren().begin();
                 it != trans->TransChildren().end();
                 ++it) {
                AddBoneChildren(tlist, *it);
            }
        }
    }
}

void CharCuff::Deform(SyncMeshCB *cb, FileMerger *fm) {
    if (mBone) {
        std::list<RndMesh *> meshes;
        for (ObjDirItr<CharCuff> it(Dir(), false); it != nullptr; ++it) {
            if (it != this) {
                if (it->mBone == mBone) {
                    if (it->mOuterRadius > mOuterRadius)
                        return;
                    if (mOuterRadius == it->mOuterRadius) {
                        if (strcmp(it->Name(), Name()) > 0)
                            return;
                    }
                    for (ObjPtrList<RndMesh>::iterator iter = it->mIgnore.begin();
                         iter != it->mIgnore.end();
                         ++iter) {
                        meshes.push_back(*iter);
                    }
                }
            }
        }
        FileMerger::Merger *merger = nullptr;
        if (fm) {
            for (int i = 0; i < fm->mMergers.size(); i++) {
                merger = &fm->mMergers[i];
                if (strstr(merger->mName.mStr, mCategory.mStr)
                    && merger->mLoadedObjects.size() != 0
                    && merger->mLoadedObjects.front()->Dir() == Dir()) {
                    break;
                }
            }
        }
        if (!merger)
            return;
        else {
            std::list<RndTransformable *> transes;
            AddBoneChildren(transes, mBone);
            for (ObjPtrList<Hmx::Object>::iterator it = merger->mLoadedObjects.begin();
                 it != merger->mLoadedObjects.end();
                 ++it) {
                RndMesh *curMesh = dynamic_cast<RndMesh *>(*it);
                if (curMesh) {
                    if (std::find(meshes.begin(), meshes.end(), curMesh)
                        == meshes.end()) {
                        unsigned int mask = BoneMask(transes, curMesh);
                        if (mask != 0) {
                            meshes.push_back(curMesh);
                            DeformMesh(curMesh, mask, cb);
                        }
                    }
                }
            }
        }
    }
}

void CharCuff::DeformMesh(RndMesh *mesh, int, SyncMeshCB *) {
    MILO_ASSERT(mesh->NumBones(), 0xF5);
    Vector4_16_01 v;
    v.GetW();
    v.GetX();
    v.GetY();
    v.GetZ();
}

SAVE_OBJ(CharCuff, 0x1A2)

DECOMP_FORCEACTIVE(CharCuff, "ObjPtr_p.h", "c.Owner()", "", "f.Owner()")

BEGIN_LOADS(CharCuff)
    LOAD_REVS(bs)
    ASSERT_REVS(8, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    for (int i = 0; i < 3; i++) {
        bs >> mShape[i].radius >> mShape[i].offset;
    }
    if (gRev > 1)
        bs >> mOuterRadius;
    else
        mOuterRadius = mShape[1].radius + 0.5f;
    if (gRev > 2)
        bs >> mOpenEnd;
    else
        mOpenEnd = false;
    if (gRev > 3)
        bs >> mBone;
    else
        mBone = TransParent();
    if (gRev > 4)
        bs >> mEccentricity;
    else
        mEccentricity = 1.0f;
    if (gRev > 5)
        bs >> mCategory;
    else
        mCategory = Symbol("");
    if (gRev > 7)
        bs >> mIgnore;
    if (gRev < 7)
        MILO_WARN("%s old CharCuff, must convert, see James", PathName(this));
END_LOADS

BEGIN_COPYS(CharCuff)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    CREATE_COPY(CharCuff)
    BEGIN_COPYING_MEMBERS
        memcpy(mShape, c->mShape, 0x18);
        COPY_MEMBER(mOuterRadius)
        COPY_MEMBER(mOpenEnd)
        COPY_MEMBER(mBone)
        COPY_MEMBER(mEccentricity)
        COPY_MEMBER(mCategory)
        COPY_MEMBER(mIgnore)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharCuff)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1FE)
END_HANDLERS

BEGIN_PROPSYNCS(CharCuff)
    SYNC_PROP(offset0, mShape[0].offset)
    SYNC_PROP(radius0, mShape[0].radius)
    SYNC_PROP(offset1, mShape[1].offset)
    SYNC_PROP(radius1, mShape[1].radius)
    SYNC_PROP(offset2, mShape[2].offset)
    SYNC_PROP(radius2, mShape[2].radius)
    SYNC_PROP(outer_radius, mOuterRadius)
    SYNC_PROP(open_end, mOpenEnd)
    SYNC_PROP(bone, mBone)
    SYNC_PROP(eccentricity, mEccentricity)
    SYNC_PROP(category, mCategory)
    SYNC_PROP(ignore, mIgnore)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS