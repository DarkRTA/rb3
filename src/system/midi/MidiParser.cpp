#include "MidiParser.h"

Hmx::Object* MidiParser::NewObject() { return new MidiParser; }

MidiParser::PostProcess::PostProcess() : zeroLength(false), startOffset(0),
            endOffset(0), minLength(0), maxLength(1e30), minGap(-1e30), 
            maxGap(1e30), useRealtimeGaps(false), variableBlendPct(0) { }

MidiParser::MidiParser() {
    mEvents = new DataEventList;
}

void MidiParser::Clear() {
    mEvents->Clear();
}

void MidiParser::Reset(float f) { mEvents->Reset(f); }
