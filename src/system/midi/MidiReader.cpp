#include "midi/Midi.h"
#include "os/Debug.h"
#include "utl/Chunks.h"
#include "utl/MultiTempoTempoMap.h"
#include "utl/MeasureMap.h"

MidiChunkID MidiChunkID::kMThd("MThd");
MidiChunkID MidiChunkID::kMTrk("MTrk");
bool MidiReader::sVerify = false;

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
        MILO_ASSERT(!mStream->LittleEndian(), 0xAA);
        Init();
}

// fn_80533C30
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

// fn_80533EC0
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

void MidiReader::ReadNextEvent(){
    if (sVerify != 0) {
        MILO_TRY {
            ReadNextEventImpl();
        } MILO_CATCH(errMsg) {
            Error(errMsg);
            mFail = true;
        }
    } else {
        ReadNextEventImpl();
    }
}

// fn_80533f70
void MidiReader::ReadNextEventImpl(){
    if(mFail) return;
    switch(mState){
        case kInTrack:
            ReadEvent(*mStream);
            return;
        case kNewTrack:
            ReadTrackHeader(*mStream);
            return;
        case kStart:
            ReadFileHeader(*mStream);
            return;
        default:
            break;
    }
}

// fn_80533FB8
void MidiReader::ReadFileHeader(BinStream& bs){
    MILO_ASSERT(mState == kStart, 0x146);
    MidiChunkHeader header(bs);
    bool kmthdcmp = strncmp(header.mID.Str(), MidiChunkID::kMThd.Str(), 4) == 0;
    if(!kmthdcmp || header.mLength != 6U){
        MILO_WARN("%s: MIDI file header is corrupt", mStreamName.c_str());
    }
    short midiType;
    bs >> midiType;
    if(midiType != 1){
        MILO_WARN("%s: Only type 1 MIDI files are supported; this file is type %d", mStreamName.c_str(), midiType);
    }
    bs >> mNumTracks;
    if(mNumTracks <= 0){
        MILO_WARN("%s: MIDI file has no tracks", mStreamName.c_str());
    }
    else {
        mTrackNames.resize(mNumTracks, String(""));
    }
    bs >> mTicksPerQuarter;
    if(mTicksPerQuarter & 0x8000U){
        MILO_WARN("%s: MIDI file uses SMPTE time division; this is not allowed", mStreamName.c_str());
    }
    if(mTicksPerQuarter != 480){
        MILO_WARN("%s: Time division must be 480 ticks per quarter; this file is %d ticks per quarter", mStreamName.c_str(), mTicksPerQuarter);
    }

    if(mNumTracks != 0 && midiType == 1 && !(mTicksPerQuarter & 0x8000U) && mTicksPerQuarter != 480){
        mFail = true;
        return;
    }
    mState = kNewTrack;
}

// fn_805341B0
void MidiReader::ReadTrackHeader(BinStream& bs){
    MILO_ASSERT(mState == kNewTrack, 0x180);
    MidiChunkHeader header(bs);
    if(!CheckChunkID(header.mID.Str(), MidiChunkID::kMTrk.Str())){
        MILO_WARN("%s: MIDI track header for track %d is corrupt", mStreamName.c_str(), mCurTrackIndex);
        mFail = true;
    }
    else {
        mTrackEndPos = bs.Tell() + header.mLength;
        mCurTrackIndex++;
        mPrevStatus = 0;
        mCurTick = 0;
        mMidiListTick = -1;
        mState = kInTrack;
        mRcvr.OnNewTrack(mCurTrackIndex - 1);
    }
}

// void fn_805341B0(int param_1,int *param_2)

// {
//   int iVar1;
//   int iVar2;
//   int iVar3;
//   JsonObject aJStack_18 [12];
  
//   fn_80534130(aJStack_18);
//   iVar1 = fn_80534108(aJStack_18,&lbl_80987EA4);
//   if (iVar1 == 0) {
//     iVar1 = JsonObject::GetJsonObjectStruct(aJStack_18);
//     iVar2 = (**(code **)(*param_2 + 0x10))(param_2);
//     iVar3 = *(int *)(param_1 + 0x28);
//     *(int *)(param_1 + 0x24) = iVar2 + iVar1;
//     *(int *)(param_1 + 0x28) = iVar3 + 1;
//     *(undefined *)(param_1 + 0x30) = 0;
//     *(undefined4 *)(param_1 + 0x2c) = 0;
//     *(undefined4 *)(param_1 + 0x50) = 0xffffffff;
//     *(undefined4 *)(param_1 + 0x18) = 2;
//     (**(code **)(**(int **)(param_1 + 0x14) + 0xc))(*(int **)(param_1 + 0x14),iVar3);
//   }
//   else {
//     String::c_str((String *)(param_1 + 8));
//     *(undefined *)(param_1 + 100) = 1;
//   }
//   return;
// }

// fn_80534280 - read event(binstream&)