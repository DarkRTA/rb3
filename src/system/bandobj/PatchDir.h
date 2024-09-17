#pragma once
#include "meta/FixedSizeSaveable.h"
#include "rndobj/Dir.h"
#include "rndobj/Group.h"
#include "rndobj/Tex.h"
#include "rndobj/TransAnim.h"
#include "world/ColorPalette.h"
#include "utl/IntPacker.h"

class PatchDir; // forward dec

class PatchDescriptor {
public:
    int patchType; // 0x0 - enum Type, but we don't know the enum names for certain
    int patchIndex; // 0x4
};

class PatchSticker {
public:
    PatchSticker();
    ~PatchSticker();

    void Unload();
    void FinishLoad();
    void MakeLoader();

    String unk0; // 0x0
    FilePath unkc; // 0xc
    float unk18; // 0x18
    float unk1c; // 0x1c
    int unk20; // 0x20
    bool unk24; // 0x24
    FileLoader* mLoader; // 0x28
    RndTex* mTex; // 0x2c
    RndTex* unk30; // 0x30
};

class PatchLayer : public Hmx::Object {
public:
    PatchLayer();
    virtual ~PatchLayer();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);

    void SavePacked(IntPacker&) const;

    void Reset();
    void SetScale(float, float);
    bool AllowColor();
    void SetDefaultColor();
    void SelectFX();
    void FlipX();
    void FlipY();
    void ClearSticker();
    void SetPosition(const Vector3&);
    void SetRotation(float);
    void SetScaleX(float);
    void SetScaleY(float);
    void SetDeformFrame(float);
    bool HasSticker() const;
    Vector3 Position() const;
    float DeformFrame() const;
    PatchSticker* GetSticker(bool) const;

    static std::vector<Symbol> sCategoryNames;
    static ColorPalette* sColorPalette;
    static RndDir* sResource;
    static RndTransAnim* sTransAnim;
    static RndGroup* sGrpAnim;
    static RndMat* sMat;
    static PatchDir* sStickerOwner;

    static void Init();
    static void InitResources();
    static void Terminate();

    Symbol mStickerCategory; // 0x1c
    int mStickerIdx; // 0x20
    int mColorIdx; // 0x24
    float unk28; // 0x28
    int mPosX; // 0x2c
    int mPosZ; // 0x30
    int mRot; // 0x34
    int mScaleX; // 0x38
    int mScaleY; // 0x3c
    int mDeformFrame; // 0x40
};

class PatchDir : public FixedSizeSaveable, public RndDir {
public:
    PatchDir();
    virtual ~PatchDir();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual RndCam* CamOverride();
    virtual void Poll();

    void LoadStickerData();
    bool HasLayers() const;
    void Clear();
    void CacheRenderedTex(RndTex*, bool);
    PatchSticker* GetSticker(Symbol, int, bool);
    void SaveRemote(BinStream&);
    void LoadRemote(BinStream&);

    static void Init();
    static void Terminate();
    static int SaveSize(int);
    static int GetCurrentRev(){ return gRev; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::vector<PatchLayer> unk194; // 0x194
    std::map<Symbol, std::vector<PatchSticker*> > unk19c; // 0x19c
    std::vector<int> unk1b4; // 0x1b4
    RndTex* mTex; // 0x1bc
    bool unk1c0; // 0x1c0
};