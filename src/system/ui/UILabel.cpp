#include "UILabel.h"
#include "obj/Object.h"
#include "os/System.h"
#include "utl/Locale.h"
#include "ui/UILabelDir.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

bool UILabel::sDebugHighlight;
bool UILabel::sDeferUpdate;
INIT_REVS(UILabel)

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

void UILabel::Poll(){
    RndGroup* grp = mLabelDir->HighlighMeshGroup();
    if(mUseHighlightMesh && grp && GetState() == UIComponent::kFocused){
        mLabelDir->Poll();
    }
    UIComponent::Poll();
}

void UILabel::Draw() {
    if (!(mAlpha <= 0)) RndDrawable::Draw();
}

float UILabel::GetDrawWidth(){
    float w = 0.0f;
    float h = 0.0f;
    mText->GetCurrentStringDimensions(w, h);
    return w;
}

float UILabel::GetDrawHeight(){
    float w = 0.0f;
    float h = 0.0f;
    mText->GetCurrentStringDimensions(w, h);
    return h;
}

void UILabel::SetUseHighlightMesh(bool b){
    mUseHighlightMesh = b;
    Update();
}

RndDrawable* UILabel::CollideShowing(const Segment& s, float& f, Plane& pl){
    return mText->Collide(s, f, pl) ? this : 0;
}

int UILabel::CollidePlane(const Plane& p){
    return mText->CollidePlane(p);
}

float UILabel::GetDistanceToPlane(const Plane& p, Vector3& v){
    return mText->GetDistanceToPlane(p, v);
}

Symbol UILabel::TextToken() const { return mTextToken; }
RndText* UILabel::TextObj(){ return mText; }

const char* UILabel::GetDefaultText() const {
    if(!mIcon.empty()) return mIcon.c_str();
    else return Localize(mTextToken, false);
}

void UILabel::SetEditText(const char*){}

void UILabel::SetTextToken(Symbol s){
    mTextToken = s;
    SetTokenFmtImp(mTextToken, 0, 0, 0, true);
}

void UILabel::SetInt(int i, bool b){
    if(b){
        SetDisplayText(LocalizeSeparatedInt(i), true);
    }
    else SetDisplayText(MakeString("%d", i), true);
}

void UILabel::SetFloat(const char* cc, float f){
    SetDisplayText(LocalizeFloat(cc, f), true);
}

void UILabel::SetIcon(char c){
    mIcon = MakeString("%c", c);
    if(!mIcon.empty() || !TheLoadMgr.EditMode()){
        SetDisplayText(mIcon.c_str(), !TheLoadMgr.EditMode());
    }
}

void UILabel::AppendIcon(char c){
    SetDisplayText(MakeString("%s%c", unk114, c), true);
}

void UILabel::SetDateTime(const DateTime& dt, Symbol s){
    String str(Localize(s, false));
    dt.Format(str);
    SetDisplayText(str.c_str(), true);
}

void UILabel::SetSubtitle(const DataArray* da){
    SetDisplayText(da->Str(2), true);
}

void UILabel::SetTokenFmt(const DataArray* da){
    DataNode& n = da->Evaluate(0);
    bool b = false;
    if(da->Size() > 1){
        if(da->Evaluate(1).Type() == kDataArray) b = true;
    }
    if(b){
        SetTokenFmtImp(da->ForceSym(0), da->Array(1), da, 2, false);
    }
    else {
        SetTokenFmtImp(da->ForceSym(0), 0, da, 1, false);
    }
}

void UILabel::SetDisplayText(const char* cc, bool b){
    if(b) mTextToken = gNullStr;
    unk114 = cc;
    Update();
}

void UILabel::SetColorOverride(UIColor* col){
    mColorOverride = col;
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
    HANDLE_EXPR(has_highlight_mesh, mLabelDir->HighlighMeshGroup() != 0)
    HANDLE(get_material_variations, OnGetMaterialVariations)
    HANDLE(get_altmaterial_variations, OnGetAltMaterialVariations)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(1554)
END_HANDLERS


BEGIN_PROPSYNCS(UILabel)
    SYNC_PROP(leading, h);
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
