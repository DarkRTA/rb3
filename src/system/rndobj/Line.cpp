#include "rndobj/Line.h"
#include "math/Color.h"
#include "math/Mtx.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Cam.h"
#include "rndobj/Draw.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"
#include "types.h"
#include <math.h>

static int LINE_REV = 4;

RndDrawable *RndLine::CollideShowing(const Segment &s, float &f, Plane &p) {
    return mMesh->Collide(s, f, p) ? this : nullptr;
}

int RndLine::CollidePlane(const Plane &p) { return mMesh->CollidePlane(p); }

void RndLine::DrawShowing() {
    if (mPoints.size() >= 2) {
        if (mLineUpdate) {
            RndCam *cam = RndCam::sCurrent;
            UpdateLine(cam->WorldXfm(), RndCam::sCurrent->NearPlane());
            mMesh->SetWorldXfm(cam->WorldXfm());
        }
        mMesh->DrawShowing();
    }
}

void RndLine::UpdateSphere() {
    Sphere s;
    MakeWorldSphere(s, true);
    Transform xfm;
    FastInvert(WorldXfm(), xfm);
    Multiply(s, xfm, s);
    SetSphere(s);
}

float RndLine::GetDistanceToPlane(const Plane &p, Vector3 &v3) {
    if (mPoints.empty())
        return 0;
    else {
        WorldXfm();
        float ret = 0;
        bool b1 = true;
        FOREACH (it, mPoints) {
            float dot = p.Dot(it->v);
            if (b1 || std::fabs(dot) < std::fabs(ret)) {
                ret = dot;
                b1 = false;
                v3 = it->v;
            }
        }
        return ret;
    }
}

bool RndLine::MakeWorldSphere(Sphere &s, bool b2) {
    if (b2) {
        s.Zero();
        FOREACH (it, mPoints) {
            s.GrowToContain(Sphere(it->v, mWidth));
        }
        return true;
    } else {
        if (mSphere.GetRadius()) {
            Multiply(mSphere, WorldXfm(), s);
            return true;
        } else
            return false;
    }
}

void RndLine::MapVerts(int i1, VertsMap &vmap) {
    if (mLineHasCaps) {
        if (mLinePairs) {
            if (i1 & 1) {
                vmap.t = 2;
            } else
                vmap.t = 1;
            vmap.v = &mMesh->Verts(i1 * 4);
        } else {
            if (i1 == 0) {
                vmap.t = 1;
                vmap.v = &mMesh->Verts(0);
            } else if (i1 != 0) {
                if (i1 + 1 == mPoints.size()) {
                    vmap.t = 2;
                    vmap.v = mMesh->Verts().back() - 3;
                } else {
                    vmap.t = 0;
                    vmap.v = &mMesh->Verts((i1 + 1) * 2);
                }
            } else {
                vmap.t = 1;
                vmap.v = &mMesh->Verts(0);
            }
        }
    } else {
        vmap.t = 0;
        vmap.v = &mMesh->Verts(i1 * 2);
    }
}

void RndLine::SetMat(RndMat *mat) {
    mMat = mat;
    mMesh->SetMat(mat);
}

void RndLine::SetNumPoints(int num) {
    mPoints.resize(num);
    if (num >= 1) {
        int i1 = num;
        if (mLineHasCaps) {
            i1 = num + 2;
            if (mLinePairs) {
                i1 = (num & 0x7ffffffeU) * 2;
            }
        }
        mMesh->Verts().resize(i1 * 2, true);
        for (int i = 0; i < mPoints.size(); i++) {
            VertsMap vmap;
            MapVerts(i, vmap);
            Hmx::Color32 &ptColor = mPoints[i].c;
            if (vmap.t == 1) {
                vmap.v->uv.Set(0, 1);
                vmap.v++->color = ptColor;
                vmap.v->uv.Set(0, 0);
                vmap.v++->color = ptColor;
            }
            vmap.v->uv.Set(1, 1);
            vmap.v++->color = ptColor;
            vmap.v->uv.Set(1, 0);
            vmap.v++->color = ptColor;
            if (vmap.t == 2) {
                vmap.v->uv.Set(1, 1);
                vmap.v++->color = ptColor;
                vmap.v->uv.Set(1, 0);
                vmap.v++->color = ptColor;
            }
        }

        if (mLinePairs) {
            if (mLineHasCaps)
                i1 = i1 * 3 >> 1;
        } else
            i1 = (i1 - 1) * 2;
        mMesh->Faces().resize(i1);
        for (int i5 = i1 - 2; i5 >= 0; i5 -= 2) {
            int i7 = i5;
            if (mLinePairs) {
                if (mLineHasCaps) {
                    i7 = i5 % 6 + (i5 / 6) * 8;
                } else
                    i7 = i5 * 2;
            }
            mMesh->Faces(i5).Set(i7, i7 + 2, i7 + 1);
            mMesh->Faces(i1 - 1).Set(i7 + 1, i7 + 2, i7 + 3);
            i1 = i5;
        }
        mMesh->Sync(0x13F);
    }
}

void RndLine::SetPointPos(int i, const Vector3 &pos) {
    MILO_ASSERT((i >= 0) && (i < mPoints.size()), 0x1D0);
    mPoints[i].v = pos;
}

void RndLine::SetPointColor(int i, const Hmx::Color32 &color, bool sync) {
    MILO_ASSERT((i >= 0) && (i < mPoints.size()), 0x1D7);
    mPoints[i].c = color;
    VertsMap vmap;
    MapVerts(i, vmap);
    vmap.v++->color = color;
    vmap.v++->color = color;
    if (vmap.t != 0) {
        vmap.v++->color = color;
        vmap.v++->color = color;
    }
    if (sync)
        mMesh->Sync(0x1F);
}

void RndLine::SetPointsColor(int start, int end, const Hmx::Color32 &color) {
    MILO_ASSERT((start >= 0) && (start < mPoints.size()) && (end >= 0) && (end < mPoints.size()), 0x1EF);
    int i = start;
    if (end < start) {
        i = end;
        end = start;
    }
    for (; i <= end; i++) {
        mPoints[i].c = color;
        VertsMap vmap;
        MapVerts(i, vmap);
        vmap.v++->color = color;
        vmap.v++->color = color;
        if (vmap.t != 0) {
            vmap.v++->color = color;
            vmap.v++->color = color;
        }
    }
    mMesh->Sync(0x1F);
}

SAVE_OBJ(RndLine, 535)

void RndLine::UpdateInternal() {
    mFoldCos = cosf(mFoldAngle);
    mMesh->SetMat(mMat);
    SetNumPoints(mPoints.size());
}

BinStream &operator>>(BinStream &bs, RndLine::Point point) {
    bs >> point.v >> point.c;
    return bs;
}

BEGIN_LOADS(RndLine)
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, LINE_REV)
    if (rev > 3) {
        Hmx::Object::Load(bs);
    }
    RndDrawable::Load(bs);
    if (rev < 3) {
        ObjPtrList<Hmx::Object> list(this, kObjListNoNull);
        int _;
        bs >> _ >> list;
    }
    RndTransformable::Load(bs);
    bs >> mMat >> mPoints >> mWidth;
    if (rev > 0) {
        bs >> mFoldAngle;
        LOAD_BITFIELD(u8, mLineHasCaps)
    }
    if (rev > 1) {
        LOAD_BITFIELD(u8, mLinePairs)
    }
    UpdateInternal();
END_LOADS

TextStream &operator<<(TextStream &, const RndLine::Point &) {}

void RndLine::Print() {
    TheDebug << "   points: " << mPoints << "\n";
    TheDebug << "   width: " << mWidth << "\n";
    TheDebug << "   foldAngle: " << mFoldAngle << "\n";
    TheDebug << "   hasCaps: " << mLineHasCaps << "\n";
    TheDebug << "   linePairs:" << mLinePairs << "\n";
}

RndLine::RndLine() : mWidth(1.0f), mFoldAngle(1.570796f), mMat(this, 0) {
    mLineHasCaps = true;
    mLinePairs = false;
    mLineUpdate = true;
    mMesh = Hmx::Object::New<RndMesh>();
    mMesh->mGeomOwner->mMutable = 0x1F;
    mMesh->SetTransParent(this, false);
    UpdateInternal();
}

RndLine::~RndLine() {}

DataNode RndLine::OnSetMat(const DataArray *array) {
    RndMat *mat = array->Obj<RndMat>(2);
    SetMat(mat);
    mShowing = mat;
    return 0;
}

BEGIN_HANDLERS(RndLine)
    HANDLE_EXPR(num_points, (int)mPoints.size())
    HANDLE_ACTION(set_point_pos, {
        Vector3 v(_msg->Float(2), _msg->Float(3), _msg->Float(4));
        SetPointPos(_msg->Int(1), v);
    })
    HANDLE_ACTION(set_update, SetUpdate(_msg->Int(2)))
    HANDLE(set_mat, OnSetMat)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(797)
END_HANDLERS

BEGIN_PROPSYNCS(RndLine)
    SYNC_PROP(width, mWidth);
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS
