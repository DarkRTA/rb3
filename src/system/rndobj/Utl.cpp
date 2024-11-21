#include "rndobj/Utl.h"
#include "MSL_Common/extras.h"
#include "decomp.h"
#include "math/Color.h"
#include "math/Geo.h"
#include "math/Mtx.h"
#include "math/Rand.h"
#include "math/Rot.h"
#include "math/Utl.h"
#include "math/Vec.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Utl.h"
#include "os/Debug.h"
#include "os/Endian.h"
#include "os/File.h"
#include "os/System.h"
#include "rndobj/Anim.h"
#include "rndobj/Cam.h"
#include "rndobj/CamAnim.h"
#include "rndobj/Dir.h"
#include "rndobj/Draw.h"
#include "rndobj/Env.h"
#include "rndobj/EnvAnim.h"
#include "rndobj/Flare.h"
#include "rndobj/Gen.h"
#include "rndobj/Group.h"
#include "rndobj/Line.h"
#include "rndobj/Lit.h"
#include "rndobj/LitAnim.h"
#include "rndobj/Mat.h"
#include "rndobj/MatAnim.h"
#include "rndobj/Mesh.h"
#include "rndobj/MeshAnim.h"
#include "rndobj/Morph.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Part.h"
#include "rndobj/PartAnim.h"
#include "rndobj/Rnd.h"
#include "rndobj/Tex.h"
#include "rndobj/Text.h"
#include "rndobj/Trans.h"
#include "rndobj/TransAnim.h"
#include "utl/Loader.h"
#include "math/Key.h"
#include "utl/Std.h"
#include "utl/ClassSymbols.h"
#include <cmath>

typedef void (*SplashFunc)(void);

float gLimitUVRange;
class ObjectDir* sSphereDir;
RndMesh* sSphereMesh;
SplashFunc gSplashPoll;
SplashFunc gSplashSuspend;
SplashFunc gSplashResume;

DECOMP_FORCEACTIVE(Utl, __FILE__, "i->from->Dir()")

RndGroup* GroupOwner(Hmx::Object* o) {
    std::vector<ObjRef*>::const_reverse_iterator rit = o->Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator ritEnd = o->Refs().rend();
    for(; rit != ritEnd; ++rit){
        RndGroup* grp = dynamic_cast<RndGroup*>((*rit)->RefOwner());
        if(grp){
            if(grp->mObjects.find(o) != grp->mObjects.end()) return grp;
        }
    }
    return 0;
}

static DataNode OnGroupOwner(DataArray* da) {
    return DataNode(GroupOwner(da->Obj<Hmx::Object>(1)));
}

bool GroupedUnder(RndGroup* grp, Hmx::Object* o){
    for(ObjPtrList<Hmx::Object>::iterator pit = grp->mObjects.begin(); pit != grp->mObjects.end(); ++pit){
        if(*pit == o) return true;
        RndGroup* casted = dynamic_cast<RndGroup*>(*pit);
        if(casted && GroupedUnder(casted, o)) return true;
    }
    return false;
}

RndEnviron* FindEnviron(RndDrawable* d) {
    RndGroup* owner = GroupOwner(d);
    if(owner){
        RndEnviron* env = owner->GetEnv();
        if(env){
            return FindEnviron(owner);
        }
        else return env;
    }
    else {
        RndDir* rdir = dynamic_cast<RndDir*>(d->Dir());
        if(rdir){
            std::list<RndDrawable*> children;
            rdir->ListDrawChildren(children);
            if(ListFind(children, d)){
                return rdir->GetEnv();
            }
        }
        MILO_WARN("Need to find environment of draw parent");
    }
    return nullptr;
}

DECOMP_FORCEACTIVE(Utl, "m")

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
    for(; rit != ritEnd; ++rit){
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
    if(draw1->GetOrder() != draw2->GetOrder())
        return draw1->GetOrder() < draw2->GetOrder();
    else {
        RndMat* mat1 = GetMat(draw1);
        RndMat* mat2 = GetMat(draw2);
        if(mat1 != mat2){
            return mat1 < mat2;
        }
        else return strcmp(draw1->Name(), draw2->Name()) < 0;
    }
}

bool SortPolls(const RndPollable* p1, const RndPollable* p2){
    float f1 = p1->ClassName() == CharTransCopy ? 0 : 1.0f;
    float f2 = p2->ClassName() == CharTransCopy ? 0 : 1.0f;
    if(f1 != f2) return f1 < f2;
    else return strcmp(p1->Name(), p2->Name()) < 0;
}

// matches in retail with the right inline settings: https://decomp.me/scratch/9OmqG
void CalcBox(RndMesh* m, Box& b) {
    for(RndMesh::Vert* it = m->Verts().begin(); it != m->Verts().end(); ++it){
        Vector3 vec;
        Multiply(it->pos, m->WorldXfm(), vec);
        b.GrowToContain(vec, it == m->Verts().begin());
    }
}

// matches in retail with the right inline settings: https://decomp.me/scratch/717x7
void CalcSphere(RndTransAnim* a, Sphere& s){
    s.Zero();
    if(!a->TransKeys().empty()){
        RndTransformable* trans = a->Trans() ? a->Trans()->TransParent() : nullptr;
        Box box;
        Vector3 vec;
        for(Keys<Vector3, Vector3>::iterator it = a->TransKeys().begin(); it != a->TransKeys().end(); ++it){
            if(trans){
                Multiply(it->value, trans->WorldXfm(), vec);
            }
            else vec = it->value;
            box.GrowToContain(vec, it == a->TransKeys().begin());
        }
        Vector3 vres;
        CalcBoxCenter(vres, box);
        Subtract(box.mMax, vres, vec);
        Vector3 vsphere;
        float fmax = Max(vec.x, vec.y, vec.z);
        CalcBoxCenter(vsphere, box);
        s.Set(vsphere, fmax);
    }
}

// matches in retail
void AddMotionSphere(RndTransformable* t, Sphere& s){
    RndTransAnim* anim = dynamic_cast<RndTransAnim*>(AnimController(t));
    if(anim){
        Sphere s_loc;
        CalcSphere(anim, s_loc);
        if(s_loc.GetRadius()){
            if(s.GetRadius()){
                s.radius += s_loc.GetRadius();
                Subtract(s.center, t->WorldXfm().v, s.center);
                Add(s_loc.center, s.center, s.center);
            }
            else s = s_loc;
        }
    }
    RndTransformable* parent = t->TransParent();
    if(parent) AddMotionSphere(parent, s);
}

int GenerationCount(RndTransformable* t1, RndTransformable* t2) {
    if(!t1 || !t2) return 0;
    int count = 0;
    for(; t2; t2 = t2->TransParent()){
        if(t2 == t1) return count;
        count++;
    }
    return 0;
}

void AttachMesh(RndMesh* main, RndMesh* attach){
    MILO_ASSERT(main && attach, 0x536);
    int nummainfaces = main->Faces().size();
    int numattachfaces = attach->Faces().size();
    main->Faces().resize(nummainfaces + numattachfaces);
    int numverts = main->Verts().size();
    for(int i = 0; i < numattachfaces; i++){
        RndMesh::Face& curattachface = attach->FaceAt(i);
        RndMesh::Face& mainface = main->FaceAt(i + nummainfaces);
        mainface.Set(curattachface.idx0 + numverts, curattachface.idx1 + numverts, curattachface.idx2 + numverts);
    }
    Transform tf50;
    FastInvert(main->WorldXfm(), tf50);
    Multiply(attach->WorldXfm(), tf50, tf50);
    int numattachverts = attach->Verts().size();
    main->Verts().resize(numverts + numattachverts, true);
    for(int i = 0; i < numattachverts; i++){
        RndMesh::Vert& mainvert = main->VertAt(i + numverts);
        RndMesh::Vert& attachvert = attach->VertAt(i);
        Multiply(attachvert.pos, tf50, mainvert.pos);
        mainvert.color = attachvert.color;
        mainvert.boneWeights = attachvert.boneWeights;
        mainvert.norm = attachvert.norm;
        mainvert.uv = attachvert.uv;
    }
    main->Sync(0x3F);
}

void RandomPointOnMesh(RndMesh* m, Vector3& v1, Vector3& v2){
    RndMesh::Face& face = m->Faces()[RandomInt(0, m->Faces().size())];
    int numverts = m->Verts().size();
    if(face.idx0 >= numverts || face.idx1 >= numverts || face.idx2 >= numverts){
        MILO_NOTIFY_ONCE("%s: %s random face contains unknown vert indices!", PathName(m), m->Name());
        v1.Zero();
        v2.Zero();
    }
    else {
        Vector3 v58, v64, v70;
        Vector3 v7c, v88, v94;
        if(m->NumBones() > 0){
            v58 = m->SkinVertex(m->Verts()[face.idx0], &v7c);
            v64 = m->SkinVertex(m->Verts()[face.idx1], &v88);
            v70 = m->SkinVertex(m->Verts()[face.idx2], &v94);
        }
        else {
            v58 = m->Verts()[face.idx0].pos;
            v64 = m->Verts()[face.idx1].pos;
            v70 = m->Verts()[face.idx2].pos;
            v7c = m->Verts()[face.idx0].norm;
            v88 = m->Verts()[face.idx1].norm;
            v94 = m->Verts()[face.idx2].norm;
        }
        float f8 = RandomFloat();
        float f9 = RandomFloat();
        if(f8 + f9 > 1.0f){
            f8 = 1.0f - f8;
            f9 = 1.0f - f9;
        }
        float f1 = (1.0f - f8) - f9;
        v58 *= f8;
        v64 *= f9;
        v70 *= f1;
        Add(v58, v64, v1);
        Add(v1, v70, v1);
        v7c *= f8;
        v88 *= f9;
        v94 *= f1;
        Add(v7c, v88, v2);
        Add(v2, v94, v2);
        Normalize(v2, v2);
    }
}

void UtilDrawSphere(const Vector3& v, float f, const Hmx::Color& col){
    if(!sSphereMesh){
        MILO_NOTIFY_ONCE("Sphere mesh is not loaded");
    }
    else {
        Transform tf58;
        tf58.Reset();
        tf58.v = v;
        Scale(Vector3(f, f, f), tf58.m, tf58.m);
        sSphereMesh->Mat()->SetColor(col);
        sSphereMesh->Mat()->SetAlpha(0.2f);
        sSphereMesh->Mat()->SetCull(false);
        sSphereMesh->SetLocalXfm(tf58);
        sSphereMesh->SetSphere(Sphere(Vector3(0,0,0), f));
        sSphereMesh->Draw();
    }
}

void UtilDrawString(const char* c, const Vector3& v, const Hmx::Color& col) {
    Vector2 v2;
    if (RndCam::sCurrent->WorldToScreen(v, v2) > 0) {
        v2.x *= (float)TheRnd->mWidth;
        v2.y *= (float)TheRnd->mHeight;
        TheRnd->DrawString(c, v2, col, true);
    }
}

void UtilDrawBox(const Transform& tf, const Box& box, const Hmx::Color& col, bool b4){
    Vector3 vecs[8] = {
        Vector3(box.mMin.x, box.mMin.y, box.mMin.z),
        Vector3(box.mMin.x, box.mMax.y, box.mMin.z),
        Vector3(box.mMax.x, box.mMax.y, box.mMin.z),
        Vector3(box.mMax.x, box.mMin.y, box.mMin.z),
        Vector3(box.mMin.x, box.mMin.y, box.mMax.z),
        Vector3(box.mMin.x, box.mMax.y, box.mMax.z),
        Vector3(box.mMax.x, box.mMax.y, box.mMax.z),
        Vector3(box.mMax.x, box.mMin.y, box.mMax.z)
    };
    for(int i = 0; i < 8; i++){
        Multiply(vecs[i], tf, vecs[i]);
    }
    TheRnd->DrawLine(vecs[0], vecs[1], col, b4);
    TheRnd->DrawLine(vecs[1], vecs[2], col, b4);
    TheRnd->DrawLine(vecs[2], vecs[3], col, b4);
    TheRnd->DrawLine(vecs[3], vecs[0], col, b4);
    
    TheRnd->DrawLine(vecs[0], vecs[4], col, b4);
    TheRnd->DrawLine(vecs[1], vecs[5], col, b4);
    TheRnd->DrawLine(vecs[2], vecs[6], col, b4);
    TheRnd->DrawLine(vecs[3], vecs[7], col, b4);
    
    TheRnd->DrawLine(vecs[4], vecs[5], col, b4);
    TheRnd->DrawLine(vecs[5], vecs[6], col, b4);
    TheRnd->DrawLine(vecs[6], vecs[7], col, b4);
    TheRnd->DrawLine(vecs[7], vecs[4], col, b4);
}

void UtilDrawPlane(const Plane& p, const Vector3& v, const Hmx::Color& c, int i4, float f){
    Transform tf88;
    ScaleAdd(v, *reinterpret_cast<const Vector3*>(&p), -p.Dot(v), tf88.v); // lol wut
    tf88.m.y = *reinterpret_cast<const Vector3*>(&p);
    Hmx::Matrix3 mb0;
    mb0.Identity();
    int idx = 0;
    int minIdx = 0;
    float ref = 10000.0f;
    for(; idx < 3; idx++){
        if(MinEq(ref, Dot(mb0[idx], tf88.m.y))){
            minIdx = idx;
        }
    }
    Cross(tf88.m.y, mb0[minIdx], tf88.m.z);
    Normalize(tf88.m.z, tf88.m.z);
    Cross(tf88.m.y, tf88.m.z, tf88.m.x);
    for(int i = 0; i < i4; i++){
        Vector3 vecbc, vecc8, vecd4, vece0;
        float scalar = (float)(i + 1) * f;
        ScaleAdd(tf88.v, tf88.m.x, scalar, vece0);
        ScaleAdd(tf88.v, tf88.m.z, scalar, vecd4);
        float negscalar = -scalar;
        ScaleAdd(tf88.v, tf88.m.x, negscalar, vecc8);
        ScaleAdd(tf88.v, tf88.m.z, negscalar, vecbc);
        TheRnd->DrawLine(vece0, vecd4, c, false);
        TheRnd->DrawLine(vecd4, vecc8, c, false);
        TheRnd->DrawLine(vecc8, vecbc, c, false);
        TheRnd->DrawLine(vecbc, vece0, c, false);
    }
}

void UtilDrawAxes(const Transform& tf, float f, const Hmx::Color& c){
    Vector3 vec38;
    Hmx::Color c48;
    ScaleAdd(tf.v, tf.m.x, f, vec38);
    Interp(c, Hmx::Color(1,0,0), 0.8f, c48);
    TheRnd->DrawLine(tf.v, vec38, c48, false);

    ScaleAdd(tf.v, tf.m.y, f, vec38);
    Interp(c, Hmx::Color(0,1,0), 0.8f, c48);
    TheRnd->DrawLine(tf.v, vec38, c48, false);

    ScaleAdd(tf.v, tf.m.z, f, vec38);
    Interp(c, Hmx::Color(0, 0, 1), 0.8f, c48);
    TheRnd->DrawLine(tf.v, vec38, c48, false);
}

void SetLocalScale(RndTransformable* t, const Vector3& vec){
    Hmx::Matrix3 m;
    Normalize(t->mLocalXfm.m, m);
    Scale(vec, m, m);
    t->SetLocalRot(m);
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

DECOMP_FORCEACTIVE(Utl, "start <= end", "ni == numKeys")

// fn_806571C0
void LinearizeKeys(RndTransAnim* anim, float f2, float f3, float f4, float f5, float f6){
    int firstFrameIdx, lastFrameIdx;
    if(f2){
        if(anim->TransKeys().size() > 2){
            Keys<Vector3, Vector3> vecKeys;
            anim->TransKeys().FindBounds(f5, f6, firstFrameIdx, lastFrameIdx);
            for(int i = firstFrameIdx + 1; i < lastFrameIdx - vecKeys.size();){
                vecKeys.push_back(anim->TransKeys()[i]);
                anim->TransKeys().Remove(i);
                for(int j = 0; j < vecKeys.size(); j++){
                    Vector3 vec;
                    InterpVector(anim->TransKeys(), anim->TransSpline(), vecKeys[j].frame, vec, 0);
                    Subtract(vec, vecKeys[j].value, vec);
                    if(Length(vec) > f2){
                        anim->TransKeys().insert(anim->TransKeys().begin() + i, vecKeys.back());
                        vecKeys.pop_back();
                        i++;
                        break;
                    }
                }
            }
        }
    }
    if(f3){
        if(anim->RotKeys().size() > 2){
            Keys<Hmx::Quat, Hmx::Quat> quatKeys;
            anim->RotKeys().FindBounds(f5, f6, firstFrameIdx, lastFrameIdx);
            for(int i = firstFrameIdx + 1; i < lastFrameIdx - quatKeys.size();){
                quatKeys.push_back(anim->RotKeys()[i]);
                anim->RotKeys().Remove(i);
                for(int j = 0; j < quatKeys.size(); j++){
                    Hmx::Quat q;
                    anim->RotKeys().AtFrame(quatKeys[j].frame, q);
                    if(AngleBetween(q, quatKeys[j].value) > f3){
                        anim->RotKeys().insert(anim->RotKeys().begin() + i, quatKeys.back());
                        quatKeys.pop_back();
                        i++;
                        break;
                    }
                }
            }
        }
    }
    if(f4){
        if(anim->ScaleKeys().size() > 2){
            Keys<Vector3, Vector3> vecKeys;
            anim->ScaleKeys().FindBounds(f5, f6, firstFrameIdx, lastFrameIdx);
            for(int i = firstFrameIdx + 1; i < lastFrameIdx - vecKeys.size();){
                vecKeys.push_back(anim->ScaleKeys()[i]);
                anim->ScaleKeys().Remove(i);
                for(int j = 0; j < vecKeys.size(); j++){
                    Vector3 vec;
                    InterpVector(anim->ScaleKeys(), anim->ScaleSpline(), vecKeys[j].frame, vec, 0);
                    Subtract(vec, vecKeys[j].value, vec);
                    if(Length(vec) > f4){
                        anim->ScaleKeys().insert(anim->ScaleKeys().begin() + i, vecKeys.back());
                        vecKeys.pop_back();
                        i++;
                        break;
                    }
                }
            }
        }
    }
}
#pragma pop

float AngleBetween(const Hmx::Quat& q1, const Hmx::Quat& q2){
    Hmx::Quat q18;
    Negate(q1, q18);
    Multiply(q2, q18, q18);
    if(q18.w > 1.0f) return 0;
    else return acosf(q18.w) * 2.0f;
}

void TransformKeys(RndTransAnim* tanim, const Transform& tf){
    Vector3 v48;
    MakeScale(tf.m, v48);
    Hmx::Matrix3 m3c;
    Scale(tf.m.x, 1.0f / v48.x, m3c.x);
    Scale(tf.m.y, 1.0f / v48.y, m3c.y);
    Scale(tf.m.z, 1.0f / v48.z, m3c.z);
    Hmx::Quat q58(m3c);
    for(Keys<Vector3, Vector3>::iterator it = tanim->TransKeys().begin(); it != tanim->TransKeys().end(); ++it){
        Multiply(it->value, tf, it->value);
    }
    for(Keys<Vector3, Vector3>::iterator it = tanim->ScaleKeys().begin(); it != tanim->ScaleKeys().end(); ++it){
        Scale(it->value, v48.x, it->value);
    }
    for(Keys<Hmx::Quat, Hmx::Quat>::iterator it = tanim->RotKeys().begin(); it != tanim->RotKeys().end(); ++it){
        Multiply(q58, it->value, it->value);
    }
}

// fn_80657B28
void RndScaleObject(Hmx::Object* o, float f1, float f2){
    RndDrawable* draw = dynamic_cast<RndDrawable*>(o);
    if(draw){
        Sphere s = draw->mSphere;
        s.center *= f1;
        s.radius *= f1;
        draw->SetSphere(s);
    }
    RndTransformable* trans = dynamic_cast<RndTransformable*>(o);
    if(trans){
        Vector3 vec;
        Scale(trans->mLocalXfm.v, f1, vec);
        trans->SetLocalPos(vec);
    }
    RndCam* cam = dynamic_cast<RndCam*>(o);
    if(cam){
        cam->SetFrustum(cam->NearPlane() * f1, cam->FarPlane() * f1, cam->YFov(), 1.0f);
        return;
    }
    RndCamAnim* camanim = dynamic_cast<RndCamAnim*>(o);
    if(camanim){
        if(camanim->KeysOwner() == camanim){
            ScaleFrame(camanim->FovKeys(), f2);
        }        
        return;
    }
    RndEnviron* env = dynamic_cast<RndEnviron*>(o);
    if(env){
        env->SetFogRange(env->GetFogStart() * f1, env->GetFogEnd() * f1);
        return;
    }
    RndEnvAnim* envanim = dynamic_cast<RndEnvAnim*>(o);
    if(envanim){
        if(envanim->KeysOwner() == envanim){
            ScaleFrame(envanim->FogColorKeys(), f2);
            ScaleFrame(envanim->AmbientColorKeys(), f2);
        }
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
        if(litanim->KeysOwner() == litanim){
            ScaleFrame(litanim->ColorKeys(), f2);
        }
        return;
    }
    RndLine* line = dynamic_cast<RndLine*>(o);
    if(line){
        line->SetWidth(line->GetWidth() * f1);
        for(int i = 0; i < line->NumPoints(); i++){
            Vector3 vec;
            Scale(line->PointAt(i).v, f2, vec);
            line->SetPointPos(i, vec);
        }
        return;
    }
    RndMatAnim* matanim = dynamic_cast<RndMatAnim*>(o);
    if(matanim){
        if(matanim->KeysOwner() == matanim){
            ScaleFrame(matanim->ColorKeys(), f2);
            ScaleFrame(matanim->AlphaKeys(), f2);
            ScaleFrame(matanim->TransKeys(), f2);
            ScaleFrame(matanim->ScaleKeys(), f2);
            ScaleFrame(matanim->RotKeys(), f2);
        }
        return;
    }
    RndMesh* mesh = dynamic_cast<RndMesh*>(o);
    if(mesh){
        if(mesh->GeometryOwner() == mesh){
            for(RndMesh::Vert* it = mesh->Verts().begin(); it != mesh->Verts().end(); ++it){
                it->pos *= f1;
            }
            mesh->Sync(0x1F);
            Transform tf78;
            tf78.m.Set(f1, 0, 0, 0, f1, 0, 0, 0, f1);
            tf78.v.Zero();
            MultiplyEq(mesh->GetBSPTree(), tf78);
        }
        mesh->ScaleBones(f1);
        return;
    }
    RndMeshAnim* meshanim = dynamic_cast<RndMeshAnim*>(o);
    if(meshanim){
        if(meshanim->KeysOwner() == meshanim){
            for(Keys<std::vector<Vector3>, std::vector<Vector3> >::iterator it = meshanim->VertPointsKeys().begin(); it != meshanim->VertPointsKeys().end(); ++it){
                for(std::vector<Vector3>::iterator vit = it->value.begin(); vit != it->value.end(); ++vit){
                    *vit *= f1;
                }
            }
            ScaleFrame(meshanim->VertNormalsKeys(), f2);
            ScaleFrame(meshanim->VertPointsKeys(), f2);
            ScaleFrame(meshanim->VertTexsKeys(), f2);
            ScaleFrame(meshanim->VertColorsKeys(), f2);
        }
        return;
    }
    RndMorph* morph = dynamic_cast<RndMorph*>(o);
    if(morph){
        for(int i = 0; i < morph->NumPoses(); i++){
            morph->PoseAt(i);
            // scaleframe
        }
        return;
    }
    RndMultiMesh* multimesh = dynamic_cast<RndMultiMesh*>(o);
    if(multimesh){
        for(std::list<RndMultiMesh::Instance>::iterator it = multimesh->mInstances.begin(); it != multimesh->mInstances.end(); ++it){
            (*it).mXfm.v *= f1;
        }
        return;
    }
    RndParticleSys* partsys = dynamic_cast<RndParticleSys*>(o);
    if(partsys){
        partsys->SetBubbleSize(partsys->mBubbleSize.x * f1, partsys->mBubbleSize.y * f1);
        partsys->SetBubblePeriod(partsys->mBubblePeriod.x * f1, partsys->mBubblePeriod.y * f1);
        partsys->SetLife(partsys->mLife.x * f1, partsys->mLife.y * f1);
        partsys->SetEmitRate(partsys->mEmitRate.x / f1, partsys->mEmitRate.y / f1);
        Vector3 vb0 = partsys->mForceDir;
        vb0 *= (f1 / f2) / f2;
        partsys->SetForceDir(vb0);
        Vector3 box1, box2;
        Scale(partsys->mBoxExtent1, f1, box1);
        Scale(partsys->mBoxExtent2, f1, box2);
        partsys->SetBoxExtent(box1, box2);
        partsys->SetSpeed((partsys->mSpeed.x * f1) / f2, (partsys->mSpeed.y * f1) / f2);
        partsys->SetStartSize(partsys->mStartSize.x * f1, partsys->mStartSize.y * f1);
        partsys->SetDeltaSize(partsys->mDeltaSize.x * f1, partsys->mDeltaSize.y * f1);
        return;
    }
    RndParticleSysAnim* partsysanim = dynamic_cast<RndParticleSysAnim*>(o);
    if(partsysanim){
        if(partsysanim->KeysOwner() == partsysanim){
            ScaleFrame(partsysanim->StartColorKeys(), f2);
            ScaleFrame(partsysanim->EndColorKeys(), f2);
            ScaleFrame(partsysanim->EmitRateKeys(), f2);
            ScaleFrame(partsysanim->SpeedKeys(), f2);
            ScaleFrame(partsysanim->LifeKeys(), f2);
            ScaleFrame(partsysanim->StartSizeKeys(), f2);
        }
        return;
    }
    RndTransAnim* transanim = dynamic_cast<RndTransAnim*>(o);
    if(transanim){
        if(transanim->KeysOwner() == transanim){
            for(Keys<Vector3, Vector3>::iterator it = transanim->TransKeys().begin(); it != transanim->TransKeys().end(); ++it){
                it->value *= f1;
            }
            ScaleFrame(transanim->TransKeys(), f2);
            ScaleFrame(transanim->RotKeys(), f2);
            ScaleFrame(transanim->ScaleKeys(), f2);
        }
        return;    
    }
}

void SortXfms(RndMultiMesh*, const Vector3&) {
    MILO_ASSERT(0, 3150);
}

void RandomXfms(RndMultiMesh*) {
    MILO_ASSERT(0, 3173);
}

DECOMP_FORCEACTIVE(Utl, "\\og\\", "/og/", "\\ng\\", "/ng/", "system", "ng")

void ScrambleXfms(RndMultiMesh* mm){
    for(std::list<RndMultiMesh::Instance>::iterator it = mm->mInstances.begin(); it != mm->mInstances.end(); ++it){
        Vector3 v48(RandomFloat(-1.0f, 1.0f), RandomFloat(-1.0f, 1.0f), RandomFloat(-1.0f, 1.0f));
        Normalize(v48, v48);
        MakeRotMatrix(Hmx::Quat(v48, RandomFloat(0, 6.283f)), it->mXfm.m);
    }
}

void DistributeXfms(RndMultiMesh* mm, int i, float f){
    int idx = 0;
    for(std::list<RndMultiMesh::Instance>::iterator it = mm->mInstances.begin(); it != mm->mInstances.end(); ++it){
        Vector3 v5c((float)(idx % i) * f, (float)(idx / i) * f, 0);
        Add(it->mXfm.v, v5c, it->mXfm.v);
        ++idx;
    }
}

void MoveXfms(RndMultiMesh* mm, const Vector3& v) {
    for (std::list<RndMultiMesh::Instance>::iterator i = mm->mInstances.begin(); i != mm->mInstances.end(); ++i) {
        Add(i->mXfm.v, v, i->mXfm.v);
    }
}

void ScaleXfms(RndMultiMesh* mm, const Vector3& v){
    for (std::list<RndMultiMesh::Instance>::iterator i = mm->mInstances.begin(); i != mm->mInstances.end(); ++i) {
        Scale(v, i->mXfm.m, i->mXfm.m);
    }
}

const char* MovieExtension(const char* cc, Platform plat){
    if(stricmp(cc, "xbv") == 0){
        if(plat - 2U <= 3){
            return "xbv";
        }
        return cc;
    }
    else return nullptr;
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

const char* CacheResource(const char* cc, CacheResourceResult& res){
    Platform thisPlatform = TheLoadMgr.GetPlatform();
    res = kCacheUnnecessary;
    char buf[256];
    const char* localized = FileLocalize(cc, buf);
    bool islocal = FileIsLocal(localized);
    const char* ext = FileGetExt(localized);
    if(stricmp(ext, "bmp") != 0 && stricmp(ext, "png") != 0){
        const char* movieExt = MovieExtension(ext, thisPlatform);
        if(movieExt){
            return MakeString("%s/%s.%s", FileGetPath(localized, 0), FileGetBase(localized, 0), movieExt);
        }
        else {
            res = kCacheUnknownExtension;
            return nullptr;
        }
    }
    else {
        if(TheLoadMgr.GetPlatform() == kPlatformPS3){
            const char* xboxStr = strstr(localized, "_xbox");
            if(xboxStr){
                static char* ps3File;
                strcpy(ps3File, localized);
                int ps3Idx = xboxStr - localized;
                strcpy(ps3File + ps3Idx, "_ps3");
                strcpy(ps3File + ps3Idx + 4, xboxStr + 5);
            }
        }
        static char* cacheFile;
        strcpy(cacheFile, MakeString("%s/gen/%s.%s_%s", FileGetPath(localized, 0), FileGetBase(localized, 0), FileGetExt(localized), PlatformSymbol(thisPlatform)));
        // the rest relies on AsyncFileWii and Holmes
    }
}

DataNode DataFindEnviron(DataArray* da) {
    return FindEnviron(da->Obj<RndDrawable>(1));
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

DECOMP_FORCEACTIVE(Utl, "%d animated meshes reset", "%d tex xfms collapsed", "%d rendered textures reset", "%d items deleted from unused buffers",
    "%d materials converted to Src\n%d materials converted to Add", "%d objects reordered", "Camera Y Field of View is 0")

void RndUtlTerminate(){
    delete sSphereDir;
    sSphereDir = 0;
    sSphereMesh = 0;
}

// fn_806598A0
float ConvertFov(float a, float b) {
    float x = tanf(0.5f * a);
    return atanf(b * x) * 2;
}

// fn_806598F4
void ListDrawGroups(RndDrawable* draw, class ObjectDir* dir, std::list<RndGroup*>& gList){
    for(ObjDirItr<RndGroup> it(dir, true); it != 0; ++it){
        std::vector<RndDrawable *>& draws = it->mDraws;
        if(std::find(draws.begin(), draws.end(), draw) != draws.end())
        // if(VectorFind(it->mDraws, draw))
        {
            gList.push_back(it);
        }
    }
}

// fn_806599A4
DataNode OnTestDrawGroups(DataArray* da){
    DataArray* arr = 0;
    class ObjectDir* dir = da->Obj<class ObjectDir>(2);
    if(da->Size() > 3) arr = da->Array(3);
    for(ObjDirItr<RndDrawable> it(dir, true); it; ++it){
        std::list<RndGroup*> gList;
        ListDrawGroups(it, dir, gList);
        if(arr){
            for(std::list<RndGroup*>::iterator gListIt = gList.begin(); gListIt != gList.end(); gListIt){
                bool canerase = false;
                for(int i = 0; i < arr->Size(); i++){
                    if(streq((*gListIt)->Name(), arr->Str(i))){
                        canerase = true;
                        break;
                    }
                }
                if(canerase) gListIt = gList.erase(gListIt);
                else ++gListIt;
            }
        }
        if(gList.size() > 1){
            class String str(MakeString("%s is in %d groups:", PathName(it), gList.size()));
            for(std::list<RndGroup*>::iterator gListIt = gList.begin(); gListIt != gList.end(); ++gListIt){
                str << " " << PathName(*gListIt);
            }
            MILO_WARN(str.c_str());
        }
    }
    return 0;
}

// fn_80659D74
void TestTextureSize(class ObjectDir* dir, int iType, int i3, int i4, int i5, int maxBpp){
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
void TestTexturePaths(class ObjectDir* dir){
    class String str(FileRoot());
    FileNormalizePath(str.c_str());
    for(ObjDirItr<RndTex> it(dir, true); it != 0; ++it){
        FilePath fp(it->mFilepath);
        if(fp.empty()) continue;
        class String relative(FileRelativePath(FileRoot(), fp.c_str()));
        FileNormalizePath(str.c_str());
        const char* normalized = relative.c_str();
        if(strstr(relative.c_str(), "..") == relative.c_str()){
            if(strstr(relative.c_str(), "../../system/run") != normalized){
                MILO_WARN("%s: %s is outside project path", PathName(it), relative);
            }
        }
        const char* normalized2 = relative.c_str();
        if(strlen(normalized2) > 2 && normalized2[1] == ':'){
            MILO_WARN("%s: %s is outside project path", PathName(it), relative);
        }
    }
    if(dir->Loader()){
        const char* fpstr = dir->Loader()->mFile.c_str();
        const char* ng = strstr(fpstr, "/ng/"); // something's up with this part here
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

void TestMaterialTextures(class ObjectDir*){}

void SwapDxtEndianness(RndBitmap* bmap){
    u16* pixels = bmap->Pixels();
    u16* end = (u16*)((u8*)pixels + bmap->PixelBytes());
    for(; pixels < end; pixels++){
        *pixels = EndianSwap(*pixels);
    }
}

void PreMultiplyAlpha(Hmx::Color& c) {
    c.red *= c.alpha;
    c.green *= c.alpha;
    c.blue *= c.alpha;
}

MatShaderOptions GetDefaultMatShaderOpts(const Hmx::Object* o, RndMat* mat){
    MatShaderOptions opts;
    const RndMesh* mesh = dynamic_cast<const RndMesh*>(o);
    if(mesh){
        if(mesh->Mat() == mat){
            opts.SetLast5(0x12);
            opts.SetHasBones(mesh->NumBones() != 0);
            opts.SetHasAOCalc(mesh->HasAOCalc());
        }
        goto ret;
    }
    const RndMultiMesh* multimesh = dynamic_cast<const RndMultiMesh*>(o);
    if(multimesh){
        RndMesh* gotmesh = multimesh->GetMesh();
        if(gotmesh && gotmesh->Mat()){
            if(gotmesh->Mat() == mat){
                int mask = gotmesh->TransConstraint() == RndTransformable::kFastBillboardXYZ ? 0xD : 0xC;
                opts.SetLast5(mask);
                opts.SetHasBones(false);
                opts.SetHasAOCalc(gotmesh->HasAOCalc());
            }
        }
        goto ret;
    }
    const RndParticleSys* partsys = dynamic_cast<const RndParticleSys*>(o);
    if(partsys){
        if(partsys->GetMat() == mat){
            opts.SetLast5(0xE);
        }
        goto ret;
    }
    const RndFlare* flare = dynamic_cast<const RndFlare*>(o);
    if(flare){
        if(flare->GetMat() == mat){
            opts.SetLast5(6);
        }
        goto ret;
    }
ret:
    return opts;
}

DataNode GetNormalMapTextures(class ObjectDir* dir){
    DataArrayPtr ptr(new DataArray(0x100));
    int idx = 0;
    ptr->Node(idx++) = NULL_OBJ;
    for(ObjDirItr<RndTex> it(dir, true); it; ++it){
        bool b1 = false;
        FilePath fp(it->File());
        if(strstr(FileGetBase(fp.c_str(), 0), "_norm")){
            b1 = true;
        }
        else {
            if(fp.empty()){
                if(it->IsRendered()) b1 = true;
            }
        }
        if(b1){
            ptr->Node(idx++) = DataNode(it);
        }
    }
    ptr->Resize(idx);
    return ptr;
}

DECOMP_FORCEACTIVE(Utl, "from < DIM(xRatio) && to < DIM(xRatio)")

DataNode GetTexturesOfType(class ObjectDir* dir, RndTex::Type texType){
    int num = 0;
    for(ObjDirItr<RndTex> it(dir, true); it != 0; ++it){
        if(texType == (texType & it->GetType())){
            num++;
        }
    }
    DataArrayPtr ptr(new DataArray(num + 1));
    num = 0;
    for(ObjDirItr<RndTex> it(dir, true); it != 0; ++it){
        if(texType == (texType & it->GetType())){
            ptr->Node(num++) = DataNode(it);
        }
    }
    ptr->Node(num) = NULL_OBJ;
    return ptr;
}

DataNode GetRenderTextures(class ObjectDir* dir){
    return GetTexturesOfType(dir, RndTex::kRendered);
}

DataNode GetRenderTexturesNoZ(class ObjectDir* dir){
    return GetTexturesOfType(dir, RndTex::kRenderedNoZ);
}

void SetRndSplasherCallback(SplashFunc func1, SplashFunc func2, SplashFunc func3){
    gSplashPoll = func1;
    gSplashSuspend = func2;
    gSplashResume = func3;
}

void RndSplasherSuspend(){
    if(gSplashSuspend) gSplashSuspend();
}

void RndSplasherResume(){
    if(gSplashResume) gSplashResume();
}

void ResetColors(std::vector<Hmx::Color>& colors, int newNumColors){
    colors.resize(newNumColors);
    for(int i = 0; i < newNumColors; i++){
        colors[i].Reset();
    }
}

bool ShouldStrip(RndTransformable* trans){
    if(!trans) return false;
    else {
        const char* name = trans->Name();
        if(name){
            return strnicmp("bone_", name, 5) == 0 || strnicmp("exo_", name, 4) == 0 || strncmp("spot_", name, 5) == 0;
        }
        else return false;
    }
}

void ConvertBonesToTranses(class ObjectDir* dir, bool b){
    std::list<RndMesh*> meshes;
    for(ObjDirItr<RndMesh> it(dir, true); it != 0; ++it){
        RndTransformable* itTrans = it;
        if(ShouldStrip(itTrans)){
            meshes.push_back(it);
        }
        else {
            if(b){
                bool b1 = false;
                std::vector<ObjRef*>::reverse_iterator rit = it->mRefs.rbegin();
                std::vector<ObjRef*>::reverse_iterator ritEnd = it->mRefs.rend();
                for(; !b1 && rit != ritEnd; ++rit){
                    RndMesh* curRefOwner = dynamic_cast<RndMesh*>((*rit)->RefOwner());
                    if(curRefOwner){
                        for(int i = 0; i < curRefOwner->NumBones(); i++){
                            if(curRefOwner->BoneTransAt(i) == itTrans){
                                meshes.push_back(it);
                                b1 = true;
                                break;
                            }   
                        }
                    }
                }
            }
        }
    }
    while(!meshes.empty()){
        ReplaceObject(meshes.front(), Hmx::Object::New<RndTransformable>(), true, true, true);
        meshes.pop_front();
    }
    for(ObjDirItr<RndTransformable> it(dir, true); it != 0; ++it){
        if(strncmp("spot_", it->Name(), 5) == 0){
            Normalize(it->mLocalXfm.m, it->DirtyLocalXfm().m);
        }
    }
}