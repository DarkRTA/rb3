#pragma once
#include "obj/Object.h"
#include "meta/FixedSizeSaveable.h"
#include "bandobj/BandPatchMesh.h"
#include "bandobj/BandHeadShaper.h"
#include "rndobj/Tex.h"

class BandCharDesc : public virtual Hmx::Object, public FixedSizeSaveable {
public:
    enum CharInstrumentType {
        kGuitar,
        kBass,
        kDrum,
        kMic,
        kKeyboard,
        kNumInstruments
    };

    class Patch : public FixedSizeSaveable {
    public:
        enum Category {
            // 0x0 - none?
            // 0x1 - legs
            // 0x1 - torso
            // 0x4 - feet
            // 0x8 - hair
            // 0x20 - unknown
            // 0x200 - guitar
            // 0x400 - bass
            // 0x800 - drum
            // 0x1000 - mic
            // 0x2000 - keyboard
        };

        // #define kPatchNone (0)
        // #define kPatchTorso (1)
        // #define kPatchLeg (2)
        // #define kPatchFeet (4)
        // #define kPatchHair (8)
        // #define kPatchTattoo (16)
        // #define kPatchMakeup (32)
        // #define kPatchFacepaint (64)
        // #define kPatchTorsoOverlay (128)
        // #define kPatchLegOverlay (256)
        // #define kPatchGuitar (512)
        // #define kPatchBass (1024)
        // #define kPatchDrum (2048)
        // #define kPatchMic (4096)
        // #define kPatchKeyboard (8192)
        // #define PATCH_CATEGORIES (
        //    ("kPatchNone" "no patch, won't be used")
        //    ("kPatchTorso" "patch torso outfit")
        //    ("kPatchLeg" "patch on the leg outfit")
        //    ("kPatchFeet" "patch on the shoes")
        //    ("kPatchHair" "patch on the hat or hair")
        //    ("kPatchTattoo" "tattoo art, goes on torso, legs, feet, head, all skin")
        //    ("kPatchMakeup" "makeup art, goes on head")
        //    ("kPatchFacepaint" "facepaint art, goes on head")
        //    ("kPatchTorsoOverlay" "torso overlays, goes on the torso skin")
        //    ("kPatchLegOverlay" "leg overlay, goes on the leg skin")
        //    ("kPatchGuitar" "patch on the guitar")
        //    ("kPatchBass" "patch on the bass")
        //    ("kPatchDrum" "patch on the drum")
        //    ("kPatchMic" "patch on the mic")
        //    ("kPatchKeyboard" "patch on the keyboards")
        // )

        Patch();
        virtual ~Patch() {}
        virtual void SaveFixed(FixedSizeSaveableStream &) const;
        virtual void LoadFixed(FixedSizeSaveableStream &, int);

        bool operator==(const Patch &) const;
        bool operator!=(const Patch &) const;

        static int SaveSize(int);

        int mTexture; // 0x8
        int mCategory; // 0xc
        String mMeshName; // 0x10
        Vector2 mUV; // 0x1c
        float mRotation; // 0x24
        Vector2 mScale; // 0x28
    };

    class OutfitPiece : public FixedSizeSaveable {
    public:
        OutfitPiece();
        virtual ~OutfitPiece() {}
        virtual void SaveFixed(FixedSizeSaveableStream &) const;
        virtual void LoadFixed(FixedSizeSaveableStream &, int);

        bool operator==(const OutfitPiece &) const;

        static int SaveSize(int);

        Symbol mName; // 0x8
        int mColors[3]; // 0xc
    };

    class Head : public FixedSizeSaveable {
    public:
        Head();
        virtual ~Head() {}
        virtual void SaveFixed(FixedSizeSaveableStream &) const;
        virtual void LoadFixed(FixedSizeSaveableStream &, int);

        void SetShape(BandHeadShaper &);
        bool operator==(const Head &) const;
        bool operator!=(const Head &) const;

        static int SaveSize(int);

        bool mHide; // 0x8
        int mEyeColor; // 0xc
        int mShape; // 0x10
        int mChin; // 0x14
        float mChinWidth; // 0x18
        float mChinHeight; // 0x1c
        float mJawWidth; // 0x20
        float mJawHeight; // 0x24
        int mNose; // 0x28
        float mNoseWidth; // 0x2c
        float mNoseHeight; // 0x30
        int mEye; // 0x34
        float mEyeSeparation; // 0x38
        float mEyeHeight; // 0x3c
        float mEyeRotation; // 0x40
        int mMouth; // 0x44
        float mMouthWidth; // 0x48
        float mMouthHeight; // 0x4c
        float mBrowSeparation; // 0x50
        float mBrowHeight; // 0x54
    };

    class Outfit : public FixedSizeSaveable {
    public:
        Outfit();
        virtual ~Outfit() {}
        virtual void SaveFixed(FixedSizeSaveableStream &) const;
        virtual void LoadFixed(FixedSizeSaveableStream &, int);

        OutfitPiece *GetPiece(Symbol);
        bool operator==(const Outfit &) const;
        bool operator!=(const Outfit &) const;

        static int SaveSize(int);

        OutfitPiece mEyebrows; // 0x8
        OutfitPiece mFaceHair; // 0x20
        OutfitPiece mHair; // 0x38
        OutfitPiece mEarrings; // 0x50
        OutfitPiece mGlasses; // 0x68
        OutfitPiece mPiercings; // 0x80
        OutfitPiece mFeet; // 0x98
        OutfitPiece mHands; // 0xb0
        OutfitPiece mLegs; // 0xc8
        OutfitPiece mRings; // 0xe0
        OutfitPiece mTorso; // 0xf8
        OutfitPiece mWrist; // 0x110
    };

    class InstrumentOutfit : public FixedSizeSaveable {
    public:
        InstrumentOutfit();
        virtual ~InstrumentOutfit() {}
        virtual void SaveFixed(FixedSizeSaveableStream &) const;
        virtual void LoadFixed(FixedSizeSaveableStream &, int);

        OutfitPiece *GetPiece(Symbol);
        bool operator==(const InstrumentOutfit &) const;
        bool operator!=(const InstrumentOutfit &) const;

        static int SaveSize(int);

        OutfitPiece mGuitar; // 0x8
        OutfitPiece mBass; // 0x20
        OutfitPiece mDrum; // 0x38
        OutfitPiece mMic; // 0x50
        OutfitPiece mKeyboard; // 0x68
    };

    BandCharDesc();
    virtual ~BandCharDesc();
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);
    OBJ_CLASSNAME(BandCharDesc);
    OBJ_SET_TYPE(BandCharDesc);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual RndTex *GetPatchTex(Patch &) { return 0; }
    virtual RndMesh *GetPatchMesh(Patch &) { return 0; }
    virtual RndTex *GetBandLogo() { return 0; }
    virtual void Compress(RndTex *, bool);
    virtual ObjectDir *GetPatchDir() { return 0; }
    virtual void AddOverlays(BandPatchMesh &) {}
    virtual void MiloReload() {}

    void SetChanged(int);
    void SetPrefab(Symbol);
    void SetGender(Symbol);
    void SetHeight(float);
    void SetWeight(float);
    void SetMuscle(float);
    void SetSkinColor(int);
    void MakeInstrumentPath(Symbol, Symbol, FilePath &);
    void MakeOutfitPath(Symbol, FilePath &);
    void CopyCharDesc(const BandCharDesc *);
    void ComputeDeformWeights(float *) const;
    bool IsSameCharDesc(const BandCharDesc &) const;
    int AddNewPatch(Patch::Category, const char *);
    int FindPatchIndex(Patch::Category, const char *);
    Patch *GetPatch(int);
    void ClearPatch(Patch::Category, const char *);
    Symbol Gender() const { return mGender; }
    Head &GetHead() { return mHead; }

    DataNode ListOutfits(Symbol);

    static const char *sDrumVenueMappings[];

    static CharInstrumentType GetInstrumentFromSym(Symbol);
    static Symbol NameToDrumVenue(const char *);
    static Symbol GetAnimInstrument(Symbol);
    static Symbol GetInstrumentSym(int);
    static bool DrumCallback(char *);
    static class CharClip *GetDeformClip(Symbol);
    static ObjectDir *GetPrefabs();
    static BandCharDesc *FindPrefab(const char *, bool);
    static void ReloadPrefabs();
    static int SaveSize(int);
    static void Init();
    static void Register() { REGISTER_OBJ_FACTORY(BandCharDesc); }
    NEW_OBJ(BandCharDesc);
    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    Symbol mPrefab; // 0xc
    Symbol mGender; // 0x10
    int mSkinColor; // 0x14
    Head mHead; // 0x18
    Outfit mOutfit; // 0x70
    InstrumentOutfit mInstruments; // 0x198
    float mHeight; // 0x218
    float mWeight; // 0x21c
    float mMuscle; // 0x220
    int unk224; // 0x224 - likely a bitfield as seen in BandCharacter methods
    std::vector<Patch> mPatches; // 0x228
};

class BandCharDescTest : public BandCharDesc {
public:
    BandCharDescTest() {}
    virtual ~BandCharDescTest() {}
    virtual Symbol ClassName() const { return ""; }
};
