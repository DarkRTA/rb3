#ifndef WORLD_SPOTLIGHT_H
#define WORLD_SPOTLIGHT_H
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"
#include "rndobj/Poll.h"
#include "rndobj/Env.h"

class RndGroup;
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
        void Load(BinStream&);
        
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
    virtual void Highlight(){ RndDrawable::Highlight(); }
    virtual ~Spotlight();

    virtual void UpdateBounds();
    virtual void Poll();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    
    bool GetAnimateFromPreset() const {
        return mAnimateColorFromPreset || mAnimateOrientationFromPreset;
    }
    void CalculateDirection(RndTransformable*, Hmx::Matrix3&);
    void CloseSlaves();
    void SetFlareEnabled(bool);
    void UpdateFlare();
    void SetFlareIsBillboard(bool);
    void ConvertGroupToMesh(RndGroup*);
    void Generate();
    void PropogateToPresets(int);
    void UpdateTransforms();
    void SetColor(int);
    void SetIntensity(float);
    RndTransformable* ResolveTarget();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(Spotlight)
    static void Register(){
        REGISTER_OBJ_FACTORY(Spotlight)
    }

    static void Init();
    static void BuildBoard();
    static RndEnviron* sEnviron;

    ObjPtr<RndMat, ObjectDir> mDiscMat; // 0xb8
    RndFlare* mFlare; // 0xc4
    float mFlareOffset; // 0xc8
    float mSpotScale; // 0xcc
    float mSpotHeight; // 0xd0
    Transform mFloorSpotXfm; // 0xd4
    Transform mLensXfm; // 0x104
    Hmx::Color32 mColor; // 0x134 - packed color
    float mIntensity; // 0x138
    ObjOwnerPtr<Spotlight, ObjectDir> mColorOwner; // 0x13c
    float mLensSize; // 0x148
    float mLensOffset; // 0x14c
    ObjPtr<RndMat, ObjectDir> mLensMaterial; // 0x150
    BeamDef mBeam; // 0x15c
    ObjPtrList<RndLight, ObjectDir> mSlaves; // 0x1c4
    ObjPtr<RndMesh, ObjectDir> mLightCanMesh; // 0x1d4
    Transform mLightCanXfm; // 0x1e0
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

inline BinStream& operator>>(BinStream& bs, Spotlight::BeamDef& bd){
    bd.Load(bs);
    return bs;
}

#endif
