#include "midi/Midi.h"
#include "os/Debug.h"
#include "math/MathFuncs.h"
#include "utl/Chunks.h"
#include "utl/MultiTempoTempoMap.h"
#include "utl/MeasureMap.h"
#include "midi/MidiConstants.h"
#include "midi/MidiVarLen.h"
#include "utl/MBT.h"
#include <algorithm>

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
    if(mNumTracks == 0 || midiType != 1 || (mTicksPerQuarter & 0x8000U) || mTicksPerQuarter != 480){
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
        int headerlen = header.mLength;
        int tell = bs.Tell();
        mTrackEndPos = tell + headerlen;
        mCurTrackIndex++;
        mPrevStatus = 0;
        mCurTick = 0;
        mMidiListTick = -1;
        mState = kInTrack;
        mRcvr.OnNewTrack(mCurTrackIndex - 1);
    }
}

// fn_80534280
void MidiReader::ReadEvent(BinStream& bs){
    bool b;
    MILO_ASSERT(mState == kInTrack, 0x19E);
    MidiVarLenNumber num(bs);
    mCurTick += num.mValue;
    int tpq = mCurTick * mDesiredTPQ / mTicksPerQuarter;
    if(tpq != mMidiListTick){
        ProcessMidiList();
        if(mState != kInTrack) return;
        mMidiListTick = tpq;
    }
    unsigned char midichar;
    unsigned char nextchar;
    bs >> midichar;
    if(MidiIsStatus(midichar)){
        b = false;
        if(!MidiIsSystem(midichar)) mPrevStatus = midichar;
    }
    else {
        b = true;
        nextchar = midichar;
        midichar = mPrevStatus;
    }
    if(MidiIsSystem(midichar)){
        ReadSystemEvent(tpq, midichar, bs);
    }
    else {
        if(!b) bs >> nextchar;
        ReadMidiEvent(tpq, midichar, nextchar, bs);
    }
}

// fn_805343A4
void MidiReader::ReadMidiEvent(int tick, unsigned char status, unsigned char data1, BinStream& bs){
    int bit = status & 0xF0;
    unsigned char uc;
    bool queue = false;
    switch(bit){
        case 0x90: bs >> uc; queue = true;
            if(uc == 0) status = status & 0xF | 0x80;
            break;
        case 0x80: bs >> uc; queue = true; break;
        case 0xB0: bs >> uc; queue = true; break;
        case 0xE0: case 0xA0: bs >> uc; break;
        case 0xC0: case 0xD0: uc = 0; break;
        default:
            MILO_WARN("%s (%s): Cannot parse event %i", mStreamName.c_str(), mCurTrackName.c_str(), bit);
            break;
    }
    if(queue) QueueChannelMsg(tick, status, data1, uc);
}

// fn_805344C0
void MidiReader::ReadSystemEvent(int i, unsigned char uc, BinStream& bs){
    switch(uc){
        case 0xF0:
        case 0xF7: {
            MidiVarLenNumber num(bs);
            bs.Seek(num.mValue, BinStream::kSeekCur);
            break;
        }
        case 0xFF: {
            unsigned char read;
            bs >> read;
            ReadMetaEvent(i, read, bs);
            break;
        }
        default:
            MILO_WARN("%s (%s): Cannot parse system event %i", mStreamName.c_str(), mCurTrackName.c_str(), uc);
            break;
    }
}

// fn_80534568
void MidiReader::ReadMetaEvent(int i, unsigned char uc, BinStream& bs){
    MidiVarLenNumber num(bs);
    unsigned int numVal = num.mValue;
    int oldtell = bs.Tell();

    switch(uc){
        case 0x1:
        case 0x2:
        case 0x3:
        case 0x5: {
            char buf[0x100];
            if(numVal >= 0x100){
                bs.Read(buf, 8);
                buf[8] = 0;
                MILO_WARN("%s (%s): Text event beginning with '%s' at %s exceeds maximum allowed length of %d characters",
                    mStreamName.c_str(), mCurTrackName.c_str(), buf, TickFormat(0, *mMeasureMap), 0xFFul);
            }
            else {
                bs.Read(buf, numVal);
                buf[numVal] = 0;
                if(uc == 3){
                    if(i != 0){
                        MILO_WARN("%s (%s): MIDI track name event must appear at %s; found track name '%s' at %s",
                            mStreamName.c_str(), buf, TickFormat(0, *mMeasureMap), buf, TickFormat(i, *mMeasureMap));
                        mFail = true;
                        return;
                    }
                    String& str = mTrackNames[mCurTrackIndex - 1];
                    if(str.empty()) str = buf;
                    else if(str != buf){
                        MILO_WARN("%s (%s): Track contains multiple track name events (%s and %s)",
                            mStreamName.c_str(), str.c_str(), str.c_str(), buf);
                        mFail = true;
                        return;
                    }
                    mCurTrackName = buf;
                }
                mRcvr.OnText(i, buf, uc);
            }
            break;
        }
        case 0x51: {
            unsigned char c,b,a;
            bs >> c >> b >> a;
            int product = a + c * 0x10000 + b * 0x100;
            if(product < 200000){
                MILO_WARN("%s (%s): Tempo marker at %s (%f bpm) is too fast; maximum is 300 bpm",
                    mStreamName.c_str(), mCurTrackName.c_str(), TickFormat(i, *mMeasureMap), 6e+07f / (float)product);
            }
            if(product > 1500000){
                MILO_WARN("%s (%s): Tempo marker at %s (%f bpm) is too slow; minimum is 40 bpm",
                    mStreamName.c_str(), mCurTrackName.c_str(), TickFormat(i, *mMeasureMap), 6e+07f / (float)product);
            }
            if(mTempoMap->AddTempoInfoPoint(i, product)){
                mRcvr.OnTempo(i, product);
            }
            else {
                MILO_WARN("%s (%s): Tempo marker at %s (%.f bpm) conflicts with other tempo markers",
                    mStreamName.c_str(), mCurTrackName.c_str(), TickFormat(i, *mMeasureMap), 6e+07f / (float)product);
            }
            break;
        }
        case 0x2F: {
            ProcessMidiList();
            if(mCurTrackIndex == mNumTracks){
                mState = kEnd;
                mRcvr.OnEndOfTrack();
                mRcvr.OnAllTracksRead();
            }
            else {
                mState = kNewTrack;
                if(mCurTrackIndex == 1 && mOwnMaps){
                    mOwnMaps = mRcvr.OnAcceptMaps(mTempoMap, mMeasureMap) == 0;
                }
                mRcvr.OnEndOfTrack();
            }
            break;
        }
        case 0x58: {
            unsigned char ts_num, ts_den;
            bs >> ts_num >> ts_den;
            if(ts_den > 6){
                MILO_WARN("%s (%s): Time signature at %s has invalid denominator (2^%d); max is 64 (2^6)",
                    mStreamName.c_str(), mCurTrackName.c_str(), TickFormat(i, *mMeasureMap), ts_den);
            }
            else {
                double base = 2;
                int powed = std::pow(base, ts_den);
                if(ts_num == 0){
                    MILO_WARN("%s (%s): Time signature %d/%d at %s has invalid numerator (%d)",
                        mStreamName.c_str(), mCurTrackName.c_str(), ts_num, powed, TickFormat(i, *mMeasureMap), ts_num);
                }
                int ts_m, ts_b, ts_t;
                mMeasureMap->TickToMeasureBeatTick(i, ts_m, ts_b, ts_t);
                if(mMeasureMap->AddTimeSignature(ts_m, ts_num, powed, true)){
                    mRcvr.OnTimeSig(i, ts_num, powed);
                }
                else {
                    MILO_WARN("%s (%s): Time signature %d/%d at %s overlaps or conflicts with nearby time signatures",
                        mStreamName.c_str(), mCurTrackName.c_str(), ts_num, powed, TickFormat(i, *mMeasureMap));
                }
                bs.Seek(2, BinStream::kSeekCur);
            }
            break;
        }
        case 4:
        case 6:
        case 7:
        case 0x20:
        case 0x21:
        case 0x54:
        case 0x59:
            break;
        default:
            MILO_WARN("%s (%s): Cannot parse meta event %i", mStreamName.c_str(), mCurTrackName.c_str(), uc);
            break;
    }
    if(mState == kInTrack) bs.Seek(oldtell + numVal, BinStream::kSeekBegin);
}

void MidiReader::QueueChannelMsg(int i, unsigned char uc1, unsigned char uc2, unsigned char uc3){
    if(!mLessFunc){
        mRcvr.OnMidiMessage(i, uc1, uc2, uc3);
    }
    else {
        Midi mid;
        mid.mStat = uc1;
        mid.mD1 = uc2;
        mid.mD2 = uc3;
        mMidiList.push_back(mid);
    }
}

void MidiReader::ProcessMidiList(){
    std::sort(mMidiList.begin(), mMidiList.end(), mLessFunc);
    for(std::vector<Midi>::iterator it = mMidiList.begin(); it != mMidiList.end(); it++){
        mRcvr.OnMidiMessage(mMidiListTick, (*it).mStat, (*it).mD1, (*it).mD2);
        if(mState != kInTrack) break;
    }
    mMidiList.clear();
}
