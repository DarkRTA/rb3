#pragma once
#include "obj/Object.h"
#include "meta/FixedSizeSaveable.h"
#include "bandobj/BandPatchMesh.h"
#include "rndobj/Tex.h"

class BandCharDesc : public virtual Hmx::Object, public FixedSizeSaveable {
public:
    class Patch : public FixedSizeSaveable {
    public:
        Patch();
        virtual ~Patch(){}
        virtual void SaveFixed(FixedSizeSaveableStream&) const;
        virtual void LoadFixed(FixedSizeSaveableStream&, int);

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
        virtual ~OutfitPiece(){}
        virtual void SaveFixed(FixedSizeSaveableStream&) const;
        virtual void LoadFixed(FixedSizeSaveableStream&, int);

        static int SaveSize(int);

        Symbol mName; // 0x8
        int mColor0; // 0xc
        int mColor1; // 0x10
        int mColor2; // 0x14
    };

    class Head : public FixedSizeSaveable {
    public:
        Head();
        virtual ~Head(){}
        virtual void SaveFixed(FixedSizeSaveableStream&) const;
        virtual void LoadFixed(FixedSizeSaveableStream&, int);

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
        virtual ~Outfit(){}
        virtual void SaveFixed(FixedSizeSaveableStream&) const;
        virtual void LoadFixed(FixedSizeSaveableStream&, int);

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
        virtual ~InstrumentOutfit(){}
        virtual void SaveFixed(FixedSizeSaveableStream&) const;
        virtual void LoadFixed(FixedSizeSaveableStream&, int);

        static int SaveSize(int);

        OutfitPiece mGuitar; // 0x8
        OutfitPiece mBass; // 0x20
        OutfitPiece mDrum; // 0x38
        OutfitPiece mMic; // 0x50
        OutfitPiece mKeyboard; // 0x68
    };

    BandCharDesc();
    virtual ~BandCharDesc();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);
    OBJ_CLASSNAME(BandCharDesc);
    OBJ_SET_TYPE(BandCharDesc);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual int GetPatchTex(Patch&);
    virtual int GetPatchMesh(Patch&);
    virtual int GetBandLogo(){ return 0; }
    virtual void Compress(RndTex*, bool);
    virtual int GetPatchDir();
    virtual void AddOverlays(BandPatchMesh&);
    virtual void MiloReload(){}

    void SetChanged(int);
    void SetPrefab(Symbol);
    void SetGender(Symbol);
    void SetHeight(float);
    void SetWeight(float);
    void SetMuscle(float);
    void SetSkinColor(int);

    DataNode ListOutfits(Symbol);

    static ObjectDir* GetPrefabs();
    static int SaveSize(int);
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(BandCharDesc);
    }
    NEW_OBJ(BandCharDesc);
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
    int unk224; // 0x224
    std::vector<Patch> mPatches; // 0x228
};

class BandCharDescTest : public BandCharDesc {
public:
    BandCharDescTest(){}
    virtual ~BandCharDescTest(){}
    virtual Symbol ClassName() const { return ""; }
};
