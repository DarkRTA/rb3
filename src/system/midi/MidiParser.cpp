#include "MidiParser.h"

std::list<MidiParser*> MidiParser::sParsers;

Hmx::Object* MidiParser::NewObject() { return new MidiParser; }

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

void MidiParser::Clear() {
    mEvents->Clear();
}

void MidiParser::Reset(float f) { mEvents->Reset(f); }
