#include "ui/UILabelDir.h"
#include "ui/UIColor.h"
#include "obj/ObjVersion.h"
#include "decomp.h"
#include "utl/Symbols.h"

INIT_REVS(UILabelDir)

UILabelDir::UILabelDir()
    : mDefaultColor(this), mColors(), mTextObj(this), mFocusAnim(this), mPulseAnim(this),
      mTopLeftHighlightBone(this), mTopRightHighlightBone(this),
      mBottomLeftHighlightBone(this), mBottomRightHighlightBone(this),
      mHighlightMeshGroup(this), mFocusedBackgroundGroup(this),
      mUnfocusedBackgroundGroup(this), mAllowEditText(0) {
    for (int i = 0; i < UIComponent::kNumStates; i++) {
        mColors.push_back(ObjPtr<UIColor>(this));
    }
}

void UILabelDir::GetStateColor(UIComponent::State state, Hmx::Color &col) const {
    MILO_ASSERT(state < UIComponent::kNumStates, 0x2E);
    UIColor *uiCol = mColors[state];
    if (uiCol) {
        col = uiCol->GetColor();
    } else if (mDefaultColor) {
        col = mDefaultColor->GetColor();
    } else
        col.Reset();
}

RndText *UILabelDir::TextObj(Symbol sym) const {
    if (NumGennedFonts() > 0)
        return GetGennedText(sym);
    else
        return mTextObj;
}

RndAnimatable *UILabelDir::FocusAnim() const { return mFocusAnim; }
RndAnimatable *UILabelDir::PulseAnim() const { return mPulseAnim; }
RndGroup *UILabelDir::HighlighMeshGroup() const { return mHighlightMeshGroup; }
RndMesh *UILabelDir::TopLeftHighlightBone() const { return mTopLeftHighlightBone; }
RndMesh *UILabelDir::TopRightHighlightBone() const { return mTopRightHighlightBone; }
RndMesh *UILabelDir::BottomLeftHighlightBone() const { return mBottomLeftHighlightBone; }
RndMesh *UILabelDir::BottomRightHighlightBone() const {
    return mBottomRightHighlightBone;
}

void UILabelDir::SetColor(UIComponent::State state, UIColor *color) {
    MILO_ASSERT(state < UIComponent::kNumStates, 0x86);
    mColors[state] = color;
}

SAVE_OBJ(UILabelDir, 0x9C)

DECOMP_FORCEACTIVE(UILabelDir, "ObjPtr_p.h", "f.Owner()", "")

void UILabelDir::SyncObjects() {
    RndDir::SyncObjects();
    UIFontImporter::FontImporterSyncObjects();
}

BEGIN_LOADS(UILabelDir)
    LOAD_SUPERCLASS(ObjectDir)
END_LOADS

void UILabelDir::PreLoad(BinStream &bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(9, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    RndDir::PreLoad(bs);
}

void UILabelDir::PostLoad(BinStream &bs) {
    RndDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    bs >> mTextObj;
    if (gRev >= 3 && gRev <= 8) {
        ObjPtr<RndFont> oPtr(this);
        bs >> oPtr;
    }
    if (gRev >= 1)
        bs >> mFocusAnim;
    if (gRev >= 2)
        bs >> mPulseAnim;
    if (gRev >= 4) {
        bs >> mHighlightMeshGroup;
        bs >> mTopLeftHighlightBone;
        bs >> mTopRightHighlightBone;
    }
    if (gRev >= 5) {
        bs >> mBottomLeftHighlightBone;
        bs >> mBottomRightHighlightBone;
    }
    if (gRev >= 6) {
        bs >> mFocusedBackgroundGroup;
        bs >> mUnfocusedBackgroundGroup;
    }
    if (gRev >= 7) {
        bs >> mAllowEditText;
    }
    bs >> mDefaultColor;
    for (int i = 0; i < UIComponent::kNumStates; i++) {
        ObjPtr<UIColor> uiCol(this);
        bs >> uiCol;
        mColors[i] = uiCol;
    }
    if (gRev >= 8) {
        UIFontImporter::Load(bs);
    }
}

BEGIN_COPYS(UILabelDir)
    COPY_SUPERCLASS(RndDir)
    CREATE_COPY(UILabelDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mDefaultColor)
        COPY_MEMBER(mColors)
        COPY_MEMBER(mHighlightMeshGroup)
        COPY_MEMBER(mTopLeftHighlightBone)
        COPY_MEMBER(mTopRightHighlightBone)
        COPY_MEMBER(mBottomLeftHighlightBone)
        COPY_MEMBER(mBottomRightHighlightBone)
        COPY_MEMBER(mAllowEditText)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_PROPSYNCS(UILabelDir)
    SYNC_PROP(text_obj, mTextObj)
    SYNC_PROP(allow_edit_text, mAllowEditText)
    SYNC_PROP(focus_anim, mFocusAnim)
    SYNC_PROP(pulse_anim, mPulseAnim)
    SYNC_PROP(highlight_mesh_group, mHighlightMeshGroup)
    SYNC_PROP(top_left_highlight_bone, mTopLeftHighlightBone)
    SYNC_PROP(top_right_highlight_bone, mTopRightHighlightBone)
    SYNC_PROP(bottom_left_highlight_bone, mBottomLeftHighlightBone)
    SYNC_PROP(bottom_right_highlight_bone, mBottomRightHighlightBone)
    SYNC_PROP(focused_background_group, mFocusedBackgroundGroup)
    SYNC_PROP(unfocused_background_group, mUnfocusedBackgroundGroup)
    SYNC_PROP(default_color, mDefaultColor)
    SYNC_PROP_SET(
        normal_color,
        mColors[UIComponent::kNormal].Ptr(),
        SetColor(UIComponent::kNormal, _val.Obj<UIColor>())
    )
    SYNC_PROP_SET(
        focused_color,
        mColors[UIComponent::kFocused].Ptr(),
        SetColor(UIComponent::kFocused, _val.Obj<UIColor>())
    )
    SYNC_PROP_SET(
        disabled_color,
        mColors[UIComponent::kDisabled].Ptr(),
        SetColor(UIComponent::kDisabled, _val.Obj<UIColor>())
    )
    SYNC_PROP_SET(
        selecting_color,
        mColors[UIComponent::kSelecting].Ptr(),
        SetColor(UIComponent::kSelecting, _val.Obj<UIColor>())
    )
    SYNC_PROP_SET(
        selected_color,
        mColors[UIComponent::kSelected].Ptr(),
        SetColor(UIComponent::kSelected, _val.Obj<UIColor>())
    )
    SYNC_SUPERCLASS(UIFontImporter)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(UILabelDir)
    HANDLE_SUPERCLASS(UIFontImporter)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x12F)
END_HANDLERS
