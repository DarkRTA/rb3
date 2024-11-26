#include "Text.h"
#include "decomp.h"
#include "math/Utl.h"
#include "milo_types.h"
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
#include "stl/_pair.h"
#include "utl/Str.h"
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

RndDrawable* RndText::CollideShowing(const Segment& s, float& f, Plane& p){
    for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
        RndMesh* mesh = it->second.mesh;
        if(mesh && mesh->CollideShowing(s, f, p)) return this;
    }
    return nullptr;
}

int RndText::CollidePlane(const Plane& p){
    int ret = 0;
    for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
        RndMesh* mesh = it->second.mesh;
        if(mesh){
            int meshCol = mesh->CollidePlane(p);
            if(meshCol == 0) return 0;
            if(meshCol > 0){
                if(ret < 0) return 0;
            }
            else if(ret > 0) return 0;
            ret = meshCol;
        }
    }
    return ret;
}

void RndText::Replace(Hmx::Object* from, Hmx::Object* to){
    RndTransformable::Replace(from, to);
    RndFont* target = nullptr;
    for(RndFont* font = mFont; font != nullptr; font = font->NextFont()){
        target = font;
        if(font == from){
            if(target){
                target->SetNextFont(dynamic_cast<RndFont*>(to));
            }
            else {
                mFont = dynamic_cast<RndFont*>(to);
            }
            UpdateText(true);
            return;
        }
    }
}

const char* RndText::FindPathName(){
    if(Name() && !*Name() && !Dir() && TransParent()){
        return MakeString("%s inside %s", ClassName().Str(), TransParent()->FindPathName());
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

void RndText::CollectGarbage(){
    for(std::set<RndText*>::iterator it = mTextMeshSet.begin(); it != mTextMeshSet.end(); it){
        RndText* cur = *it++;
        cur->unk124b4++;
        if(!cur->unkbp7 && cur->unk124b4 > 4){
            if(cur->mMeshMap.size() != 0){
                cur->unkbp5 = true;
                for(std::map<unsigned int, MeshInfo>::iterator mit = cur->mMeshMap.begin(); mit != cur->mMeshMap.end(); ++mit){
                    RndMesh* mesh = mit->second.mesh;
                    delete mesh;
                }
                cur->mMeshMap.clear();
            }
            mTextMeshSet.erase(it);
        }
    }
}

void RndText::UpdateText(bool b) {
    if (mDeferUpdate > 0) {
        unkbp5 = true;
    }
    else {
        for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
            RndMesh* mesh = it->second.mesh;
            delete mesh;
        }
        mMeshMap.clear();
        std::set<RndText*>::iterator it = mTextMeshSet.find(this);
        if(it != mTextMeshSet.end()){
            mTextMeshSet.erase(it);
        }
        mStyle.font = mFont;
        WrapText(mText.c_str(), mStyle, mLines);
        unkbp6 = true;
        unk130 = 0;
        for(std::vector<Line>::iterator it = mLines.begin(); it != mLines.end(); ++it){
            MaxEq(unk130, it->unk58);
        }
        unk12c = mLines.front().unk28.v.z - mLines.back().unk28.v.z;
        if(mFont){
            float diff = mFont->CellDiff();
            unk12c += mStyle.size * diff * mLeading;
        }
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
                RndMesh* mesh = it->second.mesh;
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
    mFixedLength(0), mDeferUpdate(0), unk124b4(0), unk124b4p1(0), unk128(0), unk12c(0.0f), unk130(0.0f) {
    mTextMarkup = false;
    unkbp4 = false;
    unkbp5 = false;
    unkbp6 = false;
    unkbp7 = false;
}

RndText::~RndText() {
    MILO_ASSERT(mDeferUpdate == 0, 723);
    for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
        RndMesh* mesh = it->second.mesh;
        delete mesh;
    }
    std::set<RndText*>::iterator it = mTextMeshSet.find(this);
    if(it != mTextMeshSet.end()){
        mTextMeshSet.erase(it);
    }
}

void RndText::SetFont(RndFont* f) {
    if(mFont != f){
        mFont = f;
        for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
            RELEASE(it->second.mesh);
        }
        mMeshMap.clear();
        std::set<RndText*>::iterator it = mTextMeshSet.find(this);
        if(it != mTextMeshSet.end()){
            mTextMeshSet.erase(it);
        }
        unsigned int fontasInt = (unsigned int)f;
        mMeshMap.insert(std::pair<unsigned int, MeshInfo>(fontasInt, MeshInfo()));
        mMeshMap[fontasInt].displayableChars = 0;
        mMeshMap[fontasInt].syncFlags = 0;
        UpdateText(true);
    }
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

const char* RndText::ParseMarkup(const char* cc, RndText::Style* style, float f3, float f4) const {
    bool b1 = cc[1] == '/';
    const char* ptr = cc + 1;
    if(b1) ptr++;
    if(strnicmp(ptr, "sup", 3) == 0){
        if(!b1){
            f3 *= gSuperscriptScale;
        }
        style->size = f3;
        ptr += 3;
    }
    else if(strnicmp(ptr, "gtr", 3) == 0){
        if(!b1){
            f3 *= gGuitarScale;
        }
        style->size = f3;
        style->zOffset = b1 ? f4 : gGuitarZOffset;
        ptr += 3;
    }
    else if(strnicmp(ptr, "it", 2) == 0){
        style->italics = b1 ? 0 : 0.1f;
    }
    else if(strnicmp(ptr, "pre", 3) == 0){
        style->pre = !b1;
    }
    else if(strnicmp(ptr, "color", 5) == 0){
        if(b1){
            ptr += 5;
            style->color = mStyle.color;
        }
        else {
            int colorVals[4] = {0};
            sscanf(ptr, "%d %d %d %d", colorVals[0], colorVals[1], colorVals[2], colorVals[3]);
            style->color.Set(colorVals[0] / 255.0f, colorVals[1] / 255.0f, colorVals[2] / 255.0f, colorVals[3] / 255.0f);
        }
    }
    else if(strnicmp(ptr, "nobreak", 7) == 0){
        if(b1) style->brk = mStyle.brk;
        else style->brk = false;
    }
    else if(strnicmp(ptr, "alt", 3) == 0){
        if(b1 || !unkbp5){
            style->color = mStyle.color;
            style->size = f3;
            style->font = mFont;
            style->zOffset = 0;
            style->italics = mStyle.italics;
        }
        else {
            style->color = mAltStyle.color;
            style->size = mAltStyle.size;
            style->font = mAltStyle.font;
            style->zOffset = mAltStyle.zOffset;
            style->italics = mAltStyle.italics;
        }
    }
    while(*ptr++ != '\0'){
        if(*ptr == '>') return ptr + 1;
    }
    return ptr;
}

bool canBreak(const char* cc, int i){
    if(i < 0) return false;
    if(cc[i] == ' ') return true;
    return cc[i] == '\t';
}

DECOMP_FORCEACTIVE(Text, "lineLen >= bestLineLen", "bestWp != -1", "curStyle.brk == false")

void RndText::SetText(const char* text){
    String tmp;
    tmp.reserve(mText.capacity());
    mText.swap(tmp);
    if(mFixedLength != 0){
        MILO_ASSERT(tmp.capacity() >= mFixedLength, 0x5D6);
        int len = UTF8StrLen(text);
        int textLen;
        if(len > mFixedLength){
            char* ptr = (char*)text;
            for(int i = 0; i < mFixedLength; i++){
                unsigned short us;
                ptr += DecodeUTF8(us, ptr);
            }
            textLen = ptr - text;
        }
        else textLen = strlen(text);
        if(mText.capacity() < textLen){
            mText.resize(textLen);
        }
        strncpy((char*)mText.c_str(), text, textLen);
        ((char*)mText.c_str())[textLen] = '\0';
    }
    else {
        mText = text;
    }
    if(!mText.empty()){
        if(mCapsMode == kForceLower || mCapsMode == kForceUpper){
            int i2 = 0;
            const char* casestr = "[noforcecase]";
            for(int i = 0; i < mText.length(); ){
                unsigned short us;
                unsigned int ui = DecodeUTF8(us, &mText[i]);
                if(us != (unsigned short)*casestr) break;
                if(i2 == 0xC){
                    mCapsMode = kCapsModeNone;
                    mText = mText.replace(0, 0xD, "");
                    break;
                }
                i2++;
                casestr++;
                i += ui;
            }
        }
        if(mCapsMode == kForceUpper){
            for(int i = 0; i < mText.length(); i){
                unsigned short us;
                unsigned int ui = DecodeUTF8(us, &mText[i]);
                UTF8ToUpper(us, &mText[i]);
                i += ui;
            }
            const char* search = "\xC3\x9F";
            unsigned int ui = 0;
            while(true){
                ui = mText.find(search, ui);
                if(ui == String::npos) break;
                mText.replace(ui, 2, "SS");
            }
        }
        else if(mCapsMode == kForceLower){
            for(int i = 0; i < mText.length(); ){
                unsigned short us;
                unsigned int len = DecodeUTF8(us, &mText[i]);
                UTF8ToLower(us, &mText[i]);
                i += len;
            }
        }
    }
    if(mText != tmp){
        UpdateText(true);
    }
}

float RndText::GetStringWidthUTF8(const char* cc1, const char* cc2, bool bbb, RndText::Style* style) const {
    unsigned short us8 = 0;
    float ret = 0;
    if(!cc2){
        cc2 = cc1 + strlen(cc1);
    }
    if(!style){
        Style myStyle = mStyle;
        style = &myStyle;
    }
    if(!style->font){
        style->font = mFont;
    }
    float size = style->size;
    float zoff = style->zOffset;
    const char* ccIt = cc1;
    while(ccIt != cc2){
        if(ccIt > cc2){
            MILO_WARN("bad utf8 string in RndText::GetStringWidth \"%s\"", cc1);
            ccIt = cc2;
            break;
        }
        unsigned short us;
        int decoded = DecodeUTF8(us, ccIt);
        if(us == 0x3C && mTextMarkup){
            ccIt = ParseMarkup(ccIt, style, size, zoff);
        }
        else {
            RndFont* font = GetDefiningFont(us, style->font);
            if(font){
                ret += style->size * font->CharAdvance(us8, us);
            }
            us8 = us;
            ccIt += decoded;
        }
    }
    if(bbb){
        unsigned short us;
        DecodeUTF8(us, ccIt);
        RndFont* font = GetDefiningFont(us, style->font);
        if(font){
            ret += style->size * font->Kerning(us8, us);
        }
    }
    return ret;
}

void RndText::ResetFaces(RndMesh* mesh, int new_size){
    MILO_ASSERT(mesh, 0x689);
    mesh->Faces().resize(new_size);
    std::vector<RndMesh::Face>::iterator it = mesh->Faces().begin();
    std::vector<RndMesh::Face>::iterator itEnd = mesh->Faces().end();
    int num = 0;
    for(; it != itEnd; it += 2, num += 4){
        RndMesh::Face* face = it;
        face->Set(num, num+1, num+2);
        face[1].Set(num, num+2, num+3);
    }
}

void RndText::UpdateMesh(RndFont* font){
    unsigned int fontAsInt = (unsigned int)font;
    MeshInfo* meshInfo = &mMeshMap[fontAsInt];
    RndMesh* mesh = meshInfo->mesh;
    MILO_ASSERT(mesh, 0x6A6);
    if(!font){
        mesh->SetShowing(false);
        return;
    }
    mesh->SetShowing(true);
    int i8 = 0x1F;
    if(mFixedLength == 0){
        int i1 = meshInfo->displayableChars * 2;
        ResetFaces(mesh, i1);
        i8 |= 0xA0;
        mesh->Verts().resize(i1 * 2, true);
    }
    else if(!(mesh->GetMutable() & 0x1F) || mFixedLength * 4 != mesh->Verts().size()){
        mesh->SetMutable(0x1F);
        ResetFaces(mesh, mFixedLength * 2);
        i8 |= 0xA0;
        mesh->Verts().resize(mFixedLength * 4, true);
    }
    int len = mFixedLength;
    if(len && meshInfo->displayableChars > len){
        ResizeText(len * 2 - meshInfo->displayableChars);
        meshInfo->displayableChars = mFixedLength;
    }
    MILO_ASSERT(mesh->Verts().size() >= meshInfo->displayableChars * 4, 0x6CF);
    mesh->SetMat(font->GetMat());
    CreateLines(font);
//   if (piVar7 != 0x0) {
//     (**(*piVar7 + 0xc))(piVar7,this_00);
//   }
    mesh->Sync(i8);
    meshInfo->syncFlags = 0;
}

void SetupCharVerts(unsigned short us1, RndMesh::Vert*& vert, float& fref, float f4, float f5, float f6, float f7, const RndText::Style& style, RndFont* font, unsigned short us10, bool b11){
    if(!b11){
        fref += style.size * font->Kerning(us10, us1);
    }
    float f1 = style.size * font->CharWidth(us1);
    if(f1 <= 0){
        f1 = style.size * font->CharAdvance(us1);
    }
    if(f1 <= 0) return;
    else {
        font->GetTexCoords(us1, vert[0].uv, vert[2].uv);
        vert[1].uv.Set(vert[0].uv.x, vert[2].uv.y);
        vert[3].uv.Set(vert[2].uv.x, vert[0].uv.y);
        vert[0].pos.Set(fref + f7, f4, f5);
        vert[1].pos.Set(fref - f7, f4, f5 - f6);
        vert[2].pos.Set(f1 + (fref - f7), f4, f5 - f6);
        vert[3].pos.Set(f1 + fref + f7, f4, f5);
        vert[0].norm.Set(0, -1, 0);
        vert[1].norm = vert[2].norm = vert[3].norm = vert[0].norm;
        vert[0].color = vert[1].color = vert[2].color = vert[3].color = style.color;
        vert += 4;
        if(!b11){
            fref += style.size * font->CharAdvance(us1);
        }
    }
}

void RndText::CreateLines(RndFont* font){
    RndMesh* mesh = mMeshMap[(unsigned int)font].mesh;
    MILO_ASSERT(mesh, 0x709);
    RndMesh::Vert* vertIt = mesh->Verts().begin();
    Style style = mLines[0].lineStyle;
    float f4 = style.italics * style.size;
    font->CellDiff();
    float f1 = mStyle.size;
    float f2 = mStyle.zOffset;
    for(int i = 0; i < mLines.size(); i++){
        Line& curLine = mLines[i];
        RndMesh::Vert* vert = vertIt;
        float f3 = curLine.unk28.v.z;
        float f90 = curLine.unk28.v.x;
        const char* cc13 = curLine.unk18;
        unsigned short i14 = 0;
        while(cc13 != curLine.unk1c){
            unsigned short us98;
            unsigned int ui = DecodeUTF8(us98, cc13);
            if(us98 == 0x3C && mTextMarkup){
                cc13 = ParseMarkup(cc13, &style, f1, f2);
                f4 = style.italics * style.size;
            }
            else {
                RndFont* definingFont = GetDefiningFont(us98, style.font);
                if(definingFont){
                    if(font == definingFont){
                        SetupCharVerts(us98, vertIt, f90, curLine.unk28.v.y, f3 + style.zOffset, style.size * definingFont->CellDiff(), f4, style, definingFont, i14, false);
                    }
                    else {
                        f90 += style.size * definingFont->CharAdvance(i14, us98);
                    }
                }
                i14 = us98;
                cc13 += ui;
            }
        }
        RotateLineVerts(curLine, vert, vertIt);
    }
    while(vertIt != mesh->Verts().end()){
        vertIt++->pos.Set(0, 0, 0);
    }
}

int RndText::NumCharsInBytes(const String& str, const RndText::Style& style, float& fref, int i4){
    int len = strlen(str.c_str());
    str.c_str();
    int i5 = 0;
    float f8 = 0;
    int s4 = 0;
    while(s4 < len){
        unsigned short us;
        int decoded = DecodeUTF8(us, str.c_str() + s4);
        if(i4 > -1 && i4 < s4 + decoded) break;
        RndFont* support = SupportChar(us, mFont);
        if((us == 0x20 || us == 9 || us == 10) && len > 0){
            i5++;
            if(support){
                f8 += style.size * support->CharAdvance(us);
            }
        }
        else {
            i5 = 0;
            f8 = 0;
        }
    }
    fref += f8;
    return s4 - i5;
}

void RndText::ApplyLineText(const String& utf8, const RndText::Style& style, float& fref, RndText::Line& line, int i5, int i6, bool* b7){
    if(!mMeshMap.empty()){
        if(mText.length() < line.endIdx){
            mText.resize(line.endIdx);
        }
        MILO_ASSERT((line.startIdx + utf8.length()) <= mFixedLength, 0x791);
        const char* theStrstr = utf8.c_str();
        const char* ptr = theStrstr;
        for(int i = 0; i < i5; i++){
            char ptrChar = *ptr;
            mText[line.startIdx + i] = ptrChar;
            ptr++;
        }
        for(int i = i5; i < i6; i++){
            mText[line.startIdx + i] = 0x20;
        }
        float f28 = 0;
        unsigned short i23 = 0;
        int i7 = 0;
        RndFont* key = (RndFont*)mMeshMap.begin()->first;
        Style localStyle(style);
        while(*theStrstr != '\0'){
            while((*theStrstr == '<' && mTextMarkup)){
                theStrstr = ParseMarkup(theStrstr, &localStyle, style.size, style.zOffset);
            }
            if(*theStrstr != '\0'){
                unsigned short use6;
                int decoded = DecodeUTF8(use6, theStrstr);
                if(i7 < i6){
                    RndFont* defining = GetDefiningFont(use6, key);
                    if(defining){
                        f28 += localStyle.size * defining->CharAdvance(use6) + localStyle.size * defining->Kerning(i23, use6);
                    }
                    i7++;
                    i23 = use6;
                }
                theStrstr += decoded;
            }
        }
        line.unk58 = f28;

        float f3 = line.unk28.v.x;
        float f4 = line.unk28.v.y;
        Alignment align = GetAlignment();
        float f26 = GetHorizontalAlignOffset(line, align);
        i7 = 0;
        i23 = 0;
        for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
            Style mapStyle(style);
            RndFont* curFontKey = (RndFont*)it->first;
            MeshInfo& meshInfo = it->second;
            RndMesh* curMesh = meshInfo.mesh;
            int uvar8 = 0;
            float fd4 = f3 + f26;
            if(curMesh){
                if(!(curMesh->GetMutable() & 0x1F) || mFixedLength * 4 != curMesh->Verts().size()){
                    curMesh->SetMutable(0x1F);
                    ResetFaces(curMesh, mFixedLength * 2);
                    curMesh->Verts().resize(mFixedLength * 4, true);
                    uvar8 |= 0xBF;
                }
                curMesh->SetMat(curFontKey->GetMat());
            }
            RndMesh::Vert* theVert = curMesh->Verts().begin() + line.startIdx * 0xD0;
            RndMesh::Vert* vertd8 = theVert;
            const char* curStrStr = utf8.c_str();
            while(*curStrStr != '\0'){
                while(*curStrStr == '<' && mTextMarkup){
                    curStrStr = ParseMarkup(curStrStr, &mapStyle, style.size, style.zOffset);
                }
                if(*curStrStr != '\0'){
                    float f6 = mapStyle.italics * mapStyle.size;
                    unsigned short use8;
                    int decoded = DecodeUTF8(use8, curStrStr);
                    if(i7 < i6){
                        RndFont* defining = GetDefiningFont(use8, curFontKey);
                        if(defining){
                            if(defining == curFontKey){
                                defining->Kerning(i23, use8);
                                defining->CharAdvance(use8);
                                float diff = defining->CellDiff();
                                float f5 = line.unk28.v.z;
                                float f1 = mapStyle.size * diff;
                                if(mAlign & 0x20){
                                    f5 += f1 / 2.0f;
                                }
                                else if(mAlign & 0x40){
                                    f5 += f1;
                                }
                                SetupCharVerts(use8, theVert, fd4, f4, f5 + mapStyle.zOffset, f1, f6, mapStyle, defining, i23, false);
                                uvar8 |= 0x1F;
                            }
                            else {
                                fd4 += style.size * defining->Kerning(i23, use8);
                                fd4 += style.size * defining->CharAdvance(use8);
                            }
                            uvar8 |= 0x1F;
                        }
                        i7++;
                        i23 = use8;
                    }
                    curStrStr += decoded;
                }
            }
            RotateLineVerts(line, theVert, vertd8);
            meshInfo.syncFlags |= uvar8;
        }
        if(b7) *b7 = true;
        else SyncMeshes();
        fref += f28;
    }
}

int RndText::AddLineUTF8(const String& utf8, const Transform& tf, const RndText::Style& style, float* fp, bool* bp, int i6){
    unkbp7 = true;
    float f98 = 0;
    if(!fp) fp = &f98;

    if(utf8.length() + mText.length() > mFixedLength){
        MILO_WARN("Text %s%s exceeds fixed length of %d, truncating", utf8.c_str(), mText.c_str(), mFixedLength);
        return -1;
    }
    else {
        int newCharsInBytes = NumCharsInBytes(utf8, style, *fp, i6);
        if(newCharsInBytes != 0 || i6 != 0){
            MILO_ASSERT(newCharsInBytes <= utf8.length(), 0x850);
            int lineIdx;
            for(lineIdx = mLines.size(); lineIdx > 0 && (mLines[lineIdx - 1].endIdx && mLines[lineIdx - 1].startIdx == mLines[lineIdx - 1].endIdx); lineIdx--);
            if(lineIdx == mLines.size()){
                if(mLines.size() == mLines.capacity()){
                    MILO_WARN("RndText::AddLineUTF8() - reserve_lines %d is too low; reallocating", mLines.capacity());
                }
                Line linetopush;
                mLines.push_back(linetopush);
            }
            Line& line = mLines[lineIdx];
            line.unk28 = tf;
            line.lineStyle = style;
            line.startIdx = 0;
            if(lineIdx != 0){
                line.startIdx = mLines[lineIdx - 1].endIdx;
            }
            if(i6 > -1){
                line.endIdx = line.startIdx + i6;
            }
            else {
                line.endIdx = line.startIdx + newCharsInBytes;
                i6 = newCharsInBytes;
            }
            MILO_ASSERT(line.endIdx <= mFixedLength, 0x874);
            line.unk18 = mText.c_str() + line.startIdx;
            line.unk1c = mText.c_str() + line.endIdx;
            ApplyLineText(utf8, style, *fp, line, newCharsInBytes, i6, bp);
            return lineIdx;
        }
        else return -1;
    }
}

void RndText::UpdateLineColor(unsigned int idx, const Hmx::Color32& col, bool* bptr){
    MILO_ASSERT(idx < mLines.size(), 0x883);
    Line& curLine = mLines[idx];
    MILO_ASSERT(mMeshMap.size() < 10, 0x887);
    if(curLine.color == col) return;
    curLine.color = col;
    int mapInts[10];
    std::map<unsigned int, MeshInfo>::iterator it;
    for(int i = 0; i < mMeshMap.size(); i++){
        mapInts[i] = 0;
    }
    
    it = mMeshMap.begin();
    for(int i = 0; i < mMeshMap.size(); i++){
        RndFont* curFont = (RndFont*)it->first;
        for(int j = 0; j < curLine.startIdx; ){
            unsigned short us86;
            int decoded = DecodeUTF8(us86, mText.c_str() + j);
            if(GetDefiningFont(us86, curLine.lineStyle.font) == curFont){
                mapInts[i]++;
            }
            j += decoded;
        }
        ++it;
    }

    it = mMeshMap.begin();
    for(int i = 0; i < mMeshMap.size(); i++){
        RndFont* curFont = (RndFont*)it->first;
        int idx = curLine.startIdx;
        int min = std::min(curLine.endIdx, (int)mFixedLength);
        int i11 = mapInts[i] * 4;
        for(; idx < min; ){
            unsigned short us88;
            int decoded = DecodeUTF8(us88, mText.c_str() + idx);
            RndFont* defining = GetDefiningFont(us88, curLine.lineStyle.font);
            if(defining == curFont){
                unsigned int definingFontAsInt = (unsigned int)defining;
                MeshInfo& curMeshInfo = mMeshMap[definingFontAsInt];
                RndMesh::Vert* vert10 = curMeshInfo.mesh->Verts().begin() + i11;
                vert10->color = col;
                i11 += 4;
                curMeshInfo.syncFlags |= 0x1F;
            }
            idx += decoded;
        }
        ++it;
    }

    curLine.lineStyle.color = col;
    if(bptr) *bptr = true;
    else SyncMeshes();
}

void RndText::SyncMeshes(){
    for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
        MeshInfo& info = it->second;
        if(info.syncFlags){
            info.mesh->Sync(info.syncFlags);
            info.syncFlags = 0;
        }
    }
}

void RndText::SetMeshForceNoQuantize(){
    for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
        MeshInfo& info = it->second;
        if(info.syncFlags){
            info.mesh->SetForceNoQuantize(true);
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

void RndText::GetVerticalBounds(float& f1, float& f2) const {
    if(!mFont){
        f1 = 0;
        f2 = 0;
    }
    else {
        f1 = mLines.front().unk28.v.z;
        f2 = -(mLeading * mStyle.size - mLines.back().unk28.v.z);
    }
}

float RndText::MaxLineWidth() const {
    float width = 0;
    for(int i = 0; i < mLines.size(); i++){
        MaxEq(width, mLines[i].unk58);
    }
    return width;
}

void RndText::GetMeshes(std::vector<RndMesh*>& meshes){
    meshes.clear();
    for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
        meshes.push_back(it->second.mesh);
    }
}

void RndText::GetStringDimensions(float& f1, float& f2, std::vector<Line>& lines, const char* cc, float size){
    lines.clear();
    Style theStyle = mStyle;
    theStyle.size = size;
    theStyle.font = mFont;
    WrapText(cc, theStyle, lines);
    f1 = 0;
    for(std::vector<Line>::iterator it = lines.begin(); it != lines.end(); ++it){
        MaxEq(f1, (*it).unk58);
    }
    f2 = lines.front().unk28.v.z - lines.back().unk28.v.z;
    if(mFont){
        float diff = mFont->CellDiff();
        f2 += theStyle.size * diff * mLeading;
    }
}

void RndText::GetCurrentStringDimensions(float& f1, float& f2){
    f1 = unk130;
    f2 = unk12c;
}

void RndText::Draw(){
    RndDrawable::Draw();
    if(!mShowing && !unkbp7){
        if(mMeshMap.size() != 0){
            unkbp5 = true;
            for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
                RndMesh* mesh = it->second.mesh;
                delete mesh;
            }
            mMeshMap.clear();
            std::set<RndText*>::iterator it = mTextMeshSet.find(this);
            if(it != mTextMeshSet.end()){
                mTextMeshSet.erase(it);
            }
        }
    }
}

void RndText::DrawShowing(){
    unk124b4 = 0;
    if(unkbp5){
        unkbp5 = false;
        UpdateText(true);
    }
    if(unkbp6){
        mTextMeshSet.insert(this);
        unkbp6 = false;
        for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
            if(it->second.mesh){
                UpdateMesh((RndFont*)it->first);
            }
        }
    }
    for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
        MeshInfo& meshInfo = it->second;
        if(meshInfo.mesh){
            meshInfo.mesh->DrawShowing();
        }
    }
}

float RndText::GetDistanceToPlane(const Plane& p, Vector3& v){
    if(mMeshMap.empty()) return 0;
    else {
        float ret = 0;
        for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
            RndMesh* mesh = it->second.mesh;
            if(mesh){
                Vector3 vec;
                ret = mesh->GetDistanceToPlane(p, vec);
                v = vec;
            }
        }
        return ret;
    }
}

bool RndText::MakeWorldSphere(Sphere& s, bool b){
    s.Zero();
    for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
        RndMesh* mesh = it->second.mesh;
        if(mesh){
            Sphere localS;
            if(b){
                mesh->MakeWorldSphere(localS, true);
            }
            else if(mSphere.GetRadius()){
                Multiply(mSphere, WorldXfm(), localS);
            }
            s.GrowToContain(localS);
        }
    }
    return s.GetRadius();
}

void RndText::UpdateSphere(){
    Sphere s;
    s.Zero();
    for(std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.begin(); it != mMeshMap.end(); ++it){
        RndMesh* mesh = it->second.mesh;
        if(mesh){
            mesh->UpdateSphere();
            s.GrowToContain(mesh->mSphere);
        }
    }
    SetSphere(s);
}

RndFont* RndText::SupportChar(unsigned short us, RndFont* font){
    RndFont* defining = GetDefiningFont(us, font);
    if(defining){
        std::map<unsigned int, MeshInfo>::iterator it = mMeshMap.find((unsigned int)defining);
        if(it == mMeshMap.end()){
            mMeshMap.insert(std::pair<unsigned int, MeshInfo>((unsigned int)defining, MeshInfo()));
            // set the iterator to the newly inserted pair here
        }
        MeshInfo& meshInfo = it->second;
        if(!meshInfo.mesh){
            meshInfo.mesh = Hmx::Object::New<RndMesh>();
            meshInfo.mesh->SetTransParent(this, false);
            meshInfo.mesh->SetTransConstraint((Constraint)2, nullptr, false);
            meshInfo.syncFlags = 0;
            meshInfo.displayableChars = 0;
        }
    }
    return defining;
}

RndFont* RndText::GetDefiningFont(unsigned short& us, RndFont* font) const {
    if(us != 10){
        for(RndFont* it = font; it != nullptr; it = it->NextFont()){
            if(it->CharDefined(us)){
                return it;
            }
        }
    }
    return nullptr;
}

void RndText::ResizeText(int size){
    int len = UTF8StrLen(mText.c_str());
    if(len > size){
        char* ptr = &mText[0];
        for(int i = 0; i < size; i++){
            unsigned short us;
            ptr += DecodeUTF8(us, ptr);
        }
        mText.resize(ptr - &mText[0]);
    }
    else if(len == 0){
        mText.resize(size);
    }
    else {
        mText.resize((size - len) + strlen(mText.c_str()));
    }
}

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

float RndText::GetHorizontalAlignOffset(const Line& line, Alignment align) const {
    float ret = 0;
    if(align & 2){
        return -(line.unk58 / 2.0f - ret);
    }
    if(!(align & 4)) return ret;
    return ret - line.unk58;
}

void RndText::RotateLineVerts(const RndText::Line& line, RndMesh::Vert* vert1, RndMesh::Vert* vert2){
    if(unk124b4p1){
        const Transform& linexfm = line.unk28;
        Transform tf48;
        Invert(linexfm, tf48);
        for(RndMesh::Vert* it = vert1; it != vert2; ++it){
            Vector3 v58(it->pos.x, it->pos.y, it->pos.z);
            Multiply(v58, tf48, v58);
            Multiply(v58, linexfm.m, v58);
            Multiply(v58, linexfm, v58);
            it->pos.x = v58.x;
            it->pos.y = v58.y;
            it->pos.z = v58.z;
        }
    }
}

BEGIN_HANDLERS(RndText)
    HANDLE(set_fixed_length, OnSetFixedLength)
    HANDLE(set_font, OnSetFont)
    HANDLE(set_align, OnSetAlign)
    HANDLE(set_text, OnSetText)
    HANDLE(set_size, OnSetSize)
    HANDLE(set_wrap_width, OnSetWrapWidth)
    HANDLE(set_color, OnSetColor)
    HANDLE_EXPR(get_text_size, Max<int>(mFixedLength, (int)mText.length()))
    HANDLE_EXPR(get_string_width, GetStringWidthUTF8(_msg->Str(2), NULL, false, NULL))

    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(2789)
END_HANDLERS

DataNode RndText::OnSetFixedLength(DataArray* da){
    SetFixedLength(da->Int(2));
    return 0;
}

DataNode RndText::OnSetFont(DataArray* da){
    SetFont(da->Obj<RndFont>(2));
    return 0;
}

DataNode RndText::OnSetAlign(DataArray* da){
    SetAlignment((Alignment)da->Int(2));
    return 0;
}

DataNode RndText::OnSetText(DataArray* da){
    SetText(da->Str(2));
    return 0;
}

DataNode RndText::OnSetWrapWidth(DataArray* da){
    SetWrapWidth(da->Float(2));
    return 0;
}

DataNode RndText::OnSetSize(DataArray* da){
    SetSize(da->Float(2));
    return 0;
}

DataNode RndText::OnSetColor(DataArray* da){
    SetColor(Hmx::Color32(da->Float(2), da->Float(3), da->Float(4), da->Float(5)));
    return 0;
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