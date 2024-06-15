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

BEGIN_HANDLERS(SynthSample)
    HANDLE_EXPR(platform_size_kb, GetPlatformSize(TheLoadMgr.GetPlatform()) / 1024)
    HANDLE_EXPR(num_markers, mSampleData.NumMarkers())
    HANDLE_EXPR(marker_name, mSampleData.GetMarker(_msg->Int(2)).name)
    HANDLE_EXPR(marker_sample, mSampleData.GetMarker(_msg->Int(2)).sample)
    HANDLE_EXPR(sample_length, LengthMs() / 1000.0f)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x121)
END_HANDLERS

BEGIN_PROPSYNCS(SynthSample)
    SYNC_PROP_MODIFY_ALT(file, mFile, Sync(sync0))
    SYNC_PROP_MODIFY(looped, mIsLooped, Sync(sync1))
    SYNC_PROP_MODIFY(loop_start_sample, mLoopStartSamp, Sync(sync1))
    SYNC_PROP_MODIFY(loop_end_sample, mLoopEndSamp, Sync(sync1))
    SYNC_PROP_SET(sample_rate, mSampleData.mSampleRate, MILO_WARN("can't set property %s", "sample_rate"))
    SYNC_PROP(markers, mSampleData.mMarkers)
END_PROPSYNCS