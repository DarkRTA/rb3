#include "Tex.h"
#include "os/Debug.h"
#include "os/File.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

bool UseBottomMip() {
    Symbol rnd("rnd");
    Symbol use_bottom_mip("use_bottom_mip");
}

void CopyBottomMip(RndBitmap& dst, const RndBitmap& src) {
    MILO_ASSERT(&src != &dst, 48);
    const RndBitmap* dingus;
    while (dingus->mMip) dingus = dingus->mMip;
    dst.Create(*dingus, dingus->mBpp, dingus->mOrder, NULL);
}

RndTex::RndTex() {
    mBitmap->Reset();
    mMipMapK = -8;
}

RndTex::~RndTex() {
    delete mLoader;
    mLoader = NULL;
    mBitmap->Reset();
}

void RndTex::Save(BinStream&) {
    MILO_ASSERT(0, 744);
}

void RndTex::SaveBitmap(const char*) {
    MILO_ASSERT(0, 1033);
}

void RndTex::Print() {
    TheDebug << "   width: " << mWidth << "\n";
    TheDebug << "   height: " << mHeight << "\n";
    TheDebug << "   bpp: " << mBpp << "\n";
    TheDebug << "   mipMapK: " << mMipMapK << "\n";
    TheDebug << "   file: " << FileRelativePath(FilePath::sRoot.c_str(), mFilename.c_str()) << "\n";
    TheDebug << "   type: " << mType << "\n";
}

BEGIN_HANDLERS(RndTex)
HANDLE(set_bitmap, OnSetBitmap)
HANDLE(set_rendered, OnSetRendered)
HANDLE_EXPR(file_path, mFilename.c_str())
HANDLE_ACTION(set_file_path, mFilename.Set(FilePath::sRoot.c_str(), _msg->Str(2)))
HANDLE_EXPR(size_kb, (int)((mWidth * mHeight * mBpp) >> 3)) // i don't like this expression. someone pls make it go away kthxbai
HANDLE_EXPR(tex_type, mType)
HANDLE_ACTION(save_bmp, SaveBitmap(_msg->Str(2)))
HANDLE_SUPERCLASS(Hmx::Object)
HANDLE_CHECK(1082)
END_HANDLERS

int RndTex::TexelsPitch() const { return 0; }
