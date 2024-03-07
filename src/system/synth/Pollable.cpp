#include "synth/Pollable.h"

std::list<SynthPollable*> SynthPollable::sPollables;

SynthPollable::SynthPollable() : mItr(sPollables.begin()), mIsActive(0) {

}
