#ifndef SYNTH_SEQUENCE_H
#define SYNTH_SEQUENCE_H
#include "obj/Object.h"
#include "synth/Pollable.h"
#include "utl/FilePath.h"

class Sequence : public Hmx::Object, public SynthPollable {
public:
    Sequence();

    void Stop(bool);
    
    int dummy;
};

#endif
