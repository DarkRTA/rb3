#include "UILabel.h"
#include "obj/Object.h"
#include "os/System.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

UILabel::UILabel() : mLabelDir(0), mText(Hmx::Object::New<RndText>()), unk114(), mFont(this, 0), unk12c(), mTextToken(), mIcon(),
    mTextSize(30.0f), mLeading(1.0f), mKerning(0.0f), mItalics(0.0f), mWidth(0.0f), mHeight(0.0f), mFixedLength(0), mReservedLine(0),
    mPreserveTruncText(), mAlpha(1.0f), mColorOverride(this, 0), mFontMatVariation(), mAltMatVariation(), mAltTextSize(mTextSize), mAltKerning(mKerning),
    mAltTextColor(this, 0), mAltZOffset(0.0f), mAltItalics(0.0f), mAltAlpha(1.0f), mFitType(0), mAlignment(0x22), mCapsMode(0), mMarkup(0), mUseHighlightMesh(0), mAltStyleEnabled(0) {
    mText->SetTransParent(this, false);
    mResourcePath = GetResourcesPath();
}

UILabel::~UILabel() {

}

void UILabel::Init() {
    Hmx::Object::RegisterFactory(StaticClassName(), NewObject);
    // Hmx::Object::RegisterFactory(UILabelDir::StaticClassName(), UILabelDir::NewObject);
}

void UILabel::Terminate() {}

BEGIN_COPYS(UILabel)
    GET_COPY_AND_ASSERT(UILabel, 96)
    COPY_SUPERCLASS(UIComponent)
    // SetCreditsText();
END_COPYS


SAVE_OBJ(UILabel, 173)

void UILabel::Load(BinStream& bs) { PreLoad(bs); PostLoad(bs); }

void UILabel::Draw() {
    if (!(mAlpha <= 0)) RndDrawable::Draw();
}

void UILabel::SetDisplayText(const char* cc, bool b){

}

void UILabel::Update() {
    if (!sDeferUpdate) LabelUpdate(false, false);
}

void UILabel::LabelUpdate(bool b, bool c) {
    
}


BEGIN_HANDLERS(UILabel)
    HANDLE_EXPR(get_string_width, mText->GetStringWidthUTF8(_msg->Str(2), NULL, false, NULL))
    HANDLE_ACTION(adjust_height, AdjustHeight(true))
    HANDLE(set_token_fmt, OnSetTokenFmt)
    HANDLE(set_int, OnSetInt)
    HANDLE_ACTION(set_float, SetFloat(_msg->Str(2), _msg->Float(3)))
    HANDLE_ACTION(center_with_label, CenterWithLabel(_msg->Obj<UILabel>(2), _msg->Int(3), _msg->Float(4)))
    // HANDLE_EXPR(has_highlight_mesh, (bool)mLabelDir->HighlightMeshGroup())
    HANDLE(get_material_variations, OnGetMaterialVariations)
    HANDLE(get_altmaterial_variations, OnGetAltMaterialVariations)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(1554)
END_HANDLERS


BEGIN_PROPSYNCS(UILabel)
    SYNC_PROP(leading, h);
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
