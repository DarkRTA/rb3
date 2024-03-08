#ifndef MIDI_MIDIPARSER_H
#define MIDI_MIDIPARSER_H

#include "obj/MsgSource.h"
#include "midi/DataEvent.h"
#include <list>

class MidiParser : public MsgSource { // 0xd0
public: 
    struct PostProcess {
        PostProcess();
        bool zeroLength;
        float startOffset;
        float endOffset;
        float minLength;
        float maxLength;
        float minGap;
        float maxGap;
        bool useRealtimeGaps;
        float variableBlendPct;
    };

    struct Note {

    };

    MidiParser();
    virtual ~MidiParser();

    void Clear();
    void Reset(float);

    DataEventList* mEvents;
    Symbol mTrackName;
    DataArray* mGemParser;
    DataArray* mNoteParser;
    DataArray* mTextParser;
    DataArray* mLyricParser;
    DataArray* mIdleParser;
    DataArray* mCurParser;
    DataArray* mAllowedNotes;
    // vector* mVocalEvents;
    // vector mNotes;
    // GemListInterface* mGems;
    bool mInverted;
    PostProcess mProcess;
    float mLastStart;
    float mLastEnd;
    float mFirstEnd;
    DataEvent* mEvent;
    Symbol mMessageType;
    bool mAppendLength;
    bool mUseVariableBlending;
    float mVariableBlendPct;
    bool mMessageSelf;
    bool mCompressed;
    int mGemIndex;
    int mNoteIndex;
    int mVicalIndex;
    float mStart;
    int mBefore;

    static Hmx::Object* NewObject();
    static void Init();

    static std::list<MidiParser> sParsers;
};

#endif // MIDI_MIDIPARSER_H
