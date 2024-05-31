#include "synth/Stream.h"
#include "synth/Faders.h"
#include "synth/Synth.h"
#include "utl/Symbols.h"

#include "decomp.h"

const float Stream::kStreamEndMs = -1.1920929E-7f;
const int Stream::kStreamEndSamples = -1;

Stream::Stream() : mFaders(new FaderGroup(0)) {
    mFaders->AddLocal(_default)->SetVal(0.0f);
    mFaders->Add(TheSynth->unk4c);
}

Stream::~Stream(){
    delete mFaders;
}

void Stream::SetVolume(float f){
    mFaders->FindLocal(_default, true)->SetVal(f);
}

// Force inline generation
DECOMP_FORCEBLOCK(Stream, (Stream* strm),
    ADSR adsr;
    Marker m;
    strm->SetADSR(0, adsr);
    strm->RemapChannel(0, 0);
    strm->AddVirtualChannels(0);
    strm->CurrentLoopPoints(m, m);
    strm->MarkerAt(0, m);
    strm->MarkerListSize();
    strm->AddMarker(m);
    strm->ClearMarkerList();
)
