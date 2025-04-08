#pragma once
#include "utl/BinStream.h"
#include "utl/TempoMap.h"
#include "utl/ChunkIDs.h"
#include <vector>

struct MidiMessage {
    unsigned int wMsg;
    unsigned long dwParam1;
    unsigned long dwParam2;
    unsigned int wTimeMs;
};

class MidiReader;
class MidiReceiver;
class MeasureMap;

class MidiChunkID : public ChunkID {
public:
    MidiChunkID(BinStream &bs) : ChunkID(bs) {}
    MidiChunkID(const char *str) : ChunkID(str) {}
    static MidiChunkID kMThd;
    static MidiChunkID kMTrk;
};

class MidiChunkHeader {
public:
    MidiChunkHeader(BinStream &bs) : mID(bs) {
        mLength = 0;
        bs >> mLength;
    }
    unsigned int Length() const { return mLength; }

    // total size: 0x8
    MidiChunkID mID; // offset 0x0, size 0x4
    unsigned int mLength; // offset 0x4, size 0x4
};

/** Handles information from a MIDI file. */
class MidiReceiver {
public:
    MidiReceiver();
    virtual ~MidiReceiver() {}
    virtual void OnNewTrack(int) = 0;
    virtual void OnEndOfTrack() = 0;
    virtual void OnAllTracksRead() = 0;
    virtual void OnMidiMessage(int, unsigned char, unsigned char, unsigned char) = 0;
    virtual void OnText(int, const char *, unsigned char) = 0;
    virtual void OnTempo(int, int) {}
    virtual void OnTimeSig(int, int, int) {}
    virtual bool OnAcceptMaps(TempoMap *, MeasureMap *) { return false; }
    virtual void SetMidiReader(MidiReader *mr) { mReader = mr; }

    /** Print a midi validation error message to the console.
     * @param [in] msg The message to print.
     * @param [in] tick The tick in the midi where this error occurs.
     */
    void Error(const char *msg, int tick);

    /** Skip the current track being parsed. */
    void SkipCurrentTrack();

    MidiReader *GetMidiReader() const { return mReader; }

private:
    /** Reads the midi information. */
    MidiReader *mReader; // 0x4
};

/** Reads information from a .mid file. */
class MidiReader {
public:
    enum State {
        /** Reading from the very start of the .mid. */
        kStart = 0,
        /** Reading a new track within the .mid. */
        kNewTrack = 1,
        /** Currently reading a track of the .mid. */
        kInTrack = 2,
        /** Reading is complete. */
        kEnd = 3,
    };
    struct Midi {
        // the status byte
        unsigned char mStat; // 0x0
        // data1
        unsigned char mD1; // 0x1
        // data2
        unsigned char mD2; // 0x2
    };

    MidiReader(BinStream &, MidiReceiver &, const char *);
    ~MidiReader();
    /** Read all tracks in the midi. */
    void ReadAllTracks();
    /** Read the next num_events tracks in the midi.
     * @param [in] num_events The number of tracks to read.
     * @returns True if we've read to the end, false if not.
     */
    bool ReadSomeEvents(int num_events);
    /** Get the midi's file name. */
    const char *GetFilename() const;
    /** Skip reading the current track. */
    void SkipCurrentTrack();

    /** Print a midi validation error message to the console.
     * @param [in] msg The message to print.
     */
    void Error(const char *msg) { mRcvr.Error(msg, mCurTick); }

    bool Fail() const { return mFail; }
    class MultiTempoTempoMap *GetTempoMap() const { return mTempoMap; }
    class MeasureMap *GetMeasureMap() const { return mMeasureMap; }
    const char *CurrentTrackName() const { return mCurTrackName.c_str(); }

    static bool sVerify;

private:
    /** Initialize the MidiReader's tempo and measure maps, and the MidiReceiver. */
    void Init();
    /** Safely read the next event. */
    void ReadNextEvent();
    /** Implementation to read the next event. */
    void ReadNextEventImpl();
    /** Read a midi event from the stream. */
    void ReadEvent(BinStream &);
    /** Read this track's header from the stream. */
    void ReadTrackHeader(BinStream &);
    /** Read the midi's file header from the stream. */
    void ReadFileHeader(BinStream &);
    void ProcessMidiList();
    void ReadMidiEvent(int, unsigned char, unsigned char, BinStream &);
    /** Read a SysEx event.
     * @param [in] tick The tick this event occurs at.
     * @param [in] type The SysEx event type.
     * @param [in] stream The stream to read from.
     */
    void ReadSystemEvent(int tick, unsigned char type, BinStream &stream);
    /** Read a meta event.
     * @param [in] tick The tick this event occurs at.
     * @param [in] type The meta event type.
     * @param [in] stream The stream to read from.
     */
    void ReadMetaEvent(int tick, unsigned char type, BinStream &stream);
    void QueueChannelMsg(int, unsigned char, unsigned char, unsigned char);
    /** Read the next track from the midi.
     @returns True if another track is up next, false if we've reached the end of the
     file.
    */
    bool ReadTrack();

    /** The stream containing the midi. */
    class BinStream *mStream; // offset 0x0, size 0x4
    /** Whether or not this MidiReader created the midi stream. */
    bool mStreamCreatedHere; // offset 0x4, size 0x1
    /** The .mid's filename. */
    class String mStreamName; // offset 0x8, size 0xC
    /** The MidiReceiver that will handle the info being read. */
    class MidiReceiver &mRcvr; // offset 0x14, size 0x4
    /** The current reading state. */
    State mState; // offset 0x18, size 0x4
    /** The number of tracks in the midi. */
    signed short mNumTracks; // offset 0x1C, size 0x2
    /** The midi's ticks per quarter note - must be 480. */
    signed short mTicksPerQuarter; // offset 0x1E, size 0x2
    /** The TPQN we want - 480. */
    signed short mDesiredTPQ; // offset 0x20, size 0x2
    int mTrackEndPos; // offset 0x24, size 0x4
    /** The current track index the reader is on. */
    int mCurTrackIndex; // offset 0x28, size 0x4
    /** The current tick the reader is on. */
    int mCurTick; // offset 0x2C, size 0x4
    unsigned char mPrevStatus; // offset 0x30, size 0x1
    /** The name of the current track we're reading. */
    class String mCurTrackName; // offset 0x34, size 0xC
    /** The list of track names in the midi. */
    std::vector<String> mTrackNames; // 0x40
    std::vector<Midi> mMidiList; // 0x48
    int mMidiListTick; // 0x50
    /** The sort function to use for the read midi list. */
    bool (*mLessFunc)(const struct Midi &, const struct Midi &); // 0x54
    /** Is this MidiReader the owner of its tempo and measure maps? */
    bool mOwnMaps; // 0x58
    /** The tempo map associated with this midi. */
    class MultiTempoTempoMap *mTempoMap; // 0x5c
    /** The measure map associated with this midi. */
    class MeasureMap *mMeasureMap; // 0x60
    /** Did this midi fail to read properly? */
    bool mFail; // 0x64
};