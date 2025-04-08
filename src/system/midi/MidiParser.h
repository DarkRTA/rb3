#pragma once
#include "obj/Msg.h"
#include "midi/DataEvent.h"
#include "utl/VectorSizeDefs.h"
#include <vector>
#include <list>

class GemListInterface; // forward dec

/**
 * @brief: A parser for a single Midi track.
 * Original _objects description:
 * "Parses midi files into messages to send to other objects or itself"
 */
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
        Note(int x, int y, int z) : note(z), startTick(x), endTick(y) {}
        int note; // 0x0
        int startTick; // 0x4
        int endTick; // 0x8
    };

    struct VocalEvent {
        // because midis can store text as either Text or Lyric types
        enum TextType {
            kText,
            kLyric
        };

        DataNode mTextContent; // 0x0
        int mTick; // 0x8

        TextType GetTextType() const {
            return mTextContent.Type() == kDataString ? kLyric : kText;
        }
    };

    MidiParser();
    OBJ_CLASSNAME(MidiParser);
    OBJ_SET_TYPE(MidiParser);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual ~MidiParser();
    virtual void SetTypeDef(DataArray *);

    void Clear();
    void Reset(float);
    bool InsertIdle(float, int);
    bool AllowedNote(int);
    bool AddMessage(float, float, DataArray *, int);
    float ConvertToBeats(float, float);
    float GetStart(int);
    float GetEnd(int);
    void SetIndex(int);
    int GetIndex();
    void SetGlobalVars(int, int, const DataNode &);
    void HandleEvent(int, int, const DataNode &);
    void Poll();
    void FixGap(float *);
    void InsertDataEvent(float, float, const DataNode &);

    /** Parse everything - the current notes this MidiParser has,
     * plus the supplied gems and text events.
     * @param [in] gems The supplied gems for this MidiParser.
     * @param [in] text The supplied text events for this MidiParser.
     * @returns The number of midi notes after parsing is complete.
     */
    int ParseAll(GemListInterface *gems, std::vector<VocalEvent VECTOR_SIZE_LARGE> &text);
    void PushIdle(float, float, int, Symbol);
    void ParseNote(int, int, unsigned char);

    DataNode OnGetStart(DataArray *);
    DataNode OnGetEnd(DataArray *);
    DataNode OnNextStartDelta(DataArray *);
    DataNode OnDebugDraw(DataArray *);
    DataNode OnInsertIdle(DataArray *);
    DataNode OnBeatToSecLength(DataArray *);
    DataNode OnSecOffsetAll(DataArray *);
    DataNode OnSecOffset(DataArray *);
    DataNode OnPrevVal(DataArray *);
    DataNode OnNextVal(DataArray *);
    DataNode OnDelta(DataArray *);
    DataNode OnHasSpace(DataArray *);
    DataNode OnRtComputeSpace(DataArray *);

    DataEventList *Events() const { return mEvents; }
    Symbol TrackName() const { return mTrackName; }

    DataEventList *mEvents; // 0x1c
    /** The midi track's name. */
    Symbol mTrackName; // 0x20
    /** The typedef array to use when parsing gems. */
    DataArray *mGemParser; // 0x24
    /** The typedef array to use when parsing midi notes. */
    DataArray *mNoteParser; // 0x28
    /** The typedef array to use when parsing text. */
    DataArray *mTextParser; // 0x2c
    /** The typedef array to use when parsing lyrics. */
    DataArray *mLyricParser; // 0x30
    /** The typedef array to use when inserting idle events. */
    DataArray *mIdleParser; // 0x34
    /** The current parser in use. */
    DataArray *mCurParser; // 0x38
    /** The list of allowed midi notes for this track. */
    DataArray *mAllowedNotes; // 0x3c
    /** The list of vocal events for this track. */
    std::vector<VocalEvent VECTOR_SIZE_LARGE> *mVocalEvents; // 0x40
    /** The list of midi notes for this track. */
    std::vector<Note VECTOR_SIZE_LARGE> mNotes; // 0x44
    /** The list of gems for this track. */
    GemListInterface *mGems; // 0x50
    bool mInverted; // 0x54
    PostProcess mProcess; // 0x58
    float mLastStart; // 0x7c
    float mLastEnd; // 0x80
    float mFirstEnd; // 0x84
    DataEvent *mEvent; // 0x88
    Symbol mMessageType; // 0x8c
    bool mAppendLength; // 0x90
    bool mUseVariableBlending; // 0x91
    float mVariableBlendPct; // 0x94
    bool mMessageSelf; // 0x98
    bool mCompressed; // 0x99
    /** The index of the current gem being parsed. */
    int mGemIndex; // 0x9c
    /** The index of the current note being parsed. */
    int mNoteIndex; // 0xa0
    /** The index of the current vocal event being parsed. */
    int mVocalIndex; // 0xa4
    float mStart; // 0xa8
    int mBefore; // 0xac

    static void ClearManagedParsers();
    static void Init();
    NEW_OBJ(MidiParser)
    static void Register() { REGISTER_OBJ_FACTORY(MidiParser) }

    static DataNode *mpStart;
    static DataNode *mpEnd;
    static DataNode *mpLength;
    static DataNode *mpPrevStartDelta;
    static DataNode *mpPrevEndDelta;
    static DataNode *mpVal;
    static DataNode *mpSingleBit;
    static DataNode *mpLowestBit;
    static DataNode *mpLowestSlot;
    static DataNode *mpHighestSlot;
    static DataNode *mpData;
    static DataNode *mpOutOfBounds;
    static DataNode *mpBeforeDeltaSec;
    static DataNode *mpAfterDeltaSec;

    static std::list<MidiParser *> sParsers;
};
