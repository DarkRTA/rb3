#pragma once
#include "rndobj/Draw.h"
#include "rndobj/Mat.h"
#include "rndobj/TexBlender.h"
#include "bandobj/BandPatchMesh.h"
#include "math/SHA1.h"
#include "world/ColorPalette.h"

class OutfitConfig : public RndDrawable {
public:
    class Piercing {
    public:
        class Piece {
        public:
            Piece(Hmx::Object* o) : mAttachment(o, 0), mHighlight(0), mVert(-1) {}

            ObjPtr<RndTransformable, ObjectDir> mAttachment; // 0x0
            bool mHighlight; // 0xc
            int mVert; // 0x10
            std::vector<unsigned short> unk14; // 0x14
        };

        Piercing(Hmx::Object*);

        ObjPtr<RndTransformable, ObjectDir> mPiercing; // 0x0
        Transform unkc; // 0xc
        bool mReskin; // 0x3c
        ObjVector<Piece> mPieces; // 0x40
    };

    class MatSwap {
    public:
        MatSwap(Hmx::Object*);
        void SyncTwoColor();

        ObjPtr<RndMat, ObjectDir> mMat; // 0x0
        ObjPtr<RndMat, ObjectDir> mResourceMat; // 0xc
        ObjPtr<RndTex, ObjectDir> mTwoColorDiffuse; // 0x18
        ObjPtr<RndTex, ObjectDir> mTwoColorInterp; // 0x24
        ObjPtr<RndTex, ObjectDir> mTwoColorMask; // 0x30
        ObjPtr<ColorPalette, ObjectDir> mColor1Palette; // 0x3c
        int mColor1Option; // 0x48
        ObjPtr<ColorPalette, ObjectDir> mColor2Palette; // 0x4c
        int mColor2Option; // 0x58
        ObjVector<ObjPtr<RndTex, ObjectDir> > mTextures; // 0x5c
        bool mTwoColor; // 0x68
    };

    class MeshAO {
    public:
        class Seam {
        public:
            int mIndex; // 0x0
            int mCoeff; // 0x4
        };

        String mMeshName; // 0x0
        String unkc; // 0xc
        std::vector<int> mCoeffs; // 0x18
        std::vector<Seam> mSeams; // 0x20
    };

    class Overlay {
    public:
        Overlay(Hmx::Object*);

        int mCategory; // 0x0
        ObjPtr<RndTex, ObjectDir> mTexture; // 0x4
    };

    OutfitConfig();
    OBJ_CLASSNAME(OutfitConfig);
    OBJ_SET_TYPE(OutfitConfig);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual void DrawPreClear();
    virtual void UpdatePreClearState();
    virtual ~OutfitConfig(){}
    virtual void PreSave(BinStream&);
    virtual void PostSave(BinStream&);

    unsigned int OverlayFlags() const;
    int NumColorOptions() const;
    void CompressTextures();
    void Recompose();
    void Randomize();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int mColors[3]; // 0x20, 0x24, 0x28
    ObjVector<MatSwap> mMats; // 0x2c
    int unk38;
    int unk3c;
    std::vector<MeshAO> mMeshAO; // 0x40
    bool mComputeAO; // 0x48
    ObjVector<BandPatchMesh> mPatches; // 0x4c
    bool mPermaProject; // 0x58
    ObjVector<Piercing> mPiercings; // 0x5c
    ObjPtr<RndTexBlender, ObjectDir> mTexBlender; // 0x68
    ObjPtr<RndTexBlender, ObjectDir> mWrinkleBlender; // 0x74
    ObjVector<Overlay> mOverlays; // 0x80
    ObjPtr<RndMat, ObjectDir> mBandLogo; // 0x8c
    CSHA1::Digest mDigest; // 0x98
};