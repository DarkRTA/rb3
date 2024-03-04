#ifndef MIDI_MIDI_H
#define MIDI_MIDI_H
#include "utl/BinStream.h"
#include "utl/TempoMap.h"
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

struct Midi {
    unsigned char mStat;
    unsigned char mD1;
    unsigned char mD2;
};

class MidiReader {
    // total size: 0x60
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
    std::vector<Midi> mMidiList; // offset 0x40, size 0xC
    int mMidiListTick; // offset 0x4C, size 0x4
    bool (* mLessFunc)(struct Midi &, struct Midi &); // offset 0x50, size 0x4
    bool mOwnMaps; // offset 0x54, size 0x1
    class MultiTempoTempoMap * mTempoMap; // offset 0x58, size 0x4
    class MeasureMap * mMeasureMap; // offset 0x5C, size 0x4
    bool mFail; // added for RB3
};

class MidiReceiver {
public:
    MidiReceiver();
    virtual ~MidiReceiver();
    virtual void OnNewTrack(int) = 0;
    virtual void OnEndOfTrack() = 0;
    virtual void OnAllTracksRead() = 0;
    virtual void OnMidiMessage(int, unsigned char, unsigned char, unsigned char) = 0;
    virtual void OnText(int, const char*, unsigned char) = 0;
    virtual void OnTempo(int, int);
    virtual void OnTimeSig(int, int, int);
    virtual bool OnAcceptMaps(TempoMap*, MeasureMap*);
    virtual void SetMidiReader(MidiReader*);

    void Error(const char*, int);
    void SkipCurrentTrack();

    MidiReader* mReader;
};

#endif
