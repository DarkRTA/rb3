#ifndef MIDI_MIDI_H
#define MIDI_MIDI_H
#include "utl/BinStream.h"
#include "utl/TempoMap.h"
#include "utl/ChunkIDs.h"
#include <vector>

class MidiReader;
class MidiReceiver;
class MeasureMap;

enum State {
    kStart = 0,
    kNewTrack = 1,
    kInTrack = 2,
    kEnd = 3,
};

class MidiChunkID : public ChunkID {
public:
    MidiChunkID(const char* str) : ChunkID(str) {}
    static MidiChunkID kMThd;
    static MidiChunkID kMTrk;
};

class MidiReader {
public:
    struct Midi {
        unsigned char mStat;
        unsigned char mD1;
        unsigned char mD2;
    };

    MidiReader(BinStream&, MidiReceiver&, const char*);
    ~MidiReader();
    void Init();
    const char* GetFilename() const;
    void SkipCurrentTrack();

    class BinStream * mStream; // offset 0x0, size 0x4
    bool mStreamCreatedHere; // offset 0x4, size 0x1
    class String mStreamName; // offset 0x8, size 0xC
    class MidiReceiver & mRcvr; // offset 0x14, size 0x4
    State mState; // offset 0x18, size 0x4
    signed short mNumTracks; // offset 0x1C, size 0x2
    signed short mTicksPerQuarter; // offset 0x1E, size 0x2
    signed short mDesiredTPQ; // offset 0x20, size 0x2
    int mTrackEndPos; // offset 0x24, size 0x4
    int mCurTrackIndex; // offset 0x28, size 0x4
    int mCurTick; // offset 0x2C, size 0x4
    unsigned char mPrevStatus; // offset 0x30, size 0x1
    class String mCurTrackName; // offset 0x34, size 0xC
    std::vector<String> mTrackNames;
    std::vector<Midi> mMidiList; 
    int mMidiListTick; 
    bool (* mLessFunc)(const struct Midi &, const struct Midi &); 
    bool mOwnMaps;
    class MultiTempoTempoMap * mTempoMap; 
    class MeasureMap * mMeasureMap;
    bool mFail;
};

class MidiReceiver {
public:
    MidiReceiver();
    virtual ~MidiReceiver(){}
    virtual void OnNewTrack(int) = 0;
    virtual void OnEndOfTrack() = 0;
    virtual void OnAllTracksRead() = 0;
    virtual void OnMidiMessage(int, unsigned char, unsigned char, unsigned char) = 0;
    virtual void OnText(int, const char*, unsigned char) = 0;
    virtual void OnTempo(int, int){}
    virtual void OnTimeSig(int, int, int){}
    virtual bool OnAcceptMaps(TempoMap*, MeasureMap*){ return false; }
    virtual void SetMidiReader(MidiReader* mr){ mReader = mr; }

    void Error(const char*, int);
    void SkipCurrentTrack();

    MidiReader* mReader;
};

#endif
