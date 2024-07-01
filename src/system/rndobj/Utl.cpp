#include "rndobj/Utl.h"
#include "math/Color.h"
#include "math/Geo.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Cam.h"
#include "rndobj/CamAnim.h"
#include "rndobj/Draw.h"
#include "rndobj/Env.h"
#include "rndobj/EnvAnim.h"
#include "rndobj/Gen.h"
#include "rndobj/Group.h"
#include "rndobj/Line.h"
#include "rndobj/Lit.h"
#include "rndobj/LitAnim.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Rnd.h"
#include "rndobj/Text.h"
#include "rndobj/TransAnim.h"
#include "utl/Loader.h"
#include "math/Key.h"
#include <cmath>

float gLimitUVRange;

DECOMP_FORCEACTIVE(Utl, __FILE__, "i->from->Dir()")

RndGroup* GroupOwner(Hmx::Object* o) {
    for(std::vector<ObjRef*>::const_reverse_iterator rit = o->Refs().rbegin(); rit != o->Refs().rend(); rit++){
        RndGroup* grp = dynamic_cast<RndGroup*>((*rit)->RefOwner());
        if(grp){
            for(ObjPtrList<Hmx::Object, class ObjectDir>::iterator pit = grp->mObjects.begin(); pit != grp->mObjects.end(); ++pit){
                if(*pit == o) return grp;
            }
        }
    }
    return 0;
}

static DataNode OnGroupOwner(DataArray* da) {
    return DataNode(GroupOwner(da->GetObj(1)));
}

RndEnviron* FindEnviron(RndDrawable*) {

}

void CalcBox(RndMesh* m, Box& b) {
    m->mOwner->mOwner;
    m->mOwner->mOwner;
    m->mOwner->mOwner;
}

void UtilDrawString(const char* c, const Vector3& v, const Hmx::Color& col) {
    Vector2 v2;
    if (RndCam::sCurrent->WorldToScreen(v, v2) > 0) {
        v2.x *= (float)TheRnd->mWidth;
        v2.y *= (float)TheRnd->mHeight;
        TheRnd->DrawString(c, v2, col, true);
    }
}

#pragma push
#pragma dont_inline on
// fn_806561EC
void SpliceKeys(RndTransAnim* anim1, RndTransAnim* anim2, float f1, float f2){
    float start = anim1->StartFrame();
    float end = anim1->EndFrame();
    if(start < 0.0f || end > f2) MILO_WARN("%s has keyframes outside (0, %f)", anim1->Name(), f2);
    else {
        RndTransformable* trans = anim1->Trans();
        if(!anim1->TransKeys().empty()){
            if(anim1->TransKeys().front().frame != 0.0f){
                anim1->TransKeys().Add(anim1->TransKeys().front().value, 0.0f, false);
            }
            if(anim1->TransKeys().back().frame != f2){
                anim1->TransKeys().Add(anim1->TransKeys().back().value, f2, false);
            }
        }
        else if(trans){
            anim1->TransKeys().Add(trans->LocalXfm().v, 0.0f, false);
            anim1->TransKeys().Add(trans->LocalXfm().v, f2, false);
        }
        else {
            anim1->TransKeys().Add(Vector3(0.0f, 0.0f, 0.0f), 0.0f, false);
            anim1->TransKeys().Add(Vector3(0.0f, 0.0f, 0.0f), f2, false);
        }

        if(!anim1->RotKeys().empty()){
            if(anim1->RotKeys().front().frame != 0.0f){
                anim1->RotKeys().Add(anim1->RotKeys().front().value, 0.0f, false);
            }
            if(anim1->RotKeys().back().frame != f2){
                anim1->RotKeys().Add(anim1->RotKeys().back().value, f2, false);
            }
        }
        else if(trans){
            Hmx::Quat q(trans->LocalXfm().m);
            anim1->RotKeys().Add(q, 0.0f, false);
            anim1->RotKeys().Add(q, f2, false);
        }
        else {
            anim1->RotKeys().Add(Hmx::Quat(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, false);
            anim1->RotKeys().Add(Hmx::Quat(0.0f, 0.0f, 0.0f, 1.0f), f2, false);
        }

        if(!anim1->ScaleKeys().empty()){
            if(anim1->ScaleKeys().front().frame != 0.0f){
                anim1->ScaleKeys().Add(anim1->ScaleKeys().front().value, 0.0f, false);
            }
            if(anim1->ScaleKeys().back().frame != f2){
                anim1->ScaleKeys().Add(anim1->ScaleKeys().back().value, f2, false);
            }
        }
        else if(trans){
            Vector3 v;
            MakeScale(trans->LocalXfm().m, v);
            anim1->ScaleKeys().Add(v, 0.0f, false);
            anim1->ScaleKeys().Add(v, f2, false);
        }
        else {
            anim1->ScaleKeys().Add(Vector3(1.0f, 1.0f, 1.0f), 0.0f, false);
            anim1->ScaleKeys().Add(Vector3(1.0f, 1.0f, 1.0f), f2, false);
        }

        for(Keys<Vector3, Vector3>::iterator it = anim1->TransKeys().begin(); it != anim1->TransKeys().end(); it++){
            (*it).frame += f1;
        }
        for(Keys<Hmx::Quat, Hmx::Quat>::iterator it = anim1->RotKeys().begin(); it != anim1->RotKeys().end(); it++){
            (*it).frame += f1;
        }
        for(Keys<Vector3, Vector3>::iterator it = anim1->ScaleKeys().begin(); it != anim1->ScaleKeys().end(); it++){
            (*it).frame += f1;
        }

        float fsum = f1 + f2;
        int transRemoved = anim2->TransKeys().Remove(f1, fsum);
        int rotRemoved = anim2->RotKeys().Remove(f1, fsum);
        int scaleRemoved = anim2->ScaleKeys().Remove(f1, fsum);

        anim2->TransKeys().insert(anim2->TransKeys().begin() + transRemoved, anim1->TransKeys().begin(), anim1->TransKeys().end());
        anim2->RotKeys().insert(anim2->RotKeys().begin() + rotRemoved, anim1->RotKeys().begin(), anim1->RotKeys().end());
        anim2->ScaleKeys().insert(anim2->ScaleKeys().begin() + scaleRemoved, anim1->ScaleKeys().begin(), anim1->ScaleKeys().end());
    }
}

void LinearizeKeys(RndTransAnim* anim, float f2, float f3, float f4, float f5, float f6){
    int int1, int2;
    float bound2 = f5;
    float bound1 = f6;
    if(f2){
        if(anim->TransKeys().size() > 2){
            Keys<Vector3, Vector3> vecKeys;
            anim->TransKeys().FindBounds(bound1, bound2, int1, int2);
            for(int i = 1; i < int2 - vecKeys.size(); i++){
                vecKeys.push_back(anim->TransKeys()[i]);
                anim->TransKeys().Remove(i);
                for(int j = 0; j < vecKeys.size(); j++){
                    Vector3 vec;
                    InterpVector(anim->TransKeys(), anim->TransSpline(), vecKeys[j].frame, vec, 0);
                    Subtract(vec, vecKeys[j].value, vec);
                    if(Length(vec) > f2){
                        anim->TransKeys().insert(anim->TransKeys().begin() + i, vecKeys.back());
                        vecKeys.pop_back();
                    }
                }
            }
        }
    }
    if(f3){
        if(anim->RotKeys().size() > 2){
            Keys<Hmx::Quat, Hmx::Quat> quatKeys;
            anim->RotKeys().FindBounds(bound1, bound2, int1, int2);
            for(int i = 1; i < int2 - quatKeys.size(); i++){
                quatKeys.push_back(anim->RotKeys()[i]);
                anim->RotKeys().Remove(i);
                for(int j = 0; j < quatKeys.size(); j++){
                    Hmx::Quat q;
                    anim->RotKeys().AtFrame(quatKeys[j].frame, q);
                    if(AngleBetween(q, quatKeys[j].value) > f3){
                        anim->RotKeys().insert(anim->RotKeys().begin() + i, quatKeys.back());
                        quatKeys.pop_back();
                    }
                }
            }
        }
    }
    if(f4){
        if(anim->ScaleKeys().size() > 2){
            Keys<Vector3, Vector3> vecKeys;
            anim->ScaleKeys().FindBounds(bound1, bound2, int1, int2);
            for(int i = 1; i < int2 - vecKeys.size(); i++){
                vecKeys.push_back(anim->ScaleKeys()[i]);
                anim->ScaleKeys().Remove(i);
                for(int j = 0; j < vecKeys.size(); j++){
                    Vector3 vec;
                    InterpVector(anim->ScaleKeys(), anim->ScaleSpline(), vecKeys[j].frame, vec, 0);
                    Subtract(vec, vecKeys[j].value, vec);
                    if(Length(vec) > f4){
                        anim->ScaleKeys().insert(anim->ScaleKeys().begin() + i, vecKeys.back());
                        vecKeys.pop_back();
                    }
                }
            }
        }
    }
}
#pragma pop

void SortXfms(RndMultiMesh*, const Vector3&) {
    MILO_ASSERT(0, 3150);
}

void RandomXfms(RndMultiMesh*) {
    MILO_ASSERT(0, 3173);
}

void MoveXfms(RndMultiMesh* mm, const Vector3& v) {
    for (std::list<RndMultiMesh::Instance>::iterator i = mm->mInstances.begin(); i != mm->mInstances.end(); i++) {
        i->mXfm.v += v;
    }

}

const char* CacheResource(const char*, Hmx::Object*);

Loader* ResourceFactory(const FilePath& f, LoaderPos p) {
    return new FileLoader(f, CacheResource(f.c_str(), NULL), p, 0, false, true, NULL);
}


DataNode DataFindEnviron(DataArray* da) {
    return DataNode(FindEnviron(da->Obj<RndDrawable>(1)));
}

void RndUtlPreInit() {
    SystemConfig("rnd")->FindData("limit_uv_range", gLimitUVRange, true);
    TheLoadMgr.RegisterFactory("bmp", ResourceFactory);
    TheLoadMgr.RegisterFactory("png", ResourceFactory);
    TheLoadMgr.RegisterFactory("xbv", ResourceFactory);
    TheLoadMgr.RegisterFactory("jpg", ResourceFactory);
    TheLoadMgr.RegisterFactory("tif", ResourceFactory);
    TheLoadMgr.RegisterFactory("tiff", ResourceFactory);
    TheLoadMgr.RegisterFactory("psd", ResourceFactory);
    TheLoadMgr.RegisterFactory("gif", ResourceFactory);
    TheLoadMgr.RegisterFactory("tga", ResourceFactory);
    DataRegisterFunc("find_environ", DataFindEnviron);
    DataRegisterFunc("group_owner", OnGroupOwner);
}

float ConvertFov(float a, float b) {
    float x = tan(0.5f * a);
    return atan(b * x) * 2;
}

void PreMultiplyAlpha(Hmx::Color& c) {
    c.red *= c.alpha;
    c.green *= c.alpha;
    c.blue *= c.alpha;
}

// fn_80657B28
void RndScaleObject(Hmx::Object* o, float f1, float f2){
    RndDrawable* draw = dynamic_cast<RndDrawable*>(o);
    if(draw){
        draw->mSphere.center *= f1;
        draw->mSphere.radius *= f1;
    }
    RndTransformable* trans = dynamic_cast<RndTransformable*>(o);
    if(trans){
        Vector3 vec;
        Scale(trans->mLocalXfm.v, f1, vec);
        trans->SetDirtyLocalXfmVec(vec.x, vec.y, vec.z);
    }
    RndCam* cam = dynamic_cast<RndCam*>(o);
    if(cam){
        cam->SetFrustum(cam->mNearPlane, cam->mFarPlane, cam->mYFov, 1.0f);
        return;
    }
    RndCamAnim* camanim = dynamic_cast<RndCamAnim*>(o);
    if(camanim){
        ScaleFrame(camanim->mKeysOwner->mFovKeys, f2);
        return;
    }
    RndEnviron* env = dynamic_cast<RndEnviron*>(o);
    if(env){
        env->mAmbientFogOwner->mFogStart *= f1;
        env->mAmbientFogOwner->mFogEnd *= f1;
        return;
    }
    RndEnvAnim* envanim = dynamic_cast<RndEnvAnim*>(o);
    if(envanim){
        ScaleFrame(envanim->mKeysOwner->mFogColorKeys, f2);
        ScaleFrame(envanim->mKeysOwner->mAmbientColorKeys, f2);
        return;
    }
    RndText* text = dynamic_cast<RndText*>(o);
    if(text){
        text->SetSize(text->Size() * f1);
        return;
    }
    RndGenerator* gen = dynamic_cast<RndGenerator*>(o);
    if(gen){
        float lo, hi;
        gen->GetRateVar(lo, hi);
        gen->SetRateVar(lo * f1, hi * f1);
        return;
    }
    RndLight* lit = dynamic_cast<RndLight*>(o);
    if(lit){
        lit->SetRange(lit->Range() * f1);
        return;
    }
    RndLightAnim* litanim = dynamic_cast<RndLightAnim*>(o);
    if(litanim){
        ScaleFrame(litanim->mKeysOwner->mColorKeys, f2);
        return;
    }
    RndLine* line = dynamic_cast<RndLine*>(o);
    if(line){

    }
}