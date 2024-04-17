#ifndef SYNTH_BINKCLIP_H
#define SYNTH_BINKCLIP_H

#include "obj/Object.h"
#include "synth/Pollable.h"
#include "utl/FilePath.h"

class BinkClip : public Hmx::Object, public SynthPollable {
    FilePath mFilePath;
};

#endif // SYNTH_BINKCLIP_H