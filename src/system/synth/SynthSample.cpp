#include "synth/SynthSample.h"
#include "synth/Utl.h"
#include "obj/ObjVersion.h"
#include "utl/Symbols.h"

INIT_REVS(SynthSample)

SynthSample::SynthSample() : mIsLooped(0), mLoopStartSamp(0), mLoopEndSamp(-1), mFileLoader(0) {

}

SynthSample::~SynthSample(){
    delete mFileLoader;
    mFileLoader = 0;
}

int SynthSample::GetSampleRate() const { return mSampleData.mSampleRate; }
SampleData::Format SynthSample::GetFormat() const { return mSampleData.mFormat; }
bool SynthSample::GetIsLooped() const { return mIsLooped; }
int SynthSample::GetLoopStartSamp() const { return mLoopStartSamp; }

SAVE_OBJ(SynthSample, 0xB2)

BEGIN_LOADS(SynthSample)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void SynthSample::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(5, 1)
    if(gRev > 1) LOAD_SUPERCLASS(Hmx::Object)
    bs >> mFile;
    bs >> mIsLooped;
    bs >> mLoopStartSamp;
    if(gRev >= 3) bs >> mLoopEndSamp;
    if(bs.Cached() && gRev >= 5){
        if(gAltRev == 0) mSampleData.Load(bs, mFile);
        else {
            CacheResourceResult res;
            mFileLoader = new FileLoader(mFile, CacheWav(mFile.c_str(), res), kLoadFront, 0, false, true, &bs);
        }
    }
    else if(gRev > 3){
        mFileLoader = dynamic_cast<FileLoader*>(TheLoadMgr.AddLoader(mFile, kLoadFront));
    }
    PushRev(packRevs(gAltRev, gRev), this);
}

void SynthSample::PostLoad(BinStream& bs){
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    SyncType ty;
    if(bs.Cached()){
        ty = sync2;
        if(gAltRev != 0) ty = sync3;
    }
    else {
        mFileLoader = 0;
        ty = sync0;
    }
    Sync(ty);
}

BEGIN_COPYS(SynthSample)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(SynthSample)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mFile)
            COPY_MEMBER(mIsLooped)
            COPY_MEMBER(mLoopStartSamp)
            COPY_MEMBER(mLoopEndSamp)
        }
    END_COPYING_MEMBERS
    Sync(sync0);
END_COPYS

BEGIN_CUSTOM_PROPSYNC(SampleMarker)
    SYNC_PROP(sample, o.sample)
    SYNC_PROP(name, o.name)
END_CUSTOM_PROPSYNC