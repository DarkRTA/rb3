#ifndef MIDI_MIDIPARSER_H
#define MIDI_MIDIPARSER_H
#include "obj/MsgSource.h"
#include "midi/DataEvent.h"
#include <vector>
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
        int mNoteNum;
        float mVolume;
        std::vector<int> mSamples;
        std::vector<int> mTransposes;
    };

    MidiParser();
    OBJ_CLASSNAME(MidiParser);
    OBJ_SET_TYPE(MidiParser);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual ~MidiParser();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Export(DataArray*, bool);
    virtual void SetTypeDef(DataArray*);

    void Clear();
    void Reset(float);
    bool InsertIdle(float, int);
    bool AllowedNote(int);
    bool AddMessage(float, float, DataArray*, int);

    DataNode OnGetStart(DataArray*);
    DataNode OnGetEnd(DataArray*);
    DataNode OnNextStartDelta(DataArray*);
    DataNode OnDebugDraw(DataArray*);
    DataNode OnInsertIdle(DataArray*);
    DataNode OnBeatToSecLength(DataArray*);
    DataNode OnSecOffsetAll(DataArray*);
    DataNode OnSecOffset(DataArray*);
    DataNode OnPrevVal(DataArray*);
    DataNode OnNextVal(DataArray*);
    DataNode OnDelta(DataArray*);
    DataNode OnHasSpace(DataArray*);
    DataNode OnRtComputeSpace(DataArray*);

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

    int unk40;
    int unk44;
    int unk48;
    int unk4c;
    int unk50;

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

    static DataNode* mpStart;
    static DataNode* mpEnd;
    static DataNode* mpLength;
    static DataNode* mpPrevStartDelta;
    static DataNode* mpPrevEndDelta;
    static DataNode* mpVal;
    static DataNode* mpSingleBit;
    static DataNode* mpLowestBit;
    static DataNode* mpLowestSlot;
    static DataNode* mpHighestSlot;
    static DataNode* mpData;
    static DataNode* mpOutOfBounds;
    static DataNode* mpBeforeDeltaSec;
    static DataNode* mpAfterDeltaSec;

    static std::list<MidiParser*> sParsers;
};

#endif // MIDI_MIDIPARSER_H
