#include "rndobj/Group.h"
#include "math/Mtx.h"
#include "math/Utl.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Anim.h"
#include "rndobj/Cam.h"
#include "rndobj/Draw.h"
#include "rndobj/Env.h"
#include "rndobj/Trans.h"
#include "rndobj/Utl.h"
#include "utl/Std.h"
#include "utl/Symbols.h"

int GROUP_REV = 14;
bool gInReplace;

RndGroup::RndGroup()
    : mObjects(this, kObjListOwnerControl), mEnv(this), mDrawOnly(this), mLod(this),
      mLodScreenSize(0), mDrawLod(0) {
    mSortInWorld = false;
}

SAVE_OBJ(RndGroup, 0x30);

void RndGroup::Load(BinStream &bs) {
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, GROUP_REV);
    if (rev > 7)
        LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    LOAD_SUPERCLASS(RndTransformable)
    LOAD_SUPERCLASS(RndDrawable)
    if (rev > 10) {
        bs >> mObjects >> mEnv;
        if (rev > 12)
            bs >> mDrawOnly;
        else
            mDrawOnly = nullptr;
        Update();
    }
    if (rev > 11) {
        bs >> mLod >> mLodScreenSize;
    }
    if (rev > 13) {
        LOAD_BITFIELD(bool, mSortInWorld)
    }
    UpdateLODState();
}

BEGIN_COPYS(RndGroup)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(RndTransformable)
    CREATE_COPY(RndGroup)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mEnv)
        COPY_MEMBER(mDrawOnly)
        COPY_MEMBER(mLod)
        COPY_MEMBER(mLodScreenSize)
        COPY_MEMBER(mSortInWorld)
        if (ty == kCopyDeep)
            COPY_MEMBER(mObjects)
        else if (ty == kCopyFromMax)
            Merge(c);
    END_COPYING_MEMBERS
    Update();
END_COPYS

void RndGroup::AddObject(Hmx::Object *o1, Hmx::Object *o2) {
    if (!o1 || o1 == this)
        return;
    if (mObjects.find(o1) != mObjects.end())
        return;
    else {
        if (o2) {
            mObjects.insert(mObjects.find(o2), o1);
            Update();
        } else {
            mObjects.push_back(o1);
            RndAnimatable *anim = dynamic_cast<RndAnimatable *>(o1);
            if (anim)
                mAnims.push_back(anim);
            RndDrawable *draw = dynamic_cast<RndDrawable *>(o1);
            if (draw)
                mDraws.push_back(draw);
            mDrawItr = mDraws.begin();
        }
    }
}

void RndGroup::RemoveObject(Hmx::Object *o) {
    mObjects.remove(o);
    VectorRemove(mDraws, o);
    VectorRemove(mAnims, o);
    if (mDrawOnly == o && !gInReplace) {
        mDrawOnly = nullptr;
    }
    mDrawItr = mDraws.begin();
}

void RndGroup::ClearObjects() {
    mObjects.clear();
    Update();
}

void RndGroup::AddObjectAtFront(Hmx::Object *o) {
    if (!o || o == this)
        return;
    if (mObjects.find(o) != mObjects.end())
        return;
    else {
        mObjects.push_front(o);
        RndAnimatable *anim = dynamic_cast<RndAnimatable *>(o);
        if (anim)
            mAnims.insert(mAnims.begin(), anim);
        RndDrawable *draw = dynamic_cast<RndDrawable *>(o);
        if (draw)
            mDraws.insert(mDraws.begin(), draw);
        mDrawItr = mDraws.begin();
    }
}

void RndGroup::Merge(const RndGroup *group) {
    if (group) {
        FOREACH (it, group->mObjects) {
            AddObject(*it);
        }
    }
}

void RndGroup::Update() {
    mAnims.clear();
    mDraws.clear();
    FOREACH (it, mObjects) {
        RndAnimatable *anim = dynamic_cast<RndAnimatable *>(*it);
        if (anim)
            mAnims.push_back(anim);
        RndDrawable *draw = dynamic_cast<RndDrawable *>(*it);
        if (draw)
            mDraws.push_back(draw);
    }
    if (mDrawOnly && !VectorFind(mDraws, mDrawOnly.Ptr())) {
        mDrawOnly = nullptr;
    }
    UpdateLODState();
    mDrawItr = mDraws.begin();
}

void RndGroup::UpdateLODState() {
    if (mLod && mLodScreenSize > 0) {
        mDrawLod = true;
    } else
        mDrawLod = false;
}

void RndGroup::SortDraws() {
    FOREACH (it, mDraws) {
        mObjects.remove(*it);
    }
    std::sort(mDraws.begin(), mDraws.end(), ::SortDraws);
    FOREACH (it, mDraws) {
        mObjects.push_back(*it);
    }
    mAnims.clear();
    FOREACH (it, mObjects) {
        RndAnimatable *anim = dynamic_cast<RndAnimatable *>(*it);
        if (anim)
            mAnims.push_back(anim);
    }
}

void RndGroup::Replace(Hmx::Object *from, Hmx::Object *to) {
    RndTransformable::Replace(from, to);
    if (mObjects.find(from) != mObjects.end()) {
        AddObject(to, from);
        gInReplace = true;
        RemoveObject(from);
        gInReplace = false;
    }
}

void RndGroup::StartAnim() {
    FOREACH (it, mAnims) {
        (*it)->StartAnim();
    }
}

void RndGroup::EndAnim() {
    FOREACH (it, mAnims) {
        (*it)->EndAnim();
    }
}

void RndGroup::SetFrame(float frame, float blend) {
    if (Showing()) {
        RndAnimatable::SetFrame(frame, blend);
        FOREACH (it, mAnims) {
            (*it)->SetFrame(frame, blend);
        }
    }
}

float RndGroup::EndFrame() {
    float end = 0;
    FOREACH (it, mAnims) {
        MaxEq(end, (*it)->EndFrame());
    }
    return end;
}

void RndGroup::ListAnimChildren(std::list<RndAnimatable *> &children) const {
    children.insert(children.end(), mAnims.begin(), mAnims.end());
}

void RndGroup::DrawShowing() { DrawShowingBudget(kHugeFloat); }

bool RndGroup::DrawShowingBudget(float f1) {
    if (mLodScreenSize) {
        Sphere s;
        if (MakeWorldSphere(s, false)
            && RndCam::sCurrent->CalcScreenHeight(s) < mLodScreenSize) {
            if (mLod)
                mLod->DrawShowing();
            return true;
        }
    }
    if (mDraws.empty())
        return true;

    RndEnvironTracker tracker(mEnv, &WorldXfm().v);
    if (mDrawOnly) {
        mDrawOnly->Draw();
    } else {
        Timer timer;
        timer.Start();
        if (mDrawItr == mDraws.end()) {
            mDrawItr = mDraws.begin();
        }
        while (mDrawItr != mDraws.end()) {
            float splitMs = timer.SplitMs();
            if (splitMs > f1)
                return false;
            if (mDrawItr && *mDrawItr && !(*mDrawItr)->DrawBudget(f1 - splitMs))
                return false;
            mDrawItr++;
        }
    }
    return true;
}

void RndGroup::ListDrawChildren(std::list<RndDrawable *> &children) {
    children.insert(children.end(), mDraws.begin(), mDraws.end());
    if (mLod)
        children.push_back(mLod);
}

void RndGroup::CollideList(const Segment &seg, std::list<Collision> &colls) {
    if (CollideSphere(seg)) {
        FOREACH (it, mDraws) {
            (*it)->CollideList(seg, colls);
        }
    }
}

int RndGroup::CollidePlane(const Plane &p) {
    int ret = -1;
    FOREACH (it, mDraws) {
        if (it == mDraws.begin()) {
            ret = (*it)->CollidePlane(p);
        } else if (ret != (*it)->CollidePlane(p)) {
            return 0;
        }
    }
    return ret;
}

RndDrawable *RndGroup::CollideShowing(const Segment &seg, float &f, Plane &p) {
    RndDrawable *ret = nullptr;
    Segment localseg(seg);
    f = 1.0f;
    float locf;
    FOREACH (it, mDraws) {
        RndDrawable *collided = (*it)->Collide(localseg, locf, p);
        if (collided) {
            Interp(localseg.start, localseg.end, locf, localseg.end);
            f *= locf;
            ret = collided;
        }
    }
    return ret;
}

void RndGroup::UpdateSphere() {
    Sphere s;
    MakeWorldSphere(s, true);
    Transform tf38;
    FastInvert(WorldXfm(), tf38);
    Multiply(s, tf38, s);
    SetSphere(s);
}

float RndGroup::GetDistanceToPlane(const Plane &p, Vector3 &v) {
    if (mDraws.empty())
        return 0;
    else {
        float ret = 0;
        bool first = true;
        FOREACH (it, mDraws) {
            Vector3 locvec;
            float dist = (*it)->GetDistanceToPlane(p, v);
            if (first || (std::fabs(dist) < std::fabs(ret))) {
                first = false;
                ret = dist;
                v = locvec;
            }
        }
        return ret;
    }
}

bool RndGroup::MakeWorldSphere(Sphere &s, bool b) {
    if (b) {
        s.Zero();
        FOREACH (it, mDraws) {
            Sphere local_s;
            (*it)->MakeWorldSphere(local_s, true);
            RndTransformable *trans = dynamic_cast<RndTransformable *>(*it);
            if (trans)
                AddMotionSphere(trans, local_s);
            s.GrowToContain(local_s);
        }
        return true;
    } else {
        const Sphere &mysphere = mSphere;
        if (mysphere.GetRadius()) {
            Multiply(mysphere, WorldXfm(), s);
            return true;
        } else
            return false;
    }
}

BEGIN_HANDLERS(RndGroup)
    HANDLE_ACTION(sort_draws, SortDraws())
    HANDLE_ACTION(add_object, AddObject(_msg->Obj<Hmx::Object>(2)))
    HANDLE_ACTION(remove_object, RemoveObject(_msg->Obj<Hmx::Object>(2)))
    HANDLE_ACTION(clear_objects, ClearObjects())
    HANDLE(get_draws, OnGetDraws)
    HANDLE_EXPR(has_object, mObjects.find(_msg->Obj<Hmx::Object>(2)) != mObjects.end())
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x29B)
END_HANDLERS

DataNode RndGroup::OnGetDraws(DataArray *) {
    DataArray *ret = new DataArray(mDraws.size() + 1);
    ret->Node(0) = NULL_OBJ;
    int idx = 0;
    FOREACH (it, mDraws) {
        ret->Node(++idx) = *it;
    }
    DataNode retNode(ret, kDataArray);
    ret->Release();
    return retNode;
}

BEGIN_PROPSYNCS(RndGroup)
    SYNC_PROP_MODIFY_ALT(objects, mObjects, Update())
    SYNC_PROP_STATIC(environ, mEnv)
    SYNC_PROP(draw_only, mDrawOnly)
    SYNC_PROP_MODIFY_ALT(lod, mLod, UpdateLODState())
    SYNC_PROP_MODIFY(lod_screen_size, mLodScreenSize, UpdateLODState()) {
        static Symbol _s("sort_in_world");
        if (sym == _s) {
            if (_op == kPropSet)
                mSortInWorld = _val.Int();
            else
                _val = mSortInWorld;
            return true;
        }
    }
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
