#include "meta_band/PatchPanel.h"
#include "bandobj/InlineHelp.h"
#include "bandobj/PatchDir.h"
#include "decomp.h"
#include "math/Mtx.h"
#include "math/Rot.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include "rndobj/Mat.h"
#include "rndobj/TexRenderer.h"
#include "ui/UIGridProvider.h"
#include "ui/UIList.h"
#include "ui/UIListCustom.h"
#include "ui/UIListMesh.h"
#include "ui/UIPanel.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

BEGIN_HANDLERS(LayerProvider)
    HANDLE_EXPR(num_layers, NumData())
    HANDLE_ACTION(set_label_for_data, SetLabelForData(_msg->Obj<UILabel>(2), _msg->Int(3)))
    HANDLE_EXPR(get_mat_for_data, GetMatForData(_msg->Int(2)))
    HANDLE_CHECK(0x1A7)
END_HANDLERS

inline RndMat *LayerProvider::GetMatForData(int idx) const {
    int layerIdx = ConvertToLayerIndex(mPatch, idx);
    PatchLayer &layer = mPatch->Layer(layerIdx);
    PatchSticker *sticker = layer.GetSticker(false);
    if (!sticker)
        MILO_FAIL("Couldn't find sticker -- using -fast?");
    RndMat *curMat = mLayerMats[layerIdx];
    sticker->SetIconOnMat(curMat);
    Transform tf50;
    tf50.Reset();
    float f5 = layer.ScaleX();
    if (f5 < 0)
        f5 *= -1.0f;
    layer.ScaleY();
    layer.ScaleY();
    Hmx::Matrix3 m74;
    Vector3 v80(0, layer.Rotation() * DEG2RAD, 0);
    MakeRotMatrix(v80, m74, true);
    Vector3 v8c(sticker->unk18, 1.0f, sticker->unk1c);
    Scale(v8c, tf50.m, tf50.m);
    if (f5 != layer.ScaleX()) {
        Vector3 v98(-1, 1, 1);
        Scale(v98, tf50.m, tf50.m);
    }
    Multiply(m74, tf50.m, tf50.m);
    // fn_8025786C(uVar1,1);
    curMat->SetTexWrap(kTexBorderBlack);
    curMat->SetTexXfm(tf50);
    // fn_802577EC(uVar1,1);
    return curMat;
}

inline void LayerProvider::SetLabelForData(UILabel *label, int idx) const {
    mPatch->Layer(ConvertToLayerIndex(mPatch, idx));
    int numLayers = (mPatch->NumLayersUsed() - idx) + 1;
    label->SetTokenFmt(patch_layer_fmt, numLayers);
}

inline int LayerProvider::NumData() const {
    MILO_ASSERT(mPatch, 0x196);
    return mPatch->NumLayersUsed() + 1;
}

PatchPanel::PatchPanel()
    : mPatch(0), mCategoryProvider(0), mStickerProvider(0), mGridProvider(0),
      mLayerProvider(0), unk50(0), unk51(0), unk58(6), unk5c(6), unk60(0.15f),
      unk64(0.3f), unk68(5.0f), unk6c(30.0f), unk70(8.0f), unk74(0.1f), unk78(1.0f),
      unk7c(0.3f), unk80(0), unk84(50.0f), mBaseSizeX(1), mBaseSizeY(1), mUndoColorIdx(0),
      mUndoRotation(0), mUndoScaleX(0), mUndoScaleY(0), mUndoDeformFrame(0) {
    mUndoPosition.Zero();
}

PatchPanel::~PatchPanel() {}

void PatchPanel::Enter() {
    mCategoryProvider = new CategoryProvider(LoadedDir(), mPatch);
    mStickerProvider = new StickerProvider();
    mGridProvider = new UIGridProvider(mStickerProvider, 4);
    ResetDirections();
    ResetVelocities();
    mMode = "move";
    mEditLayerIdx = 0;
    mLayerProvider = new LayerProvider(mPatch);
    RndTexRenderer *tex = mDir->Find<RndTexRenderer>("patch.rndtex", true);
    tex->SetForce(true);
    tex->SetDraw(mPatch);
    UIPanel::Enter();
}

void PatchPanel::Load() {
    UIPanel::Load();
    mPatch = new PatchDir();
    mPatch->LoadStickerData();
    CopyFromPatch(Property(editing_patch)->Obj<PatchDir>());
    mPatch->LoadLayerStickers();
}

void PatchPanel::PollForLoading() {
    UIPanel::PollForLoading();
    mPatch->Poll();
}

bool PatchPanel::IsLoaded() const {
    return UIPanel::IsLoaded() && !mPatch->IsLoadingStickers();
}

void PatchPanel::Unload() {
    delete mCategoryProvider;
    delete mGridProvider;
    delete mStickerProvider;
    delete mLayerProvider;
    RndTexRenderer *tex = mDir->Find<RndTexRenderer>("patch.rndtex", true);
    tex->SetForce(false);
    RELEASE(mPatch);
    UIPanel::Unload();
}

FORCE_LOCAL_INLINE
PatchLayer &PatchPanel::EditLayer() { return mPatch->Layer(mEditLayerIdx); }
END_FORCE_LOCAL_INLINE

int PatchPanel::GetEditLayerListIndex() const {
    MILO_ASSERT(mPatch, 0x31C);
    return mPatch->NumLayersUsed() - mEditLayerIdx;
}

DataNode PatchPanel::SwapLayers(DataArray *a) {
    int i2 = a->Int(2);
    int i3 = a->Int(3);
    int num = mPatch->NumLayers();
    if (i2 < num && i2 >= 0 && i3 < mPatch->NumLayers() && i3 >= 0) {
        if (mPatch->Layer(i2).HasSticker() && mPatch->Layer(i3).HasSticker()) {
            PatchLayer layer;
            layer = mPatch->Layer(i2);
            mPatch->Layer(i2) = mPatch->Layer(i3);
            mPatch->Layer(i3) = layer;
            mPatch->CollapseEmptyLayers();
            return 1;
        }
    }
    return 0;
}

DataNode PatchPanel::ClearLayer(DataArray *a) {
    mPatch->Layer(a->Int(2)).ClearSticker();
    mPatch->CollapseEmptyLayers();
    return 0;
}

DataNode PatchPanel::DupeLayer(DataArray *a) {
    int i1 = a->Int(2);
    int i2 = mPatch->NumLayers();
    if (i1 < i2 && i1 >= 0) {
        i2 = mPatch->FindEmptyLayer();
        if (i2 >= 0) {
            mPatch->Layer(i2).Copy(&mPatch->Layer(i1), kCopyDeep);
            mEditLayerIdx = i2;
            return 1;
        }
    }
    return 0;
}

void PatchPanel::ResetDirections() {
    mDeform = 0;
    mScaleX = mScaleY = 0;
    mRot = 0;
    mMoveX = mMoveY = 0;
}

void PatchPanel::ResetVelocities() {
    mDeformVel = 0;
    mScaleVelX = mScaleVelY = 0;
    mRotVel = 0;
    mMoveVelX = mMoveVelY = 0;
}

void PatchPanel::RestoreUndo() {
    PatchLayer &layer = EditLayer();
    ResetVelocities();
    ResetDirections();
    layer.mStickerCategory = mUndoStickerCategory;
    layer.mStickerIdx = mUndoStickerIdx;
    layer.mColorIdx = mUndoColorIdx;
    layer.SetPosition(mUndoPosition);
    layer.SetScaleX(mUndoScaleX);
    layer.SetScaleY(mUndoScaleY);
    layer.SetDeformFrame(mUndoDeformFrame);
    layer.SetRotation(mUndoRotation);
}

void PatchPanel::StoreUndo() {
    PatchLayer &layer = EditLayer();
    mUndoStickerCategory = layer.mStickerCategory;
    mUndoStickerIdx = layer.mStickerIdx;
    mUndoColorIdx = layer.mColorIdx;
    mUndoPosition = layer.Position();
    mUndoScaleX = layer.ScaleX();
    mUndoScaleY = layer.ScaleY();
    mUndoDeformFrame = layer.DeformFrame();
    mUndoRotation = layer.Rotation();
}

void PatchPanel::CopyFromPatch(const PatchDir *dir) { mPatch->Copy(dir, kCopyShallow); }

void PatchPanel::CopyToPatch(PatchDir *dir) const {
    dir->Copy(mPatch, kCopyShallow);
    RndTexRenderer *tex = mDir->Find<RndTexRenderer>("patch.rndtex", true);
    dir->CacheRenderedTex(tex->GetOutputTexture(), false);
}

void PatchPanel::SetBaseSize(float baseX, float baseY) {
    MILO_ASSERT(baseX > 0.0f, 0x3A4);
    MILO_ASSERT(baseY > 0.0f, 0x3A5);
    mBaseSizeX = baseX;
    mBaseSizeY = baseY;
}

void PatchPanel::SetStickerCategory(Symbol) {}

int ConvertToLayerIndex(PatchDir *patch, int i2) {
    MILO_ASSERT(patch, 0x3CB);
    if (i2 == 0)
        return patch->FindEmptyLayer();
    else
        return patch->NumLayersUsed() - i2;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(PatchPanel)
    HANDLE_EXPR(edit_layer, &EditLayer())
    HANDLE_EXPR(get_edit_layer_list_index, GetEditLayerListIndex())
    HANDLE_EXPR(empty_layer_ix, mPatch->FindEmptyLayer())
    HANDLE_EXPR(category_provider, mCategoryProvider)
    HANDLE_ACTION(set_sticker_provider, _msg->Obj<UIList>(2)->SetProvider(mGridProvider))
    HANDLE_EXPR(
        selected_sticker_ix_from_list,
        mGridProvider->GetDataFromList(_msg->Obj<UIList>(2))
    )
    HANDLE_ACTION(
        set_selected_sticker_ix,
        mGridProvider->SetListToData(_msg->Obj<UIList>(2), _msg->Int(3))
    )
    HANDLE_ACTION(set_sticker_category, SetStickerCategory(_msg->Sym(2)))
    HANDLE_EXPR(layer_provider, mLayerProvider)
    HANDLE_ACTION(reset_directions, ResetDirections())
    HANDLE_ACTION(reset_velocities, ResetVelocities())
    HANDLE_ACTION(store_undo, StoreUndo())
    HANDLE_ACTION(restore_undo, RestoreUndo())
    HANDLE(swap_layers, SwapLayers)
    HANDLE(clear_layer, ClearLayer)
    HANDLE(dupe_layer, DupeLayer)
    HANDLE_ACTION(copy_from_patch, CopyFromPatch(_msg->Obj<PatchDir>(2)))
    HANDLE_ACTION(copy_to_patch, CopyToPatch(_msg->Obj<PatchDir>(2)))
    HANDLE_ACTION(set_base_size, SetBaseSize(_msg->Float(2), _msg->Float(3)))
    HANDLE_EXPR(convert_to_layer_index, ConvertToLayerIndex(mPatch, _msg->Int(2)))
    HANDLE_ACTION(patch_changed, unk50 = true)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x407)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(PatchPanel)
    SYNC_PROP(patch, mPatch)
    SYNC_PROP_MODIFY(mode, mMode, Handle(Message("on_set_mode"), false))
    SYNC_PROP_MODIFY(edit_layer_idx, mEditLayerIdx, StoreUndo())
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS

inline void
LayerProvider::Custom(int, int idx, UIListCustom *slot, Hmx::Object *obj) const {
    if (slot->Matches("layer_help")) {
        InlineHelp *help = dynamic_cast<InlineHelp *>(obj);
        MILO_ASSERT(help, 0x182);
        if (idx == 0) {
            help->ResetConfig();
            DataNode node = create_layer;
            help->SetActionToken(kAction_Confirm, node);
        } else {
            DataNode modNode = modify_layer;
            DataNode optionsNode = layer_options;
            help->SetActionToken(kAction_Confirm, modNode);
            help->SetActionToken(kAction_Option, optionsNode);
        }
    }
}

inline RndMat *LayerProvider::Mat(int, int idx, UIListMesh *slot) const {
    if (idx == 0 && mPatch->NumLayersUsed() >= 50)
        return nullptr;
    else if (!slot->Matches("layer")) {
        return slot->DefaultMat();
    } else if (idx > 0)
        return GetMatForData(idx);
    else
        return nullptr;
}

inline void LayerProvider::InitData(RndDir *dir) {
    RndMat *mat = dir->Find<RndMat>("layer.mat", true);
    for (int i = 0; i < 50; i++) {
        mLayerMats[i]->Copy(mat, kCopyDeep);
    }
}

inline void LayerProvider::Text(int, int idx, UIListLabel *slot, UILabel *label) const {
    MILO_ASSERT(mPatch, 0xF7);
    if (idx == 0)
        label->SetTextToken(patch_new);
    else {
        SetLabelForData(label, idx);
    }
}

inline bool LayerProvider::IsActive(int idx) const {
    if (idx == 0) {
        MILO_ASSERT(mPatch, 0xED);
        return mPatch->NumLayersUsed() < 50;
    } else
        return true;
}

inline UIColor *
LayerProvider::SlotColorOverride(int, int idx, UIListWidget *w, UIColor *c) const {
    if (!w && idx > 0) {
        mPatch->Layer(ConvertToLayerIndex(mPatch, idx));
        return c;
    } else
        return c;
}

inline Symbol CategoryProvider::DataSymbol(int idx) const {
    return PatchLayer::sCategoryNames[idx];
}
inline int CategoryProvider::NumData() const { return PatchLayer::sCategoryNames.size(); }

inline RndMat *CategoryProvider::Mat(int, int idx, UIListMesh *slot) const {
    if (slot->Matches("sticker")) {
        return mCategoryMats[idx];
    } else
        return slot->DefaultMat();
}

inline void CategoryProvider::Text(int, int idx, UIListLabel *, UILabel *label) const {
    label->SetTextToken(DataSymbol(idx));
}

inline void CategoryProvider::InitData(RndDir *dir) {
    DataArray *cfg = SystemConfig("art_maker", "stickers");
    RndMat *stickerMat = dir->Find<RndMat>("sticker.mat", true);
    for (int i = 1; i < cfg->Size(); i++) {
        DataArray *arr = cfg->Array(i);
        RndMat *mat = Hmx::Object::New<RndMat>();
        mat->Copy(stickerMat, kCopyDeep);
        RndTex *t = mResource->Find<RndTex>(arr->Str(1), true);
        MILO_ASSERT(t, 0xA8);
        mat->SetDiffuseTex(t);
        mCategoryMats.push_back(mat);
    }
}

inline int StickerProvider::NumData() const {
    if (mStickers)
        return mStickers->size();
    else
        return 0;
}

inline RndMat *StickerProvider::Mat(int, int data, UIListMesh *slot) const {
    MILO_ASSERT(data < mStickerMats.size(), 0x7A);
    if (slot->Matches("sticker"))
        return mStickerMats[data];
    else
        return slot->DefaultMat();
}

inline void StickerProvider::InitData(RndDir *dir) {
    mStickerMat = dir->Find<RndMat>("sticker.mat", true);
}