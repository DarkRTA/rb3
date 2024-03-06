#include "midi/Midi.h"
#include "os/Debug.h"
#include "utl/MultiTempoTempoMap.h"
#include "utl/MeasureMap.h"

MidiChunkID MidiChunkID::kMThd("MThd");
MidiChunkID MidiChunkID::kMTrk("MTrk");

namespace {
    bool DefaultMidiLess(const MidiReader::Midi& m1, const MidiReader::Midi& m2){
        int ui1, ui2;
        switch(m1.mStat & 0xF0){
            case 0x80: ui1 = 1; break;
            case 0xB0: ui1 = 2; break;
            case 0xC0: ui1 = 3; break;
            case 0xD0: ui1 = 4; break;
            case 0xE0: ui1 = 5; break;
            case 0xA0: ui1 = 6; break;
            case 0x90: ui1 = 7; break;
            default: ui1 = 8; break;
        }
        switch(m2.mStat & 0xF0){
            case 0x80: ui2 = 1; break;
            case 0xB0: ui2 = 2; break;
            case 0xC0: ui2 = 3; break;
            case 0xD0: ui2 = 4; break;
            case 0xE0: ui2 = 5; break;
            case 0xA0: ui2 = 6; break;
            case 0x90: ui2 = 7; break;
            default: ui2 = 8; break;
        }
        return ui1 < ui2;
    }
}

MidiReader::MidiReader(BinStream& bs, MidiReceiver& rec, const char* name) : mStream(&bs), mStreamCreatedHere(0), mStreamName(name), 
    mRcvr(rec), mState(kStart), mNumTracks(0), mTicksPerQuarter(0), mDesiredTPQ(480), mCurTrackIndex(0), mCurTick(0), mPrevStatus(0), mCurTrackName(),
    mMidiListTick(0), mLessFunc(DefaultMidiLess), mFail(0) {
        MILO_ASSERT(!mStream->mLittleEndian, 0xAA);
        Init();
}

void MidiReader::Init(){
    mOwnMaps = true;
    mTempoMap = new MultiTempoTempoMap();
    mMeasureMap = new MeasureMap();
    mRcvr.SetMidiReader(this);
}

MidiReader::~MidiReader(){
    if(mStreamCreatedHere) delete mStream;
    if(mOwnMaps){
        delete mTempoMap;
        delete mMeasureMap;
    }
}

void MidiReader::ReadAllTracks(){
    if(mStream->Tell() != 0){
        mStream->Seek(0, BinStream::kSeekBegin);
    }
    while(ReadTrack());
}

bool MidiReader::ReadSomeEvents(int cnt){
    for(int i2 = 0; i2 < cnt; i2++){
        ReadNextEvent();
        if(mState == kEnd || mFail) return true;
    }
    return false;
}

bool MidiReader::ReadTrack(){
    do {
        ReadNextEvent();
        if(mState == kEnd || mState == kNewTrack) break;
    } while(!mFail);
    return mState == kNewTrack;
}

void MidiReader::SkipCurrentTrack(){
    if(mState == kInTrack){
        if(mCurTrackIndex == mNumTracks){
            mState = kEnd;
            mRcvr.OnEndOfTrack();
            mRcvr.OnAllTracksRead();
        }
        else {
            mState = kNewTrack;
            mStream->Seek(mTrackEndPos, BinStream::kSeekBegin);
            mRcvr.OnEndOfTrack();
        }
    }
}

const char* MidiReader::GetFilename() const {
    return mStreamName.c_str();
}
