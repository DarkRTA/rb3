#include "world/CameraShot.h"
#include "world/Spotlight.h"
#include "world/Crowd.h"
#include "rndobj/Trans.h"
#include "rndobj/TransProxy.h"
#include "rndobj/Utl.h"

INIT_REVS(CamShot);

CamShot::CamShot() : mKeyFrames(this), mLoopKeyframe(0), mNear(1.0f), mFar(1000.0f), mFilter(0.9f), mClampHeight(-1.0f), mCategory(), 
    mAnims(this, kObjListNoNull), mPath(this, 0), mDrawOverrides(this, kObjListNoNull), mPathFrame(-1.0f), mPlatformOnly(0),
    mPostProcOverrides(this, kObjListNoNull), mCrowds(this), mGlowSpot(this, 0), unkc4(0.0f, 0.0f, 0.0f), unkd0(0.0f, 0.0f, 0.0f),
    unkdc(0.0f, 0.0f, 0.0f), unke8(0.0f, 0.0f, 0.0f), unkf4(0.0f, 0.0f, 0.0f), unk100(0.0f, 0.0f, 0.0f), unk10c(0), unk110(0),
    mDuration(0.0f), mDisabled(0), unk11c(0), mLooping(1), mUseDepthOfField(0), mPS3PerPixel(0) {

}

#pragma push
#pragma dont_inline on
BEGIN_COPYS(CamShot)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    CREATE_COPY(CamShot)
    BEGIN_COPYING_MEMBERS
        mKeyFrames.clear();
        for(int i = 0; i != c->mKeyFrames.size(); i++){
            mKeyFrames.push_back(CamShotFrame(this, c->mKeyFrames[i]));
        }
        mCrowds.clear();
        for(int i = 0; i != c->mCrowds.size(); i++){
            mCrowds.push_back(CamShotCrowd(this, c->mCrowds[i]));
        }
        COPY_MEMBER(mNear)
        COPY_MEMBER(mFar)
        COPY_MEMBER(mUseDepthOfField)
        COPY_MEMBER(mFilter)
        COPY_MEMBER(mClampHeight)
        COPY_MEMBER(mPath)
        COPY_MEMBER(mPlatformOnly)
        COPY_MEMBER(mCategory)
        COPY_MEMBER(unk5c)
        COPY_MEMBER(unk6c)
        COPY_MEMBER(unk6c)
        COPY_MEMBER(unk64)
        COPY_MEMBER(mLooping)
        COPY_MEMBER(mLoopKeyframe)
        COPY_MEMBER(mGlowSpot)
        COPY_MEMBER(mDrawOverrides)
        COPY_MEMBER(mPostProcOverrides)
        COPY_MEMBER(mPS3PerPixel)
        COPY_MEMBER(unk11c)
        COPY_MEMBER(mAnims)
        CacheFrames();
    END_COPYING_MEMBERS
END_COPYS
#pragma pop

RndTransformable* LoadSubPart(BinStream& bs, CamShot* shot){
    if(CamShot::gRev < 0x2B){
        int dummy;
        bs >> dummy;
    }
    String str;
    bs >> str;
    Symbol sym;
    bs >> sym;
    if(str.empty()) return 0;
    RndTransformable* foundTrans = dynamic_cast<RndTransformable*>(shot->Dir()->FindObject(str.c_str(), false));
    if(sym.Null()){
        if(foundTrans) return foundTrans;
        TheDebug << MakeString("%s could not find %s, assuming character, attaching to base\n", PathName(shot), str);
    }
    char buf[256];
    strcpy(buf, sym.Str());
    char* buf_ptr = strchr(buf, '.');
    if(buf_ptr) *buf_ptr = '\0';
    else if(buf[0] == '\0'){
        strcpy(buf, "base");
    }
    const char* search = MakeString("%s_%s.tp", str, buf);
    RndTransProxy* proxy = dynamic_cast<RndTransProxy*>(shot->Dir()->FindObject(search, false));
    if(!proxy){
        proxy = Hmx::Object::New<RndTransProxy>();
        proxy->SetName(search, shot->Dir());
        // proxy->SetProxy(dynamic_cast<ObjectDir>(foundTrans));
        proxy->SetPart(sym);
    }
    return proxy;
}

SAVE_OBJ(CamShot, 0x409);

#pragma push
#pragma dont_inline on
BEGIN_LOADS(CamShot)
    LOAD_REVS(bs)
    ASSERT_REVS(0x32, 1)
    if(unk120p2) UnHide();
    float somefloat = 0.0f;
    if(gRev != 0){
        LOAD_SUPERCLASS(Hmx::Object)
        LOAD_SUPERCLASS(RndAnimatable)
    }
    if(gRev > 0xC){
        bs >> mKeyFrames;
        bool b;
        bs >> b;
        mLooping = b;
        if(gRev > 0x1E) bs >> mLoopKeyframe;
        else mLoopKeyframe = 0;
        if(gRev < 0x28) bs >> somefloat;
        bs >> mNear;
        bs >> mFar;
        bool bb;
        bs >> bb;
        mUseDepthOfField = bb;
        bs >> mFilter;
        bs >> mClampHeight;
    }
    else {
        mLoopKeyframe = 0;
        mLooping = false;
        float f1, f2;
        bs >> f1;
        bs >> f2;
        if(gRev < 9){
            f1 = ConvertFov(f1, 0.75f);
            f2 = ConvertFov(f2, 0.75f);
        }
        Transform tf1;
        Transform tf2;
        bs >> tf1;
        bs >> tf2;
        Vector2 vec1;
        Vector2 vec2;
        bs >> vec1;
        bs >> vec2;
        if(gRev < 0x28) bs >> somefloat;
        float fdummy1;
        bool b;
        bs >> fdummy1;
        bs >> mNear;
        bs >> mFar;
        bs >> b;
        mUseDepthOfField = b;
        float someotherfloat = 1.0f;
        if(gRev > 9){
            float f;
            float ff, ff2;
            bs >> f >> ff >> ff2;
            someotherfloat = someotherfloat - f;
        }
        if(gRev < 4){
            bool bbb;
            bs >> bbb;
            SetRate((Rate)!bbb);
        }
        bs >> mFilter;
        if(gRev < 7) mFilter = 0.9f;
        bs >> mClampHeight;
        ObjPtrList<RndTransformable, ObjectDir> pList(this, kObjListNoNull);
        ObjPtr<RndTransformable, ObjectDir> ptr(this, 0);
        int listsize;
        bs >> listsize;
        for(int i = 0; i < listsize; i++){
            RndTransformable* subpart = LoadSubPart(bs, this);
            if(subpart) pList.push_back(subpart);
        }
        ptr = LoadSubPart(bs, this);
        bool somebool = false;
        if(gRev > 10) bs >> somebool;
        CamShotFrame csf1(this);
        CamShotFrame csf2(this);
        if(fdummy1 > 0.0f){
            float locf1 = 0.0f;
            float locf2 = fdummy1;
            TransformNoScale tns;
            tns.Set(tf1);
            Vector2 locv;
            locv = vec1;
            // more
        }
        // more
    }
    bs >> mPath;
    if(gRev - 2 < 0x2B){
        float f2b;
        bs >> f2b;
    }
    if(gRev > 2){
        bs >> mCategory;
        if(gRev < 0x26){
            float f26;
            bs >> f26;
        }
    }
    if(gRev >= 0x23) bs >> mPlatformOnly;
    if(gRev > 0x21){
        int state;
        bs >> state;
        if(state == 1) mPlatformOnly = 2;
        else if(state == 2) mPlatformOnly = 4;
        else mPlatformOnly = 0;
    }
    if(gRev == 0) LOAD_SUPERCLASS(RndAnimatable)
    CamShotCrowd csc(this);
END_LOADS
#pragma pop