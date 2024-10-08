#include "UILabel.h"
#include "obj/Object.h"
#include "os/System.h"
#include "utl/Locale.h"
#include "ui/UILabelDir.h"
#include "ui/UI.h"
#include "rndobj/Cam.h"
#include "math/MathFuncs.h"
#include "utl/SuperFormatString.h"
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

void UILabel::PreLoad(BinStream& bs){
    LOAD_REVS(bs)
    ASSERT_REVS(0x18, 0)
    UIComponent::PreLoad(bs);
    if(gRev != 0 && gRev < 0xE){
        bool b; bs >> b;
    }
    bs >> mTextToken;
    if(gRev > 0xD){
        String s; bs >> s;
    }
    if(gRev > 0xE) bs >> mIcon;
    if(gRev > 1){
        int alignment, capsMode;
        bs >> mTextSize >> alignment >> capsMode;
        MILO_ASSERT(alignment < 255, 0xFF);
        MILO_ASSERT(capsMode < 255, 0x100);
        mAlignment = alignment;
        mCapsMode = capsMode;
        if(gRev > 7){
            LOAD_BITFIELD(bool, mMarkup)
        }
        bs >> mLeading >> mKerning;
    }
    if(gRev > 4) bs >> mItalics;
    if(gRev > 2){
        int fitType;
        bs >> fitType;
        MILO_ASSERT(fitType < 255, 0x113);
        mFitType = fitType;
        bs >> mWidth >> mHeight;
    }
    if(gRev < 4){
        Transform xfm = LocalXfm();
        if(mAlignment & 1){
            xfm.v.x -= mWidth * 0.5f;
        }
        else if(mAlignment & 4){
            xfm.v.x += mWidth * 0.5f;
        }
        if(mAlignment & 0x10){
            xfm.v.z += mHeight * 0.5f;
        }
        else if(mAlignment & 0x40){
            xfm.v.z -= mHeight * 0.5f;
        }
        SetLocalXfm(xfm);
    }
    if(gRev > 5){
        int fixedLength;
        bs >> fixedLength;
        MILO_ASSERT(fixedLength < 32767, 0x12F);
        MILO_ASSERT(fixedLength >= 0, 0x130);
        mFixedLength = fixedLength;
    }
    if(gRev > 6){
        int reserveLines;
        bs >> reserveLines;
        MILO_ASSERT(reserveLines < 32767, 0x138);
        MILO_ASSERT(reserveLines >= 0, 0x139);
        mReservedLine = reserveLines;
    }
    if(gRev - 9 < 7U){
        bool b;
        int a, c, d;
        bs >> b >> a >> c >> d;
    }
    if(gRev > 9) bs >> mPreserveTruncText;
    if(gRev > 10) bs >> mAlpha;
    if(gRev > 0xC) bs >> mColorOverride;
    if(gRev > 0x10){
        LOAD_BITFIELD(bool, mUseHighlightMesh)
    }
    if(gRev > 0x11){
        bs >> mAltTextSize >> mAltTextColor;
        LOAD_BITFIELD(bool, mAltStyleEnabled)
    }
    if(gRev > 0x12) bs >> mAltKerning;
    else mAltKerning = mKerning;
    if(gRev > 0x13) bs >> mAltZOffset;
    if(gRev > 0x14) bs >> mFontMatVariation;
    if(gRev > 0x15){
        bs >> mAltFontResourceName;
        AltFontResourceFileUpdated(true);
    }
    if(gRev > 0x16) bs >> mAltMatVariation;
    if(gRev > 0x17){
        bs >> mAltItalics >> mAltAlpha;
    }
}

void UILabel::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    LabelUpdate(false, true);
    sDeferUpdate = true;
    if(!mIcon.empty()) unk114 = mIcon;
    else SetTextToken(mTextToken);
    if(TheUI->RequireFixedText()){
        if(mFixedLength == 0){
            MILO_WARN("%s: %s is preloaded, but doesn't have fixed length", PathName(Dir()), Name());
        }
        if(mReservedLine == 0){
            MILO_WARN("%s: %s is preloaded, but doesn't have reserve lines", PathName(Dir()), Name());
        }
    }
    sDeferUpdate = false;
    if(mTextToken.Null()){
        if(mIcon.empty()){
            ObjectDir* rdir = ResourceDir();
            if(rdir && mFixedLength == 0 && mReservedLine != 0){
                mText->SetFont(0);
            }
            else Update();
        }
    }
    if(!mAltFontResourceName.empty()) mObjDirPtr.PostLoad(0);
}

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

DECOMP_FORCEACTIVE(UILabel, "LabelDir is not yet loaded, can't tell if edit text is allowed")

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

RndFont* UILabel::AltFont(){
    if(mObjDirPtr){
        UILabelDir* ldir = dynamic_cast<UILabelDir*>(mObjDirPtr.Ptr());
        if(!ldir) MILO_FAIL("bad UILabel alt font resource dir type!");
        RndText* t = ldir->TextObj(mAltMatVariation);
        if(!t){
            MILO_WARN("Label %s's alt font is referencing a mat variation '%s' that no longer exists, setting to default...", Name(), mAltMatVariation.Str());
            mAltMatVariation = Symbol();
            t = ldir->TextObj(mAltMatVariation);
        }
        MILO_ASSERT(t, 0x430);
        RndFont* font = t->mFont;
        MILO_ASSERT(font, 0x432);
        return font;
    }
    else return 0;
}

RndFont* UILabel::Font(){
    MILO_ASSERT(mLabelDir, 0x43B);
    if(mFont && mFontMatVariation == unk12c) return mFont;
    RndText* t = mLabelDir->TextObj(mFontMatVariation);
    if(!t){
        MILO_WARN("Label %s is referencing a mat variation '%s' that no longer exists, setting to default...", Name(), mFontMatVariation.Str());
        mFontMatVariation = Symbol();
        t = mLabelDir->TextObj(mFontMatVariation);
    }
    MILO_ASSERT(t, 0x448);
    RndFont* font = t->mFont;
    MILO_ASSERT(font, 0x44A);
    mFont = font;
    unk12c = mFontMatVariation;
    return mFont;
}

void UILabel::SetAlignment(RndText::Alignment a){
    mAlignment = a;
    Update();
}

void UILabel::SetCapsMode(RndText::CapsMode c){
    mCapsMode = c;
    Update();
}

void UILabel::SetFitType(UILabel::FitType f){
    mFitType = f;
    Update();
}

void UILabel::OnSetIcon(const char* cc){
    if(strlen(cc) > 1) MILO_WARN("%s is not a valid icon, must be one character", cc);
    SetIcon(*cc);
}

DataNode UILabel::OnSetTokenFmt(const DataArray* da){
    DataNode& n = da->Evaluate(2);
    if(n.Type() == kDataArray){
        DataArray* arr = n.Array(0);
        bool b = false;
        if(arr->Size() > 1){
            if(arr->Evaluate(1).Type() == kDataArray) b = true;
        }
        if(b){
            SetTokenFmtImp(arr->ForceSym(0), arr->Array(1), arr, 2, false);
        }
        else SetTokenFmtImp(arr->ForceSym(0), 0, arr, 1, false);
    }
    else {
        bool b = false;
        if(da->Size() > 3){
            if(da->Evaluate(3).Type() == kDataArray) b = true;
        }
        if(b){
            SetTokenFmtImp(da->ForceSym(2), da->Array(3), da, 4, false);
        }
        else {
            SetTokenFmtImp(da->ForceSym(2), 0, da, 3, false);
        }
    }
    return DataNode(1);
}

void UILabel::SetTokenFmtImp(Symbol s, const DataArray* da1, const DataArray* da2, int i, bool b){
    mTextToken = s;
    if(mTextToken.Null()) SetDisplayText(gNullStr, true);
    else {
        bool* b2;
        const char* localized = Localize(mTextToken, b2);
        if(*b2){
            SuperFormatString str(localized, da1, b);
            if(da2){
                for(; i < da2->Size(); i++){
                    DataNode& n = da2->Evaluate(i);
                    if(n.Type() == kDataSymbol){
                        str << Localize(n.Sym(0), 0);
                    }
                    else str << n;
                }
            }
            const char* text;
            if(b) text = str.RawFmt();
            else text = str.Str();
            SetDisplayText(text, false);
        }
        else SetDisplayText(localized, false);
    }
}

DataNode UILabel::OnSetInt(const DataArray* da){
    int i = da->Int(2);
    bool b = false;
    if(da->Size() > 3) b = da->Int(3);
    SetInt(i, b);
    return DataNode(1);
}

void UILabel::CenterWithLabel(UILabel* label, bool b, float f){
    MILO_ASSERT(TextObj()->GetAlignment() == RndText::kTopCenter || TextObj()->GetAlignment() == RndText::kMiddleCenter || TextObj()->GetAlignment() == RndText::kBottomCenter || label->TextObj()->GetAlignment() == RndText::kTopCenter || label->TextObj()->GetAlignment() == RndText::kMiddleCenter || label->TextObj()->GetAlignment() == RndText::kBottomCenter, 0x592);
    int num = 1;
    if(b) num = -1;
    Transform xfm = LocalXfm();
    float width = mText->MaxLineWidth();
    Transform otherxfm = label->LocalXfm();
    float otherwidth = label->mText->MaxLineWidth();
    SetLocalXfm(xfm);
    label->SetLocalXfm(otherxfm);
}

float GetTextSizeFromPctHeight(float f){
    if(TheLoadMgr.EditMode()){
        float transnum = -TheUI->unk34->mLocalXfm.v.Y();
        Vector2 vec2_1(0.0f, 0.0f);
        Vector3 vec3_1;
        TheUI->unk34->ScreenToWorld(vec2_1, transnum, vec3_1);
        Vector2 vec2_2(0.0f, f);
        Vector3 vec3_2;
        TheUI->unk34->ScreenToWorld(vec2_2, transnum, vec3_2);
        return std::fabs(vec3_1.z - vec3_2.z);
    }
    else return f;
}

float GetPctHeightFromTextSize(float f){
    if(TheLoadMgr.EditMode()){
        Vector3 vec3_1(0.0f, 0.0f, 0.0f);
        Vector2 vec2_1;
        TheUI->unk34->WorldToScreen(vec3_1, vec2_1);
        Vector3 vec3_2(0.0f, 0.0f, -f);
        Vector2 vec2_2;
        TheUI->unk34->WorldToScreen(vec3_2, vec2_2);
        return std::fabs(vec2_1.y - vec2_2.y);
    }
    else return f;
}

DataNode UILabel::OnGetMaterialVariations(const DataArray* da){
    int count = mLabelDir->NumMatVariations();
    DataArray* arr = new DataArray(count + 1);
    arr->Node(0) = DataNode(Symbol());
    for(int i = 1; i <= count; i++){
        arr->Node(i) = DataNode(mLabelDir->GetMatVariationName(i - 1));
    }
    DataNode ret = DataNode(arr, kDataArray);
    arr->Release();
    return ret;
}

DataNode UILabel::OnGetAltMaterialVariations(const DataArray* da){
    if(mObjDirPtr){
        UILabelDir* labeldir = dynamic_cast<UILabelDir*>(mObjDirPtr.Ptr());
        int count = labeldir->NumMatVariations();
        DataArray* arr = new DataArray(count + 1);
        arr->Node(0) = DataNode(Symbol());
        for(int i = 1; i <= count; i++){
            arr->Node(i) = DataNode(labeldir->GetMatVariationName(i - 1));
        }
        DataNode ret = DataNode(arr, kDataArray);
        arr->Release();
        return ret;
    }
    else {
        DataArray* arr = new DataArray(1);
        arr->Node(0) = DataNode(Symbol());
        DataNode ret = DataNode(arr, kDataArray);
        arr->Release();
        return ret;
    }
}

BEGIN_HANDLERS(UILabel)
    HANDLE_EXPR(get_string_width, mText->GetStringWidthUTF8(_msg->Str(2), NULL, false, NULL))
    HANDLE_ACTION(adjust_height, AdjustHeight(true))
    HANDLE(set_token_fmt, OnSetTokenFmt)
    HANDLE(set_int, OnSetInt)
    HANDLE_ACTION(set_float, SetFloat(_msg->Str(2), _msg->Float(3)))
    HANDLE_ACTION(center_with_label, CenterWithLabel(_msg->Obj<UILabel>(2), _msg->Int(3), _msg->Float(4)))
    HANDLE_EXPR(has_highlight_mesh, HasHighlightMesh())
    HANDLE(get_material_variations, OnGetMaterialVariations)
    HANDLE(get_altmaterial_variations, OnGetAltMaterialVariations)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(1554)
END_HANDLERS

BEGIN_PROPSYNCS(UILabel)
    SYNC_PROP_SET(text_token, mTextToken, SetTextToken(_val.ForceSym(0)))
    SYNC_PROP_SET(icon, mIcon.c_str(), OnSetIcon(_val.Str(0)))
    SYNC_PROP_SET(text_size, GetPctHeightFromTextSize(mTextSize), mTextSize = GetTextSizeFromPctHeight(_val.Float(0)); Update())
    SYNC_PROP_SET(alignment, mAlignment, SetAlignment((RndText::Alignment)_val.Int(0)))
    SYNC_PROP_SET(caps_mode, mCapsMode, SetCapsMode((RndText::CapsMode)_val.Int(0)))
    SYNC_PROP_SET(markup, mMarkup, mMarkup = _val.Int(0); Update())
    SYNC_PROP_MODIFY(leading, mLeading, Update())
    SYNC_PROP_MODIFY(kerning, mKerning, LabelUpdate(true, false))
    SYNC_PROP_MODIFY(italics, mItalics, Update())
    SYNC_PROP_SET(fit_type, mFitType, SetFitType((FitType)_val.Int(0)))
    SYNC_PROP_MODIFY(width, mWidth, Update())
    SYNC_PROP_MODIFY(height, mHeight, Update())
    SYNC_PROP_MODIFY(fixed_length, mFixedLength, Update())
    SYNC_PROP_MODIFY(reserve_lines, mReservedLine, Update())
    SYNC_PROP_MODIFY_ALT(preserve_trunc_text, mPreserveTruncText, Update())
    SYNC_PROP_SET(use_highlight_mesh, mUseHighlightMesh, SetUseHighlightMesh(_val.Int(0)))
    SYNC_PROP(color_override, mColorOverride)
    SYNC_PROP(alpha, mAlpha)
    SYNC_PROP_MODIFY_ALT(alt_font_resource_name, mAltFontResourceName, AltFontResourceFileUpdated(false))
    SYNC_PROP_SET(alt_text_size, GetPctHeightFromTextSize(mAltTextSize), mAltTextSize = GetTextSizeFromPctHeight(_val.Float(0)); Update())
    SYNC_PROP_MODIFY(alt_kerning, mAltKerning, Update())
    SYNC_PROP_MODIFY_ALT(alt_text_color, mAltTextColor, Update())
    SYNC_PROP_MODIFY(alt_z_offset, mAltZOffset, Update())
    SYNC_PROP_MODIFY(alt_italics, mAltItalics, Update())
    SYNC_PROP_MODIFY(alt_alpha, mAltAlpha, Update())
    SYNC_PROP_SET(alt_style_enabled, mAltStyleEnabled, mAltStyleEnabled = _val.Int(0); Update())
    SYNC_PROP_MODIFY(font_mat_variation, mFontMatVariation, LabelUpdate(false, false))
    SYNC_PROP_MODIFY(alt_mat_variation, mAltMatVariation, Update())
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
