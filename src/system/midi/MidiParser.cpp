#include "MidiParser.h"
#include "math/Utl.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "utl/TimeConversion.h"
#include "beatmatch/GemListInterface.h"
#include "obj/Task.h"
#include "midi/MidiParserMgr.h"
#include "rndobj/Rnd.h"
#include "midi/DisplayEvents.h"
#include "utl/Symbols.h"
#include <climits>

std::list<MidiParser *> MidiParser::sParsers;
DataNode *MidiParser::mpStart;
DataNode *MidiParser::mpEnd;
DataNode *MidiParser::mpLength;
DataNode *MidiParser::mpPrevStartDelta;
DataNode *MidiParser::mpPrevEndDelta;
DataNode *MidiParser::mpVal;
DataNode *MidiParser::mpSingleBit;
DataNode *MidiParser::mpLowestBit;
DataNode *MidiParser::mpLowestSlot;
DataNode *MidiParser::mpHighestSlot;
DataNode *MidiParser::mpData;
DataNode *MidiParser::mpOutOfBounds;
DataNode *MidiParser::mpBeforeDeltaSec;
DataNode *MidiParser::mpAfterDeltaSec;

void MidiParser::ClearManagedParsers() {
    std::list<MidiParser *> parsers;
    FOREACH (it, sParsers) {
        MidiParser *curParser = *it;
        if (curParser) {
            if (!ObjectDir::sMainDir->Find<MsgSource>(curParser->Name(), false)) {
                curParser->Events()->Clear();
            } else
                parsers.push_back(curParser);
        }
    }
    FOREACH (it, parsers) {
        delete *it;
    }
}

void MidiParser::Init() {
    MidiParser::Register();
    MidiParser::mpStart = &DataVariable("mp.start");
    MidiParser::mpEnd = &DataVariable("mp.end");
    MidiParser::mpLength = &DataVariable("mp.length");
    MidiParser::mpPrevStartDelta = &DataVariable("mp.prev_start");
    MidiParser::mpPrevEndDelta = &DataVariable("mp.prev_end");
    MidiParser::mpData = &DataVariable("mp.data");
    MidiParser::mpVal = &DataVariable("mp.val");
    MidiParser::mpSingleBit = &DataVariable("mp.single_bit");
    MidiParser::mpLowestBit = &DataVariable("mp.lowest_bit");
    MidiParser::mpLowestSlot = &DataVariable("mp.lowest_slot");
    MidiParser::mpHighestSlot = &DataVariable("mp.highest_slot");
    MidiParser::mpOutOfBounds = &DataVariable("mp.out_of_bounds");
    MidiParser::mpBeforeDeltaSec = &DataVariable("mp.before_delta_sec");
    MidiParser::mpAfterDeltaSec = &DataVariable("mp.after_delta_sec");
}

MidiParser::PostProcess::PostProcess()
    : zeroLength(false), startOffset(0), endOffset(0), minLength(0),
      maxLength(kHugeFloat), minGap(-kHugeFloat), maxGap(kHugeFloat),
      useRealtimeGaps(false), variableBlendPct(0) {}

MidiParser::MidiParser()
    : mTrackName(), mGemParser(0), mNoteParser(0), mTextParser(0), mLyricParser(0),
      mCurParser(0), mVocalEvents(0), mNotes(), mGems(0), mInverted(0),
      mLastStart(-kHugeFloat), mLastEnd(-kHugeFloat), mFirstEnd(-kHugeFloat),
      mMessageType(), mAppendLength(false), mUseVariableBlending(false),
      mMessageSelf(false), mCompressed(false), mStart(0), mBefore(0) {
    mEvents = new DataEventList();
    sParsers.push_back(this);
}

MidiParser::~MidiParser() {
    sParsers.remove(this);
    RELEASE(mEvents);
}

void MidiParser::SetTypeDef(DataArray *arr) {
    if (TypeDef() != arr) {
        Hmx::Object::SetTypeDef(arr);
        mInverted = false;
        mTrackName = Symbol("");
        mAppendLength = false;
        mUseVariableBlending = false;
        mMessageSelf = false;
        mMessageType = Symbol("");
        mCompressed = false;
        if (arr) {
            arr->FindData("inverted", mInverted, false);
            arr->FindData("track_name", mTrackName, true);
            arr->FindData("append_length", mAppendLength, false);
            arr->FindData("use_variable_blending", mUseVariableBlending, false);
            arr->FindData("message_self", mMessageSelf, false);
            arr->FindData("message_type", mMessageType, false);
            arr->FindData("compress", mCompressed, false);
            if (mCompressed) {
                DataArray *localArr =
                    new DataArray(!mMessageType.Null() + 2 + mAppendLength);
                localArr->Node(0) = 0;
                int i = 1;
                if (!mMessageType.Null()) {
                    localArr->Node(i++) = mMessageType;
                }
                localArr->Node(i) = 0;
                mEvents->Compress(localArr, i);
                localArr->Release();
            }
            mGemParser = arr->FindArray("gem", false);
            mNoteParser = arr->FindArray("midi", false);
            mTextParser = arr->FindArray("text", false);
            mLyricParser = arr->FindArray("lyric", false);
            mIdleParser = arr->FindArray("idle", false);
            MILO_ASSERT_FMT(
                mGemParser || mNoteParser || mTextParser || mLyricParser || mIdleParser,
                "%s has no parser",
                Name()
            );
            MILO_ASSERT_FMT(
                !(mGemParser && mNoteParser),
                "%s has both gem and note parsers, disallowed",
                Name()
            );
            DataArray *allowedArr = arr->FindArray("allowed_notes", false);
            mAllowedNotes = allowedArr ? allowedArr->Array(1) : nullptr;
            if (!mNoteParser && mAllowedNotes)
                MILO_FAIL("%s has no midi parser but has allowed_notes", Name());
        }
    }
}

void MidiParser::Clear() {
    mEvents->Clear();
    mFirstEnd = -kHugeFloat;
    mCurParser = nullptr;
    mVocalEvents = nullptr;
    mGems = nullptr;
    mStart = 0;
    mBefore = 0;
}

void MidiParser::Reset(float f) { mEvents->Reset(f); }

void MidiParser::Poll() {
    float beat = TheTaskMgr.Beat();
    static DataNode &parser = DataVariable("mp.parser");
    parser = this;
    while (mEvent = (DataEvent *)mEvents->NextEvent(beat), mEvent) {
        *mpStart = mEvent->start;
        *mpEnd = mEvent->end;
        *mpLength = Max(0.0f, mEvent->end - beat);
        DataArray *eventMsg = mEvent->Msg();
        if (mAppendLength) {
            eventMsg->Node(eventMsg->Size() - 1) = mpLength->Float();
        }
        if (mMessageSelf) {
            DataNode ret = HandleType(eventMsg);
            MILO_ASSERT(ret.Type() != kDataUnhandled, 0x112);
        } else {
            Export(eventMsg, false);
        }
        *mpData = 0;
    }
}

bool MidiParser::InsertIdle(float f, int i) {
    mStart = f;
    mBefore = i;
    if (mIdleParser) {
        DataNode node = mIdleParser->ExecuteScript(1, this, 0, 1);
        if (node.Int() != 0)
            return true;
    }
    return false;
}

bool MidiParser::AllowedNote(int note) {
    if (!mAllowedNotes)
        return true;
    else {
        for (int i = 0; i < mAllowedNotes->Size(); i++) {
            if (note == mAllowedNotes->Int(i))
                return true;
        }
        return false;
    }
}

void MidiParser::ParseNote(int startTick, int endTick, unsigned char data1) {
    if (mNoteParser && AllowedNote(data1)) {
        MemDoTempAllocations m(true, false);
        if (mNotes.size() == 0)
            mNotes.reserve(20000);
        int idx;
        for (idx = mNotes.size() - 1; idx >= 0; idx--) {
            if (startTick >= mNotes[idx].startTick)
                break;
        }
        mNotes.insert(mNotes.begin() + (idx + 1), Note(startTick, endTick, data1));
    }
}

void MidiParser::PushIdle(float start, float end, int at, Symbol idleMessage) {
    DataNode node;
    if (mCompressed)
        node = idleMessage;
    else {
        DataArray *arr = new DataArray(!mMessageType.Null() + 2 + mAppendLength);
        arr->Node(0) = 0;
        int idx = 1;
        if (!mMessageType.Null()) {
            arr->Node(idx++) = mMessageType;
        }
        arr->Node(idx++) = idleMessage;
        node = DataNode(arr, kDataArray);
        arr->Release();
    }
    MemDoTempAllocations m(true, false);
    mEvents->InsertEvent(start, end, node, at);
}

int MidiParser::GetIndex() {
    MILO_ASSERT(mCurParser, 0x178);
    if (mCurParser == mTextParser || mCurParser == mLyricParser)
        return mVocalIndex;
    else if (mCurParser == mNoteParser)
        return mNoteIndex;
    else {
        MILO_ASSERT(mCurParser == mGemParser, 0x17F);
        return mGemIndex;
    }
}

void MidiParser::SetIndex(int idx) {
    if (idx > 0) {
        if (mCurParser == mNoteParser) {
            if (idx < mNotes.size()) {
                mNoteIndex = idx;
                Note &curNote = mNotes[idx];
                SetGlobalVars(curNote.startTick, curNote.endTick, curNote.note);
            }
        } else if (mCurParser == mGemParser) {
            int x, y, z;
            if (mGems->GetGem(idx, x, y, z)) {
                mGemIndex = idx;
                SetGlobalVars(x, y, z);
                return;
            }
        } else if (mCurParser == mTextParser || mCurParser == mLyricParser) {
            if (idx < mVocalEvents->size()) {
                mVocalIndex = idx;
                VocalEvent &ev = (*mVocalEvents)[idx];
                SetGlobalVars(ev.mTick, ev.mTick, ev.mTextContent);
                return;
            }
        } else
            MILO_WARN("%s calling set index without note or gem parser", Name());
    }
    *mpOutOfBounds = 1;
}

// matches in retail
int MidiParser::ParseAll(
    GemListInterface *gems, std::vector<VocalEvent VECTOR_SIZE_LARGE> &text
) {
    mLastStart = -kHugeFloat;
    mLastEnd = -kHugeFloat;
    *mpStart = -kHugeFloat;
    *mpEnd = -kHugeFloat;
    DataArray *initArr = TypeDef()->FindArray("init", false);
    if (initArr)
        initArr->ExecuteScript(1, this, 0, 1);
    mGemIndex = 0;
    mNoteIndex = 0;
    mVocalIndex = 0;
    mGems = mGemParser ? gems : nullptr;
    mVocalEvents = mTextParser || mLyricParser ? &text : nullptr;
    while (true) {
        int startTick = INT_MAX;
        int which = -1;
        int loc48, loc4c, loc50;
        if (mVocalEvents) {
            if (mVocalIndex < mVocalEvents->size()
                && MinEq(startTick, (*mVocalEvents)[mVocalIndex].mTick)) {
                which = 0;
            }
        }
        if (mNoteParser) {
            if (mNoteIndex < mNotes.size()
                && MinEq(startTick, mNotes[mNoteIndex].startTick)) {
                which = 1;
            }
        }
        if (mGems && mGems->GetGem(mGemIndex, loc48, loc4c, loc50)
            && MinEq(startTick, loc48)) {
            which = 2;
        }
        if (which == 0) {
            VocalEvent &vocEv = (*mVocalEvents)[mVocalIndex];
            if ((vocEv.GetTextType() == VocalEvent::kLyric && mLyricParser)
                || (vocEv.GetTextType() == VocalEvent::kText && mTextParser)) {
                mCurParser = vocEv.GetTextType() == VocalEvent::kLyric ? mLyricParser
                                                                       : mTextParser;
                HandleEvent(vocEv.mTick, vocEv.mTick, vocEv.mTextContent);
            }
            mVocalIndex++;
        } else if (which == 1) {
            mCurParser = mNoteParser;
            Note &curNote = mNotes[mNoteIndex];
            HandleEvent(curNote.startTick, curNote.endTick, curNote.note);
            mNoteIndex++;
        } else if (which == 2) {
            mCurParser = mGemParser;
            HandleEvent(loc48, loc4c, loc50);
            mGemIndex++;
        } else
            break;
        continue;
    }
    if (mEvents->Size() != 0 && mIdleParser) {
        InsertIdle(kHugeFloat, mEvents->Size() - 1);
    }
    mCurParser = nullptr;
    DataArray *termArr = TypeDef()->FindArray("term", false);
    if (termArr)
        termArr->ExecuteScript(1, this, 0, 1);
    if (mInverted)
        mEvents->Invert(mFirstEnd);
    int numNotes = mNotes.size();
    ClearAndShrink(mNotes);
    mEvents->Compact();
    return numNotes;
}

void MidiParser::SetGlobalVars(int startTick, int endTick, const DataNode &data) {
    float startBeat = TickToBeat(startTick);
    float endBeat = TickToBeat(endTick);
    *mpOutOfBounds = 0;
    *mpStart = startBeat;
    *mpEnd = endBeat;
    *mpLength = endBeat - startBeat;
    *mpPrevStartDelta = startBeat - mLastStart;
    *mpPrevEndDelta = startBeat - mLastEnd;
    *mpData = data;
    if (mCurParser == mTextParser) {
        MILO_ASSERT(data.Type() == kDataArray, 0x230);
        if (data.Array()->Type(0) == kDataSymbol) {
            *mpVal = data.Array()->Sym(0);
        } else
            MILO_WARN("Text Event in midi file is missing Text.  \n");
    } else if (mCurParser == mLyricParser) {
        MILO_ASSERT(data.Type() == kDataString, 0x23A);
        *mpVal = data.Str();
    } else {
        *mpVal = data;
        if (mCurParser == mGemParser) {
            int gemval = data.Int();
            int lowestBit = 1;
            int i6 = 0x1000000;
            int lowestSlot = 0;
            int highestSlot = 0x17;
            for (; lowestBit <= 0x1000000; lowestBit <<= 1) {
                if (gemval & lowestBit)
                    break;
                lowestSlot++;
            }
            if (lowestBit > 0x1000000) {
                MILO_WARN("Bad gem, value 0x%x", gemval);
            } else {
                for (; i6 > 0; i6 >>= 1) {
                    if (gemval & i6)
                        break;
                    highestSlot--;
                }
            }
            *mpSingleBit = (gemval & ~lowestBit) == 0;
            *mpLowestBit = lowestBit;
            *mpLowestSlot = lowestSlot;
            *mpHighestSlot = highestSlot;
        }
    }
    mLastStart = startBeat;
    mLastEnd = endBeat;
}

void MidiParser::HandleEvent(int startTick, int endTick, const DataNode &data) {
    MILO_ASSERT(mCurParser, 0x27F);
    SetGlobalVars(startTick, endTick, data);
    mCurParser->ExecuteScript(1, this, 0, 1);
    *mpData = 0;
}

void MidiParser::InsertDataEvent(float start, float end, const DataNode &ev) {
    float f7 = start + mProcess.startOffset;
    if (mProcess.zeroLength)
        end = f7;
    end += mProcess.endOffset;
    int back = mEvents->FindStartFromBack(f7);
    if (InsertIdle(f7, back)) {
        back++;
    } else {
        FixGap(mBefore < 0 ? &mFirstEnd : mEvents->EndPtr(mBefore));
    }
    float clamped = Clamp(mProcess.minLength, mProcess.maxLength, end - f7);
    MemDoTempAllocations m(true, false);
    mEvents->InsertEvent(f7, f7 + clamped, ev, back + 1);
}

bool MidiParser::AddMessage(float start, float end, DataArray *msg, int firstArg) {
    DataNode node(msg->Evaluate(firstArg));
    if (node.Type() == kDataUnhandled)
        return false;
    if (!mCompressed) {
        int arr_size;
        if (node.Type() == kDataArray) {
            msg = node.Array();
            firstArg = 0;
            arr_size = msg->Size();
            arr_size++;
            if (arr_size == 1)
                return false;
            node = msg->Evaluate(0);
            if (node.Type() == kDataUnhandled)
                return false;
        } else {
            arr_size = msg->Size();
            arr_size = (arr_size - firstArg) + 1;
        }
        int i4 = 1;
        if (!mMessageType.Null()) {
            i4 = 2;
            arr_size++;
        }
        DataArray *new_arr = new DataArray(arr_size + mAppendLength);
        new_arr->Node(0) = 0;
        if (!mMessageType.Null()) {
            new_arr->Node(1) = mMessageType;
        }
        new_arr->Node(i4) = node;
        int i3;
        for (i3 = 1; i3 < arr_size - i4; i3++) {
            new_arr->Node(i3 + i4) = msg->Evaluate(i3 + firstArg);
        }
        if (mAppendLength) {
            new_arr->Node(i3 + i4) = 0.0f;
        }
        node = DataNode(new_arr, kDataArray);
        new_arr->Release();
    }
    InsertDataEvent(start, end, node);
    return true;
}

float MidiParser::GetStart(int i) {
    if (i < 0)
        return -kHugeFloat;
    else {
        MILO_ASSERT(mCurParser, 0x307);
        if (mCurParser == mGemParser) {
            int x, y, z;
            if (mGems->GetGem(i, x, y, z)) {
                return TickToBeat(x);
            }
        } else if (mCurParser == mNoteParser) {
            if (i < mNotes.size()) {
                return TickToBeat(mNotes[i].startTick);
            }
        } else {
            MILO_WARN("%s calling get_start outside of gem or note parser", Name());
        }
        return kHugeFloat;
    }
}

float MidiParser::GetEnd(int i) {
    if (i < 0)
        return -kHugeFloat;
    else {
        MILO_ASSERT(mCurParser, 0x321);
        if (mCurParser == mGemParser) {
            int x, y, z;
            if (mGems->GetGem(i, x, y, z)) {
                return TickToBeat(x);
            }
        } else if (mCurParser == mNoteParser) {
            if (i < mNotes.size()) {
                return TickToBeat(mNotes[i].endTick);
            }
        } else {
            MILO_WARN("%s calling get_end outside of gem or note parser", Name());
        }
        return kHugeFloat;
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(MidiParser)
    HANDLE_EXPR(
        add_message,
        AddMessage(MidiParser::mpStart->Float(), MidiParser::mpEnd->Float(), _msg, 2)
    )
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
#pragma pop

#pragma push
#pragma fp_contract off
DataNode MidiParser::OnInsertIdle(DataArray *arr) {
    Symbol sym = arr->Sym(2);
    float f3 = arr->Float(3);
    float f4 = arr->Float(4);
    float f5 = arr->Float(5);
    float maxgap = mProcess.maxGap;
    float mingap = mProcess.minGap;

    if (mProcess.useRealtimeGaps) {
        maxgap = ConvertToBeats(mProcess.maxGap, mStart);
        mingap = ConvertToBeats(mProcess.minGap, mStart);
    }
    float *fp;
    if (mBefore < 0)
        fp = &mFirstEnd;
    else
        fp = mEvents->EndPtr(mBefore);
    MILO_ASSERT(mIdleParser, 0x38C);
    f4 = *fp + f4;
    float sub = mStart - f5;
    if (sub - f4 >= f3) {
        if (mUseVariableBlending) {
            float f10 = -kHugeFloat;
            if (mBefore >= 0) {
                f10 = mEvents->Event(mBefore).start;
            }
            *fp = f4 - mProcess.variableBlendPct * (f4 - f10);
        } else {
            *fp = f4 - Clamp(mingap, maxgap, f4 - *fp);
        }
        mBefore++;
        PushIdle(f4, sub, mBefore, sym);
        return 1;
    } else {
        FixGap(fp);
        return 0;
    }
}
#pragma pop

float MidiParser::ConvertToBeats(float f1, float f2) {
    float secs = BeatToSeconds(f2);
    return SecondsToBeat(secs + f1) - f2;
}

#pragma push
#pragma fp_contract off
void MidiParser::FixGap(float *fp) {
    if (mUseVariableBlending) {
        float f4 = -kHugeFloat;
        if (mBefore >= 0) {
            f4 = mEvents->Event(mBefore).start;
        }
        *fp = mStart - mProcess.variableBlendPct * (mStart - f4);
    } else {
        float f4;
        if (mProcess.useRealtimeGaps) {
            float start = mStart;
            f4 = Clamp(
                ConvertToBeats(mProcess.minGap, mStart),
                ConvertToBeats(mProcess.maxGap, start),
                mStart - *fp
            );
        } else
            f4 = Clamp(mProcess.minGap, mProcess.maxGap, mStart - *fp);
        *fp = mStart - f4;
    }
}
#pragma pop

DataNode MidiParser::OnNextStartDelta(DataArray *arr) {
    int curidx = mEvents->CurIndex();
    float f;
    if (curidx >= mEvents->Size())
        f = kHugeFloat;
    else
        f = mEvents->Event(curidx).start;
    return f - mEvent->start;
}

DataNode MidiParser::OnGetStart(DataArray *arr) { return GetStart(arr->Int(2)); }

DataNode MidiParser::OnGetEnd(DataArray *arr) { return GetEnd(arr->Int(2)); }

DataNode MidiParser::OnDebugDraw(DataArray *arr) {
    float f2 = arr->Float(2);
    float f3 = arr->Float(3);
    TheRnd->DrawString(Name(), Vector2(0, f2), Hmx::Color(1, 1, 1), true);
    return DisplayEvents(mEvents, f2 + 12.0f, f3);
}

DataNode MidiParser::OnBeatToSecLength(DataArray *arr) {
    float f2 = arr->Float(2);
    float secs = TheTaskMgr.Seconds(TaskMgr::kRealTime);
    float bts = BeatToSeconds(TheTaskMgr.Beat() + f2);
    return bts - secs;
}

DataNode MidiParser::OnSecOffsetAll(DataArray *arr) {
    mEvents->SecOffset(arr->Float(2));
    return 0;
}

DataNode MidiParser::OnSecOffset(DataArray *arr) {
    float f2 = arr->Float(2);
    float f3 = arr->Float(3) * 1000.0f;
    return MsToBeat(f3 + BeatToMs(f2));
}

DataNode MidiParser::OnNextVal(DataArray *arr) {
    int idx = GetIndex();
    SetIndex(idx + 1);
    DataNode ret(*mpVal);
    SetIndex(idx);
    return ret;
}

DataNode MidiParser::OnPrevVal(DataArray *arr) {
    int idx = GetIndex();
    if (idx != 0) {
        SetIndex(idx - 1);
        DataNode ret(*mpVal);
        SetIndex(idx);
        return ret;
    } else
        return 0;
}

DataNode MidiParser::OnDelta(DataArray *arr) {
    int idx = GetIndex();
    return GetStart(idx + 1) - mpStart->Float();
}

DataNode MidiParser::OnHasSpace(DataArray *arr) {
    float f2 = arr->Float(2);
    float f3 = arr->Float(3);
    int idx = GetIndex();
    bool ret = false;
    if (mpPrevStartDelta->Float() > f2) {
        if (GetStart(idx + 1) - mpStart->Float() > f3) {
            ret = true;
        }
    }
    return ret;
}

DataNode MidiParser::OnRtComputeSpace(DataArray *arr) {
    int idx = GetIndex();
    *mpBeforeDeltaSec = BeatToSeconds(mpStart->Float() - GetEnd(idx - 1));
    *mpAfterDeltaSec = BeatToSeconds(GetStart(idx + 1) - mpEnd->Float());
    return 0;
}

BEGIN_PROPSYNCS(MidiParser)
    SYNC_PROP(zero_length, mProcess.zeroLength)
    SYNC_PROP(start_offset, mProcess.startOffset)
    SYNC_PROP(end_offset, mProcess.endOffset)
    SYNC_PROP(min_length, mProcess.minLength)
    SYNC_PROP(max_length, mProcess.maxLength)
    SYNC_PROP(min_gap, mProcess.minGap)
    SYNC_PROP(max_gap, mProcess.maxGap)
    SYNC_PROP(use_realtime_gaps, mProcess.useRealtimeGaps)
    SYNC_PROP(variable_blend_pct, mProcess.variableBlendPct)
    SYNC_PROP_SET(index, GetIndex(), SetIndex(_val.Int()))
    SYNC_PROP_SET(song_name, TheMidiParserMgr->GetSongName(), )
END_PROPSYNCS
