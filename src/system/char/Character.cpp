#include "char/Character.h"
#include "char/CharUtl.h"
#include "char/CharacterTest.h"
#include "char/CharPollable.h"
#include "decomp.h"
#include "math/Mtx.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/Timer.h"
#include "rndobj/Anim.h"
#include "rndobj/Cam.h"
#include "rndobj/Env.h"
#include "rndobj/Mesh.h"
#include "rndobj/Poll.h"
#include "rndobj/Rnd.h"
#include "rndobj/ShadowMap.h"
#include "rndobj/Trans.h"
#include "utl/Std.h"
#include "rndobj/Utl.h"
#include "char/CharDriver.h"
#include "obj/ObjVersion.h"
#include "char/Waypoint.h"
#include "char/CharInterest.h"
#include "char/CharServoBone.h"
#include "char/CharEyes.h"
#include "utl/Str.h"
#include "utl/Symbols.h"

INIT_REVS(Character)

Character *gCharMe;
int CharPollableSorter::sSearchID;

DECOMP_FORCEACTIVE(Character, "ObjPtr_p.h", "f.Owner()", "")

BinStream &operator>>(BinStream &bs, Character::Lod &lod) {
    bs >> lod.mScreenSize;
    if (Character::gRev < 6) {
        lod.mScreenSize /= 0.75f;
    }
    if (gCharMe) {
        ObjPtrList<RndDrawable> draws(gCharMe);
        bs >> draws;
        lod.mGroup = gCharMe->New<RndGroup>(MakeString("group%x", (int)&lod));
        for (ObjPtrList<RndDrawable>::iterator it = draws.begin(); it != draws.end();
             ++it) {
            lod.mGroup->AddObject(*it);
        }
    } else {
        bs >> lod.mGroup;
        if (Character::gRev > 0xD) {
            bs >> lod.mTransGroup;
        }
    }
    return bs;
}

Character::Lod::Lod(Hmx::Object *obj)
    : mScreenSize(0.0f), mGroup(obj, 0), mTransGroup(obj, 0) {}

Character::Lod::Lod(const Character::Lod &lod)
    : mScreenSize(lod.mScreenSize), mGroup(lod.mGroup), mTransGroup(lod.mTransGroup) {}

Character::Lod &Character::Lod::operator=(const Character::Lod &lod) {
    mScreenSize = lod.mScreenSize;
    mGroup = lod.mGroup;
    mTransGroup = lod.mTransGroup;
    return *this;
}

// fn_8049C858 - charpollablesorter::sort
void CharPollableSorter::Sort(std::vector<RndPollable *> &polls) {
    std::vector<Dep *> deps;
    deps.reserve(polls.size());
    for (int i = polls.size() - 1, last = i; i >= 0; i--) {
        CharPollable *c = dynamic_cast<CharPollable *>(polls[i]);
        if (c) {
            Dep &dep = mDeps[c];
            dep.obj = c;
            dep.poll = c;
            deps.push_back(&dep);
        } else {
            polls[last--] = polls[i];
        }
    }
    if (deps.empty())
        return;
    else {
        std::sort(deps.begin(), deps.end(), CharPollableSorter::AlphaSort());
        std::list<Dep *> depList;
        for (int i = 0; i < deps.size(); i++)
            depList.push_back(deps[i]);
        while (!depList.empty()) {
            Dep *curDep = depList.back();
            depList.pop_back();
            CharPollable *c = dynamic_cast<CharPollable *>(curDep->obj);
            if (c) {
                std::list<Hmx::Object *> depList1;
                std::list<Hmx::Object *> depList2;
                c->PollDeps(depList1, depList2);
                AddDeps(curDep, depList1, depList, true);
                AddDeps(curDep, depList2, depList, false);
            }
            RndTransformable *t = dynamic_cast<RndTransformable *>(curDep->obj);
            if (t) {
                std::list<Hmx::Object *> tDepList;
                tDepList.push_back(t->TransParent());
                AddDeps(curDep, tDepList, depList, true);
            }
        }

        std::list<Dep *> otherDepList;
        for (int i = 0; i < deps.size(); i++) {
            Dep *curDep = deps[i];
            std::list<Dep *>::iterator it = otherDepList.begin();
            for (; it != otherDepList.end(); ++it) {
                if (ChangedBy(curDep, *it))
                    break;
            }
            otherDepList.insert(it, curDep);
        }

        int idx = 0;
        for (std::list<Dep *>::iterator it = otherDepList.begin();
             it != otherDepList.end();
             ++it) {
            polls[idx++] = (*it)->poll;
        }
    }
}

bool CharPollableSorter::ChangedBy(Dep *d1, Dep *d2) {
    if (d1 == d2)
        return false;
    sSearchID++;
    mTarget = d1;
    return ChangedByRecurse(d2);
}

bool CharPollableSorter::ChangedByRecurse(Dep *d) {
    if (!d)
        return false;
    else if (d == mTarget)
        return true;
    else if (d->searchID == sSearchID)
        return false;
    else {
        d->searchID = sSearchID;
        for (std::list<Dep *>::iterator it = d->changedBy.begin();
             it != d->changedBy.end();
             ++it) {
            if (ChangedByRecurse(*it))
                return true;
        }
        return false;
    }
}

// fn_8049DD04
void CharPollableSorter::AddDeps(
    Dep *me, const std::list<Hmx::Object *> &odeps, std::list<Dep *> &toDo, bool changedBy
) {
    for (std::list<Hmx::Object *>::const_iterator it = odeps.begin(); it != odeps.end();
         ++it) {
        Hmx::Object *cur = *it;
        if (cur) {
            Dep *mapDep = &mDeps[cur];
            if (!mapDep->obj) {
                mapDep->obj = cur;
                toDo.push_back(mapDep);
            }
            if (changedBy) {
                me->changedBy.push_back(mapDep);
            } else {
                mapDep->changedBy.push_back(me);
            }
        }
    }
}

void Character::Init() { Register(); }
void Character::Terminate() {}

Character::Character()
    : mLods(this), mLastLod(0), mMinLod(0), mShadow(this), mTransGroup(this), mDriver(0),
      mSelfShadow(0), mSpotCutout(0), mFloorShadow(1), mSphereBase(this, this),
      mBounding(), mPollState(kCharCreated), mTest(new CharacterTest(this)), mFrozen(0),
      mDrawMode(kCharDrawAll), mTeleported(1), mInterestToForce(), unk1fc(this)
#ifdef MILO_DEBUG
      ,
      mDebugDrawInterestObjects(0)
#endif
{
}

Character::~Character() {
    UnhookShadow();
    delete mTest;
}

void Character::Enter() {
    mPollState = kCharEntered;
    mMinLod = -1;
    mFrozen = false;
    mLastLod = 0;
    mTeleported = true;
    mInterestToForce = Symbol();
    RndDir::Enter();
}

void Character::Exit() {
    mPollState = kCharExited;
    RndDir::Exit();
}

void Character::Poll() {
    START_AUTO_TIMER("char_poll");
    if (!mFrozen) {
        if (LOADMGR_EDITMODE)
            mTest->Poll();
        RndDir::Poll();
        mTeleported = false;
        mPollState = kCharPolled;
    }
}

void Character::DrawLodOrShadow(int lod, Character::DrawMode mode) {
    bool oldUpdate = RndMesh::sUpdateApproxLight;
    RndMesh::SetUpdateApproxLight(false);
    if (mode & 1 && RndEnviron::sCurrent) {
        Sphere s48;
        if (MakeWorldSphere(s48, false) && s48.GetRadius() > 0) {
            RndEnviron::sCurrent->UpdateApproxLighting(&s48.center, nullptr);
        }
    }
    if (mode == 1) {
        unk1fc = RndEnviron::sCurrent;
        unk208 = RndEnviron::CurrentPos();
    }
    mPollState = (PollState)5;
    if (mode == 4 && mShadow) {
        mShadow->DrawShowing();
    } else {
        mLastLod = Clamp<int>(0, mLods.size() - 1, lod);
        Lod *curLod = mLods.size() != 0 ? &mLods[mLastLod] : nullptr;
        if (mode & 5) {
            RndDir::DrawShowing();
            if (curLod && curLod->Group()) {
                curLod->Group()->DrawShowing();
            }
        }
        if (mode & 2 && (mTransGroup || (curLod && curLod->TransGroup()))) {
            if (mode == 2) {
                RndEnvironTracker tracker(unk1fc, unk208);
                if (mTransGroup)
                    mTransGroup->DrawShowing();
                if (curLod && curLod->TransGroup()) {
                    curLod->TransGroup()->DrawShowing();
                }
            } else {
                if (mTransGroup)
                    mTransGroup->DrawShowing();
                if (curLod && curLod->TransGroup()) {
                    curLod->TransGroup()->DrawShowing();
                }
            }
        }
    }
    RndMesh::SetUpdateApproxLight(oldUpdate);
}

void Character::DrawLod(int lod) {
    unsigned char drawMode = mDrawMode & 1;
    if (TheRnd->DrawMode() != 4 && (TheRnd->DrawMode() != 2 || (mSpotCutout && drawMode))
        && (TheRnd->DrawMode() != 3 || mFloorShadow && drawMode)) {
        DrawLodOrShadow(
            lod,
            TheRnd->DrawMode() == 2 || TheRnd->DrawMode() == 3 || TheRnd->DrawMode() == 1
                ? (DrawMode)4
                : mDrawMode
        );
    }
}

CharEyes *Character::GetEyes() { return Find<CharEyes>("CharEyes.eyes", false); }

void Character::DrawShowing() {
    START_AUTO_TIMER("char_draw");
    float screenSize = ComputeScreenSize(RndCam::sCurrent);
    int i7;
    if (mMinLod < 0) {
        for (i7 = 0; i7 < (int)mLods.size() - 1; i7++) {
            float f1;
            if (i7 < mLastLod)
                f1 = 0.09f;
            else
                f1 = -0.09f;
            if (screenSize >= (f1 + 1.0f) * mLods[i7].mScreenSize)
                break;
        }
    } else {
        i7 = Clamp<int>(0, mLods.size() - 1, mMinLod);
    }
    bool b2 = false;
    if (mSelfShadow && TheRnd->DrawMode() == 0 && i7 <= 1 && mDrawMode & 1) {
        b2 = true;
    }
    if (b2) {
        int lastMinLod = mMinLod;
        mMinLod = i7;
        RndShadowMap::PrepShadow(this, mEnv);
        mMinLod = lastMinLod;
    }
    DrawLod(i7);
    if (b2)
        RndShadowMap::EndShadow();
}

DECOMP_FORCEACTIVE(Character, "character.show_name", "bone_head")

void Character::UpdateSphere() {
    Sphere s78 = mBounding;
    Transform tf38;
    FastInvert(WorldXfm(), tf38);
    Transform tf68;
    Multiply(mSphereBase->WorldXfm(), tf38, tf68);
    FastInvert(tf68, tf68);
    Multiply(s78, tf68, s78);
    SetSphere(s78);
}

void Character::CalcBoundingSphere() {
    Transform tf50(mLocalXfm);
    DirtyLocalXfm().Reset();
    mBounding.Zero();
    static const char *boneNames[5] = { "bone_head.mesh",
                                        "bone_R-ankle.mesh",
                                        "bone_L-ankle.mesh",
                                        "bone_R-toe.mesh",
                                        "bone_L-toe.mesh" };
    for (int i = 0; i < 5; i++) {
        RndTransformable *t = Find<RndTransformable>(boneNames[i], false);
        if (t) {
            mBounding.GrowToContain(Sphere(t->WorldXfm().v, 0.1f));
        }
    }

    RndTransformable *transLClavicle = CharUtlFindBoneTrans("bone_L-clavicle", this);
    if (transLClavicle) {
        RndTransformable *transLHand = CharUtlFindBoneTrans("bone_L-hand", this);
        if (transLHand) {
            Vector3 vClavicle = transLClavicle->WorldXfm().v;
            vClavicle.z += Distance(vClavicle, transLHand->WorldXfm().v);
            mBounding.GrowToContain(Sphere(vClavicle, 7.0f));
        }
    }
    RndTransformable *transRClavicle = CharUtlFindBoneTrans("bone_R-clavicle", this);
    if (transRClavicle) {
        RndTransformable *transRHand = CharUtlFindBoneTrans("bone_R-hand", this);
        if (transRHand) {
            Vector3 vClavicle = transRClavicle->WorldXfm().v;
            vClavicle.z += Distance(vClavicle, transRHand->WorldXfm().v);
            mBounding.GrowToContain(Sphere(vClavicle, 7.0f));
        }
    }
    if (mBounding.GetRadius() == 0) {
        for (ObjDirItr<RndTransformable> it(this, true); it != nullptr; ++it) {
            if (strncmp(it->Name(), "bone_", 5) == 0
                || strncmp(it->Name(), "spot_", 5) == 0) {
                mBounding.GrowToContain(Sphere(it->WorldXfm().v, 0.1f));
            }
            RndMesh *mesh = dynamic_cast<RndMesh *>(&*it);
            if (mesh && mesh->Showing()) {
                for (int i = 0; i < mesh->Verts().size(); i++) {
                    mBounding.GrowToContain(
                        Sphere(mesh->SkinVertex(mesh->Verts(i), nullptr), 0.001f)
                    );
                }
            }
        }
    }
    UpdateSphere();
    DirtyLocalXfm() = tf50;
}

bool Character::MakeWorldSphere(Sphere &s, bool b) {
    if (b) {
        s = mBounding;
        return true;
    } else {
        Sphere &mySphere = mSphere;
        if (mySphere.GetRadius()) {
            Multiply(mySphere, mSphereBase->WorldXfm(), s);
            return true;
        } else
            return false;
    }
}

void Character::SetSphereBase(RndTransformable *trans) {
    if (!trans)
        trans = this;
    Sphere s18;
    MakeWorldSphere(s18, false);
    Multiply(trans->WorldXfm(), s18.center, s18.center);
    SetSphere(s18);
    mSphereBase = trans;
}

void Character::SetShadow(RndGroup *shadow) {
    if (shadow != mShadow) {
        MILO_ASSERT(!shadow || shadow->Dir() == this, 699);
        if (mShadow) {
            mDraws.push_back(mShadow);
        }
        mShadow = shadow;
        VectorRemove(mDraws, mShadow);
    }
}

void Character::DrawShadow(const Transform &tf, const Plane &pl) {
    if (Showing() && mShadow && mShadow->Showing()) {
        MILO_ASSERT(GetGfxMode() == kOldGfx, 0x2CB);
        Transform tf40;
        Transpose(tf, tf40);
        Plane plb0;
        Multiply(pl, tf40, plb0);
        Transform tf70;
        tf70.m.Set(1, -plb0.a / plb0.b, 0, 0, 0, 0, 0, -plb0.c / plb0.b, 1);
        tf70.v.Set(0, -plb0.d / plb0.b, 0);
        Transform tfa0;
        Multiply(tf40, tf70, tfa0);
        Multiply(tfa0, tf, tfa0);
        for (int i = 0; i < mShadowBones.size(); i++) {
            ShadowBone *cur = mShadowBones[i];
            Multiply(cur->Parent()->WorldXfm(), tfa0, cur->DirtyLocalXfm());
        }
        mShadow->DrawShowing();
    }
}

#pragma push
#pragma force_active on
inline CharServoBone *Character::BoneServo() {
    if (mDriver)
        return dynamic_cast<CharServoBone *>(mDriver->GetBones());
    else
        return nullptr;
}
#pragma pop

void Character::Teleport(Waypoint *way) {
    if (way) {
        Transform tf38(way->WorldXfm());
        Normalize(tf38.m, tf38.m);
        SetLocalXfm(tf38);
    }
    if (BoneServo()) {
        BoneServo()->SetRegulateWaypoint(way);
    }
    mTeleported = true;
}

void Character::FindInterestObjects(ObjectDir *dir) {
    if (dir) {
        Timer timer;
        timer.Restart();
        CharEyes *eyes = GetEyes();
        if (eyes) {
            eyes->ClearAllInterestObjects();
            for (ObjDirItr<CharInterest> it(dir, true); it != nullptr; ++it) {
                if (ValidateInterest(it, dir)) {
                    eyes->AddInterestObject(it);
                }
            }
            for (ObjDirItr<Character> it(dir, true); it != nullptr; ++it) {
                if (!streq(it->Name(), Name())) {
                    for (ObjDirItr<CharInterest> it2(it, true); it2 != nullptr; ++it2) {
                        if (ValidateInterest(it2, it)) {
                            eyes->AddInterestObject(it2);
                        }
                    }
                }
            }
        }
    }
}

void Character::SetInterestObjects(
    const ObjPtrList<CharInterest, ObjectDir> &oList, ObjectDir *dir
) {
    CharEyes *eyes = GetEyes();
    if (eyes) {
        eyes->ClearAllInterestObjects();
        for (ObjPtrList<CharInterest, ObjectDir>::iterator it = oList.begin();
             it != oList.end();
             it++) {
            if (ValidateInterest(*it, dir ? dir : (*it)->Dir()))
                eyes->AddInterestObject(*it);
        }
    }
}

void Character::ForceBlink() {
    CharEyes *eyes = GetEyes();
    if (eyes)
        eyes->ForceBlink();
}

void Character::EnableBlinks(bool b1, bool b2) {
    CharEyes *eyes = GetEyes();
    if (eyes)
        eyes->SetEnableBlinks(b1, b2);
}

bool Character::SetFocusInterest(CharInterest *interest, int i) {
    CharEyes *eyes = GetEyes();
    if (eyes)
        return eyes->SetFocusInterest(interest, i);
    else
        return false;
}

bool Character::SetFocusInterest(Symbol s, int iii) {
    CharEyes *eyes = GetEyes();
    if (eyes) {
        CharInterest *interest = nullptr;
        for (int i = 0; i < eyes->NumInterests(); i++) {
            if (s == eyes->GetInterest(i)->Name()) {
                interest = eyes->GetInterest(i);
                break;
            }
        }
        if (!s.Null() && !interest) {
            MILO_WARN("Couldn't find interest named %s to force on %s", s.Str(), Name());
        }
        return SetFocusInterest(interest, iii);
    } else
        return false;
}

void Character::SetInterestFilterFlags(int flags) {
    CharEyes *eyes = GetEyes();
    if (eyes) {
        eyes->SetInterestFilterFlags(flags);
    }
}

void Character::ClearInterestFilterFlags() {
    CharEyes *eyes = GetEyes();
    if (eyes) {
        eyes->ClearInterestFilterFlags();
    }
}

float Character::ComputeScreenSize(RndCam *cam) {
    Sphere sphere;
    MakeWorldSphere(sphere, false);
    if (cam && cam->CompareSphereToWorld(sphere)) {
        return 0;
    } else {
        float ret = 1.0f;
        sphere.radius = 1.0f;
        if (cam)
            ret = cam->CalcScreenHeight(sphere);
        return ret;
    }
}

ShadowBone *Character::AddShadowBone(RndTransformable *trans) {
    if (!trans)
        return 0;
    else {
        for (int i = 0; i < mShadowBones.size(); i++) {
            if (mShadowBones[i]->Parent() == trans)
                return mShadowBones[i];
        }
        mShadowBones.push_back(new ShadowBone());
        mShadowBones.back()->SetParent(trans);
        return mShadowBones.back();
    }
}

void Character::UnhookShadow() {
    for (int i = 0; i < mShadowBones.size(); i++) {
        ShadowBone *cur = mShadowBones[i];
        const std::vector<ObjRef *> &refs = cur->Refs();
        while (!refs.empty()) {
            ObjRef *curRef = refs.back();
            curRef->Replace(cur, cur->Parent());
        }
    }
    DeleteAll(mShadowBones);
}

void Character::Replace(Hmx::Object *from, Hmx::Object *to) {
    RndDir::Replace(from, to);
    if (from == mSphereBase) {
        mSphereBase = dynamic_cast<RndTransformable *>(to);
        if (!mSphereBase)
            mSphereBase = this;
    }
}

void Character::SyncShadow() {
    UnhookShadow();
    if (mShadow) {
#ifdef MILO_DEBUG
        if (GetGfxMode() == kOldGfx) {
#endif
            std::vector<RndDrawable *> &draws = mShadow->mDraws;
            for (std::vector<RndDrawable *>::iterator it = draws.begin();
                 it != draws.end();
                 ++it) {
                RndMesh *mesh = dynamic_cast<RndMesh *>(*it);
                if (mesh) {
                    if (mesh->NumBones() != 0) {
                        for (int i = 0; i < mesh->NumBones(); i++) {
                            mesh->SetBone(i, AddShadowBone(mesh->BoneTransAt(i)), false);
                        }
                    } else {
                        mesh->SetTransParent(AddShadowBone(mesh->TransParent()), false);
                    }
                }
            }
#ifdef MILO_DEBUG
        }
#endif
        VectorRemove(mDraws, mShadow);
    }
}

void Character::SyncObjects() {
    mPollState = kCharSyncObject;
    if (Find<RndMesh>("bone_pelvis.mesh", false))
        ConvertBonesToTranses(this, false);
    RndDir::SyncObjects();
    VectorRemove(mDraws, mTransGroup);
    for (int i = 0; i < mLods.size(); i++) {
        VectorRemove(mDraws, mLods[i].Group());
        VectorRemove(mDraws, mLods[i].TransGroup());
    }
    SyncShadow();
    CharPollableSorter sorter;
    sorter.Sort(mPolls);
}

void Character::RemoveFromPoll(RndPollable *poll) { VectorRemove(mPolls, poll); }

void Character::AddedObject(Hmx::Object *o) {
    if (dynamic_cast<CharPollable *>(o)) {
        CharDriver *driver = dynamic_cast<CharDriver *>(o);
        if (driver) {
            if (streq(driver->Name(), "main.drv")) {
                mDriver = driver;
            }
        }
    }
}

void Character::RemovingObject(Hmx::Object *o) {
    if (o == mDriver)
        mDriver = 0;
    RndDir::RemovingObject(o);
}

void Character::CopyBoundingSphere(Character *c) {
    SetSphere(c->mSphere);
    mBounding = c->mBounding;
    if (c->mSphereBase)
        mSphereBase = c->mSphereBase;
    else
        mSphereBase = 0;
}

void Character::RepointSphereBase(ObjectDir *dir) {
    if (mSphereBase) {
        RndTransformable *trans = dir->Find<RndTransformable>(mSphereBase->Name(), false);
        if (trans)
            mSphereBase = trans;
    }
}

void Character::PreSave(BinStream &bs) { UnhookShadow(); }
SAVE_OBJ(Character, 0x495)

void Character::PreLoad(BinStream &bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(0x11, 0);
    if (gRev > 1) {
        RndDir::PreLoad(bs);
        if (gRev < 7)
            SetRate(k1_fpb);
    } else {
        int somerev;
        bs >> somerev;
        if (somerev > 3) {
            RndTransformable::Load(bs);
            RndDrawable::Load(bs);
        }
        ObjectDir::PreLoad(bs);
        PushRev(somerev, this);
    }
    PushRev(packRevs(gAltRev, gRev), this);
}

#pragma push
#pragma dont_inline on
void Character::PostLoad(BinStream &bs) {
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    int oldRev = gRev;
    if (gRev > 1) {
        RndDir::PostLoad(bs);
        gRev = oldRev;
        if (gRev < 4 || !IsProxy()) {
            if (gRev < 9) {
                ObjVector<ObjVector<Character::Lod> > ovec(this);
                bs >> ovec;
                if (ovec.size() != 0)
                    mLods = ovec[0];
                else
                    mLods.clear();
            } else
                bs >> mLods;
            bs >> mShadow;
            if (gRev > 2)
                bs >> mSelfShadow;
            else
                mSelfShadow = false;
            if (gRev > 4) {
                ObjPtr<RndTransformable, ObjectDir> tPtr(this, 0);
                bs >> tPtr;
                mSphereBase = tPtr.Ptr();
            } else
                mSphereBase = this;
            if (gRev > 0xA)
                bs >> mBounding;
            else
                mBounding.Zero();
            if (gRev < 0xC) {
                if (mSphereBase == this) {
                    float rad = mBounding.GetRadius();
                    if (rad == 0.0f) {
                        if (GetSphere().GetRadius() != 0.0f) {
                            Multiply(GetSphere(), mSphereBase->WorldXfm(), mBounding);
                        }
                    }
                }
            }
            if (gRev > 0xC)
                bs >> mFrozen;
            if (gRev > 0xE)
                bs >> mMinLod;
            if (gRev > 0x10)
                bs >> mTransGroup;
            if (gRev > 9)
                mTest->Load(bs);
        } else if (gRev > 0xF)
            mTest->Load(bs);
    } else {
        int otherrev = PopRev(this);
        int oldotherrev = gRev;
        ObjectDir::PostLoad(bs);
        gRev = oldotherrev;
        if (otherrev > 4)
            bs >> mEnv;
        if (otherrev > 3) {
            gCharMe = otherrev < 6 ? this : 0;
            ObjVector<ObjVector<Character::Lod> > ovec(this);
            bs >> ovec;
            if (ovec.size() != 0)
                mLods = ovec[0];
            else
                mLods.clear();
            if (gCharMe) {
                for (int i = 0; i < mLods.size(); i++) {
                    RndGroup *grp = mLods[i].Group();
                    grp->SetName(MakeString("lod%d.grp", i), this);
                }
            }
            gCharMe = 0;
        } else
            mLods.clear();
        if (otherrev > 6)
            bs >> mShadow;
    }
    if (gRev < 8) {
        float rad = GetSphere().GetRadius();
        for (int i = 0; i < mLods.size(); i++) {
            mLods[i].SetScreenSize(mLods[i].ScreenSize() / rad);
        }
    }
}
#pragma pop

BEGIN_COPYS(Character)
    COPY_SUPERCLASS(RndDir)
    CREATE_COPY(Character)
    BEGIN_COPYING_MEMBERS
        if (ty != kCopyFromMax) {
            COPY_MEMBER(mLods)
            COPY_MEMBER(mLastLod)
            COPY_MEMBER(mMinLod)
            COPY_MEMBER(mShadow)
            COPY_MEMBER(mDriver)
            COPY_MEMBER(mSelfShadow)
            COPY_MEMBER(mSphereBase)
            COPY_MEMBER(mFrozen)
            COPY_MEMBER(mMinLod)
            COPY_MEMBER(mTransGroup)
        }
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(Character)
    HANDLE_ACTION(teleport, Teleport(_msg->Obj<Waypoint>(2)))
    HANDLE(play_clip, OnPlayClip)
    HANDLE_ACTION(calc_bounding_sphere, CalcBoundingSphere())
    HANDLE(copy_bounding_sphere, OnCopyBoundingSphere)
    HANDLE_ACTION(find_interest_objects, FindInterestObjects(_msg->Obj<ObjectDir>(2)))
    HANDLE_ACTION(force_interest, SetFocusInterest(_msg->Obj<CharInterest>(2), false))
    HANDLE_ACTION(force_interest_named, SetFocusInterest(_msg->Sym(2), 0))
    HANDLE_ACTION_IF_ELSE(
        enable_blink,
        _msg->Size() > 3,
        EnableBlinks(_msg->Int(2), _msg->Int(3)),
        EnableBlinks(_msg->Int(2), false)
    )
#ifdef MILO_DEBUG
    HANDLE(list_interest_objects, OnGetCurrentInterests)
    HANDLE_MEMBER_PTR(mTest)
#endif
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x57B)
END_HANDLERS

DataNode Character::OnCopyBoundingSphere(DataArray *da) {
    Character *c = da->Obj<Character>(2);
    if (c)
        CopyBoundingSphere(c);
    return DataNode(0);
}

DataNode Character::OnPlayClip(DataArray *msg) {
    if (mDriver) {
        int playint = msg->Size() > 3 ? msg->Int(3) : 4;
        MILO_ASSERT(msg->Size()<=4, 0x58B);
        return DataNode(mDriver->Play(msg->Node(2), playint, -1.0f, 1e+30f, 0.0f) != 0);
    } else
        return DataNode(0);
}

#ifdef MILO_DEBUG
void Character::SetDebugDrawInterestObjects(bool b) { mDebugDrawInterestObjects = b; }
#endif

DataNode Character::OnGetCurrentInterests(DataArray *da) {
    int size = 0;
    CharEyes *eyes = GetEyes();
    if (eyes)
        size = eyes->mInterests.size();
    DataArrayPtr ptr;
    ptr->Resize(size + 1);
    ptr->Node(0) = Symbol();
    for (int i = 0; i < size; i++) {
        ptr->Node(i + 1) = Symbol(eyes->GetInterest(i)->Name());
    }
    return ptr;
}

BEGIN_CUSTOM_PROPSYNC(Character::Lod)
    SYNC_PROP(screen_size, o.mScreenSize)
    SYNC_PROP(group, o.mGroup)
    SYNC_PROP(trans_group, o.mTransGroup)
END_CUSTOM_PROPSYNC

#include "utl/ClassSymbols.h"
BEGIN_PROPSYNCS(Character)
    SYNC_PROP_SET(sphere_base, mSphereBase, SetSphereBase(_val.Obj<RndTransformable>()))
    SYNC_PROP(lods, mLods)
    SYNC_PROP(force_lod, mMinLod)
    SYNC_PROP(trans_group, mTransGroup)
    SYNC_PROP(self_shadow, mSelfShadow)
    SYNC_PROP(bounding, mBounding)
    SYNC_PROP(frozen, mFrozen)
    SYNC_PROP_SET(shadow, mShadow, SetShadow(_val.Obj<RndGroup>()))
    SYNC_PROP_SET(driver, mDriver, )
    SYNC_PROP_MODIFY(
        interest_to_force, mInterestToForce, SetFocusInterest(mInterestToForce, 0)
    )
#ifdef MILO_DEBUG
    SYNC_PROP(debug_draw_interest_objects, mDebugDrawInterestObjects)
    SYNC_PROP(CharacterTesting, *mTest)
#endif
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS
