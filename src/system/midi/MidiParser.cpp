#include "MidiParser.h"

Hmx::Object* MidiParser::NewObject() { return new MidiParser; }

MidiParser::PostProcess::PostProcess() : a(0), b(0), c(0), d(0), e(1e30), f(-1e30), g(1e30), h(0), j(0) {

}

MidiParser::MidiParser() {
    mEvents = new DataEventList;
}

void MidiParser::Clear() {
    mEvents->Clear();
}

void MidiParser::Reset(float f) { mEvents->Reset(f); }
