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
    StickerProvider() : mStickerMat(0), unk2c(0), unk30(gNullStr) {}
    virtual ~StickerProvider() { DeleteAll(mStickerMats); }
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual int NumData() const;
    virtual void InitData(RndDir *);

    RndMat *mStickerMat; // 0x20
    std::vector<RndMat *> mStickerMats; // 0x24
    int unk2c; // 0x2c - mStickers? ptr to some vec?
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
    void CopyToPatch(const PatchDir *) const;
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
    bool unk50;
    bool unk51;
    int mEditLayerIdx; // 0x54
    float unk58;
    float unk5c;
    float unk60;
    float unk64;
    float unk68;
    float unk6c;
    float unk70;
    float unk74;
    float unk78;
    float unk7c;
    float unk80;
    float unk84;
    int unk88;
    int unk8c;
    int unk90;
    int unk94;
    int unk98;
    int unk9c;
    int unka0;
    int unka4;
    int unka8;
    int unkac;
    int unkb0;
    int unkb4;
    float unkb8;
    float unkbc;
    int unkc0;
    Vector3 unkc4;
    float unkd0;
    float unkd4;
    float unkd8;
    float unkdc;
    Symbol unke0;
    int unke4;
};

int ConvertToLayerIndex(PatchDir *, int);