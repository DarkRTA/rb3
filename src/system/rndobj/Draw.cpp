#include "rndobj/Draw.h"
#include "rndobj/Cam.h"
#include "rndobj/Utl.h"
#include "math/Geo.h"
#include "obj/PropSync_p.h"
#include "utl/Symbols.h"

HighlightStyle RndDrawable::sHighlightStyle;
bool RndDrawable::sForceSubpartSelection;
float RndDrawable::sNormalDisplayLength = 1.0f;
int DRAW_REV = 3;

RndDrawable::RndDrawable() : mShowing(1), mSphere(), mOrder(0.0f) {
    mSphere.Zero();
}

void RndDrawable::Draw(){
    if(mShowing){
        Sphere sphere;
        int worldSphere = MakeWorldSphere(sphere, false);
        if(worldSphere == 0 || !RndCam::sCurrent->CompareSphereToWorld(sphere)){
            DrawShowing();
        }
    }
}

bool RndDrawable::DrawBudget(float f){
    if(!mShowing) return true;
    else {
        Sphere sphere;
        int worldSphere = MakeWorldSphere(sphere, false);
        if(worldSphere != 0 && RndCam::sCurrent->CompareSphereToWorld(sphere)){
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
        if(!MakeWorldSphere(s, false) || !RndCam::sCurrent->CompareSphereToWorld(s)){
            bool showing = mShowing;
            mShowing = true;
            #ifdef MILO_DEBUG
                UtilDrawSphere(s.center, s.radius, Hmx::Color(1.0f, 1.0f, 0.0f));
            #else
                UtilDrawSphere(s.center, s.GetRadius(), Hmx::Color(1.0f, 1.0f, 0.0f));
            #endif
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
        #ifdef MILO_DEBUG
            float zero = 0.0f;
            float rad = mSphere.GetRadius();
            if(rad != zero){
                rad = c->mSphere.GetRadius();
                if(rad != zero){
                    COPY_MEMBER(mSphere)
                }
            }
        #else
            float rad = mSphere.GetRadius();
            if(rad && c->mSphere.GetRadius()){
                COPY_MEMBER(mSphere);
            }
        #endif
        }
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(RndDrawable, 0xAE)

void RndDrawable::Load(BinStream& bs){
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, DRAW_REV);
    if(gLoadingProxyFromDisk){
        bool dummy;
        bs >> dummy;
    }
    else {
        bool bs_showing;
        bs >> bs_showing;
        mShowing = bs_showing;
    }
    if(rev < 2){
        int count;
        bs >> count;
        RndGroup* grp = dynamic_cast<RndGroup*>(this);
        if(count != 0){
            for(; count != 0; count--){
                char buf[0x80];
                bs.ReadString(buf, 0x80);
                if(grp){
                    Hmx::Object* found = Dir()->Find<Hmx::Object>(buf, true);
                    RndEnviron* env = dynamic_cast<RndEnviron*>(found);
                    if(env){
                        if(grp->GetEnv()) MILO_WARN("%s won't set %s", grp->Name(), buf);
                        else grp->SetEnv(env);
                    }
                    else {
                        RndCam* cam = dynamic_cast<RndCam*>(found);
                        if(!cam){
                            grp->RemoveObject(found);
                            grp->AddObject(found, 0);
                        }
                    }
                }
                else MILO_WARN("%s not in group", buf);
            }
        }
    }
    if(rev > 0) bs >> mSphere;
    if(rev > 2){
        if(gLoadingProxyFromDisk){
            float dummy;
            bs >> dummy;
        }
        else bs >> mOrder;
    }
}

void RndDrawable::DumpLoad(BinStream& bs){
    unsigned char dummy;
    int y, x, w;
    int rev;
    int i, j;
    int z;
    bs >> rev;
    MILO_ASSERT(rev < 4, 0xFD);
    bs >> dummy;
    if(rev < 2){
        char buf[0x80];
        bs >> i;
        for(; i != 0; i--){
            bs.ReadString(buf, 0x80);
        }
    }
    if(rev > 0){
    #ifdef MILO_DEBUG
        bs >> w >> x >> y >> z;
    #else
        Sphere s;
        bs >> s;
    #endif
    }
    if(rev > 2){
        bs >> j;
    }
    if(rev > 3){
        ObjPtr<RndDrawable, class ObjectDir> ptr(0, 0);
        bs >> ptr;
    }
}

bool RndDrawable::CollideSphere(const Segment& seg){
    if(!mShowing) return false;
    else {
        Sphere sphere;
        if(MakeWorldSphere(sphere, false) && !Intersect(seg, sphere)) return false;
        else return true;
    }
}

RndDrawable* RndDrawable::Collide(const Segment& seg, float& f, Plane& plane){
    START_AUTO_TIMER("collide");
    if(!CollideSphere(seg)) return false;
    else return CollideShowing(seg, f, plane);
}

// retail: https://decomp.me/scratch/X3MyB
// debug: https://decomp.me/scratch/rLOfM
int RndDrawable::CollidePlane(const Plane& plane){
    if(!mShowing) return -1;
    else {
        Sphere sphere;
        if(MakeWorldSphere(sphere, false)){
            const Vector3& vec = sphere.center;
            float prod = plane.Dot(vec);
            if(prod >= sphere.radius){
                return 1;
            }
            else return sphere.radius < -prod ? -1 : 0;
        }
        else return -1;
    }
}

void RndDrawable::CollideList(const Segment& seg, std::list<RndDrawable::Collision>& collisions){
    float f;
    Plane pl;
    RndDrawable* draw = Collide(seg, f, pl);
    if(draw){
        RndDrawable::Collision coll;
        coll.object = draw;
        coll.distance = f;
        coll.plane = pl;
        collisions.push_back(coll);
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
    *da->Var(5) = DataNode(mSphere.GetRadius());
    return DataNode(0);
}

DataNode RndDrawable::OnSetShowing(const DataArray* da){
    SetShowing(da->Int(2));
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
