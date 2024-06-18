#include "UILabel.h"
#include "obj/Object.h"
#include "os/System.h"
#include "ui/UILabelDir.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

UILabel::UILabel() : mLabelDir(0), mText(Hmx::Object::New<RndText>()), unk114(), mFont(this, 0), unk12c(), mTextToken(), mIcon(),
    mTextSize(30.0f), mLeading(1.0f), mKerning(0.0f), mItalics(0.0f), mWidth(0.0f), mHeight(0.0f), mFixedLength(0), mReservedLine(0),
    mPreserveTruncText(), mAlpha(1.0f), mColorOverride(this, 0), mFontMatVariation(), mAltMatVariation(), mAltTextSize(mTextSize), mAltKerning(mKerning),
    mAltTextColor(this, 0), mAltZOffset(0.0f), mAltItalics(0.0f), mAltAlpha(1.0f), mFitType(0), mAlignment(0x22), mCapsMode(0), mMarkup(0), mUseHighlightMesh(0), mAltStyleEnabled(0) {
    mText->SetTransParent(this, false);
    mResourcePath = GetResourcesPath();
}

UILabel::~UILabel() {
    delete mText;
}

void UILabel::Init(){
    TheUI->InitResources("UILabel");
    Register();
    UILabelDir::Init();
}

void UILabel::Terminate() {}

BEGIN_COPYS(UILabel)
    CREATE_COPY_AS(UILabel, f)
    MILO_ASSERT(f, 96);
    COPY_SUPERCLASS(UIComponent)
    Update();
END_COPYS

void UILabel::CopyMembers(const UIComponent* o, Hmx::Object::CopyType ty){
    UIComponent::CopyMembers(o, ty);
    CREATE_COPY_AS(UILabel, l)
    MILO_ASSERT(l, 0x6A);
    COPY_MEMBER_FROM(l, mTextToken)
    COPY_MEMBER_FROM(l, mIcon)
    COPY_MEMBER_FROM(l, mTextSize)
    COPY_MEMBER_FROM(l, mCapsMode)
    COPY_MEMBER_FROM(l, mAlignment)
    COPY_MEMBER_FROM(l, mMarkup)
    COPY_MEMBER_FROM(l, mLeading)
    COPY_MEMBER_FROM(l, mKerning)
    COPY_MEMBER_FROM(l, mItalics)
    COPY_MEMBER_FROM(l, mFitType)
    COPY_MEMBER_FROM(l, mWidth)
    COPY_MEMBER_FROM(l, mHeight)
    COPY_MEMBER_FROM(l, mFixedLength)
    COPY_MEMBER_FROM(l, mAlpha)
    COPY_MEMBER_FROM(l, mColorOverride)
    COPY_MEMBER_FROM(l, mPreserveTruncText)
    if(mFixedLength != 0) mText->SetFixedLength(mFixedLength);
    COPY_MEMBER_FROM(l, mReservedLine)
    if(mReservedLine != 0) mText->ReserveLines(mReservedLine);
    COPY_MEMBER_FROM(l, unk114)
    COPY_MEMBER_FROM(l, mUseHighlightMesh)
    COPY_MEMBER_FROM(l, mAltTextSize)
    COPY_MEMBER_FROM(l, mAltKerning)
    COPY_MEMBER_FROM(l, mAltTextColor)
    COPY_MEMBER_FROM(l, mAltZOffset)
    COPY_MEMBER_FROM(l, mAltItalics)
    COPY_MEMBER_FROM(l, mAltAlpha)
    COPY_MEMBER_FROM(l, mAltStyleEnabled)
    COPY_MEMBER_FROM(l, mFontMatVariation)
    COPY_MEMBER_FROM(l, mAltMatVariation)
    COPY_MEMBER_FROM(l, mAltFontResourceName)
    COPY_MEMBER_FROM(l, mObjDirPtr)
}

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
