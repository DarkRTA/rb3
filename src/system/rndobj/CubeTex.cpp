#include "rndobj/CubeTex.h"
#include "utl/Loader.h"

INIT_REVS(RndCubeTex)

static const char* cubeStrs [] = { __FILE__, "0" };

void RndCubeTex::CubeTexProperties::Set(const RndBitmap& bmap){
    mBpp = bmap.mBpp;
    mHeight = bmap.mHeight;
    mWidth = bmap.mWidth;
    mNumMips = bmap.NumMips();
    mOrder = bmap.mOrder;
}

void RndCubeTex::CubeTexProperties::Load(BinStream& bs){
    bs >> mBpp >> mHeight >> mWidth >> mNumMips >> mOrder;
}

RndCubeTex::RndCubeTex(){

}

bool RndCubeTex::LoadBitmap(const FilePath& fp, RndBitmap& bmap){
    bool ret = true;
    const char* cc;
    FileLoader* fLoader = dynamic_cast<FileLoader*>(TheLoadMgr.ForceGetLoader(fp));
    if(fLoader){
        cc = fLoader->GetBuffer(0);
        delete fLoader;
    }
    else cc = 0;
    if(!cc){
        bmap.Reset();
        ret = false;
    }
    else {
        bmap.Create((void*)cc);
        if(bmap.Width() != bmap.Height()){
            MILO_WARN("%s: CubeTex bitmap (%s) is not square.", PathName(this), fp.c_str());
            bmap.Reset();
        }
        ret = false;
    }
    return ret;
}

void RndCubeTex::Update(){
    std::vector<CubeFace> vec;
    if(!ValidateBitmapProperties(vec)){
        Reset();
        return;
    }
    else {
        props = moreprops[0];
        Sync();
        return;
    }
}

RndCubeTex::~RndCubeTex(){
    
}

SAVE_OBJ(RndCubeTex, 0x116);

void RndCubeTex::Load(BinStream& bs){
    PreLoad(bs);
    PostLoad(bs);
}

void RndCubeTex::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev > 1){
        if(bs.Cached()){
            props.Load(bs);
            for(int i = 0; i < 6; i++){
                moreprops[i].Load(bs);
            }
        }
        else {
            CubeTexProperties ctprops;
            ctprops.Load(bs);
            for(int i = 0; i < 6; i++){
                ctprops.Load(bs);
            }
        }
    }
    else {
        int i, j;
        bs >> i;
        bs >> j;
        props.mWidth = i;
        props.mHeight = i;
        props.mBpp = j;
    }
    for(int i = 0; i < 6; i++){
        bs >> mFile[i];
        if(!bs.Cached()) TheLoadMgr.AddLoader(mFile[i], kLoadFront);
    }
}

void RndCubeTex::PostLoad(BinStream& bs){
    if(gRev < 2){
        bool b;
        bs >> b;
    }
    for(int i = 0; i < 6; i++){
        if(bs.Cached()){
            mBitmap[i].Load(bs);
        }
        else if(!mFile[i].empty()){
            SetBitmap((CubeFace)i, mFile[i], false);
        }
        if(gRev < 2){
            props = moreprops[i];
        }
    }
    Update();
}

BEGIN_COPYS(RndCubeTex)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(RndCubeTex)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(props)
        for(int i = 0; i < 6; i++){
            COPY_MEMBER(moreprops[i])
            COPY_MEMBER(mFile[i])
            mBitmap[i].Create(c->mBitmap[i], c->mBitmap[i].mBpp, c->mBitmap[i].mOrder, 0);
        }
    END_COPY_CHECKED
    Update();
END_COPYS

BEGIN_HANDLERS(RndCubeTex)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1D3)
END_HANDLERS
