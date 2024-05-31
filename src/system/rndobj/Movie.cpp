#include "rndobj/Movie.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

#include "decomp.h"

INIT_REVS(RndMovie);

RndMovie::RndMovie() : mFile(), mStream(0), mLoop(1), mTex(this, 0) {

}

SAVE_OBJ(RndMovie, 0x1F);

void RndMovie::Load(BinStream& bs){
    PreLoad(bs);
    PostLoad(bs);
}

void RndMovie::PreLoad(BinStream& bs){
    char buf[0x100];
    LOAD_REVS(bs);
    ASSERT_REVS(8, 0);
    if(gRev > 6) Hmx::Object::Load(bs);
    RndAnimatable::Load(bs);
    bs.ReadString(buf, 0x100);
    mFile.Set(FilePath::sRoot.c_str(), buf);
    if(gRev > 3) bs >> mTex;
    if(gRev > 4) bs >> mStream;
    if(gRev > 7 && !mStream){
        TheLoadMgr.AddLoader(mFile, kLoadFront);
    }
}

void RndMovie::PostLoad(BinStream& bs){
    if(gRev > 5) bs >> mLoop;
    else if(gRev == 5) mLoop = (mStream == 0);
    SetFile(mFile, mStream);
}

void RndMovie::SetFile(const FilePath& fp, bool b){
    mFile = fp;
    mStream = b;
}

BEGIN_COPYS(RndMovie)
    const RndMovie* t = dynamic_cast<const RndMovie*>(o);
    MILO_ASSERT(t, 0x52);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    mLoop = t->mLoop;
    mTex = t->mTex;
    SetFile(t->mFile, t->mStream);
END_COPYS

void RndMovie::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mTex == from){
        SetTex(dynamic_cast<RndTex*>(to));
    }
}

void RndMovie::SetTex(RndTex* tex){
    mTex = tex;
}

BEGIN_HANDLERS(RndMovie)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x73)
END_HANDLERS

BEGIN_PROPSYNCS(RndMovie)
    if(sym == movie_file){
        if(_op == kPropSet){
            const char* str = _val.Str(0);
            FilePath fp;
            fp.SetRoot(str);
            SetFile(fp, mStream);
        }
        else {
            if(_op == (PropOp)0x40) return false;
            _val = DataNode(mFile.FilePathRelativeToRoot());
        }
        return true;
    }
    if(sym == stream){
        if(_op == kPropSet){
            SetFile(mFile, _val.Int(0) != 0);
        }
        else {
            if(_op == (PropOp)0x40) return false;
            _val = DataNode(mStream);
        }
        return true;
    }
    SYNC_PROP(loop, mLoop)
    if(sym == tex){
        if(_op == kPropSet){
            SetTex(_val.Obj<RndTex>(0));
        }
        else {
            if(_op == (PropOp)0x40) return false;
            _val = DataNode(mTex);
        }
        return true;
    }
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS

// Force inline generation
DECOMP_FORCEFUNC(Movie, RndMovie, SetType(Symbol()))
DECOMP_FORCEFUNC(Movie, RndMovie, Loop())
