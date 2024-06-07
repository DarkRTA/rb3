#include "rndobj/Tex.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/File.h"
#include "utl/BinStream.h"
#include "utl/BufStream.h"
#include "os/System.h"
#include "rndobj/Rnd.h"
#include "rndobj/Utl.h"
#include "obj/ObjVersion.h"
#include "utl/Symbols.h"

INIT_REVS(RndTex)

bool UseBottomMip() {
    DataArray* found = SystemConfig("rnd")->FindArray("use_bottom_mip", false);
    return found ? (found->Int(1) != 0) : false;
}

void CopyBottomMip(RndBitmap& dst, const RndBitmap& src) {
    MILO_ASSERT(&src != &dst, 48);
    while (src.mMip) {
        &src = src.mMip;
    }
    dst.Create(src, src.mBpp, src.mOrder, NULL);
}

RndTex::RndTex() : mMipMapK(-8.0f), mType(Regular), mWidth(0), mHeight(0), mBpp(32), mFilepath(), mNumMips(0), mOptimizeForPS3(0), mLoader(0) {

}

RndTex::~RndTex() {
    delete mLoader;
    mLoader = NULL;
}

void RndTex::PlatformBppOrder(const char* cc, int& bpp, int& order, bool hasAlpha){
    Platform plat = TheLoadMgr.GetPlatform();
    bool bbb;

    switch (TheLoadMgr.GetPlatform()) {
        case kPlatformWii:
            order = 8;
            if(hasAlpha){
                order |= 0x100;
                bpp = 8;
            }
            else bpp = 4;
            order |= 0x40;
            break;

        case kPlatformPS2:
            break;
        
        case kPlatformXBox:
        case kPlatformPC:
        case kPlatformPS3:
            bbb = cc && strstr(cc, "_norm");
            
            if(bbb){
                if(plat == kPlatformXBox) order = 0x20;
                else if(plat == kPlatformPS3) order = 8;
                else order = 0;
            }
            else {
                order = hasAlpha ? 0x18 : 8;
            }
            if(order == 8) bpp = 4;
            else if(order & 0x38U) bpp = 8;
            else if(bbb) bpp = 0x18;
            else if(bpp < 0x10) bpp = 0x10;
            break;

        
        case kPlatformNone:
            order = 0;
            break;
    }
}

void RndTex::SetBitmap(int w, int h, int bpp, Type ty, bool useMips, const char* path){
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
                PlatformBppOrder(path, x, y, true);
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

void RndTex::SetBitmap(const RndBitmap& bmap, const char* cc, bool b){
    PresyncBitmap();
    mWidth = bmap.Width();
    mHeight = bmap.Height();
    SetPowerOf2();
    mBpp = bmap.Bpp();
    mType = Regular;
    mFilepath.SetRoot("");
    mNumMips = bmap.NumMips();
    MILO_ASSERT(!mNumMips, 0x111);
    const char* sizeStr = CheckSize(mWidth, mHeight, mBpp, mNumMips, mType, false);
    if(sizeStr){
        MILO_WARN(sizeStr, Name());
        mBitmap.Reset();
    }
    else {
        int i = bmap.Bpp();
        int j = bmap.Order();
        if(!b){
            PlatformBppOrder(cc, i, j, bmap.IsTranslucent());
        }
        mBitmap.Create(bmap, i, j, 0);
    }
    SyncBitmap();
}

void RndTex::SetBitmap(FileLoader* fl){
    PresyncBitmap();
    mType = Regular;
    void* buffer;
    if(fl){
        mFilepath = ((Loader*)fl)->mFile;
        TheLoadMgr.PollUntilLoaded(fl, 0);
        int i = 0;
        buffer = (void*)fl->GetBuffer(&i);
        if(!TheLoadMgr.EditMode() && fl != mLoader){
            if(!strstr(mFilepath.c_str(), "_keep")){
                MILO_WARN("%s will not be included on a disc build", mFilepath);
            }
        }
        delete fl;
    }
    else {
        mFilepath.SetRoot("");
        buffer = 0;
    }

    if(buffer){
        if(UseBottomMip()){
            RndBitmap someotherbmap;
            someotherbmap.Create(buffer);
            CopyBottomMip(mBitmap, someotherbmap);
        }
        else {
            mBitmap.Create(buffer);
        }

        mWidth = mBitmap.Width();
        mHeight = mBitmap.Height();
        SetPowerOf2();
        mBpp = mBitmap.Bpp();
        mNumMips = mBitmap.NumMips();
        MILO_ASSERT(!mNumMips, 0x183);
    }
    else {
        mBitmap.Reset();
        mHeight = 0;
        mWidth = 0;
        SetPowerOf2();
        mBpp = 0x20;
        mNumMips = 0;
    }
    SyncBitmap();
}

void RndTex::SetBitmap(const FilePath& fp){
    SetBitmap(dynamic_cast<FileLoader*>(TheLoadMgr.ForceGetLoader(fp)));
}

const char* CheckDim(int dim, RndTex::Type ty, bool b){
    const char* ret = 0;
    if(dim == 0) return ret;
    else {
        if(ty == RndTex::Movie && (dim % 16 != 0)){
            ret = "%s: dimensions not multiple of 16";
        }
        if(GetGfxMode() == 0){
            if(b && dim > 0x400){
                ret = "%s: dimensions greater than 1024";
            }
            else if(dim > 0x800){
                ret = "%s: dimensions greater than 2048";
            }
            if(dim % 8 != 0){
                ret = "%s: dimensions not multiple of 8";
            }
        }
        if(b){
            bool bbb;
            if(dim < 0) bbb = false;
            else if(dim == 0) bbb = true;
            else bbb = (dim & (dim - 1)) == 0;
            if(!bbb) ret = "%s: dimensions are not power-of-2";
        }
    }
    return ret;
}

const char* RndTex::CheckSize(int width, int height, int bpp, int numMips, Type ty, bool file){
    const char* ret;
    if(ty == DepthVolumeMap || ty == DensityMap || (ty & DeviceTexture)) return 0;
    else {
        ret = CheckDim(width, ty, file);
        if(!ret) ret = CheckDim(height, ty, file);
        if(!ret && bpp != 4 && bpp != 8 && bpp != 0x10 && bpp != 0x18 && bpp != 0x20){
            ret = "%s: invalid bpp";
        }
        int u3 = (width * height * bpp) >> 3;
        if(GetGfxMode() == 0){
            if(!ret && u3 > 0x7FFF0){
                ret = "%s: size over 524,272 bytes";
            }
            if(!ret && (u3 & 0xf)){
                ret = "%s: size not multiple of 16 bytes";
            }
            if(!ret && numMips > 0){
                ret = "%s: more than 0 mip levels";
            }
        }
    }
    return ret;
}

void RndTex::SetPowerOf2(){
    bool set;
    if(mWidth < 0) set = false;
    else if(mWidth == 0) set = true;
    else set = (mWidth & (mWidth - 1)) == 0;

    if(set){
        if(mHeight < 0) set = false;
        else if(mHeight == 0) set = true;
        else set = (mHeight & (mHeight - 1)) == 0;
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
    LOAD_REVS(bs)
    ASSERT_REVS(11, 1)
    if (gRev > 8) LOAD_SUPERCLASS(Hmx::Object)
    if (gRev == 1) {
        short s1, s2;
        bs >> s1 >> s2;
        mWidth = s1;
        mHeight = s2;
    }
    else bs >> mWidth >> mHeight;
    SetPowerOf2();
    bs >> mBpp;
    bs >> mFilepath;
    if(gRev > 9 && !bs.Cached()){
        mLoader = new FileLoader(mFilepath, CacheResource(mFilepath.c_str(), this), kLoadFront, 0, false, true, 0);
    }
    else {
        if(bs.Cached() && gAltRev != 0){
            mLoader = new FileLoader(mFilepath, CacheResource(mFilepath.c_str(), this), kLoadFront, 0, true, true, &bs);
        }
    }
    PushRev(packRevs(gAltRev, gRev), this);
}

void RndTex::PostLoad(BinStream& bs){
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(gRev < 5){
        int cubemapmask;
        bs >> cubemapmask;
        if(cubemapmask != 0 && !mFilepath.empty()){
            if(cubemapmask & 1) MILO_WARN("%s: kTransparentWhite no longer supported", Name());
            else if(cubemapmask & 2){
                mFilepath.insert(mFilepath.find('.'), "_tb");
            }
            else if(cubemapmask & 0x10){
                mFilepath.insert(mFilepath.find('.'), "_ga");
            }
            else if(cubemapmask & 0x20){
                mFilepath.insert(mFilepath.find('.'), "_gw");
            }
            else if(cubemapmask & 0x40){
                MILO_WARN("%s: kCubeMap no longer supported", Name());
            }
        }
    }
    if(gRev != 0 && gRev < 3){
        bool b;
        bs >> b;
    }
    if(gRev > 7) bs >> mMipMapK;
    else if(gRev > 3){
        int i;
        bs >> i;
        mMipMapK = i / 16.0f;
    }

    if(gRev > 6){
        bs >> (int&)mType;
    }
    else if(gRev > 5){
        Type types[5] = { Regular, Rendered, Movie, BackBuffer, FrontBuffer };
        int i;
        bs >> i;
        mType = types[i];
    }
    else if(gRev > 4){
        bool b;
        bs >> b;
        Type ty = Regular;
        if(b) ty = Rendered;
        mType = ty;
    }

    if(mFilepath.empty()){
        if(strcmp(Name(), "movie.tex") != 0 && strcmp(Name(), "movie_splash.tex") != 0 && (mType & Rendered)){
            while(mWidth > 0x100) mWidth /= 2;
            while(mHeight > 0x100) mHeight /= 2;
        }
    }
    if(gRev > 7){
        bool b;
        bs >> b;
    }
    if(gRev > 10){
        bool b;
        bs >> b;
        mOptimizeForPS3 = b;
    }

    if(bs.Cached()){
        void* buffer = 0;
        int size = 0;
        if(mLoader){
            buffer = (void*)mLoader->GetBuffer(0);
            size = mLoader->GetSize();
            delete mLoader;
            mLoader = 0;
        }
        BufStream bufs(buffer, size, true);
        if(buffer) &bs = &bufs;
        PresyncBitmap();
        if(UseBottomMip()){
            RndBitmap someotherbmap;
            someotherbmap.Load(bs);
            CopyBottomMip(mBitmap, someotherbmap);
        }
        else mBitmap.Load(bs);
        if(buffer) _MemFree(buffer);
        mNumMips = mBitmap.NumMips();
        MILO_ASSERT(!mNumMips, 0x3B7);
        SyncBitmap();
    }
    else if(mFilepath.empty() || mType != Regular){
        MILO_ASSERT(!mNumMips, 0x3BE);
        SetBitmap(mWidth, mHeight, mBpp, mType, false, 0);
    }
    else if(TheLoadMgr.GetPlatform() != kPlatformNone){
        MILO_ASSERT(!mNumMips, 0x3C7);
        SetBitmap(mLoader);
        mLoader = 0;
    }
    else {
        delete mLoader;
        mLoader = 0;
    }
}

BEGIN_COPYS(RndTex)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(RndTex)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mMipMapK)
        }
        if(ty == kCopyFromMax && mType != c->mType) return;
        PresyncBitmap();
        COPY_MEMBER(mType)
        COPY_MEMBER(mWidth)
        COPY_MEMBER(mHeight)
        SetPowerOf2();
        COPY_MEMBER(mBpp)
        COPY_MEMBER(mFilepath)
        COPY_MEMBER(mNumMips)
        MILO_ASSERT(!mNumMips, 1000);
        COPY_MEMBER(mOptimizeForPS3)
        mBitmap.Create(c->mBitmap, c->mBitmap.mBpp, c->mBitmap.mOrder, 0);
        SyncBitmap();
    END_COPYING_MEMBERS
END_COPYS

DECOMP_FORCEACTIVE(Tex,
    "Regular", "Rendered", "Movie", "BackBuffer", "FrontBuffer", "RenderedNoZ",
    "ShadowMap", "DepthVolumeMap", "DensityMap", "DeviceTexture", "Scratch"
)

TextStream& operator<<(TextStream& ts, RndTex::Type ty){
    if(ty <= RndTex::RenderedNoZ){
        if(ty <= RndTex::Movie){
            if(ty <= RndTex::Rendered){
                if(ty < RndTex::Rendered && ty > 0) ts << "Regular";
                else if(ty == RndTex::Rendered) ts << "Rendered";
            }
            else if(ty == RndTex::Movie) ts << "Movie";
        }
        else if(ty <= RndTex::FrontBuffer){
            if(ty < RndTex::FrontBuffer && ty == RndTex::BackBuffer) ts << "BackBuffer";
            else if(ty == RndTex::FrontBuffer) ts << "FrontBuffer";
        }
        else if(ty == RndTex::RenderedNoZ) ts << "RenderedNoZ";
    }
    else if(ty <= RndTex::DensityMap){
        if(ty < RndTex::DepthVolumeMap && ty == RndTex::ShadowMap) ts << "ShadowMap";
        else if(ty == RndTex::DepthVolumeMap) ts << "DepthVolumeMap";
        else if(ty == RndTex::DensityMap) ts << "DensityMap";
    }
    else if(ty == RndTex::DeviceTexture) ts << "DeviceTexture";
    else if(ty < RndTex::DeviceTexture && ty == RndTex::Scratch) ts << "Scratch";
    return ts;
}

void RndTex::SaveBitmap(const char*) {
    MILO_ASSERT(0, 1033);
}

void RndTex::Print() {
    TheDebug << "   width: " << mWidth << "\n";
    TheDebug << "   height: " << mHeight << "\n";
    TheDebug << "   bpp: " << mBpp << "\n";
    TheDebug << "   mipMapK: " << mMipMapK << "\n";
    TheDebug << "   file: " << mFilepath << "\n";
    TheDebug << "   type: " << mType << "\n";
}

BEGIN_HANDLERS(RndTex)
    HANDLE(set_bitmap, OnSetBitmap)
    HANDLE(set_rendered, OnSetRendered)
    HANDLE_EXPR(file_path, mFilepath.c_str())
    HANDLE_ACTION(set_file_path, mFilepath.Set(FilePath::sRoot.c_str(), _msg->Str(2)))
    HANDLE_EXPR(size_kb, (int)((mWidth * mHeight * mBpp) / 8 / 1024)) // i don't like this expression. someone pls make it go away kthxbai
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
    SetBitmap(mWidth, mHeight, mBpp, mType, mNumMips > 0, NULL);
    return DataNode();
}

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(RndTex)
    { 
        static Symbol _s("width"); 
        if(sym == _s && _op & kPropGet) return PropSync(mWidth, _val, _prop, _i + 1, _op); 
    }
    {
        static Symbol _s("height");
        if(sym == _s && _op & kPropGet) return PropSync(mHeight, _val, _prop, _i + 1, _op);
    }
    {
        static Symbol _s("bpp");
        if(sym == _s && _op & kPropGet) return PropSync(mBpp, _val, _prop, _i + 1, _op);
    }
    SYNC_PROP(mip_map_k, mMipMapK)
    SYNC_PROP(optimize_for_ps3, mOptimizeForPS3)
    SYNC_PROP_MODIFY_ALT(file_path, mFilepath, SetBitmap(mFilepath))
END_PROPSYNCS
#pragma pop
