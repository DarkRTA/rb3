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
ObjectDir* sSphereDir;
RndMesh* sSphereMesh;

DECOMP_FORCEACTIVE(Utl, __FILE__, "i->from->Dir()")

RndGroup* GroupOwner(Hmx::Object* o) {
    std::vector<ObjRef*>::const_reverse_iterator rit = o->Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator ritEnd = o->Refs().rend();
    for(; rit != ritEnd; rit++){
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

bool GroupedUnder(RndGroup* grp, Hmx::Object* o){
    for(ObjPtrList<Hmx::Object, class ObjectDir>::iterator pit = grp->mObjects.begin(); pit != grp->mObjects.end(); ++pit){
        if(*pit == o) return true;
        RndGroup* casted = dynamic_cast<RndGroup*>(*pit);
        if(casted && GroupedUnder(casted, o)) return true;
    }
    return false;
}

RndEnviron* FindEnviron(RndDrawable*) {

}

bool AnimContains(const RndAnimatable* anim1, const RndAnimatable* anim2){
    if(anim1 == anim2) return true;
    else {
        std::list<RndAnimatable*> children;
        anim1->ListAnimChildren(children);
        for(std::list<RndAnimatable*>::iterator it = children.begin(); it != children.end(); ++it){
            if(AnimContains(*it, anim2)) return true;
        }
        return false;
    }
}

RndAnimatable* AnimController(Hmx::Object* o){
    std::vector<ObjRef*>::const_reverse_iterator rit = o->Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator ritEnd = o->Refs().rend();
    for(; rit != ritEnd; rit++){
        RndAnimatable* a = dynamic_cast<RndAnimatable*>((*rit)->RefOwner());
        if(a && a->AnimTarget() == o) return a;
    }
    return 0;
}

RndMat* GetMat(RndDrawable* draw){
    std::list<RndMat*> mats;
    draw->Mats(mats, false);
    RndMat* ret;
    if(mats.empty()) ret = 0;
    else ret = mats.front();
    return ret;
}

bool SortDraws(RndDrawable* draw1, RndDrawable* draw2){
    if(draw1->mOrder != draw2->mOrder)
        return draw1->mOrder < draw2->mOrder;
    else {
        RndMat* mat1 = GetMat(draw1);
        RndMat* mat2 = GetMat(draw2);
        if(mat1 != mat2){
            return mat1 == mat2;
        }
        else return strcmp(draw1->Name(), draw2->Name()) == 0;
    }
}

void CalcBox(RndMesh* m, Box& b) {
    m->mGeomOwner->mGeomOwner;
    m->mGeomOwner->mGeomOwner;
    m->mGeomOwner->mGeomOwner;
}

int GenerationCount(RndTransformable* t1, RndTransformable* t2) {
    if (t1 == NULL || t2 == NULL) return 0; else for (int i = 0; t2 != NULL; i++) {
        if (t2 == t1) return i;
        t2 = t2->mParent.mPtr;
    }
    return 0;
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

// fn_806571C0
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

Loader* ResourceFactory(const FilePath& f, LoaderPos p) {
    return new FileLoader(f, CacheResource(f.c_str(), NULL), p, 0, false, true, NULL);
}

const char* CacheResource(const char* cc, Hmx::Object* o){
    if(!cc || (*cc == '\0')) return 0;
    else {
        CacheResourceResult res;
        const char* ret = CacheResource(cc, res);
        if(res > kCacheUnnecessary){
            switch(res){
                case kCacheUnknownExtension:
                    if(o) MILO_WARN("%s: \"%s\" has unrecognized extension \"%s\"", PathName(o), cc, FileGetExt(cc));
                    else MILO_WARN("Unrecognized extension \"%s\" to \"%s\"", FileGetExt(cc), cc);
                    break;
                case kCacheMissingFile:
                    if(o) MILO_WARN("%s: couldn't find %s", PathName(o), cc);
                    else MILO_WARN("Couldn't find %s", cc);
                    break;
                default:
                    if(o) MILO_WARN("%s: unknown CacheResource error %s", PathName(o), cc);
                    else MILO_WARN("Unknown CacheResource error %s", cc);
                    break;
            }
        }
        return ret;
    }
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

void RndUtlInit(){
    if(!UsingCD()){
        sSphereDir = DirLoader::LoadObjects(FilePath(FileSystemRoot(), "rndobj/sphere.milo"), 0, 0);
    }
    if(sSphereDir){
        sSphereMesh = sSphereDir->Find<RndMesh>("sphere.mesh", true);
    }
}

void RndUtlTerminate(){
    delete sSphereDir;
    sSphereDir = 0;
    sSphereMesh = 0;
}

// fn_806598A0
float ConvertFov(float a, float b) {
    float x = std::tan(0.5f * a);
    return std::atan(b * x) * 2;
}

// fn_806598F4
void ListDrawGroups(RndDrawable* draw, ObjectDir* dir, std::list<RndGroup*>& gList){
    for(ObjDirItr<RndGroup> it(dir, true); it != 0; ++it){
        std::vector<RndDrawable*>& drawVec = it->mDraws;
        std::vector<RndDrawable*>::iterator draw_it = std::find(drawVec.begin(), drawVec.end(), draw); // wonder if this is inlined?
        if(draw_it != drawVec.end()){
            gList.push_back(it);
        }
    }
}

// fn_806599A4
DataNode OnTestDrawGroups(DataArray* da){
    DataArray* arr = 0;
    ObjectDir* dir = da->Obj<ObjectDir>(2);
    if(da->Size() > 3) arr = da->Array(3);
    for(ObjDirItr<RndDrawable> it(dir, true); it != 0; ++it){
        std::list<RndGroup*> gList;
        ListDrawGroups(it, dir, gList);
        if(arr){
            for(std::list<RndGroup*>::iterator gListIt = gList.begin(); gListIt != gList.end(); gListIt){
                bool canerase = false;
                for(int i = 0; i < arr->Size(); i++){
                    bool namesmatch = strcmp((*gListIt)->Name(), arr->Str(i)) == 0;
                    if(namesmatch){
                        canerase = true;
                        break;
                    }
                }
                if(canerase) gListIt = gList.erase(gListIt);
                else gListIt++;
            }
        }
        unsigned long listcount = 0;
        for(std::list<RndGroup*>::iterator gListIt = gList.begin(); gListIt != gList.end(); gListIt++) listcount++;
        if(listcount > 1){
            unsigned long listcountfr = 0;
            for(std::list<RndGroup*>::iterator gListIt = gList.begin(); gListIt != gList.end(); gListIt++) listcountfr++;
            String str(MakeString("%s is in %d groups:", PathName(it), listcountfr));
            for(std::list<RndGroup*>::iterator gListIt = gList.begin(); gListIt != gList.end(); gListIt++){
                str << " " << PathName(*gListIt);
            }
            MILO_WARN(str.c_str());
        }
    }
    return DataNode(0);
}

// fn_80659D74
void TestTextureSize(ObjectDir* dir, int iType, int i3, int i4, int i5, int maxBpp){
    bool rendered = false;
    if(iType == RndTex::kRendered || iType == RndTex::kRenderedNoZ) rendered = true;
    bool b2 = false;
    if(GetGfxMode() == 0 || rendered) b2 = true;
    int ivar4 = 1;
    if(b2) ivar4 = i5;
    for(ObjDirItr<RndTex> it(dir, true); it != 0; ++it){
        if(iType == it->GetType()){
            int local_bpp = b2 ? it->mBpp : 1;
            if(rendered && GetGfxMode() == 1 && local_bpp == 0x10) local_bpp = 0x20;
            int product = it->Width() * it->Height() * local_bpp;
            if(product > i3 * i4 * ivar4){
                MILO_WARN("%s is too big w:%d h:%d bpp:%d", PathName(it), it->Width(), it->Height(), local_bpp);
            }
            if(product != 0 && b2 && local_bpp > maxBpp){
                MILO_WARN("%s is %d bpp > %d, too big", PathName(it), local_bpp, maxBpp);
            }
        }
    }
}

// fn_80659E6C
void TestTexturePaths(ObjectDir* dir){
    String str(FileRoot());
    FileNormalizePath(str.c_str());
    for(ObjDirItr<RndTex> it(dir, true); it != 0; ++it){
        FilePath fp(it->mFilepath);
        if(fp.empty()) continue;
        String relative(FileRelativePath(FileRoot(), fp.c_str()));
        FileNormalizePath(relative.c_str());
        if(strstr(relative.c_str(), "..") == relative.c_str()){
            if(strstr(relative.c_str(), "../../system/run") != relative.c_str()){
                MILO_WARN("%s: %s is outside project path", PathName(it), relative);
            }
        }
        if(relative.length() > 2 && str.c_str()[1] == ':'){
            MILO_WARN("%s: %s is outside project path", PathName(it), relative);
        }
    }
    if(dir->Loader()){
        const char* fpstr = dir->Loader()->mFile.c_str();
        const char* ng = strstr(fpstr, "/ng/");
        for(ObjDirItr<RndTex> it(dir, true); it != 0; ++it){
            const char* texStr = it->mFilepath.c_str();
            if(ng == 0 && strstr(texStr, "/ng/") != 0){
                MILO_WARN("og %s has ng texture %s", fpstr, texStr);
            }
            else if(ng && strstr(texStr, "/og/") != 0){
                MILO_WARN("ng %s has og texture %s", fpstr, texStr);
            }
        }
    }
}

void TestMaterialTextures(ObjectDir*){}

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
        trans->SetLocalPos(vec.x, vec.y, vec.z);
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
