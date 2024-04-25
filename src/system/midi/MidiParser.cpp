#include "MidiParser.h"
#include "obj/Data.h"
#include "utl/Symbols.h"

std::list<MidiParser*> MidiParser::sParsers;
DataNode* MidiParser::mpStart = 0;
DataNode* MidiParser::mpEnd = 0;
DataNode* MidiParser::mpLength = 0;
DataNode* MidiParser::mpPrevStartDelta = 0;
DataNode* MidiParser::mpPrevEndDelta = 0;
DataNode* MidiParser::mpVal = 0;
DataNode* MidiParser::mpSingleBit = 0;
DataNode* MidiParser::mpLowestBit = 0;
DataNode* MidiParser::mpLowestSlot = 0;
DataNode* MidiParser::mpHighestSlot = 0;
DataNode* MidiParser::mpData = 0;
DataNode* MidiParser::mpOutOfBounds = 0;
DataNode* MidiParser::mpBeforeDeltaSec = 0;
DataNode* MidiParser::mpAfterDeltaSec = 0;

void MidiParser::Init(){
    Hmx::Object::RegisterFactory(StaticClassName(), NewObject);
    MidiParser::mpStart = DataVariable("mp.start");
    MidiParser::mpEnd = DataVariable("mp.end");
    MidiParser::mpLength = DataVariable("mp.length");
    MidiParser::mpPrevStartDelta = DataVariable("mp.prev_start");
    MidiParser::mpPrevEndDelta = DataVariable("mp.prev_end");
    MidiParser::mpData = DataVariable("mp.data");
    MidiParser::mpVal = DataVariable("mp.val");
    MidiParser::mpSingleBit = DataVariable("mp.single_bit");
    MidiParser::mpLowestBit = DataVariable("mp.lowest_bit");
    MidiParser::mpLowestSlot = DataVariable("mp.lowest_slot");
    MidiParser::mpHighestSlot = DataVariable("mp.highest_slot");
    MidiParser::mpOutOfBounds = DataVariable("mp.out_of_bounds");
    MidiParser::mpBeforeDeltaSec = DataVariable("mp.before_delta_sec");
    MidiParser::mpAfterDeltaSec = DataVariable("mp.after_delta_sec");
}

Hmx::Object* MidiParser::NewObject() { return new MidiParser(); }

MidiParser::PostProcess::PostProcess() : zeroLength(false), startOffset(0),
            endOffset(0), minLength(0), maxLength(1e30), minGap(-1e30), 
            maxGap(1e30), useRealtimeGaps(false), variableBlendPct(0) { }

MidiParser::MidiParser() : mTrackName(), mGemParser(0), mNoteParser(0), mTextParser(0), mLyricParser(0), mCurParser(0), 
    unk40(0), unk44(0), unk48(0), unk4c(0), unk50(0), mInverted(0), mLastStart(-1e+30f), mLastEnd(-1e+30f), mFirstEnd(-1e+30f),
    mMessageType(), mAppendLength(false), mUseVariableBlending(false), mMessageSelf(false), mCompressed(false), mStart(0.0f), mBefore(0) {
    mEvents = new DataEventList();
    sParsers.push_back(this);
}

MidiParser::~MidiParser(){

}

void MidiParser::SetTypeDef(DataArray* arr){
    if(mTypeDef != arr){
        Hmx::Object::SetTypeDef(arr);
        mInverted = false;
        mTrackName = Symbol("");
        mAppendLength = false;
        mUseVariableBlending = false;
        mMessageSelf = false;
        mMessageType = Symbol("");
        mCompressed = false;
        if(arr){
            arr->FindData("inverted", mInverted, false);
            arr->FindData("track_name", mTrackName, true);
            arr->FindData("append_length", mAppendLength, false);
            arr->FindData("use_variable_blending", mUseVariableBlending, false);
            arr->FindData("message_self", mMessageSelf, false);
            arr->FindData("compress", mCompressed, false);
            if(mCompressed){
                DataArray* localArr = new DataArray(mAppendLength - mMessageType.IsNull() + 2);
                localArr->Node(0) = DataNode(0);
                int i = 1;
                if(!mMessageType.IsNull()){
                    localArr->Node(1) = DataNode(mMessageType);
                    i = 2;
                }
                localArr->Node(i) = DataNode(0);
                mEvents->Compress(localArr, i);
                localArr->Release();
            }
            mGemParser = arr->FindArray("gem", false);
            mNoteParser = arr->FindArray("midi", false);
            mTextParser = arr->FindArray("text", false);
            mLyricParser = arr->FindArray("lyric", false);
            mIdleParser = arr->FindArray("idle", false);
            bool allgood = false;
            if(mGemParser || mNoteParser || mTextParser || mLyricParser || mIdleParser) allgood = true;
            if(!allgood) MILO_FAIL("%s has no parser", mName);
            if(mGemParser && mNoteParser) MILO_FAIL("%s has both gem and note parsers, disallowed", mName);
            DataArray* allowedArr = arr->FindArray("allowed_notes", false);
            mAllowedNotes = allowedArr ? allowedArr->Array(1) : 0;
            if(!mNoteParser && allowedArr) MILO_FAIL("%s has no midi parser but has allowed_notes", mName);
        }
    }
}

void MidiParser::Clear() {
    mEvents->Clear();
    mFirstEnd = -1e+30f;
    mCurParser = 0;
    unk40 = 0;
    unk50 = 0;
    mStart = 0.0f;
    mBefore = 0;
}

void MidiParser::Reset(float f) { mEvents->Reset(f); }

bool MidiParser::InsertIdle(float f, int i){
    mStart = f;
    mBefore = i;
    if(mIdleParser){
        int theInt = mIdleParser->ExecuteScript(1, this, 0, 1).Int(0);
        if(theInt != 0) return true;
    }
    return false;
}

bool MidiParser::AllowedNote(int i){
    if(!mAllowedNotes) return true;
    else {
        for(int i = 0; i < mAllowedNotes->Size(); i++){
            if(i == mAllowedNotes->Int(i)) return true;
        }
        return false;
    }
}

#pragma dont_inline on
BEGIN_HANDLERS(MidiParser)
    HANDLE_EXPR(add_message, AddMessage(MidiParser::mpStart->Float(0), MidiParser::mpEnd->Float(0), _msg, 2))
    HANDLE_EXPR(add_message_se, AddMessage(_msg->Float(2), _msg->Float(3), _msg, 4))
    HANDLE(get_start, OnGetStart)
    HANDLE(get_end, OnGetEnd)
    HANDLE(next_start_delta, OnNextStartDelta)
    HANDLE(debug_draw, OnDebugDraw)
    HANDLE_EXPR(num_events, mEvents->Size())
    HANDLE_ACTION(clear_events, mEvents->Clear())
    HANDLE(insert_idle, OnInsertIdle)
    HANDLE(beat_to_sec_length, OnBeatToSecLength)
    HANDLE(sec_offset_all, OnSecOffsetAll)
    HANDLE(sec_offset, OnSecOffset)
    HANDLE(prev_val, OnPrevVal)
    HANDLE(next_val, OnNextVal)
    HANDLE(delta, OnDelta)
    HANDLE(has_space, OnHasSpace)
    HANDLE(rt_compute_space, OnRtComputeSpace)
    HANDLE_ACTION(reset_to_beat, Reset(_msg->Float(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x369)
END_HANDLERS
#pragma dont_inline reset