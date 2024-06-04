#include "rndobj/Draw.h"
#include "rndobj/Cam.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

int DRAW_REV = 3;

RndDrawable::RndDrawable() : mShowing(1), mSphere(), mOrder(0.0f) {
    mSphere.Zero();
}

void RndDrawable::Draw(){
    if(mShowing){
        Sphere sphere;
        int worldSphere = MakeWorldSphere(sphere, false);
        if(worldSphere == 0 || !(sphere > RndCam::sCurrent->mWorldFrustum)){
            DrawShowing();
        }
    }
}

bool RndDrawable::DrawBudget(float f){
    if(!mShowing) return true;
    else {
        Sphere sphere;
        int worldSphere = MakeWorldSphere(sphere, false);
        if(worldSphere != 0 && (sphere > RndCam::sCurrent->mWorldFrustum)){
            return true;
        }
        else return DrawShowingBudget(f);
    }
}

bool RndDrawable::DrawShowingBudget(float f){
    DrawShowing();
    return true;
}

void RndDrawable::Highlight(){
    if(sHighlightStyle != kHighlightNone){
        Sphere s;
        if(!MakeWorldSphere(s, false) || !(s > RndCam::sCurrent->mWorldFrustum)){
            bool showing = mShowing;
            mShowing = true;
            Hmx::Color col(1.0f, 1.0f, 0.0f);
            UtilDrawSphere(s.center, s.radius, col);
            mShowing = showing;
        }
    }
}

BEGIN_COPYS(RndDrawable)
    CREATE_COPY(RndDrawable)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mShowing)
            COPY_MEMBER(mOrder)
            COPY_MEMBER(mSphere)
        }
        else {
            if(mSphere.Radius() != 0.0f && c->mSphere.Radius() != 0.0f){
                COPY_MEMBER(mSphere)
            }
        }
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(RndDrawable, 0xAE)

extern bool gLoadingProxyFromDisk;

void RndDrawable::Load(BinStream& bs){
    int rev;
    bs >> rev;
    if (rev > DRAW_REV){
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), rev, DRAW_REV);
    }
    if(gLoadingProxyFromDisk){
        bool dummy;
        bs >> dummy;
    }
    else {
        bool bs_showing;
        bs >> bs_showing;
        mShowing = bs_showing;
    }
    // more stuff involving ObjectDir
}

void RndDrawable::DumpLoad(BinStream& bs){
    int rev;
    bs >> rev;
    MILO_ASSERT(rev < 4, 0xFD);
    unsigned char dummy;
    bs >> dummy;
    if(rev < 3){
        int i;
        char buf[0x80];
        bs >> i;
        for(; i != 0; i--){
            bs.ReadString(buf, 0x80);
        }
    }
    if(rev > 0){
        int w, x, y, z;
        bs >> w >> x >> y >> z;
    }
    if(rev > 2){
        int j;
        bs >> j;
    }
    if(rev > 3){
        ObjPtr<RndDrawable, class ObjectDir> ptr(0, 0);
        bs >> ptr;
    }
}

BEGIN_HANDLERS(RndDrawable)
    HANDLE(set_showing, OnSetShowing)
    HANDLE(showing, OnShowing)
    HANDLE(zero_sphere, OnZeroSphere)
    HANDLE_ACTION(update_sphere, UpdateSphere())
    HANDLE(get_sphere, OnGetSphere)
    HANDLE(copy_sphere, OnCopySphere)
    HANDLE_CHECK(0x168)
END_HANDLERS

DataNode RndDrawable::OnCopySphere(const DataArray* da){
    RndDrawable* draw = da->Obj<RndDrawable>(2);
    if(draw) mSphere = draw->mSphere;
    return DataNode(0);
}

DataNode RndDrawable::OnGetSphere(const DataArray* da){
    *da->Var(2) = DataNode(mSphere.center.X());
    *da->Var(3) = DataNode(mSphere.center.Y());
    *da->Var(4) = DataNode(mSphere.center.Z());
    *da->Var(5) = DataNode(mSphere.Radius());
    return DataNode(0);
}

DataNode RndDrawable::OnSetShowing(const DataArray* da){
    mShowing = da->Int(2) != 0;
    return DataNode(0);
}

DataNode RndDrawable::OnShowing(const DataArray* da){
    return DataNode(mShowing);
}

DataNode RndDrawable::OnZeroSphere(const DataArray* da){
    mSphere.Zero();
    return DataNode(0);
}

BEGIN_PROPSYNCS(RndDrawable)
    SYNC_PROP(draw_order, mOrder)
    static Symbol _s("showing");
    if(sym == _s){
        if(_op == kPropSet){
            mShowing = _val.Int(0) != 0;
        }
        else {
            _val = DataNode(mShowing);
        }
        return true;
    }
    SYNC_PROP(sphere, mSphere);
END_PROPSYNCS
