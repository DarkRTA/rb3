#include "rndobj/Movie.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

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
    SYNC_PROP(movie_file, mFile)
    SYNC_PROP(stream, mStream)
    SYNC_PROP(loop, mLoop)
    // SYNC_PROP(tex, mTex)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS