#pragma once
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"
#include "rndobj/Poll.h"
#include "rndobj/Env.h"

class RndGroup;
class RndFlare;
class RndMesh;
class RndTex;
class RndLight;

/** "Represents a beam and floorspot for venue modeling" */
class Spotlight : public RndDrawable, public RndTransformable, public RndPollable {
public:
    class BeamDef {
    public:
        enum Shape {
            kBeamConic = 0,
            kBeamRect = 1,
            kBeamSheet = 2,
            kBeamQuadXYZ = 3,
            kBeamQuadZ = 4
        };

        BeamDef(Hmx::Object *);
        BeamDef(const BeamDef &);
        ~BeamDef();
        void OnSetMat(RndMat *);
        void Load(BinStream &);
        Vector2 NGRadii() const;

        RndMesh *mBeam; // 0x0
        /** "Whether this is a beam or a cone" */
        bool mIsCone; // 0x4
        /** "Length of the beam/cone" */
        float mLength; // 0x8
        /** "Radius at the top of the beam/cone" */
        float mTopRadius; // 0xc
        /** "Radius at the bottom of the beam/cone" */
        float mBottomRadius; // 0x10
        /** "For beams, length of the side transparency border at the top of the beam" */
        float mTopSideBorder; // 0x14
        /** "For beams, length of the side transparency border at the bottom of the beam"
         */
        float mBottomSideBorder; // 0x18
        /** "Length of the bottom transparency border" */
        float mBottomBorder; // 0x1c
        /** "Offset of beam along trajectory" */
        float mOffset; // 0x20
        /** "Amount to offset beam rotation (in degrees)" */
        Vector2 mTargetOffset; // 0x24
        /** "raise or lower intensity compared to og beams" */
        float mBrighten; // 0x2c
        /** "expand or shrink the radii compared to og beams" */
        float mExpand; // 0x30
        /** "Shape of the beam" */
        int mShape; // 0x34 - enum Shape
        /** "Number of divisions along length" */
        int mNumSections; // 0x38
        /** "Number of divisions along width or around cone" */
        int mNumSegments; // 0x3c
        /** "cross section intensity override texture" */
        ObjPtr<RndTex> mXSection; // 0x40
        /** "Objects that create cutout shadow in the beam." */
        ObjPtrList<RndDrawable> mCutouts; // 0x4c
        /** "The material to use for the beam/cone" */
        ObjPtr<RndMat> mMat; // 0x5c
    };

    Spotlight();
    OBJ_CLASSNAME(Spotlight);
    OBJ_SET_TYPE(Spotlight);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void UpdateSphere();
    virtual bool MakeWorldSphere(Sphere &, bool);
    virtual void Mats(std::list<class RndMat *> &, bool);
    virtual void DrawShowing();
    virtual void ListDrawChildren(std::list<RndDrawable *> &);
    virtual RndDrawable *CollideShowing(const Segment &, float &, Plane &);
    virtual int CollidePlane(const Plane &);
    virtual void Highlight() { RndDrawable::Highlight(); }
    virtual ~Spotlight();

    virtual void UpdateBounds();
    virtual void Poll();
    virtual void Replace(Hmx::Object *, Hmx::Object *);

    void BuildNGCone(BeamDef &, int);
    void BuildNGSheet(BeamDef &);
    void BuildNGQuad(BeamDef &, RndTransformable::Constraint);
    void BuildNGShaft(BeamDef &);
    void BuildShaft(BeamDef &);
    void BuildCone(BeamDef &);
    void BuildBeam(BeamDef &);

    bool GetAnimateFromPreset() const {
        return mAnimateColorFromPreset || mAnimateOrientationFromPreset;
    }
    void CalculateDirection(RndTransformable *, Hmx::Matrix3 &);
    void CloseSlaves();
    void UpdateSlaves();
    void SetFlareEnabled(bool);
    void UpdateFlare();
    void SetFlareIsBillboard(bool);
    void ConvertGroupToMesh(RndGroup *);
    void Generate();
    void PropogateToPresets(int);
    void UpdateTransforms();
    void SetColor(int);
    void SetIntensity(float);
    void SetColorIntensity(const Hmx::Color &, float);
    RndTransformable *ResolveTarget();
    void CheckFloorSpotTransform();
    void UpdateFloorSpotTransform(const Transform &);
    Hmx::Color32 Color() const { return mColorOwner->mColor; }
    float Intensity() const { return mColorOwner->mIntensity; }
    bool LightCanSort() const { return mLightCanSort; }
    RndTransformable *Target() const { return mTarget; }
    bool IsFlareEnabled() const { return mFlareEnabled; }
    bool AnimateColorFromPreset() const { return mAnimateColorFromPreset; }
    bool AnimateOrientationFromPreset() const { return mAnimateOrientationFromPreset; }
    RndFlare *GetFlare() const { return mFlare; }

    RndTransformable *GetFloorSpotTarget() const {
        return mSpotTarget ? mSpotTarget : mTarget;
    }

    bool DoFloorSpot() const {
        bool ret = false;
        if (mDiscMat && GetFloorSpotTarget()) {
            if (GetFloorSpotTarget()->WorldXfm().m.y.z != 0.0f)
                ret = true;
        }
        return ret;
    }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(Spotlight)
    static void Register() { REGISTER_OBJ_FACTORY(Spotlight) }

    static void Init();
    static void BuildBoard();
    static RndEnviron *sEnviron;
    static RndMesh *sDiskMesh;

    ObjPtr<RndMat> mDiscMat; // 0xb8
    RndFlare *mFlare; // 0xc4
    /** "Offset of flare along spotlight trajectory" */
    float mFlareOffset; // 0xc8
    /** "Scale of the floor disc" */
    float mSpotScale; // 0xcc
    /** "Height offset of the floor disc" */
    float mSpotHeight; // 0xd0
    Transform mFloorSpotXfm; // 0xd4
    Transform mLensXfm; // 0x104
    /** "Color of the spotlight" */
    Hmx::Color32 mColor; // 0x134 - packed color
    /** "Intensity of the spotlight" */
    float mIntensity; // 0x138
    /** "Master for light color and intensity" */
    ObjOwnerPtr<Spotlight> mColorOwner; // 0x13c
    /** "Size of the lens billboard" */
    float mLensSize; // 0x148
    /** "Offset of the lens billboard" */
    float mLensOffset; // 0x14c
    /** "Material to use for the lens" */
    ObjPtr<RndMat> mLensMaterial; // 0x150
    BeamDef mBeam; // 0x15c
    /** "Slave lights for projection lights and shadows" */
    ObjPtrList<RndLight> mSlaves; // 0x1c4
    /** "Optional light can mesh to use" */
    ObjPtr<RndMesh> mLightCanMesh; // 0x1d4
    Transform mLightCanXfm; // 0x1e0
    /** "Offset of light can along beam trajectory" */
    float mLightCanOffset; // 0x210
    /** "Object to target spotlight" */
    ObjPtr<RndTransformable> mTarget; // 0x214
    /** "Reference object for floor height, uses spot target if not set" */
    ObjPtr<RndTransformable> mSpotTarget; // 0x220
    float unk22c;
    Hmx::Matrix3 unk230;
    /** "0-1, controls how fast spotlight moves to reach target" */
    float mDampingConstant; // 0x254
    /** "Additional objects that should be drawn by the spotlight." */
    ObjPtrList<RndDrawable> mAdditionalObjects; // 0x258
    Vector3 unk268;
    Hmx::Quat unk274;
    /** "Whether the flare is enabled (keyframed by light presets)" */
    bool mFlareEnabled; // 0x284
    /** "Whether the flare performs a visiblity test (or is always visible)" */
    bool mFlareVisibilityTest; // 0x285
    bool unk286;
    /** "Whether the target should cast a shadow" */
    bool mTargetShadow; // 0x287
    /** "Can't optimize render end of render batching of light can with others" */
    bool mLightCanSort; // 0x288
    bool unk289;
    /** "Whether this spotlight coloring should be animated by light presets." */
    bool mAnimateColorFromPreset; // 0x28a
    /** "Whether this spotlight position/rotation should be animated by light presets." */
    bool mAnimateOrientationFromPreset; // 0x28b
    bool unk28c;

    // spot material: "Material to use for the floor spot"
    // flare material: "Material to use for the flare"
    // flare size: "Size of the flare"
    // flare range: "Range of the flare"
    // flare steps: "Steps for the flare"
    // propogate coloring to presets: "Propogate the spotlight's current color state to
    // all light presets in the file." propogate targeting to presets: "Propogate the
    // spotlight's current target/rotation state to all light presets in the file."
};

inline BinStream &operator>>(BinStream &bs, Spotlight::BeamDef &bd) {
    bd.Load(bs);
    return bs;
}
