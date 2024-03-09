#include "rndobj/CubeTex.h"

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

RndCubeTex::~RndCubeTex(){
    
}

SAVE_OBJ(RndCubeTex, 0x116);

void RndCubeTex::Load(BinStream& bs){
    PreLoad(bs);
    PostLoad(bs);
}

BEGIN_HANDLERS(RndCubeTex)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1D3)
END_HANDLERS
