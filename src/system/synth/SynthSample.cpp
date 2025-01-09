#include "synth/SynthSample.h"
#include "synth/Utl.h"
#include "utl/BufStream.h"
#include "obj/ObjVersion.h"
#include "utl/Symbols.h"

INIT_REVS(SynthSample)

void* SynthSample::SampleAlloc(int i, const char*){
    return _MemAlloc(i, 0x20);
}

void SynthSample::SampleFree(void* v){ _MemFree(v); }

void SynthSample::Init(){
    Register();
    SampleData::SetAllocator(SampleAlloc, SampleFree);
}

SynthSample::SynthSample() : mIsLooped(0), mLoopStartSamp(0), mLoopEndSamp(-1), mFileLoader(0) {

}

SynthSample::~SynthSample(){
    RELEASE(mFileLoader);
}

int SynthSample::GetSampleRate() const { return mSampleData.GetSampleRate(); }
SampleData::Format SynthSample::GetFormat() const { return mSampleData.GetFormat(); }
bool SynthSample::GetIsLooped() const { return mIsLooped; }
int SynthSample::GetLoopStartSamp() const { return mLoopStartSamp; }

void SynthSample::Sync(SynthSample::SyncType ty){
    if(ty == sync3){
        void* buf = (void*)mFileLoader->GetBuffer(0);
        int size = mFileLoader->GetSize();
        RELEASE(mFileLoader);
        BufStream bufs(buf, size, true);
        mSampleData.Load(bufs, mFile);
        if(buf) _MemFree(buf);
    }
    else if(ty == sync0){
        mSampleData.Reset();
        if(!mFile.empty()){
            FileLoader* fl = dynamic_cast<FileLoader*>(TheLoadMgr.ForceGetLoader(mFile));
            const char* buf;
            int size;
            if(fl) buf = fl->GetBuffer(&size);
            else buf = 0;
            delete fl;
            if(buf){
                BufStream bufs((void*)buf, size, true);
                if(TheLoadMgr.GetPlatform() == kPlatformPC){
                    mSampleData.LoadWAV(bufs, mFile);
                }
                else mSampleData.Load(bufs, mFile);
                delete buf;
            }
        }
    }
}

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
    if(!bs.Cached() || gRev < 5){
        if (gRev > 3) {
            mFileLoader = dynamic_cast<FileLoader*>(TheLoadMgr.AddLoader(mFile, kLoadFront));
        }
    }
    else if (gAltRev != 0) {
        CacheResourceResult res;
        mFileLoader = new FileLoader(mFile, CacheWav(mFile.c_str(), res), kLoadFront, 0, false, true, &bs);
    }
    else mSampleData.Load(bs, mFile);
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
    HANDLE_EXPR(marker_sample, mSampleData.GetMarker(_msg->Int(2)).Sample())
    HANDLE_EXPR(sample_length, LengthMs() / 1000.0f)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x121)
END_HANDLERS

BEGIN_PROPSYNCS(SynthSample)
    SYNC_PROP_MODIFY_ALT(file, mFile, Sync(sync0))
    SYNC_PROP_MODIFY(looped, mIsLooped, Sync(sync1))
    SYNC_PROP_MODIFY(loop_start_sample, mLoopStartSamp, Sync(sync1))
    SYNC_PROP_MODIFY(loop_end_sample, mLoopEndSamp, Sync(sync1))
    SYNC_PROP_SET(sample_rate, mSampleData.GetSampleRate(), MILO_WARN("can't set property %s", "sample_rate"))
    SYNC_PROP(markers, mSampleData.mMarkers)
END_PROPSYNCS

int SynthSample::GetPlatformSize(Platform plat){
    return mSampleData.SizeAs(SampleData::kPCM);
}

DECOMP_FORCEACTIVE(SynthSample, "%i kB", "%i blocks")
