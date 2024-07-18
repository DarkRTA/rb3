#include "synth/SampleData.h"
#include "os/PlatformMgr.h"
#include "utl/ChunkStream.h"
#include "utl/WaveFile.h"

SampleDataAllocFunc SampleData::sAlloc = 0;
SampleDataFreeFunc SampleData::sFree = 0;
BinStream& operator>>(BinStream& bs, SampleMarker& m);

DECOMP_FORCEACTIVE(SampleData, __FILE__, "0")

void SampleData::SetAllocator(SampleDataAllocFunc a, SampleDataFreeFunc f){
    sAlloc = a;
    sFree = f;
}

SampleData::SampleData() : mData(0), mMarkers() {
    Reset();
}

SampleData::~SampleData(){
    sFree(mData);
}

void SampleData::Load(BinStream& bs, const FilePath& fp){
    Reset();
    int rev;
    bs >> rev;
    if(rev > 0xE){
        if(rev - 0x3e9U <= 0x24606){
            MILO_LOG("%s: loading old cached sample\n", fp);
            mSampleRate = rev;
            bs >> mSizeBytes;
            mFormat = kBigEndPCM;
            mNumSamples = mSizeBytes / 2;
            mData = sAlloc(mSizeBytes, fp.c_str());
            MILO_ASSERT(!((uint)mData & 31), 0x6A);
            bs.Read(mData, mSizeBytes);
        }
        else MILO_WARN("can't load new SampleData: %s", fp);
    }
    else {
        int fmt;
        bs >> fmt >> mNumSamples >> mSampleRate >> mSizeBytes;
        bool b = true;
        mFormat = (Format)fmt;
        if(rev >= 0xB){
            bs >> b;
        }
        if(b){
            if(ThePlatformMgr.mEnableSFX){
                mData = sAlloc(mSizeBytes, fp.c_str());
                ReadChunks(bs, mData, mSizeBytes, 0x8000);
            }
            else {
                bs.Seek(mSizeBytes, BinStream::kSeekCur);
                mNumSamples = 0;
                mSizeBytes = 0;
                mData = 0;
            }
        }
        if(rev >= 0xE) bs >> mMarkers;
    }
}

void SampleData::LoadWAV(BinStream& bs, const FilePath& fp){
    Reset();
    WaveFile wav(bs);
    if(wav.mNumChannels != 1) MILO_WARN("Wave file %s has multiple channels", fp);
    else if(wav.mBitsPerSample != 0x10) MILO_WARN("Wave file %s is not 16-bit", fp);
    else if(wav.mSamplesPerSec != 1) MILO_WARN("Wave file %s is compressed", fp);
    else {
        mFormat = kPCM;
        mNumSamples = wav.mNumSamples;
        mSampleRate = wav.mSamplesPerSec;
        mSizeBytes = SizeAs(kPCM);
        mData = sAlloc(mSizeBytes, fp.c_str());
        WaveFileData wavdata(wav);
        wavdata.Read(mData, mSizeBytes);
        for(int i = 0; i < wav.mMarkers.size(); i++){
            // mMarkers.push_back(wav.mMarkers[i]);
        }
    }
}

DECOMP_FORCEACTIVE(SampleData, "size % 192 == 0")

void SampleData::Reset(){
    sFree(mData);
    mData = 0;
    mFormat = kPCM;
    mSizeBytes = 0;
    mSampleRate = 0;
    mNumSamples = 0;
    mMarkers.clear();
}

int SampleData::SizeAs(Format fmt) const {
    switch(fmt){
        case kPCM:
            return mNumSamples * 2;
        case kBigEndPCM:
            return mNumSamples * 2;
        case kVAG:
            int tmp = (mNumSamples + 0x6F) / 0x70 + (mNumSamples + 0x6F >> 0x1F);
            return (tmp - (tmp >> 0x1F)) * 0x40;
        case kATRAC:
            int tmpa = mNumSamples + 0x3FF;
            return (tmpa >> 10) + (tmpa < 0 && (tmpa & 0x3FF) != 0) * 0xC0;
        case kMP3:
            int tmpm = mNumSamples + 0x3FF;
            return (tmpm >> 10) + (tmpm < 0 && (tmpm & 0x3FF) != 0) * 0xC0;
        case kXMA:
            MILO_WARN("don't know size as XMA");
            int tmpx = mNumSamples / 5 + (mNumSamples >> 0x1F);
            return tmpx - (tmpx >> 0x1F);
        case kNintendoADPCM:
            return ((mNumSamples * 2) / 3.4f) + 0x60;
        default:
            MILO_ASSERT(0, 0x136);
            return 0;
    }
}

int SampleData::NumMarkers() const { return mMarkers.size(); }
const SampleMarker& SampleData::GetMarker(int i) const { return mMarkers[i]; }

BinStream& operator>>(BinStream& bs, SampleMarker& m){
    bs >> m.name;
    bs >> m.sample;
    return bs;
}