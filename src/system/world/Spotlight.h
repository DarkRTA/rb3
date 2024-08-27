#ifndef WORLD_SPOTLIGHT_H
#define WORLD_SPOTLIGHT_H
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"
#include "rndobj/Poll.h"

class RndFlare;
class RndMesh;
class RndTex;
class RndLight;

class Spotlight : public RndDrawable, public RndTransformable, public RndPollable {
public:

    class BeamDef {
    public:
        BeamDef(Hmx::Object*);
        BeamDef(const BeamDef&);
        ~BeamDef();
        void OnSetMat(RndMat*);
        
        RndMesh* mBeam; // 0x0
        bool mIsCone; // 0x4
        float mLength; // 0x8
        float mTopRadius; // 0xc
        float mRadius; // 0x10
        float mTopSideBorder; // 0x14
        float mBottomSideBorder; // 0x18
        float mBottomBorder; // 0x1c
        float mOffset; // 0x20
        Vector2 mTargetOffset; // 0x24
        float mBrighten; // 0x2c
        float mExpand; // 0x30
        int mShape; // 0x34 - enum Shape
        int mNumSections; // 0x38
        int mNumSegments; // 0x3c
        ObjPtr<RndTex, ObjectDir> mXSection; // 0x40
        ObjPtrList<RndDrawable, ObjectDir> mCutouts; // 0x4c
        ObjPtr<RndMat, ObjectDir> mMat; // 0x5c
    };

    Spotlight();
    OBJ_CLASSNAME(Spotlight);
    OBJ_SET_TYPE(Spotlight);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void UpdateSphere();
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual void DrawShowing();
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual void Highlight();
    virtual ~Spotlight();

    virtual void UpdateBounds();
    virtual void Poll();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    
    bool GetAnimateFromPreset() const;

    static void Init();

    ObjPtr<RndMat, ObjectDir> mDiscMat; // 0xb8
    RndFlare* mFlare; // 0xc4
    float mFlareOffset; // 0xc8
    float mSpotScale; // 0xcc
    float mSpotHeight; // 0xd0
    Transform unkd4;
    Transform unk104;
    int unk134;
    float unk138;
    ObjOwnerPtr<Spotlight, ObjectDir> mColorOwner; // 0x13c
    float mLensSize; // 0x148
    float mLensOffset; // 0x14c
    ObjPtr<RndMat, ObjectDir> mLensMaterial; // 0x150
    BeamDef mBeam; // 0x15c
    ObjPtrList<RndLight, ObjectDir> mSlaves; // 0x1c4
    ObjPtr<RndMesh, ObjectDir> mLightCanMesh;
    Transform mLightCanXfm;
    float mLightCanOffset; // 0x210
    ObjPtr<RndTransformable, ObjectDir> mTarget; // 0x214
    ObjPtr<RndTransformable, ObjectDir> mSpotTarget; // 0x220
    float unk22c;
    Hmx::Matrix3 unk230;
    float mDampingConstant; // 0x254
    ObjPtrList<RndDrawable, ObjectDir> mAdditionalObjects; // 0x258
    Vector3 unk268;
    Hmx::Quat unk274;
    bool mFlareEnabled; // 0x284
    bool mFlareVisibilityTest; // 0x285
    bool unk286;
    bool mTargetShadow; // 0x287
    bool mLightCanSort; // 0x288
    bool unk289;
    bool mAnimateColorFromPreset; // 0x28a
    bool mAnimateOrientationFromPreset; // 0x28b
    bool unk28c;
};

#endif
