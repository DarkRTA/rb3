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
