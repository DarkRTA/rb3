#ifndef WORLD_CAMERASHOT_H
#define WORLD_CAMERASHOT_H
#include "rndobj/Anim.h"
#include "rndobj/TransAnim.h"
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"

class Spotlight;

// CamShotFrame and CamShotCrowd class headers go here

class CamShot : public RndAnimatable {
public:
    CamShot();
    OBJ_CLASSNAME(CamShot);
    OBJ_SET_TYPE(CamShot);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~CamShot();
    
    virtual void StartAnim();
    virtual void EndAnim();
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget();
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;
    virtual void SetPreFrame(float, float);
    virtual void CurrentShot(){}
    virtual bool CheckShotStarted();
    virtual bool CheckShotOver(float);

    ObjVector<int> mKeyFrames; // 0x10 - CamShotFrame
    int mLoopKeyframe; // 0x1c
    float mNear; // 0x20
    float mFar; // 0x24
    float mFilter; // 0x28
    float mClampHeight; // 0x2c
    Symbol mCategory; // 0x30
    int unk34;
    ObjPtrList<RndAnimatable, ObjectDir> mAnims; // 0x38
    ObjPtr<RndTransAnim, ObjectDir> mPath; // 0x48
    float mPathFrame; // 0x54
    int mPlatformOnly; // 0x58 - enum Platform?
    std::vector<int> unk5c;
    std::vector<int> unk64;
    std::vector<int> unk6c;
    std::vector<int> unk74;
    ObjPtrList<RndDrawable, ObjectDir> mDrawOverrides; // 0x7c
    ObjPtrList<RndDrawable, ObjectDir> mPostProcOverrides; // 0x8c
    ObjVector<int> mCrowds; // 0x9c - CamShotCrowd
    ObjPtr<Spotlight, ObjectDir> mGlowSpot; // 0xa8
    std::vector<int> unkb4;
    std::vector<int> unkbc;
    Vector3 unkc4;
    Vector3 unkd0;
    Vector3 unkdc;
    Vector3 unke8;
    Vector3 unkf4;
    Vector3 unk100;
    int unk10c;
    int unk110;
    float mDuration; // 0x114
    int mDisabled; // 0x118
    int unk11c;
    bool mLooping : 1; // 0x120 >> 7
    bool mUseDepthOfField : 1; // 0x120 >> 6 & 1
    bool mPS3PerPixel : 1; // 0x120 >> 5 & 1
};

#endif