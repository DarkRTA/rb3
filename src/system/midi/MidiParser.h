#pragma once
#include "obj/Msg.h"
#include "midi/DataEvent.h"
#include "utl/VectorSizeDefs.h"
#include <vector>
#include <list>

class GemListInterface; // forward dec

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

        DataNode unk0;
        int unk8; // tick

        TextType GetTextType() const { return unk0.Type() == kDataString ? kLyric : kText; }
    };

    MidiParser();
    OBJ_CLASSNAME(MidiParser);
    OBJ_SET_TYPE(MidiParser);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual ~MidiParser();
    virtual void SetTypeDef(DataArray*);

    void Clear();
    void Reset(float);
    bool InsertIdle(float, int);
    bool AllowedNote(int);
    bool AddMessage(float, float, DataArray*, int);
    float ConvertToBeats(float, float);
    float GetStart(int);
    float GetEnd(int);
    void SetIndex(int);
    int GetIndex();
    void SetGlobalVars(int, int, const DataNode&);
    void HandleEvent(int, int, const DataNode&);
    void Poll();
    void FixGap(float*);
    void InsertDataEvent(float, float, const DataNode&);
    int ParseAll(GemListInterface*, std::vector<VocalEvent VECTOR_SIZE_LARGE>&);
    void PushIdle(float, float, int, Symbol);
    void ParseNote(int, int, unsigned char);
    DataEventList* Events() const { return mEvents; }
    Symbol TrackName() const { return mTrackName; }

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

    DataEventList* mEvents; // 0x1c
    Symbol mTrackName; // 0x20
    DataArray* mGemParser; // 0x24
    DataArray* mNoteParser; // 0x28
    DataArray* mTextParser; // 0x2c
    DataArray* mLyricParser; // 0x30
    DataArray* mIdleParser; // 0x34
    DataArray* mCurParser; // 0x38
    DataArray* mAllowedNotes; // 0x3c
    std::vector<VocalEvent VECTOR_SIZE_LARGE>* mVocalEvents; // 0x40
    std::vector<Note VECTOR_SIZE_LARGE> mNotes; // 0x44
    GemListInterface* mGems; // 0x50
    bool mInverted; // 0x54
    PostProcess mProcess; // 0x58
    float mLastStart; // 0x7c
    float mLastEnd; // 0x80
    float mFirstEnd; // 0x84
    DataEvent* mEvent; // 0x88
    Symbol mMessageType; // 0x8c
    bool mAppendLength; // 0x90
    bool mUseVariableBlending; // 0x91
    float mVariableBlendPct; // 0x94
    bool mMessageSelf; // 0x98
    bool mCompressed; // 0x99
    int mGemIndex; // 0x9c
    int mNoteIndex; // 0xa0
    int mVocalIndex; // 0xa4
    float mStart; // 0xa8
    int mBefore; // 0xac

    static void ClearManagedParsers();
    static void Init();
    NEW_OBJ(MidiParser)
    static void Register(){
        REGISTER_OBJ_FACTORY(MidiParser)
    }

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
