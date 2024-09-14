#pragma once
#include "meta/FixedSizeSaveable.h"
#include "rndobj/Dir.h"
#include "rndobj/Tex.h"
#include "world/ColorPalette.h"

class PatchSticker {
public:
    PatchSticker();
    ~PatchSticker();

    void Unload();

    String unk0;
    FilePath unkc;
    float unk18;
    float unk1c;
    int unk20;
    bool unk24;
    int unk28;
    int unk2c;
    int unk30;
};

class PatchLayer : public Hmx::Object {
public:
    PatchLayer();
    virtual ~PatchLayer();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);

    void Reset();
    void SetScale(float, float);
    bool AllowColor();
    void SetDefaultColor();
    void SelectFX();
    void FlipX();
    void FlipY();
    void ClearSticker();

    static std::vector<Symbol> sCategoryNames;
    static ColorPalette* sColorPalette;

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

    static int SaveSize(int);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::vector<PatchLayer> unk194; // 0x194
    std::map<Symbol, std::vector<PatchSticker*> > unk19c; // 0x19c
    std::vector<int> unk1b4; // 0x1b4
    RndTex* mTex; // 0x1bc
    bool unk1c0; // 0x1c0
};