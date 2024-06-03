#ifndef SYNTH_SFXINST_H
#define SYNTH_SFXINST_H
#include "synth/SeqInst.h"
#include "synth/Sfx.h"

class SfxInst : public SeqInst {
public:
    SfxInst(Sfx*);

    int dummysfxinst;
};

#endif
