#include "rndobj/Font.h"
#include "decomp.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "rndobj/Bitmap.h"
#include "rndobj/Mat.h"
#include "math/Rot.h"
#include "types.h"
#include "utl/BinStream.h"
#include "utl/MakeString.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"
#include <map>

INIT_REVS(RndFont)

BinStream& operator>>(BinStream& bs, RndFont::KernInfo& ki) {
    if (RndFont::gRev < 17) {
        char x;
        bs >> x; ki.unk0 = x;
        bs >> x; ki.unk2 = x;
    } else {
        bs >> ki.unk0;
        bs >> ki.unk2;
    }
    if (RndFont::gRev < 6) {
        u8 x; bs >> x; bs >> x;
    }
    bs >> ki.unk4;
    return bs;
}

int NonTransparentColumn(RndBitmap& bmp, int min, int max, int i3, int i4 ) {
    int asdf, i = min;
    while (i != max) {
        u8 isntTrans = bmp.ColumnNonTransparent(i, i3, i4, &asdf);
        if (isntTrans) return i;
        int t;
        t = i - 1; if (max > min) t = i + 1;
        i = t; // probably wrong!
    }
    return i;
}

void RndFont::GetTexCoords(unsigned short c, Vector2& tl, Vector2& br) const {
    if (mTextureOwner != this) {
        mTextureOwner->GetTexCoords(c, tl, br);
    } else {
        MILO_ASSERT(HasChar(c), 290);
        std::map<unsigned short, CharInfo>::const_iterator it = unk34.find(c);
        const CharInfo& info = it->second;
        tl.x = info.unk0;
        br.x = info.charWidth * unk6c.x + info.unk0;
        tl.y = info.unk4;
        br.y = info.unk4 + unk6c.y;
    }
}

float RndFont::CharWidth(unsigned short c) const {
    MILO_ASSERT(HasChar(c), 0x12E);
    CharInfo& info = mTextureOwner->unk34[c];
    float w = info.charWidth;
    MILO_ASSERT(w >= 0, 0x131);
    return w;
}

float RndFont::CharAdvance(unsigned short c) const {
    MILO_ASSERT(HasChar(c), 0x137);
    if(IsMonospace()) return 1.0f;
    else {
        CharInfo& info = mTextureOwner->unk34[c];
        return info.unkc;
    }
}

void RndFont::SetBaseKerning(float k){ mBaseKerning = k; }

void RndFont::SetCellSize(float x, float y) {
    mCellSize.Set(x, y);
    UpdateChars();
}

void RndFont::SetCharInfo(RndFont::CharInfo* info, RndBitmap& bmap, const Vector2& vec2){
    if(mMonospace){
        info->unk0 = vec2.x / (float)bmap.Width();
        info->charWidth = 1.0f;
        info->unkc = 1.0f;
    }
    else {
        int i5 = vec2.x;
        int i1 = vec2.y;
        int i2 = vec2.x + mCellSize.x;
        int i3 = vec2.y + mCellSize.y;
        float i6 = NonTransparentColumn(bmap, i5, i2, i1, i3);
        float i7 = NonTransparentColumn(bmap, i2 - 1, i5 - 1, i1, i3);
        float f4 = (i7 + 1.0f) - i6;
        if(f4 <= 0){
            int w = bmap.Width();
            info->unk0 = vec2.x / w;
            info->charWidth = 0.25f;
            info->unkc = 0.25f;
        }
        else {
            info->unk0 = i6 / bmap.Width();
            f4 = f4 / mCellSize.x;
            info->charWidth = f4;
            info->unkc = f4;
        }
    }
    info->unk4 = vec2.y / bmap.Height();
    MILO_ASSERT(info->charWidth >= 0, 0x168);
}

float RndFont::Kerning(unsigned short, unsigned short) const {

}

float RndFont::CharAdvance(unsigned short us1, unsigned short us2) const {
    return Kerning(us1, us2) + CharAdvance(us2);
}

bool RndFont::CharDefined(unsigned short c) const {
    if(HasChar(c)){
        std::map<unsigned short, CharInfo>::const_iterator it = unk34.find(c);
        const CharInfo& info = it->second;
        return info.unk0 != 0 || info.unk4 != 0 || info.unkc != 0;
    }
    else return false;
}

RndTex* RndFont::ValidTexture() const {
    if (mMat != NULL) return mMat->GetDiffuseTex();
    else return NULL;
}

void RndFont::SetBitmapSize(const Vector2& cs, unsigned int i1, unsigned int i2) {
    mCellSize = cs;
    unk6c.x = mCellSize.x / i1;
    unk6c.y = mCellSize.y / i2;
}

void RndFont::UpdateChars() {
    if (IsPacked()) {
        RndTex* t = ValidTexture();
        if (t) SetBitmapSize(mCellSize, t->Width(), t->Height());
    }
    else {
        if (!mChars.empty() && mChars[0] == 160) {
            MILO_WARN("%s: first character is ascii 160, converting to the space character.\n", Name());
            unsigned short& firstChar = mChars[0];
            firstChar = ' ';
        }
        unk34.clear();
        BitmapLocker l(this);
        RndBitmap* lockedBmap = l.PtrToBitmap();
        if(lockedBmap){
            unk6c.x = mCellSize.x / lockedBmap->Width();
            unk6c.y = mCellSize.y / lockedBmap->Height();
            Vector2 v80(0,0);
            for(int i = 0; i < mChars.size(); i++){
                unsigned short curChar = mChars[i];
                if(v80.x + mCellSize.x > lockedBmap->Width()){
                    v80.x = 0;
                    v80.y += mCellSize.y;
                }
                if(v80.y + mCellSize.y > lockedBmap->Height()){
                    MILO_WARN("%s: too many characters for bitmap, truncating.\n", Name());
                    mChars.resize(i);
                    break;
                }
                SetCharInfo(&unk34[curChar], *lockedBmap, v80);
                v80.x += mCellSize.x;
                if(curChar == 0x20){
                    unk34[curChar].charWidth = 0;
                }
                else if(curChar == 9){
                    MILO_ASSERT(HasChar(L' ' ), 0x205);
                    unk34[curChar] = unk34[0x20];
                    unk34[curChar].unkc *= 3.0f;
                }
            }
        }
    }
}

void RndFont::BleedTest(){
    BitmapLocker locker(this);
    RndBitmap* bmap = locker.PtrToBitmap();
    if(bmap){
        bool haswrap = mMat->GetTexWrap() == kClamp;
        String errStr;
        for(int i = 0; i < mChars.size(); i++){
            unsigned short curChar = mChars[i];
            CharInfo& curInfo = unk34[curChar];
            int i2 = Round(curInfo.unk4 * bmap->Height());
            int i5 = Round(curInfo.unk0 * bmap->Width());
            int i6 = Round(curInfo.charWidth * mCellSize.x) + i5;
            int iptr;
            if((i2 != 0) || !haswrap){
                unsigned char row = bmap->RowNonTransparent(i5, i6, i2, &iptr);
                if(row){
                    errStr += MakeString("Top bleeding in 0x%04x, alpha %d, pixel %d,%d\n", curChar, row, iptr, i2);
                }
            }
            i2 += (int)mCellSize.y - 1;
            if(!haswrap && i2 >= bmap->Height() - 1){
                unsigned char row = bmap->RowNonTransparent(i5, i6, i2, &iptr);
                if(row){
                    errStr += MakeString("Bottom bleeding in 0x%04x, alpha %d, pixel %d,%d\n", curChar, row, iptr, i2);
                }
            }
            i2 = Round(curInfo.unk4 * bmap->Height());
            int ia0 = i5 - 1;
            if(i5 != 0 || (!haswrap && ia0 <= 0)){
                MaxEq(ia0, 0);
                unsigned char row = bmap->ColumnNonTransparent(ia0, i2, i2 + (int)mCellSize.y, &iptr);
                if(row){
                    errStr += MakeString("Left bleeding in 0x%04x, alpha %d, pixel %d,%d\n", curChar, row, ia0, iptr);
                }
            }

            ia0 = i6;
            if(!haswrap && ia0 >= bmap->Width() - 1){
                MinEq(ia0, bmap->Width() - 1);
                unsigned char row = bmap->ColumnNonTransparent(ia0, i2, i2 + (int)mCellSize.y, &iptr);
                if(row){
                    errStr += MakeString("Right bleeding in 0x%04x, alpha %d, pixel %d,%d\n", curChar, row, ia0, iptr);
                }
            }
        }
        if(errStr.length() != 0){
            MILO_WARN("Bleeding in %s:\n\n%s", Name(), errStr);
        }
        else MILO_WARN("No bleeding over found.  \n");
    }
}

void RndFont::GetKerning(std::vector<KernInfo>& info) const {
    if(mKerningTable) mKerningTable->GetKerning(info);
    else info.clear();
    return;
    if(!mKerningTable) info.clear();
    else mKerningTable->GetKerning(info);
}

void RndFont::SetKerning(const std::vector<KernInfo>& info){
    if(info.empty()){
        RELEASE(mKerningTable);
    }
    else {
        if(!mKerningTable){
            mKerningTable = new KerningTable();
        }
        mKerningTable->SetKerning(info, this);        
    }
}

BinStream& operator>>(BinStream& bs, MatChar& mc) {
    char x[0x80]; bs.ReadString(x, 0x80);
    bs >> mc.width; bs >> mc.height;
    return bs;
}

SAVE_OBJ(RndFont, 695)

DECOMP_FORCEACTIVE(Font, "ObjPtr_p.h", "f.Owner()", "")

BEGIN_LOADS(RndFont)
    LOAD_REVS(bs)
    if (gRev < 7) Hmx::Object::Load(bs);

    if (gRev < 3) {
        String s;
        int a,b,c,d;
        char x;
        bs >> a; bs >> b; bs >> c; bs >> x; bs >> d;
        bs >> s;
    }

    if (gRev < 1) {
        std::map<char, MatChar> x;
        bs >> x;
    } else {
        bs >> mMat;
    }
END_LOADS

BEGIN_COPYS(RndFont)
    CREATE_COPY_AS(RndFont, f)
    MILO_ASSERT(f, 996);
    COPY_SUPERCLASS_FROM(Hmx::Object, f)
END_COPYS

void RndFont::Print() {
    TextStream& ts = TheDebug;
    ts << "   mat: " << mMat << "\n";
    ts << "   cellSize: " << mCellSize << "\n";
    ts << "   deprecated size: " << mDeprecatedSize << "\n";
    ts << "   space: " << mBaseKerning   << "\n";

    ts << "\n";
    ts << "   kerning: TODO\n";
}

RndFont::RndFont() : mMat(this), mTextureOwner(this, this), mKerningTable(0), mBaseKerning(0.0f), mCellSize(1.0f, 1.0f),
    mDeprecatedSize(0.0f), mMonospace(0), unk6c(0.0f, 0.0f), mPacked(0), unk78(this) {

}

void RndFont::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mTextureOwner == from){
        if(!to) mTextureOwner = this;
        else {
            mTextureOwner = dynamic_cast<RndFont*>(to)->mTextureOwner;
        }
    }
}

RndFont::~RndFont(){

}

BEGIN_HANDLERS(RndFont)
    HANDLE_EXPR(mat, GetMat())
    HANDLE_EXPR(texture_owner, mTextureOwner.Ptr())
    HANDLE_ACTION(bleed_test, BleedTest())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(1224)
END_HANDLERS

BEGIN_PROPSYNCS(RndFont)
    SYNC_PROP_MODIFY_ALT(texture_owner, mTextureOwner, UpdateChars())
    SYNC_PROP_MODIFY_ALT(mat, mMat, UpdateChars())
    SYNC_PROP_MODIFY_ALT(monospace, mMonospace, UpdateChars())
    SYNC_PROP_MODIFY_ALT(packed, mPacked, UpdateChars())

    SYNC_PROP_MODIFY_ALT(base_kerning, mBaseKerning     , UpdateChars())
END_PROPSYNCS
