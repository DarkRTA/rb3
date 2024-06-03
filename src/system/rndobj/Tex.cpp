#include "rndobj/Tex.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/File.h"
#include "utl/BinStream.h"
#include "utl/Symbols.h"
#include "os/System.h"
#include "rndobj/Rnd.h"
#include "utl/Symbols.h"

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

RndTex::RndTex() : mMipMapK(-8.0f), mType(Regular), mWidth(0), mHeight(0), mBpp(32), mFilepath(), mNumMips(0), mOptimizeForPS3(0), mLoader(0) {

}

RndTex::~RndTex() {
    delete mLoader;
    mLoader = NULL;
}

void RndTex::PlatformBppOrder(const char* cc, int& i, int& j, bool b){
    Platform plat = TheLoadMgr.mPlatform;
    if(plat < kPlatformXBox || kPlatformPS3 < plat){
        if(plat == kPlatformWii){
            j = 8;
            if(b){
                j |= 0x100;
                i = 8;
            }
            else i = 4;
            j |= 0x40;
        }
        else if(plat == kPlatformNone) j = 0;
    }
    else {
        bool bbb = false;
        if(strstr(cc, "_norm")) bbb = true;
        
        if(bbb){
            if(plat == kPlatformXBox) j = 0x20;
            else if(plat == kPlatformPS3) j = 8;
            else j = 0;
        }
        else {
            j = b ? 0x18 : 8;
        }
        if(j == 8) i = 4;
        else if(j & 0x38U) i = 8;
        else if(bbb) i = 0x18;
        else if(i < 0x10) i = 0x10;
        else j = 0;
    }
}

void RndTex::SetBitmap(int w, int h, int bpp, Type ty, bool useMips, const char* cc){
    PresyncBitmap();
    mWidth = w;
    mHeight = h;
    SetPowerOf2();
    mBpp = bpp;
    mType = ty;
    mFilepath.SetRoot("");
    mNumMips = 0;
    mBitmap.Reset();
    if(mType & BackBuffer){
        mWidth = TheRnd->mWidth;
        mHeight = TheRnd->mHeight;
        SetPowerOf2();
        mBpp = TheRnd->mScreenBpp;
    }
    else if(mType & Rendered){
        if(useMips){
            for(int i = mWidth, j = mHeight; i > 0x10 && j > 0x10; i >>= 1, j >>= 1){
                mNumMips++;
            }
        }
    }
    else {
        const char* sizeStr = CheckSize(mWidth, mHeight, mBpp, mNumMips, mType, false);
        if(sizeStr) MILO_WARN(sizeStr, Name());
        else {
            if(!(mType & 0x204U)){
                int x = mBpp;
                int y;
                PlatformBppOrder(cc, x, y, true);
                mBitmap.Create(mWidth, mHeight, 0, x, y, 0, 0, 0);
                if(useMips){
                    MILO_ASSERT(!useMips, 0xF8);
                    mBitmap.GenerateMips();
                    mNumMips = mBitmap.NumMips();
                }
            }
        }
    }
    SyncBitmap();
}

void RndTex::SetBitmap(const FilePath& fp){
    SetBitmap(dynamic_cast<FileLoader*>(TheLoadMgr.ForceGetLoader(fp)));
}

void RndTex::SetPowerOf2(){
    bool set;
    if(mWidth < 0) set = false;
    else if(mWidth == 0) set = true;
    else set = mWidth == 1;

    if(set){
        if(mHeight < 0) set = false;
        else if(mHeight == 0) set = true;
        else set = mHeight == 1;
    }
    mIsPowerOf2 = set;
}

void RndTex::LockBitmap(RndBitmap& bmap, int i){
    if(mBitmap.mOrder & 0x38){
        bmap.Create(mBitmap, 0x20, 0, 0);
    }
    else {
        bmap.Create(mBitmap.mWidth, mBitmap.mHeight, mBitmap.mRowBytes, mBitmap.mBpp, mBitmap.mOrder, mBitmap.mPalette, mBitmap.mPixels, 0);
    }
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
    SetBitmap(mWidth, mHeight, mBpp, mType, mNumMips, NULL); // this is *almost* it... but the `or` needs to be an `andc`
    return DataNode();
}

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(RndTex)
    SYNC_PROP_STATIC(width, mWidth)
    SYNC_PROP_STATIC(height, mHeight)
    SYNC_PROP_STATIC(bpp, mBpp)
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
#pragma pop

int RndTex::TexelsPitch() const { return 0; }
