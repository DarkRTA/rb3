#include "world/Instance.h"
#include "math/Rot.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Utl.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Group.h"
#include "obj/ObjVersion.h"
#include "rndobj/Trans.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(WorldInstance)

void SharedGroup::TryPoll(WorldInstance *inst) {
    if (!mPollMaster)
        mPollMaster = inst;
    else if (mPollMaster != inst)
        return;
    for (std::list<RndPollable *>::iterator it = mPolls.begin(); it != mPolls.end();
         ++it) {
        (*it)->Poll();
    }
}

void SharedGroup::TryEnter(WorldInstance *inst) {
    if (!mPollMaster)
        mPollMaster = inst;
    else if (mPollMaster != inst)
        return;
    for (std::list<RndPollable *>::iterator it = mPolls.begin(); it != mPolls.end();
         ++it) {
        (*it)->Enter();
    }
    MsgSource *src = dynamic_cast<MsgSource *>(mPollMaster->Dir());
    if (src) {
        MsgSource *src2 = dynamic_cast<MsgSource *>(mGroup->Dir());
        if (src2)
            src2->ChainSource(src, 0);
    }
}

void SharedGroup::Draw(const Transform &tf) {
    mGroup->SetWorldXfm(tf);
    mGroup->Draw();
}

bool SharedGroup::Collide(const Transform &tf, const Segment &s, float &f, Plane &pl) {
    mGroup->SetWorldXfm(tf);
    return mGroup->Collide(s, f, pl);
}

float SharedGroup::DistanceToPlane(const Transform &tf, const Plane &pl, Vector3 &v) {
    mGroup->SetWorldXfm(tf);
    return mGroup->GetDistanceToPlane(pl, v);
}

bool SharedGroup::MakeWorldSphere(const Transform &tf, Sphere &s) {
    mGroup->SetWorldXfm(tf);
    return mGroup->MakeWorldSphere(s, true);
}

SharedGroup::SharedGroup(RndGroup *group) : mGroup(group), mPollMaster(this, 0) {
    AddPolls(group);
}

SharedGroup::~SharedGroup() {}

void SharedGroup::AddPolls(RndGroup *grp) {
    for (ObjPtrList<Hmx::Object, ObjectDir>::iterator it = grp->mObjects.begin();
         it != grp->mObjects.end();
         ++it) {
        RndPollable *poll = dynamic_cast<RndPollable *>(*it);
        if (poll)
            mPolls.push_back(poll);
        else {
            RndGroup *group = dynamic_cast<RndGroup *>(*it);
            if (group)
                AddPolls(group);
        }
    }
}

void SharedGroup::ClearPollMaster() { mPollMaster = 0; }

WorldInstance::WorldInstance() : mDir(), mSharedGroup(0), mSharedGroup2(0) {}

WorldInstance::~WorldInstance() {
    if (mSharedGroup2)
        mSharedGroup2->ClearPollMaster();
    delete mSharedGroup2;
}

void WorldInstance::Poll() {
    if (mSharedGroup)
        mSharedGroup->TryPoll(this);
    RndDir::Poll();
}

void WorldInstance::Enter() {
    if (mSharedGroup)
        mSharedGroup->TryEnter(this);
    RndDir::Enter();
}

void WorldInstance::DrawShowing() {
    RndDir::DrawShowing();
    if (mSharedGroup)
        mSharedGroup->Draw(WorldXfm());
}

RndDrawable *WorldInstance::CollideShowing(const Segment &s, float &f, Plane &pl) {
    if (RndDir::CollideShowing(s, f, pl))
        return this;
    else {
        if (mSharedGroup) {
            if (mSharedGroup->Collide(WorldXfm(), s, f, pl)) {
                return this;
            }
        }
        return 0;
    }
}

float WorldInstance::GetDistanceToPlane(const Plane &pl, Vector3 &v) {
    float dist = RndDir::GetDistanceToPlane(pl, v);
    if (mSharedGroup) {
        Vector3 v28;
        float grpdist = mSharedGroup->DistanceToPlane(WorldXfm(), pl, v28);
        if (dist > grpdist) {
            v = v28;
            dist = grpdist;
        }
    }
    return dist;
}

bool WorldInstance::MakeWorldSphere(Sphere &s, bool b) {
    if (b) {
        RndDir::MakeWorldSphere(s, true);
        if (mSharedGroup) {
            Sphere s28;
            mSharedGroup->MakeWorldSphere(WorldXfm(), s28);
            s.GrowToContain(s28);
        }
        return true;
    } else {
        Sphere &mysphere = mSphere;
        if (mysphere.GetRadius()) {
            Multiply(mysphere, WorldXfm(), s);
            return true;
        } else
            return false;
    }
}

SAVE_OBJ(WorldInstance, 0x10A)

void WorldInstance::PreSave(BinStream &bs) {}

void WorldInstance::LoadPersistentObjects(BinStream *bs) {
    if (IsProxy()) {
        if (gRev > 2) {
            // allocate more hashtable and stringtable space
            int hashSize, stringSize;
            *bs >> hashSize;
            *bs >> stringSize;
            hashSize *= 2;
            Reserve(hashSize, stringSize);
        }
        // create the persistent objects using their ClassName and Name
        // then push them into our persistent object list
        std::list<Hmx::Object *> objlist;
        int count;
        *bs >> count;
        while (count-- != 0) {
            Symbol objClassName;
            *bs >> objClassName;
            char objName[0x80];
            bs->ReadString(objName, 0x80);
#ifdef MILO_DEBUG
            if (!Hmx::Object::RegisteredFactory(objClassName)) {
                MILO_WARN("%s: Can't make %s", mStoredFile.c_str(), objClassName);
                DeleteObjects();
                return;
            }
#endif
            Hmx::Object *obj = Hmx::Object::NewObject(objClassName);
            obj->SetName(objName, this);
            objlist.push_back(obj);
        }

        String dirNameStr;
        ObjectDir *dirDir = nullptr;
        DataArray *dirTypeDef = nullptr;
        ObjDirPtr<ObjectDir> subDir;
        if (mDir) {
            dirNameStr = mDir->Name();
            dirDir = mDir->Dir();
            dirTypeDef = (DataArray *)mDir->TypeDef();
            subDir = mDir;
            AppendSubDir(subDir);
        }
        while (!objlist.empty()) {
            Hmx::Object *cur = objlist.front();
            cur->PreLoad(*bs);
            cur->PostLoad(*bs);
            objlist.pop_front();
        }
        if (mDir) {
            RemoveSubDir(subDir);
            mDir->SetName(dirNameStr.c_str(), dirDir);
            mDir->SetTypeDef(dirTypeDef);
        }
    }
}

void WorldInstance::DeleteTransientObjects() {
    if (!Dir() || Dir() == DirLoader::sTopSaveDir
        || Dir()->InlineSubDirType() != kInlineAlways) {
        DeleteObjects();
    } else
        for (ObjDirItr<Hmx::Object> obj(this, false); obj != 0; ++obj) {
            if (obj != this) {
                Hmx::Object *to = mDir->Find<Hmx::Object>(obj->Name(), true);
                MILO_ASSERT(obj->ClassName() == to->ClassName(), 0x1CB);
                std::vector<ObjRef *> refs;
                {
                    MemDoTempAllocations m(true, false);
                    refs = obj->mRefs;
                }
                std::vector<ObjRef *>::const_reverse_iterator it = refs.rbegin();
                std::vector<ObjRef *>::const_reverse_iterator itEnd = refs.rend();
                for (; it != itEnd; ++it) {
                    if ((*it)->RefOwner() && (*it)->RefOwner()->Dir() == this) {
                        (*it)->Replace(obj, to);
                    }
                }
                delete obj;
            }
        }
}

void WorldInstance::PostSave(BinStream &bs) { SyncDir(); }

BEGIN_COPYS(WorldInstance)
    COPY_SUPERCLASS(RndDir)
END_COPYS

BEGIN_LOADS(WorldInstance)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void WorldInstance::PreLoad(BinStream &bs) {
    if (IsProxy())
        DeleteObjects();
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    if (gRev != 0) {
        FilePath fp;
        bs >> fp;
        PreLoadInlined(fp, true, kInlineCachedShared);
    } else
        bs >> mDir;
    PushRev(packRevs(gAltRev, gRev), this);
    RndDir::PreLoad(bs);
    if (mProxyFile.length() != 0) {
        MILO_WARN(
            "WorldInstance %s was created as RndDir. Object needs to be deleted and recreated.",
            Name()
        );
    }
}

void WorldInstance::Replace(Hmx::Object *from, Hmx::Object *to) {
    RndDir::Replace(from, to);
}

void WorldInstance::PostLoad(BinStream &bs) {
    RndDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if (gRev != 0) {
        mDir = dynamic_cast<WorldInstance *>(PostLoadInlined().Ptr());
    } else
        mDir.PostLoad(0);
    if (gRev > 1)
        LoadPersistentObjects(&bs);
    SyncDir();
}

void WorldInstance::SetProxyFile(const FilePath &fp, bool override) {
    MILO_ASSERT(!override, 599);
    DeleteObjects();
    mDir.LoadFile(fp, false, true, kLoadFront, false);
    SyncDir();
    if (mDir) {
        Hmx::Object::Copy(mDir, kCopyShallow);
    }
}

#include "utl/ClassSymbols.h"

void WorldInstance::SyncDir() {
    if (IsProxy()) {
        DeleteTransientObjects();
        mSharedGroup = nullptr;
        if (mDir) {
            RndGroup *grp = mDir->Find<RndGroup>("shared.grp", false);
            if (!mDir->mSharedGroup2 && grp) {
                mDir->mSharedGroup2 = new SharedGroup(grp);
            }
            mSharedGroup = mDir->mSharedGroup2;
            Sphere sphere = mDir->mSphere;
            Vector3 v98;
            MakeScale(WorldXfm().m, v98);
            float f21 = Max(v98.y, v98.z);
            f21 = Max(v98.x, f21);
            if (f21 > 1.0f)
                sphere.radius *= f21;
            SetSphere(sphere);
            std::list<ObjPair> objPairs;
            objPairs.push_back(ObjPair(mDir, this));
            for (ObjDirItr<Hmx::Object> it(mDir, false); it != nullptr; ++it) {
                RndMesh *curMesh = dynamic_cast<RndMesh *>(&*it);
                if (!grp)
                    goto iterate;
                if (it != grp && !GroupedUnder(grp, it))
                    goto iterate;
                if (curMesh) {
                    grp->RemoveObject(it);
                    goto iterate;
                }
                continue;
            iterate:
                if (it->ClassName() == Tex || it->ClassName() == CubeTex
                    || it->ClassName() == SynthSample || it->ClassName() == Movie
                    || it == mDir)
                    continue;
                else {
                    EventTrigger *trig = dynamic_cast<EventTrigger *>(&*it);
                    if (trig && trig->HasTriggerEvents()) {
                        MILO_WARN("%s must be in shared.grp", PathName(it));
                    } else {
                        Hmx::Object *foundObj = FindObject(it->Name(), false);
                        if (!foundObj) {
                            foundObj = Hmx::Object::NewObject(it->ClassName());
                            bool deep = true;
                            if (it->ClassName() == Group)
                                deep = false;
                            CopyObject(it, foundObj, (Hmx::Object::CopyType)deep, true);
                        }
                        objPairs.push_back(ObjPair(foundObj, it));
                    }
                }
            }

            for (std::list<ObjPair>::iterator p = objPairs.begin(); p != objPairs.end();
                 ++p) {
                MILO_ASSERT(p->from->Dir(), 0x2CA);
                std::vector<ObjRef *> fromRefs = p->from->mRefs;
                std::vector<ObjRef *>::reverse_iterator it = fromRefs.rbegin();
                std::vector<ObjRef *>::reverse_iterator itEnd = fromRefs.rend();
                while (it != itEnd) {
                    if (!(*it)->RefOwner()->Dir()) {
                        (*it)->Replace(p->from, p->to);
                    }
                    ++it;
                }
            }

            Reserve(mDir->HashTableSize(), mDir->StrTableSize());

            for (std::list<ObjPair>::iterator p = objPairs.begin(); p != objPairs.end();
                 ++p) {
                if (p->to != this) {
                    p->to->SetName(p->from->Name(), this);
                }
            }

            if (f21 > 1.0f) {
                for (ObjDirItr<RndTransformable> it(this, true); it != nullptr; ++it) {
                    if (GenerationCount(this, it) > 0) {
                        RndDrawable *draw = dynamic_cast<RndDrawable *>(&*it);
                        if (draw) {
                            Sphere s = draw->mSphere;
                            s.radius *= f21;
                            draw->SetSphere(s);
                        }
                    }
                }
            }
        }
        SyncObjects();
    }
}

BEGIN_HANDLERS(WorldInstance)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x308)
END_HANDLERS

BEGIN_PROPSYNCS(WorldInstance)
    SYNC_PROP_MODIFY(instance_file, mDir, SyncDir())
    SYNC_PROP_SET(shared_group, mSharedGroup ? mSharedGroup->Group() : NULL_OBJ, )
    SYNC_PROP_SET(poll_master, mSharedGroup ? mSharedGroup->PollMaster() == 0 : 0, )
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS