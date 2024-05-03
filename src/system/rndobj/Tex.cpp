#include "rndobj/Tex.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/File.h"
#include "utl/BinStream.h"
#include "utl/Symbols.h"
#include "os/System.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

INIT_REVS(RndTex)

bool UseBottomMip() {
    DataArray* found = SystemConfig("rnd")->FindArray("use_bottom_mip", false);
    return found ? (found->Int(1) != 0) : false;
}

void CopyBottomMip(RndBitmap& dst, const RndBitmap& src) {
    MILO_ASSERT(&src != &dst, 48);
    const RndBitmap* dingus;
    while (dingus->mMip) dingus = dingus->mMip;
    dst.Create(src, dingus->mBpp, dingus->mOrder, NULL);
}

RndTex::RndTex() : mMipMapK(-8.0f), mType(Regular), mWidth(0), mHeight(0), mBpp(32), mFilepath(), mLoader(0), mOptimizeForPS3(0), unk60(0) {
    
}

RndTex::~RndTex() {
    delete mLoader; // should be unk60, but it's unknown as of current
    mLoader = NULL;
}

SAVE_OBJ(RndTex, 744)

void RndTex::Load(BinStream& bs) { PreLoad(bs); PostLoad(bs); }

void RndTex::PreLoad(BinStream& bs) {
    short s_dump;
    LOAD_REVS(bs)
    ASSERT_REVS(11, 1)
    if (gRev > 8) Hmx::Object::Load(bs);
    if (gRev == 1) {
        bs >> s_dump;
    }
}

void RndTex::SaveBitmap(const char*) {
    MILO_ASSERT(0, 1033);
}

void RndTex::Print() {
    TheDebug << "   width: " << mWidth << "\n";
    TheDebug << "   height: " << mHeight << "\n";
    TheDebug << "   bpp: " << mBpp << "\n";
    TheDebug << "   mipMapK: " << mMipMapK << "\n";
    TheDebug << "   file: " << FileRelativePath(FilePath::sRoot.c_str(), mFilepath.c_str()) << "\n";
    TheDebug << "   type: " << mType << "\n";
}

BEGIN_HANDLERS(RndTex)
    HANDLE(set_bitmap, OnSetBitmap)
    HANDLE(set_rendered, OnSetRendered)
    HANDLE_EXPR(file_path, mFilepath.c_str())
    HANDLE_ACTION(set_file_path, mFilepath.Set(FilePath::sRoot.c_str(), _msg->Str(2)))
    HANDLE_EXPR(size_kb, (int)((mWidth * mHeight * mBpp) >> 3)) // i don't like this expression. someone pls make it go away kthxbai
    HANDLE_EXPR(tex_type, mType)
    HANDLE_ACTION(save_bmp, SaveBitmap(_msg->Str(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(1082)
END_HANDLERS

DataNode RndTex::OnSetBitmap(const DataArray* da) {
    if (da->Size() == 3) {
        const char* s = da->Str(2);
        FilePath p;
        p.Set(FilePath::sRoot.c_str(), s);
        SetBitmap(p);
    } else {
        SetBitmap(da->Int(2), da->Int(3), da->Int(4), (RndTex::Type)da->Int(5), (bool)da->Int(6), NULL);
    }
    return DataNode();
}

DataNode RndTex::OnSetRendered(const DataArray*) {
    MILO_ASSERT(IsRenderTarget(), 1101);
    SetBitmap(mWidth, mHeight, mBpp, mType, mLoader, NULL); // this is *almost* it... but the `or` needs to be an `andc`
    return DataNode();
}

BEGIN_PROPSYNCS(RndTex)
    SYNC_PROP("width", mWidth)
    SYNC_PROP("height", mHeight)
    SYNC_PROP("bpp", mBpp)
    SYNC_PROP(mip_map_k, mMipMapK)
    SYNC_PROP(optimize_for_ps3, mOptimizeForPS3)
    if (sym == file_path) { // mfw have to manually branch predict
        bool synced = PropSync(mFilepath, _val, _prop, _i + 1, _op);
        if (synced) {
            if (!(_op & (0x11))) {
                SetBitmap(mFilepath);
                ;
            }
            return true;
        }
        return false;
    }
END_PROPSYNCS

int RndTex::TexelsPitch() const { return 0; }
