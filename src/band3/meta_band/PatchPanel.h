#pragma once
#include "bandobj/PatchDir.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"
#include "rndobj/Mat.h"
#include "ui/PanelDir.h"
#include "ui/UIGridProvider.h"
#include "ui/UIListProvider.h"
#include "ui/UIPanel.h"
#include "utl/Std.h"
#include "utl/Symbol.h"

class LayerProvider : public UIListProvider, public Hmx::Object {
public:
    LayerProvider(PatchDir *p) : mPatch(p) {
        for (int i = 0; i < 50; i++) {
            mLayerMats.push_back(Hmx::Object::New<RndMat>());
        }
    }
    virtual ~LayerProvider() { DeleteAll(mLayerMats); }
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual void Custom(int, int, class UIListCustom *, Hmx::Object *) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual void InitData(RndDir *);
    virtual UIColor *SlotColorOverride(int, int, class UIListWidget *, UIColor *c) const;
    virtual DataNode Handle(DataArray *, bool);

    void SetLabelForData(UILabel *, int) const;
    RndMat *GetMatForData(int) const;

    PatchDir *mPatch; // 0x20
    std::vector<RndMat *> mLayerMats; // 0x24
};

class CategoryProvider : public UIListProvider, public Hmx::Object {
public:
    CategoryProvider(PanelDir *panel, PatchDir *patch)
        : mPatch(patch), mResource(panel) {}
    virtual ~CategoryProvider() { DeleteAll(mCategoryMats); }
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;
    virtual void InitData(RndDir *);

    std::vector<RndMat *> mCategoryMats; // 0x20
    PatchDir *mPatch; // 0x28
    PanelDir *mResource; // 0x2c
};

class StickerProvider : public UIListProvider, public Hmx::Object {
public:
    StickerProvider() : mStickerMat(0), mStickers(0), unk30(gNullStr) {}
    virtual ~StickerProvider() { DeleteAll(mStickerMats); }
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual int NumData() const;
    virtual void InitData(RndDir *);

    RndMat *mStickerMat; // 0x20
    std::vector<RndMat *> mStickerMats; // 0x24
    std::vector<PatchSticker *> *mStickers; // 0x2c
    Symbol unk30; // 0x30
};

class PatchPanel : public UIPanel {
public:
    PatchPanel();
    OBJ_CLASSNAME(PatchPanel);
    OBJ_SET_TYPE(PatchPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~PatchPanel();
    virtual void Enter();
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    void ResetDirections();
    void ResetVelocities();
    void CopyFromPatch(const PatchDir *);
    PatchLayer &EditLayer();
    int GetEditLayerListIndex() const;
    void RestoreUndo();
    void StoreUndo();
    float CalcMotion(float, int);
    void CopyToPatch(PatchDir *) const;
    void SetBaseSize(float, float);
    void SetStickerCategory(Symbol);

    DataNode OnMsg(const ButtonDownMsg &);
    DataNode OnMsg(const ButtonUpMsg &);
    DataNode SwapLayers(DataArray *);
    DataNode ClearLayer(DataArray *);
    DataNode DupeLayer(DataArray *);

    PatchDir *mPatch; // 0x38
    CategoryProvider *mCategoryProvider; // 0x3c
    StickerProvider *mStickerProvider; // 0x40
    UIGridProvider *mGridProvider; // 0x44
    LayerProvider *mLayerProvider; // 0x48
    Symbol mMode; // 0x4c
    bool unk50; // 0x50
    bool unk51; // 0x51
    int mEditLayerIdx; // 0x54
    float unk58; // 0x58
    float unk5c; // 0x5c
    float unk60; // 0x60
    float unk64; // 0x64
    float unk68; // 0x68
    float unk6c; // 0x6c
    float unk70; // 0x70
    float unk74; // 0x74
    float unk78; // 0x78
    float unk7c; // 0x7c
    float unk80; // 0x80
    float unk84; // 0x84
    int mMoveX; // 0x88
    int mMoveY; // 0x8c
    float mMoveVelX; // 0x90
    float mMoveVelY; // 0x94
    int mRot; // 0x98
    float mRotVel; // 0x9c
    int mScaleX; // 0xa0
    int mScaleY; // 0xa4
    float mScaleVelX; // 0xa8
    float mScaleVelY; // 0xac
    int mDeform; // 0xb0
    float mDeformVel; // 0xb4
    float mBaseSizeX; // 0xb8
    float mBaseSizeY; // 0xbc
    int mUndoColorIdx; // 0xc0
    Vector3 mUndoPosition; // 0xc4
    float mUndoRotation; // 0xd0
    float mUndoScaleX; // 0xd4
    float mUndoScaleY; // 0xd8
    float mUndoDeformFrame; // 0xdc
    Symbol mUndoStickerCategory; // 0xe0
    int mUndoStickerIdx; // 0xe4
};

int ConvertToLayerIndex(PatchDir *, int);