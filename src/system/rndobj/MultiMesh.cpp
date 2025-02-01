#include "rndobj/MultiMesh.h"
#include "math/Color.h"
#include "math/Mtx.h"
#include "math/Rot.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMeshProxy.h"
#include "rndobj/Utl.h"
#include "stl/_pair.h"
#include "types.h"
#include "utl/BinStream.h"
#include "utl/Loader.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/TextStream.h"
#include <list>

INIT_REVS(RndMultiMesh)
std::list<std::pair<RndMultiMeshProxy *, int> > RndMultiMesh::sProxyPool;

void RndMultiMesh::Terminate() {
    for (std::list<std::pair<RndMultiMeshProxy *, int> >::iterator it =
             sProxyPool.begin();
         it != sProxyPool.end();
         ++it)
        delete it->first;
}

BEGIN_COPYS(RndMultiMesh)
    CREATE_COPY_AS(RndMultiMesh, f)
    MILO_ASSERT(f, 38);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    if (ty != kCopyFromMax)
        COPY_MEMBER_FROM(f, mMesh)
    COPY_MEMBER_FROM(f, mInstances)
    UpdateMesh();
END_COPYS

void RndMultiMesh::Print() {
    TextStream &ts = TheDebug;
    ts << "   mesh: " << mMesh << "\n";
    ts << "   instances: " << mInstances << "\n";
}

RndMultiMesh::Instance::Instance() { mXfm.Reset(); }

void RndMultiMesh::Instance::LoadRev(BinStream &bs, int rev) {
    bs >> mXfm;
    if (rev < 3) {
        Hmx::Color col;
        bs >> col;
    } else if (rev < 4) {
        std::vector<Hmx::Color> cols;
        bs >> cols;
    }
}

void RndMultiMesh::Instance::Load(BinStream &bs) { LoadRev(bs, RndMultiMesh::gRev); }

SAVE_OBJ(RndMultiMesh, 0x66)

BEGIN_LOADS(RndMultiMesh)
    LOAD_REVS(bs)
    ASSERT_REVS(4, 0)
    if (gRev != 0)
        LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndDrawable)
    bs >> mMesh;
    if (gRev < 2) {
        std::list<Transform> xfms;
        bs >> xfms;
        mInstances.clear();
        for (std::list<Transform>::iterator it = xfms.begin(); it != xfms.end(); ++it) {
            mInstances.push_back(Instance(*it));
        }
    } else {
        bs >> mInstances;
        if (gRev < 4) {
            u8 dump;
            bs >> dump;
        }
    }
END_LOADS

void RndMultiMesh::InvalidateProxies() {
    if (LOADMGR_EDITMODE) {
        for (std::list<std::pair<RndMultiMeshProxy *, int> >::iterator it =
                 sProxyPool.begin();
             it != sProxyPool.end();
             ++it) {
            if (it->first->mMultiMesh == this) {
                it->first->SetMultiMesh(0, 0);
            }
        }
    } else
        MILO_ASSERT(sProxyPool.empty(), 0xA7);
}

void RndMultiMesh::CollideList(const Segment &seg, std::list<Collision> &colls) {
    static int stamp = 0;
    if (LOADMGR_EDITMODE && CollideSphere(seg)) {
        stamp++;
        if (mMesh) {
            for (std::list<RndMultiMesh::Instance>::iterator it = mInstances.begin();
                 it != mInstances.end();
                 ++it) {
                mMesh->SetWorldXfm((*it).mXfm);
                float f;
                Plane pl;
                if (mMesh->CollideShowing(seg, f, pl)) {
                    RndMultiMeshProxy *proxy = nullptr;
                    for (std::list<std::pair<RndMultiMeshProxy *, int> >::iterator sit =
                             sProxyPool.begin();
                         sit != sProxyPool.end();
                         ++sit) {
                        proxy = sit->first;
                        if (proxy->mMultiMesh == this && proxy->mIndex == it)
                            break;
                    }
                    RndMultiMeshProxy *proxy00 = proxy;
                    if (!proxy) {
                        for (std::list<std::pair<RndMultiMeshProxy *, int> >::iterator
                                 sit = sProxyPool.begin();
                             sit != sProxyPool.end();
                             ++sit) {
                            if (stamp != sit->second) {
                                proxy00 = sit->first;
                                if (!proxy00->TransChildren().size()) {
                                    sit->second = stamp;
                                    break;
                                }
                            }
                        }
                    }
                    if (!proxy00) {
                        RndMultiMeshProxy *new_proxy =
                            Hmx::Object::New<RndMultiMeshProxy>();
                        sProxyPool.push_front(std::make_pair(new_proxy, stamp));
                        new_proxy->SetMultiMesh(this, it);
                        colls.push_back(Collision(new_proxy, f, pl));
                    }
                }
            }
        }
    }
}

void RndMultiMesh::DrawShowing() {
    if (mMesh) {
        for (std::list<RndMultiMesh::Instance>::const_iterator it = mInstances.begin();
             it != mInstances.end();
             ++it) {
            mMesh->SetWorldXfm(it->mXfm);
            mMesh->DrawShowing();
        }
    }
}

void RndMultiMesh::Mats(std::list<RndMat *> &mats, bool) {
    if (mMesh && mMesh->Mat()) {
        mMesh->Mat()->SetShaderOpts(GetDefaultMatShaderOpts(this, mMesh->Mat()));
        mats.push_back(mMesh->Mat());
    }
}

void RndMultiMesh::ListDrawChildren(std::list<RndDrawable *> &draws) {
    if (mMesh)
        draws.push_back(mMesh);
}

void RndMultiMesh::UpdateSphere() {
    Sphere s;
    MakeWorldSphere(s, true);
    SetSphere(s);
}

float RndMultiMesh::GetDistanceToPlane(const Plane &pl, Vector3 &vout) {
    if (mInstances.empty())
        return 0;
    else {
        float ret = 0;
        if (mMesh) {
            for (std::list<RndMultiMesh::Instance>::iterator it = mInstances.begin();
                 it != mInstances.end();
                 ++it) {
                mMesh->SetWorldXfm(it->mXfm);
                Vector3 vtmp;
                float dist = mMesh->GetDistanceToPlane(pl, vtmp);
                if (std::fabs(dist) < std::fabs(ret)) {
                    vout = vtmp;
                    ret = dist;
                }
            }
        }
        return ret;
    }
}

bool RndMultiMesh::MakeWorldSphere(Sphere &s, bool b) {
    if (b) {
        s.Zero();
        if (mMesh) {
            Sphere mySphere;
            mMesh->MakeWorldSphere(mySphere, true);
            Transform tf38;
            FastInvert(mMesh->WorldXfm(), tf38);
            Multiply(mySphere, tf38, mySphere);
            for (std::list<RndMultiMesh::Instance>::const_iterator it =
                     mInstances.begin();
                 it != mInstances.end();
                 ++it) {
                Sphere sGrow;
                Multiply(mySphere, it->mXfm, sGrow);
                s.GrowToContain(sGrow);
            }
        }
        return true;
    } else {
        if (mSphere.GetRadius()) {
            s = mSphere;
            return true;
        } else
            return false;
    }
}

RndMultiMesh::RndMultiMesh() : mMesh(this) { mModulateColor = 0; }

void RndMultiMesh::SetMesh(RndMesh *mesh) {
    mMesh = mesh;
    UpdateMesh();
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(RndMultiMesh)
    HANDLE(move_xfms, OnMoveXfms)
    HANDLE(scale_xfms, OnScaleXfms)
    HANDLE(sort_xfms, OnSortXfms)
    HANDLE(random_xfms, OnRandomXfms)
    HANDLE(scramble_xfms, OnScrambleXfms)
    HANDLE(distribute, OnDistribute)
    HANDLE(get_pos, OnGetPos)
    HANDLE(set_pos, OnSetPos)
    HANDLE(get_rot, OnGetRot)
    HANDLE(set_rot, OnSetRot)
    HANDLE(get_scale, OnGetScale)
    HANDLE(set_scale, OnSetScale)
    HANDLE(mesh, OnMesh)
    HANDLE(add_xfm, OnAddXfm)
    HANDLE(add_xfms, OnAddXfms)
    HANDLE(remove_xfm, OnRemoveXfm)
    HANDLE(num_xfms, OnNumXfms)
    HANDLE_ACTION(set_mesh, SetMesh(_msg->Obj<RndMesh>(2)))
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x196)
END_HANDLERS
#pragma pop

DataNode RndMultiMesh::OnGetPos(const DataArray *da) {
    Instance &inst = Instances(da->Int(2));
    *da->Var(3) = inst.mXfm.v.x;
    *da->Var(4) = inst.mXfm.v.y;
    *da->Var(5) = inst.mXfm.v.z;
    return 0;
}

DataNode RndMultiMesh::OnSetPos(const DataArray *da) {
    Vector3 &pos = NextItr(mInstances.begin(), da->Int(2))->mXfm.v;
    pos.Set(da->Float(3), da->Float(4), da->Float(5));
    return 0;
}

DataNode RndMultiMesh::OnGetRot(const DataArray *da) {
    Vector3 rot;
    MakeEuler(Instances(da->Int(2)).mXfm.m, rot);
    rot *= RAD2DEG;
    *da->Var(3) = rot.x;
    *da->Var(4) = rot.y;
    *da->Var(5) = rot.z;
    return 0;
}

DataNode RndMultiMesh::OnSetRot(const DataArray *da) {
    Instance &inst = *NextItr(mInstances.begin(), da->Int(2));
    MakeRotMatrix(Vector3(da->Float(3), da->Float(4), da->Float(5)), inst.mXfm.m, true);
    return 0;
}

DataNode RndMultiMesh::OnGetScale(const DataArray *da) {
    Vector3 scale;
    MakeScale(Instances(da->Int(2)).mXfm.m, scale);
    *da->Var(3) = scale.x;
    *da->Var(4) = scale.y;
    *da->Var(5) = scale.z;
    return 0;
}

DataNode RndMultiMesh::OnSetScale(const DataArray *da) {
    Hmx::Matrix3 &mtx = NextItr(mInstances.begin(), da->Int(2))->mXfm.m;
    Normalize(mtx, mtx);
    Scale(Vector3(da->Float(3), da->Float(4), da->Float(5)), mtx, mtx);
    return 0;
}

DataNode RndMultiMesh::OnAddXfm(const DataArray *da) {
    RndMultiMesh *otherMesh = da->Obj<RndMultiMesh>(2);
    Instance &inst = otherMesh->Instances(da->Int(3));
    mInstances.push_back(inst);
    return 0;
}

DataNode RndMultiMesh::OnAddXfms(const DataArray *da) {
    int idx = da->Int(2);
    if (idx > 0) {
        Transform tf;
        tf.Reset();
        mInstances.insert(mInstances.end(), idx, Instance(tf));
    }
    return 0;
}

DataNode RndMultiMesh::OnRemoveXfm(const DataArray *da) {
    RemoveInstance(da->Int(2));
    return 0;
}

DataNode RndMultiMesh::OnNumXfms(const DataArray *) { return (int)mInstances.size(); }

DataNode RndMultiMesh::OnMesh(const DataArray *) { return mMesh.Ptr(); }

DataNode RndMultiMesh::OnMoveXfms(const DataArray *da) {
    MoveXfms(this, Vector3(da->Float(2), da->Float(3), da->Float(4)));
    return 0;
}

DataNode RndMultiMesh::OnScaleXfms(const DataArray *da) {
    ScaleXfms(this, Vector3(da->Float(2), da->Float(3), da->Float(4)));
    return 0;
}

DataNode RndMultiMesh::OnSortXfms(const DataArray *da) {
    SortXfms(this, Vector3(da->Float(2), da->Float(3), da->Float(4)));
    return 0;
}

DataNode RndMultiMesh::OnRandomXfms(const DataArray *da) {
    RandomXfms(this);
    return 0;
}

DataNode RndMultiMesh::OnScrambleXfms(const DataArray *da) {
    ScrambleXfms(this);
    return 0;
}

DataNode RndMultiMesh::OnDistribute(const DataArray *da) {
    DistributeXfms(this, da->Int(2), da->Float(3));
    return 0;
}

BEGIN_PROPSYNCS(RndMultiMesh)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS

TextStream &operator<<(TextStream &ts, const RndMultiMesh::Instance &i) {
    ts << i.mXfm << "\n";
    return ts;
}
