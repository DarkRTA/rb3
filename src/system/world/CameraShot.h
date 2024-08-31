#ifndef WORLD_CAMERASHOT_H
#define WORLD_CAMERASHOT_H
#include "rndobj/Anim.h"
#include "rndobj/TransAnim.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"

class CamShot;
class Spotlight;
class WorldCrowd;

// size 0x8c
class CamShotFrame {
public:
    CamShotFrame(Hmx::Object*);
    CamShotFrame(Hmx::Object*, const CamShotFrame&);
    void Load(BinStream&);
    bool OnSyncTargets(ObjPtrList<RndTransformable, ObjectDir>&, DataNode&, DataArray*, int, PropOp);
    bool OnSyncParent(ObjPtr<RndTransformable, ObjectDir>&, DataNode&, DataArray*, int, PropOp);
    bool HasTargets() const;
    void GetCurrentTargetPosition(Vector3&) const;
    void UpdateTarget() const;
    void Interp(const CamShotFrame&, float, float, RndCam*);
    bool SameTargets(const CamShotFrame&) const;
    void BuildTransform(RndCam*, Transform&, bool) const;
    const Vector2 MaxAngularOffset() const;

    float BlurDepth() const { return mBlurDepth * 0.0039215689f; }
    float MaxBlur() const { return mMaxBlur * 0.0039215689f; }
    float MinBlur() const { return mMinBlur * 0.0039215689f; }
    float ZoomFieldOfView() const { return mZoomFOV * 0.012319971f; }
    float FieldOfView() const { return mFOV * 0.012319971f; }
    void SetZoomFieldOfView(float f){ mZoomFOV = f * 81.16902f; }
    void SetFieldOfView(float f){ mFOV = f * 81.16902f; }
    void SetBlurDepth(float f){ mBlurDepth = f * 255.0f; }
    void SetMaxBlur(float f){ mMaxBlur = f * 255.0f; }
    void SetMinBlur(float f){ mMinBlur = f * 255.0f; }
    void SetMaxAngularOffset(const Vector2& v){
        mMaxAngularOffsetX = v.x * 81.16902f;
        mMaxAngularOffsetY = v.y * 81.16902f;
    }

    float mDuration; // 0x0
    float mBlend; // 0x4
    float mBlendEase; // 0x8
    float unkc;
    TransformNoScale unk10;
    Vector2 mScreenOffset; // 0x24
    float mShakeNoiseAmp; // 0x2c
    float mShakeNoiseFreq; // 0x30
    Vector3 unk34;
    float mFocusBlurMultiplier; // 0x40
    TransformNoScale unk44;
    ObjPtrList<RndTransformable, ObjectDir> mTargets; // 0x58
    CamShot* unk68;
    ObjPtr<RndTransformable, ObjectDir> mParent; // 0x6c
    ObjPtr<RndTransformable, ObjectDir> mFocusTarget; // 0x78
    mutable unsigned char mFOV; // 0x84
    mutable char mZoomFOV; // 0x85
    mutable unsigned char mBlurDepth; // 0x86
    unsigned char mMaxBlur; // 0x87
    unsigned char mMinBlur; // 0x88
    unsigned char mMaxAngularOffsetX; // 0x89
    unsigned char mMaxAngularOffsetY; // 0x8a
    unsigned char mBlendEaseMode : 6; // 0x8b >> 2 & 1
    unsigned char unk8bp1 : 1;
    unsigned char unk8bp0 : 1;
    // mUseParentNotation: 0x8b >> 1 & 1
    // mParentFirstFrame: 0x8b & 1
    // mFieldOfView: 0x84, lensMM, lensPreset
    // mZoomFOV: 0x85
};

inline BinStream& operator>>(BinStream& bs, CamShotFrame& csf){
    csf.Load(bs);
    return bs;
}

// size 0x1c
class CamShotCrowd {
public:
    CamShotCrowd(Hmx::Object*);
    CamShotCrowd(Hmx::Object*, const CamShotCrowd&);

    void Set3DCrowd();
    void Load(BinStream&);
    void ClearCrowdChars();
    void AddCrowdChars();
    void SetCrowdChars();
    void OnCrowdChanged();
    void ClearCrowdList();
    void GetSelectedCrowd(std::list<std::pair<RndMultiMesh*, std::list<RndMultiMesh::Instance>::iterator> >&);
    void AddCrowdChars(std::list<std::pair<RndMultiMesh*, std::list<RndMultiMesh::Instance>::iterator> >&);
    
    ObjPtr<WorldCrowd, ObjectDir> mCrowd; // 0x0
    int mCrowdRotate; // 0xc
    std::vector<std::pair<int, int> > unk10; // 0x10
    CamShot* unk18; // 0x18
};

inline BinStream& operator>>(BinStream& bs, CamShotCrowd& csc){
    csc.Load(bs);
    return bs;
}

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
    virtual void SetPreFrame(float, float){}
    virtual void CurrentShot(){}
    virtual bool CheckShotStarted();
    virtual bool CheckShotOver(float);

    void CacheFrames();
    void DoHide();
    void UnHide();
    bool ShotOk(CamShot*);
    bool PlatformOk() const;
    int Disabled() const { return mDisabled; }
    int Flags() const { return mFlags; }
    float GetDurationSeconds() const;
    RndCam* GetCam();
    void SetShotOver();
    bool SetPos(CamShotFrame&, RndCam*);
    void Shake(float, float, const Vector2&, Vector3&, Vector3&);
    void Disable(bool, int);

    DataNode OnHasTargets(DataArray*);
    DataNode OnSetPos(DataArray*);
    DataNode OnSetCrowdChars(DataArray*);
    DataNode OnAddCrowdChars(DataArray*);
    DataNode OnClearCrowdChars(DataArray*);
    DataNode OnGetOccluded(DataArray*);
    DataNode OnSetAllCrowdChars3D(DataArray*);
    DataNode OnRadio(DataArray*);

    DECLARE_REVS;
    NEW_OBJ(CamShot);
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(CamShot)
    }
    static Hmx::Object* sAnimTarget;

    ObjVector<CamShotFrame> mKeyFrames; // 0x10
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
    std::vector<RndDrawable*> unk5c;
    std::vector<RndDrawable*> unk64;
    std::vector<RndDrawable*> unk6c;
    std::vector<RndDrawable*> unk74;
    ObjPtrList<RndDrawable, ObjectDir> mDrawOverrides; // 0x7c
    ObjPtrList<RndDrawable, ObjectDir> mPostProcOverrides; // 0x8c
    ObjVector<CamShotCrowd> mCrowds; // 0x9c
    ObjPtr<Spotlight, ObjectDir> mGlowSpot; // 0xa8
    std::vector<RndDrawable*> unkb4;
    std::vector<RndDrawable*> unkbc;
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
    int mFlags; // 0x11c
    bool mLooping : 1; // 0x120 >> 7
    bool mUseDepthOfField : 1; // 0x120 >> 6 & 1
    bool mPS3PerPixel : 1; // 0x120 >> 5 & 1
    bool unk120p4 : 1;
    bool mShotOver : 1; // 0x120 >> 3 & 1
    bool mHidden : 1; // 0x120 >> 2 & 1
    bool unk120p1 : 1;
    bool unk120p0 : 1;
};

void LoadDrawables(BinStream&, std::vector<RndDrawable*>&, ObjectDir*);

#endif
