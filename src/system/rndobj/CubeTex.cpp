#include "rndobj/CubeTex.h"
#include "utl/Loader.h"
#include "rndobj/Tex.h"
#include "utl/Symbols.h"

#include "decomp.h"

INIT_REVS(RndCubeTex)

DECOMP_FORCEACTIVE(CubeTex,
    __FILE__,
    "0"
)

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
    const char* cc;
    bool ret = true;
    FileLoader* fLoader = dynamic_cast<FileLoader*>(TheLoadMgr.ForceGetLoader(fp));
    if(fLoader){
        cc = fLoader->GetBuffer(0);
    }
    else cc = 0;

    delete fLoader;
    if(!cc){
        bmap.Reset();
        ret = false;
    }
    else {
        bmap.Create((void*)cc);
        int width = bmap.Width();
        int height = bmap.Height();
        if(width != height){
            MILO_WARN("%s: CubeTex bitmap (%s) is not square.", PathName(this), fp.c_str());
            bmap.Reset();
            ret = false;
        }
    }
    return ret;
}

void RndCubeTex::SetBitmap(CubeFace face, const FilePath& fp, bool b){
    if(LoadBitmap(fp, mBitmap[face])){
        mFile[face] = fp;
        moreprops[face].Set(mBitmap[face]);
        props = moreprops[face];
    }
    if(b) Update();
}

bool RndCubeTex::ValidateBitmapProperties(std::vector<CubeFace>& faces){
    if(props.mWidth == 0 || props.mHeight == 0) return false;
    else {
        const char* sizeStr = RndTex::CheckSize(props.mWidth, props.mHeight, props.mBpp, props.mNumMips, RndTex::Regular, false);
        if(sizeStr){
            MILO_WARN(sizeStr, Name());
            return false;
        }
        else {
            for(int i = 1; i < 6; i++){
                CubeTexProperties& propsToAnalyze = moreprops[i];
                if(props.mWidth != propsToAnalyze.mWidth || props.mHeight != propsToAnalyze.mHeight || props.mBpp != propsToAnalyze.mBpp ||
                    props.mNumMips != propsToAnalyze.mNumMips || props.mOrder != propsToAnalyze.mOrder){
                    faces.push_back((CubeFace)i);
                    return false;
                }
            }
            return true;
        }
    }
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
    CREATE_COPY(RndCubeTex)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(props)
        for(int i = 0; i < 6; i++){
            COPY_MEMBER(moreprops[i])
            COPY_MEMBER(mFile[i])
            mBitmap[i].Create(c->mBitmap[i], c->mBitmap[i].mBpp, c->mBitmap[i].mOrder, 0);
        }
    END_COPYING_MEMBERS
    Update();
END_COPYS

BEGIN_HANDLERS(RndCubeTex)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1D3)
END_HANDLERS

BEGIN_PROPSYNCS(RndCubeTex)
    if(sym == right){
        if(_op == kPropSet) SetBitmap(kCubeFaceRight, FilePath(_val.Str(0)), true);
        else {
            if(_op == (PropOp)0x40) return false;
            _val = DataNode(FileRelativePath(FilePath::sRoot.c_str(), mFile[kCubeFaceRight].c_str()));
        }
        return true;
    }
    if(sym == left){
        if(_op == kPropSet) SetBitmap(kCubeFaceLeft, FilePath(_val.Str(0)), true);
        else {
            if(_op == (PropOp)0x40) return false;
            _val = DataNode(FileRelativePath(FilePath::sRoot.c_str(), mFile[kCubeFaceLeft].c_str()));
        }
        return true;
    }
    if(sym == top){
        if(_op == kPropSet) SetBitmap(kCubeFaceTop, FilePath(_val.Str(0)), true);
        else {
            if(_op == (PropOp)0x40) return false;
            _val = DataNode(FileRelativePath(FilePath::sRoot.c_str(), mFile[kCubeFaceTop].c_str()));
        }
        return true;
    }
    if(sym == bottom){
        if(_op == kPropSet) SetBitmap(kCubeFaceBottom, FilePath(_val.Str(0)), true);
        else {
            if(_op == (PropOp)0x40) return false;
            _val = DataNode(FileRelativePath(FilePath::sRoot.c_str(), mFile[kCubeFaceBottom].c_str()));
        }
        return true;
    }
    if(sym == front){
        if(_op == kPropSet) SetBitmap(kCubeFaceFront, FilePath(_val.Str(0)), true);
        else {
            if(_op == (PropOp)0x40) return false;
            _val = DataNode(FileRelativePath(FilePath::sRoot.c_str(), mFile[kCubeFaceFront].c_str()));
        }
        return true;
    }
    if(sym == back){
        if(_op == kPropSet) SetBitmap(kCubeFaceBack, FilePath(_val.Str(0)), true);
        else {
            if(_op == (PropOp)0x40) return false;
            _val = DataNode(FileRelativePath(FilePath::sRoot.c_str(), mFile[kCubeFaceBack].c_str()));
        }
        return true;
    }
END_PROPSYNCS
