#include "Text.h"
#include "math/MathFuncs.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/Font.h"
#include "utl/UTF8.h"
#include "utl/Symbols.h"

std::set<RndText*> RndText::mTextMeshSet;
float gSuperscriptScale = 0.7f;
float gGuitarScale = 0.7f;
float gGuitarZOffset = 1.0f;

INIT_REVS(RndText)

void RndText::Init() {
    Register();
    SystemConfig("rnd")->FindData("text_superscript_scale", gSuperscriptScale, false);
    SystemConfig("rnd")->FindData("text_guitar_scale", gGuitarScale, false);
    SystemConfig("rnd")->FindData("text_guitar_z_offset", gGuitarZOffset, false);
}

void RndText::Mats(std::list<class RndMat*>& matList, bool b){
    for(RndFont* font = mFont; font != 0; font = font->unk78){
        matList.push_back(font->mMat);
    }
}

void RndText::Replace(Hmx::Object* from, Hmx::Object* to){
    RndTransformable::Replace(from, to);
    RndFont* font = 0;
    if(font){

    }
    else {

    }
}

const char* RndText::FindPathName(){
    if(Name() && !*Name() && !Dir() && mParent){
        return MakeString("%s inside %s", ClassName().Str());
    }
    else return Hmx::Object::FindPathName();
}

SAVE_OBJ(RndText, 171)

void RndText::Load(BinStream& bs) {
    int dump;
    LOAD_REVS(bs)
    ASSERT_REVS(21, 0)
    if (gRev > 15) LOAD_SUPERCLASS(Hmx::Object);
    LOAD_SUPERCLASS(RndDrawable);
    if (gRev < 7) {
        ObjPtrList<Hmx::Object, class ObjectDir> dir(this, kObjListNoNull);
        bs >> dump;
        bs >> dir;
    }
    if(gRev > 1) LOAD_SUPERCLASS(RndTransformable);
    bs >> mFont;
    if(gRev < 3){
        int idx;
        bs >> idx;
        Alignment align_choices[6] = { kTopLeft, kTopCenter, kTopRight, kBottomLeft, kBottomCenter, kBottomRight };
        mAlign = align_choices[idx];
    }
    else {
        int align;
        bs >> align;
        MILO_ASSERT(align < 255, 0xE7);
        mAlign = align;
    }
    if(gRev < 2){
        float new_x, new_z;
        bs >> new_x >> new_z;
        SetLocalPos(new_x, 0.0f, -new_z * 0.75f);
    }
    bs >> unk_cc;
    if(gRev < 0x14){
        std::vector<unsigned short> vec;
        ASCIItoWideVector(vec, unk_cc.c_str());
        WideVectorToUTF8(vec, unk_cc);
    }
    if(gRev != 0){
        Hmx::Color col;
        bs >> col;
        mColor = col.Pack();
    }
    if(gRev > 0xC) bs >> mWrapWidth;
    else if(gRev > 3){
        bool b;
        bs >> b >> mWrapWidth;
        if(!b) mWrapWidth = 0.0f;
        if(gRev < 5 && (mWrapWidth < 0.0f || mWrapWidth > 1000.0f)) mWrapWidth = 0.0f;
    }
    if(gRev == 5){
        String str;
        bs >> str;
    }
    if(gRev == 5 || gRev == 6 || gRev == 7 || gRev == 8 || gRev == 9 || gRev == 10){
        bool b;
        bs >> b;
        if(mFont && mFont->mMat){
            int i = 0;
            if(b) i = 2;
            mFont->mMat->mDirty |= 2;
        }
    }
    if(gRev > 7) bs >> mLeading;
    int fixedLength;
    if(gRev > 0xB){
        bs >> fixedLength;
    }
    else if(gRev > 8){
        bool b;
        bs >> b;
        if(b){
            unk_cc.length();
        }
    }
    MILO_ASSERT(fixedLength < 65535, 0x13C);
    MILO_ASSERT(fixedLength >= 0, 0x13D);
    mFixedLength = fixedLength;
    if(mFixedLength != 0) ResizeText(mFixedLength);
    if(gRev > 9) bs >> mItalicStrength;
    if(gRev > 0xC) bs >> mSize;
    else {
        if(mFont){
            mSize = mFont->mDeprecatedSize;
        }
    }
    if(gRev < 0xD){
        mItalicStrength /= mSize;
    }
    if(gRev > 0xD){
        LOAD_BITFIELD(bool, mTextMarkup)
    }
    if(gRev > 0xE){
        int capsMode;
        bs >> capsMode;
        MILO_ASSERT(capsMode < 255, 0x158);
        mCapsMode = capsMode;
    }
    else mCapsMode = kCapsModeNone;
    if(gRev == 0x12 || gRev == 0x13 || gRev == 0x14){
        bool b; bs >> b;
    }
    if(gRev == 0x13 || gRev == 0x14){
        int i, j, k;
        bs >> i >> j >> k;
    }
    if(gRev < 0x11 && mCapsMode != kCapsModeNone){
        SetText(unk_cc.c_str());
    }
    unkf0 = unkd8;
    mAltSize = mSize;
    mAltItalicStrength = mItalicStrength;
    mAltColor = mColor;
    unk100 = unke8;
    unk101 = unke9;
    mAltZOffset = mZOffset;
    UpdateText(true);
}

void RndText::DeferUpdateText(){
    MILO_ASSERT(mDeferUpdate >= 0, 0x174);
    MILO_ASSERT(mDeferUpdate < 15, 0x175);
    mDeferUpdate++;
}

void RndText::ResolveUpdateText(){
    MILO_ASSERT(mDeferUpdate > 0, 0x17E);
    MILO_ASSERT(mDeferUpdate < 15, 0x17F);
    mDeferUpdate--;
    if(unkbp5 && mDeferUpdate == 0){
        unkbp5 = 0;
        UpdateText(true);
    }
}

void RndText::UpdateText(bool) {
    if (mDeferUpdate) {
        unk9p2 = true;
        return;
    }
}

void RndText::SetWrapWidth(float f){
    if(mWrapWidth == f) return;
    mWrapWidth = f;
    UpdateText(true);
}

void RndText::SetFixedLength(int len){
    if(mFixedLength != len){
        MILO_ASSERT(len < 65535, 0x1F2);
        mFixedLength = len;
        if(len != 0) ResizeText(len);
        UpdateText(true);
    }
}

void RndText::SetSize(float f) {
    if (mSize == f) return;
    mSize = f;
    UpdateText(true);
}

void RndText::SetItalics(float f){
    if(mItalicStrength == f) return;
    mItalicStrength = f;
    UpdateText(true);
}

void RndText::SetMarkup(bool b){
    if(mTextMarkup == b) return;
    mTextMarkup = b;
    UpdateText(true);
}

void RndText::SetAltSizeAndZOffset(float f1, float f2){
    if(mAltSize == f1 && mAltZOffset == f2) return;
    if(f1 == 0.0f) f1 = mSize;
    mAltSize = f1;
    mAltZOffset = f2;
    UpdateText(true);
}

BEGIN_COPYS(RndText)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(RndTransformable)
    if (ty == kCopyFromMax) return;
    CREATE_COPY(RndText)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mFont)
    END_COPYING_MEMBERS
    UpdateText(true);
END_COPYS

void RndText::Print() {
    TheDebug << "   font: " << mFont << "\n";
}

RndText::RndText() : mFont(this, NULL), mWrapWidth(0.0f), mLeading(1.0f), unkd8(mFont), mSize(1.0f), mItalicStrength(0.0f), mColor(-1), unke8(true), unke9(false),
    mZOffset(0.0f), unkf0(0), mAltSize(1.0f), mAltItalicStrength(0.0f), mAltColor(-1), unk100(true), unk101(false), mAltZOffset(0.0f), mAlign(kTopLeft), mCapsMode(kCapsModeNone),
    mFixedLength(0), mDeferUpdate(0), unk124b4(0), unk128(0), unk12c(0.0f), unk130(0.0f) {
    mTextMarkup = false;
    unkbp4 = false;
    unkbp5 = false;
    unkbp6 = false;
    unkbp7 = false;
}

RndText::~RndText() {
    MILO_ASSERT(mDeferUpdate == 0, 723);
}

void RndText::SetFont(RndFont* f) {
    mFont = f;
    UpdateText(true);
}

void RndText::SetAlignment(Alignment a){
    if(mAlign == a) return;
    mAlign = a;
    UpdateText(true);
}

void RndText::SetLeading(float f){
    if(mLeading == f) return;
    mLeading = f;
    UpdateText(true);
}

void RndText::ReserveLines(int i) { mLines.reserve(i); }

class String RndText::TextASCII() const {
    class String s;
    s.resize(UTF8StrLen(unk_cc.c_str()) + 1);
    UTF8toASCIIs(s.mStr, s.mCap, unk_cc.c_str(), '*');
    return s;
}

void RndText::SetTextASCII(const char* cc) {
    class String s;
    std::vector<unsigned short> vec;
    ASCIItoWideVector(vec, cc);
    WideVectorToUTF8(vec, s);
    SetText(s.c_str());

}

BEGIN_HANDLERS(RndText)
    HANDLE(set_fixed_length, OnSetFixedLength)
    HANDLE(set_font, OnSetFont)
    HANDLE(set_align, OnSetAlign)
    HANDLE(set_text, OnSetText)
    HANDLE(set_size, OnSetSize)
    HANDLE(set_wrap_width, OnSetWrapWidth)
    HANDLE(set_color, OnSetColor)
    HANDLE_EXPR(get_text_size, Max(mFixedLength, (int)unk_cc.length()))
    HANDLE_EXPR(get_string_width, GetStringWidthUTF8(_msg->Str(2), NULL, false, NULL))

    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(2789)
END_HANDLERS

DataNode RndText::OnSetFixedLength(DataArray* da){
    SetFixedLength(da->Int(2));
    return DataNode(0);
}

DataNode RndText::OnSetFont(DataArray* da){
    SetFont(da->Obj<RndFont>(2));
    return DataNode(0);
}

DataNode RndText::OnSetAlign(DataArray* da){
    SetAlignment((Alignment)da->Int(2));
    return DataNode(0);
}

DataNode RndText::OnSetText(DataArray* da){
    SetText(da->Str(2));
    return DataNode(0);
}

DataNode RndText::OnSetWrapWidth(DataArray* da){
    SetWrapWidth(da->Float(2));
    return DataNode(0);
}

DataNode RndText::OnSetSize(DataArray* da){
    SetSize(da->Float(2));
    return DataNode(0);
}
