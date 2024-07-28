#include "rndobj/Font.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "rndobj/Mat.h"
#include "math/Rot.h"
#include "types.h"
#include "utl/BinStream.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"
#include <map>

INIT_REVS(RndFont)

BinStream& operator>>(BinStream& bs, RndFont::KernInfo& ki) {
    if (RndFont::gRev < 17) {
        char x; bs >> x; ki.unk0 = x;
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

void RndFont::GetTexCoords(unsigned short us, Vector2& tl, Vector2& br) const {
    if (mTextureOwner != this) {
        mTextureOwner->GetTexCoords(us, tl, br); 
    } else {
        char c;
        MILO_ASSERT(HasChar(c), 290);
        float* r4; // TODO i have no damn clue what class this is. matchar???   
        tl.x = r4[5];
        br.x = (r4[7] * unk6c.x) + r4[5];
        tl.y = r4[6];
        br.y = r4[6] + unk6c.y;
    }
}

void RndFont::SetCellSize(float x, float y) {
    mCellSize.x = x; mCellSize.y = y;
    UpdateChars();
}

RndTex* RndFont::ValidTexture() const {
    if (mMat != NULL) return mMat->mDiffuseTex;
    else return NULL;
}

void RndFont::SetBitmapSize(const Vector2& cs, unsigned int i1, unsigned int i2) {
    mCellSize = cs;
    unk6c.x = cs.x / i1;
    unk6c.y = cs.y / i2;
}

void RndFont::UpdateChars() {
    if (mPacked) {
        RndTex* t = ValidTexture();
        if (t) SetBitmapSize(mCellSize, t->Width(), t->Height());
    } else {
        if (mChars.size() != 0 && mChars[0] == 160) {
            MILO_WARN("%s: first character is ascii 160, converting to the space character.\n", Name());
            mChars[0] = L' ';
        }
        unk34.clear();
        BitmapLocker l(this);
    }
}

BinStream& operator>>(BinStream& bs, MatChar& mc) {
    char x[0x80]; bs.ReadString(x, 0x80);
    bs >> mc.width; bs >> mc.height;
    return bs;
}

SAVE_OBJ(RndFont, 695)

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

RndFont::RndFont() : mMat(this, 0), mTextureOwner(this, this), unk4c(0), mBaseKerning(0.0f), mCellSize(1.0f, 1.0f), mDeprecatedSize(0.0f), mMonospace(0), unk6c(0.0f, 0.0f), mPacked(0), unk78(this, 0) {

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
    HANDLE_EXPR(mat, mMat)
    HANDLE_EXPR(texture_owner, mTextureOwner)
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
