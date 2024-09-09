#pragma once
#include "rndobj/Draw.h"
#include "rndobj/Mat.h"
#include "rndobj/TexBlender.h"
#include "bandobj/BandPatchMesh.h"
#include "math/SHA1.h"

class OutfitConfig : public RndDrawable {
public:
    class MatSwap {
    public:
    };

    class MeshAO {
    public:
    };

    class Piercing {
    public:
    };

    class Overlay {
    public:
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
    virtual ~OutfitConfig();
    virtual void PreSave(BinStream&);
    virtual void PostSave(BinStream&);

    int mColors[3]; // 0x20, 0x24, 0x28
    ObjVector<MatSwap> mMats; // 0x2c
    int unk38;
    int unk3c;
    std::vector<MeshAO> unk40; // 0x40
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