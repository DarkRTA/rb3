#pragma once
#include "rndobj/Anim.h"
#include "rndobj/Env.h"
#include "rndobj/TransAnim.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "utl/Symbol.h"

class CamShot;
class Spotlight;
class WorldCrowd;

// size 0x8c
class CamShotFrame {
public:
    enum BlendEaseMode {
        /** "blend in and out the same amount" */
        kBlendEaseInAndOut = 0,
        /** "slow rate of change, then fast" */
        kBlendEaseIn = 1,
        /** "fast rate of change, then slow" */
        kBlendEaseOut = 2
    };

    CamShotFrame(Hmx::Object*);
    CamShotFrame(Hmx::Object*, const CamShotFrame&);
    void Load(BinStream&);
    bool OnSyncTargets(ObjPtrList<RndTransformable>&, DataNode&, DataArray*, int, PropOp);
    bool OnSyncParent(ObjPtr<RndTransformable>&, DataNode&, DataArray*, int, PropOp);
    bool HasTargets() const;
    void GetCurrentTargetPosition(Vector3&) const;
    void UpdateTarget() const;
    void Interp(const CamShotFrame&, float, float, RndCam*);
    bool SameTargets(const CamShotFrame&) const;
    void BuildTransform(RndCam*, Transform&, bool) const;
    const Vector2& MaxAngularOffset() const {
        return Vector2(mMaxAngularOffset[0] * 0.012319971f, mMaxAngularOffset[1] * 0.012319971f);
    }

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
        mMaxAngularOffset[0] = v.x * 81.16902f;
        mMaxAngularOffset[1] = v.y * 81.16902f;
    }

    /** "Duration this keyframe holds steady" */
    float mDuration; // 0x0
    /** "Duration this keyframe blends into the next one" */
    float mBlend; // 0x4
    /** "Amount to ease into this keyframe" */
    float mBlendEase; // 0x8
    float mFrame; // 0xc
    /** "Camera position for this keyframe" */
    TransformNoScale mWorldOffset; // 0x10
    /** "Screen space offset of target for this keyframe" */
    Vector2 mScreenOffset; // 0x24
    /** "Noise amplitude for camera shake" */
    float mShakeNoiseAmp; // 0x2c
    /** "Noise frequency for camera shake" */
    float mShakeNoiseFreq; // 0x30
    Vector3 mLastTargetPos; // 0x34
    /** "Multiplier of distance from camere to focal target. Offsets focal point of blur. */
    float mFocusBlurMultiplier; // 0x40
    TransformNoScale unk44;
    /** "Target(s) that the camera should look at" */
    ObjPtrList<RndTransformable> mTargets; // 0x58
    CamShot* mCamShot; // 0x68
    /** "Parent that the camera should attach itself to" */
    ObjPtr<RndTransformable> mParent; // 0x6c
    /** "The focal point when calculated depth of field" */
    ObjPtr<RndTransformable> mFocusTarget; // 0x78
    /** "Field of view, in degrees, for this keyframe. Same as setting lens focal length below" */
    mutable unsigned char mFOV; // 0x84
    /** "Field of view adjustment (not affected by target reframing)" */
    mutable char mZoomFOV; // 0x85
    /** "0 to 1 scale representing the Depth size of the blur valley 
     * (offset from the focal target + focus_blur_multiplier) 
     * in the Camera Frustrum. Zero puts everything in Blur. 
     * 1 puts everything in the Blur falloff valley." */
    mutable unsigned char mBlurDepth; // 0x86
    /** "Maximum blurriness" */
    unsigned char mMaxBlur; // 0x87
    /** "Minimum blurriness" */
    unsigned char mMinBlur; // 0x88
    char mMaxAngularOffset[2]; // 0x89 - X and Y
    /** "Amount to ease out to the next keyframe" */
    unsigned char mBlendEaseMode : 6; // 0x8b >> 2 & 1
    /** "Whether to take the parent object's rotation into account" */
    unsigned char mUseParentNotation : 1; // 0x8b >> 1 & 1
    /** "Only parent on the first frame" */
    unsigned char mParentFirstFrame : 1; // 0x8b & 1
    // mFieldOfView: 0x84, lensMM, lensPreset
    // mZoomFOV: 0x85
    // lensMM: "Lens focal length for this keyframe. Same as setting field of view above."
    // lens preset: "A preset lens for a 35mm camera that sets the appropriate field of view"
    // shake max angle: "Maximum angle for camera shake"
};

inline BinStream& operator>>(BinStream& bs, CamShotFrame& csf){
    csf.Load(bs);
    return bs;
}

enum CrowdRotate {
    /** "Face along the placement mesh, or along focus, if set" */
    kCrowdRotateNone = 0,
    /** "Face towards the camera" */
    kCrowdRotateFace = 1,
    /** "Face away from the camera" */
    kCrowdRotateAway = 2
};

// size 0x1c
class CamShotCrowd {
public:

    CamShotCrowd(Hmx::Object*);
    CamShotCrowd(Hmx::Object*, const CamShotCrowd&);

    /** "Sets the selected crowd characters to be 3D for this shot" */
    void Set3DCrowd();
    void Load(BinStream&);
    void ClearCrowdChars();
    void AddCrowdChars();
    void SetCrowdChars();
    void OnCrowdChanged();
    void ClearCrowdList();
    void GetSelectedCrowd(std::list<std::pair<RndMultiMesh*, std::list<RndMultiMesh::Instance>::iterator> >&);
    void AddCrowdChars(std::list<std::pair<RndMultiMesh*, std::list<RndMultiMesh::Instance>::iterator> >&);

    // add 3d crowd: "Adds the selected crowd characters to be 3D for this shot"
    // clear 3d crowd: "Clears the list of 3D crowd characters for this shot"
    // set all to 3d: "Sets all crowd characters to 3D for this shot"
    // gen hide list: "Append occluded objects to this cam shot's hide list"
    // clear hide list: "Clear this cam shot's hide list"
    
    /** "The crowd to show for this shot" */
    ObjPtr<WorldCrowd> mCrowd; // 0x0
    /** "How to rotate crowd" */
    CrowdRotate mCrowdRotate; // 0xc
    std::vector<std::pair<int, int> > unk10; // 0x10
    CamShot* unk18; // 0x18
};

inline BinStream& operator>>(BinStream& bs, CamShotCrowd& csc){
    csc.Load(bs);
    return bs;
}

/** "A camera shot. This is an animated camera path with keyframed settings." */
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
    virtual float StartFrame(){ return 0; }
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget();
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;
    virtual void SetPreFrame(float, float){}
    virtual CamShot* CurrentShot(){}
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
    void GetKey(float, CamShotFrame*&, CamShotFrame*&, float&);

    void SetNear(float n){ mNear = n; }
    void SetFar(float f){ mFar = f; }
    float Duration() const { return mDuration; }
    Symbol Category() const { return mCategory; }
    Spotlight* GlowSpot() const { return mGlowSpot; }

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

    /** The collection of keyframes. */
    ObjVector<CamShotFrame> mKeyframes; // 0x10
    /** "If looping true, which keyframe to loop to." */
    int mLoopKeyframe; // 0x1c
    /** "Near clipping plane for the camera" */
    float mNear; // 0x20
    /** "Far clipping plane for the camera" */
    float mFar; // 0x24
    /** "Filter amount" */
    float mFilter; // 0x28
    /** "Height above target's base at which to clamp camera" */
    float mClampHeight; // 0x2c
    /** "Category for shot-picking" */
    Symbol mCategory; // 0x30
    int unk34;
    /** "animatables to be driven with the same frame" */
    ObjPtrList<RndAnimatable> mAnims; // 0x38
    /** "Optional camera path to use" */
    ObjPtr<RndTransAnim> mPath; // 0x48
    float mPathFrame; // 0x54
    /** "Limit this shot to given platform" - the options are kPlatformNone/PS3/Xbox */
    Platform mPlatformOnly; // 0x58
    /** "List of objects to hide while this camera shot is active, shows them when done" */
    std::vector<RndDrawable*> mHideList; // 0x5c
    std::vector<RndDrawable*> unk64;
    /** "List of objects to show while this camera shot is active, hides them when done" */
    std::vector<RndDrawable*> mShowList; // 0x6c
    std::vector<Symbol> unk74;
    /** "List of objects to draw in order instead of whole world" */
    ObjPtrList<RndDrawable> mDrawOverrides; // 0x7c
    /** "List of objects to draw after post-processing" */
    ObjPtrList<RndDrawable> mPostProcOverrides; // 0x8c
    ObjVector<CamShotCrowd> mCrowds; // 0x9c
    /** "The spotlight to get glow settings from" */
    ObjPtr<Spotlight> mGlowSpot; // 0xa8
    std::vector<RndDrawable*> mEndHideList; // 0xb4
    std::vector<RndDrawable*> mEndShowList; // 0xbc
    Vector3 mLastShakeOffset; // 0xc4
    Vector3 mLastShakeAngOffset; // 0xd0
    Vector3 mLastDesiredShakeOffset; // 0xdc
    Vector3 mLastDesiredShakeAngOffset; // 0xe8
    Vector3 mShakeVelocity; // 0xf4
    Vector3 mShakeAngVelocity; // 0x100
    CamShotFrame* mLastNext; // 0x10c
    CamShotFrame* mLastPrev; // 0x110
    /** "duration of the camshot" */
    float mDuration; // 0x114
    /** "disabled bits" */
    int mDisabled; // 0x118
    int mFlags; // 0x11c
    /** "Whether the animation should loop." */
    bool mLooping : 1; // 0x120 >> 7
    /** "Whether to use depth-of-field effect on platforms that support it" */
    bool mUseDepthOfField : 1; // 0x120 >> 6 & 1
    /** "global per-pixel setting for PS3" */
    bool mPS3PerPixel : 1; // 0x120 >> 5 & 1
    bool unk120p4 : 1;
    bool mShotOver : 1; // 0x120 >> 3 & 1
    bool mHidden : 1; // 0x120 >> 2 & 1
    bool unk120p1 : 1;
    bool unk120p0 : 1;

    // gen hide list: "Automatically generated list of objects to hide while this camera shot is active, shows them when done.  Not editable"
};

class AutoPrepTarget {
public:
    AutoPrepTarget(CamShotFrame& frame) : mFrame(&frame), mShot(frame.mCamShot) {
        mShot->StartAnim();
        mOldFilter = mShot->mFilter;
        mOldCamHeight = mShot->mClampHeight;
        mOldZoomFov = mFrame->ZoomFieldOfView();
        mFrame->mZoomFOV = 0;
        mShot->mFilter = 0;
        mShot->mClampHeight = -1.0f;
        mShot->mLastDesiredShakeOffset.Set(0,0,0);
        mShot->mLastDesiredShakeAngOffset.Set(0,0,0);
        mShot->mLastShakeOffset.Set(0,0,0);
        mShot->mLastShakeAngOffset.Set(0,0,0);
        sChanging = true;
        mFrame->UpdateTarget();
        mShot->SetFrame(mFrame->mFrame, 1.0f);
    }

    ~AutoPrepTarget(){
        mShot->SetPos(*mFrame, nullptr);
        mFrame->UpdateTarget();
        mShot->mFilter = mOldFilter;
        mShot->mClampHeight = mOldCamHeight;
        mFrame->SetZoomFieldOfView(mOldZoomFov);
        sChanging = false;
        mShot->EndAnim();
    }

    CamShotFrame* mFrame; // 0x0
    CamShot* mShot; // 0x4
    float mOldFilter; // 0x8
    float mOldCamHeight; // 0xc
    float mOldZoomFov; // 0x10

    static bool sChanging;
};

void LoadDrawables(BinStream&, std::vector<RndDrawable*>&, ObjectDir*);

struct NameSort {
    bool operator()(CamShot* o1, CamShot* o2) const { return strcmp(o1->Name(), o2->Name()) < 0; }
};
