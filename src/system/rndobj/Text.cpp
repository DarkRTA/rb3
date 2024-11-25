#include "Text.h"
#include "math/Utl.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/Font.h"
#include "rndobj/Mat.h"
#include "rndobj/Mesh.h"
#include "rndobj/Trans.h"
#include "utl/Symbols2.h"
#include "utl/TextStream.h"
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
    for(RndFont* font = mFont; font != 0; font = font->NextFont()){
        if(font->GetMat()) matList.push_back(font->GetMat());
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
    bs >> mText;
    if(gRev < 0x14){
        std::vector<unsigned short> vec;
        ASCIItoWideVector(vec, mText.c_str());
        WideVectorToUTF8(vec, mText);
    }
    if(gRev != 0){
        bs >> mStyle.color;
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
        if(mFont && mFont->GetMat()){
            int i = 0;
            if(b) i = 2;
            mFont->GetMat()->SetZMode((ZMode)i);
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
            mText.length();
        }
    }
    MILO_ASSERT(fixedLength < 65535, 0x13C);
    MILO_ASSERT(fixedLength >= 0, 0x13D);
    mFixedLength = fixedLength;
    if(mFixedLength != 0) ResizeText(mFixedLength);
    if(gRev > 9) bs >> mStyle.italics;
    if(gRev > 0xC) bs >> mStyle.size;
    else {
        if(mFont){
            mStyle.size = mFont->mDeprecatedSize;
        }
    }
    if(gRev < 0xD){
        mStyle.italics /= mStyle.size;
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
        SetText(mText.c_str());
    }
    mAltStyle = mStyle;
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
    if (mStyle.size == f) return;
    mStyle.size = f;
    UpdateText(true);
}

void RndText::SetItalics(float f){
    if(mStyle.italics == f) return;
    mStyle.italics = f;
    UpdateText(true);
}

void RndText::SetColor(const Hmx::Color32& col){
    if(mStyle.color == col) return;
    else {
        mStyle.color = col;
        bool b1 = false;
        if(!mTextMarkup){
            for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
                RndMesh* mesh = it->second.unk0;
                if(mesh && mesh->GetMutable()){
                    RndMesh::VertVector& verts = mesh->Verts();
                    for(RndMesh::Vert* it = verts.begin(); it != verts.end(); ++it){
                        it->color = col;
                    }
                    mesh->Sync(0x1F);
                    b1 = true;
                }
            }
        }
        if(!b1){
            UpdateText(true);
        }
    }
}

void RndText::SetMarkup(bool b){
    if(mTextMarkup == b) return;
    mTextMarkup = b;
    UpdateText(true);
}

void RndText::SetData(Alignment a, const char* text, RndFont* font, float leading, float wrapwidth, float size, float italics, const Hmx::Color32& col, bool markup, CapsMode caps, int fixedLength){
    RndTextUpdateDeferrer deferrer(this);
    if(mAlign != a || mCapsMode != caps || mFont != font || mLeading != leading || mWrapWidth != wrapwidth ||
        mTextMarkup != markup || mStyle.size != size || mStyle.italics != italics || mStyle.color != col || mFixedLength != fixedLength){
        SetFont(font);
        mAlign = a;
        mCapsMode = caps;
        mFont = font;
        mLeading = leading;
        mWrapWidth = wrapwidth;
        mTextMarkup = markup;
        mStyle.size = size;
        mStyle.italics = italics;
        mStyle.color = col;
        MILO_ASSERT(fixedLength < 65535, 0x256);
        mFixedLength = fixedLength;
        if(mFixedLength != 0) ResizeText(mFixedLength);
        UpdateText(true);
    }
    SetText(text);
}

void RndText::SetAltStyle(RndFont* font, float size, const Hmx::Color32* col, float z, float italics, bool b){
    RndTextUpdateDeferrer def(this);
    mAltStyle.font = font ? font : mFont.Ptr();
    mAltStyle.size = size ? size : mStyle.size;
    mAltStyle.color = col ? *col : mStyle.color;
    mAltStyle.zOffset = z;
    mAltStyle.italics = italics;
    unkbp4 = b;
    UpdateText(true);
}

void RndText::SetAltSizeAndZOffset(float f1, float f2){
    if(mAltStyle.size == f1 && mAltStyle.zOffset == f2) return;
    mAltStyle.size = f1 ? f1 : mStyle.size;
    mAltStyle.zOffset = f2;
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
        COPY_MEMBER(mAlign)
        COPY_MEMBER(mCapsMode)
        COPY_MEMBER(mText)
        COPY_MEMBER(mWrapWidth)
        COPY_MEMBER(mLeading)
        COPY_MEMBER(mStyle)
        COPY_MEMBER(mTextMarkup)
        COPY_MEMBER(mFixedLength)
        if(mFixedLength != 0) ResizeText(mFixedLength);
    END_COPYING_MEMBERS
    UpdateText(true);
END_COPYS

void RndText::Print() {
    TextStream* ts = &TheDebug;
    *ts << "   font: " << mFont << "\n";
    *ts << "   align: " << mAlign << "\n";
    *ts << "   text: ";
    for(int i = 0; i < mText.length(); ){
        unsigned short us;
        int next = DecodeUTF8(us, &mText.c_str()[i]);
        *ts << WideCharToChar(&us);
        i += next;
    }
    *ts << "\n";
    *ts << "   wrap width: " << mWrapWidth << "\n";
    *ts << "   leading: " << mLeading << "\n";
    *ts << "   size: " << mStyle.size << "\n";
    *ts << "   italics: " << mStyle.italics << "\n";
    *ts << "   color: " << Hmx::Color(mStyle.color) << "\n";
    *ts << "   markup: " << mTextMarkup << "\n";
    *ts << "   capsMode: " << mCapsMode << "\n";
}

RndText::RndText() : mFont(this), mWrapWidth(0.0f), mLeading(1.0f), mStyle(mFont, 1, 0, -1, 0),
    mAltStyle(nullptr, 1, 0, -1, 0), mAlign(kTopLeft), mCapsMode(kCapsModeNone),
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

void RndText::SetMeshForceNoQuantize(){
    for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
        if(it->second.unk4){
            it->second.unk0->mForceNoQuantize = true;
        }
    }
}

void RndText::SetMeshForceNoUpdate(){
    if(unkbp6){
        mTextMeshSet.insert(this);
        unkbp6 = false;
    }
}

void RndText::ReserveLines(int i) { mLines.reserve(i); }

class String RndText::TextASCII() const {
    class String s;
    s.resize(UTF8StrLen(mText.c_str()) + 1);
    UTF8toASCIIs((char*)s.c_str(), s.capacity(), mText.c_str(), '*');
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
    HANDLE_EXPR(get_text_size, Max(mFixedLength, (int)mText.length()))
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

BEGIN_PROPSYNCS(RndText)
    SYNC_PROP_SET(text, TextASCII(), SetTextASCII(_val.Str()));
    SYNC_PROP_MODIFY_ALT(font, mFont, UpdateText(true))
    SYNC_PROP_MODIFY_ALT(align, mAlign, UpdateText(true))
    SYNC_PROP_MODIFY_ALT(caps_mode, mCapsMode, SetText(mText.c_str()))
    SYNC_PROP_SET(color, mStyle.color.Opaque(), Hmx::Color32 col(_val.Int()); col.a = mStyle.color.a; SetColor(col))
    SYNC_PROP_SET(alpha, mStyle.color.fa(), Hmx::Color32 col(mStyle.color); col.SetAlpha(_val.Float()); SetColor(col))
    SYNC_PROP_SET(wrap_width, mWrapWidth, SetWrapWidth(_val.Float()))
    SYNC_PROP_SET(leading, mLeading, SetLeading(_val.Float()))
    SYNC_PROP_SET(italics, mStyle.italics, SetItalics(_val.Float()))
    SYNC_PROP_SET(fixed_length, mFixedLength, SetFixedLength(_val.Int()))
    SYNC_PROP_SET(size, mStyle.size, SetSize(_val.Float()))
    SYNC_PROP_SET(markup, mTextMarkup, SetMarkup(_val.Int()))
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS