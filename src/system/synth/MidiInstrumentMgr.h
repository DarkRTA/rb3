#ifndef SYNTH_MIDIINSTRUMENTMGR_H
#define SYNTH_MIDIINSTRUMENTMGR_H
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "synth/MidiInstrument.h"

class MidiInstrumentMgr {
public:
    MidiInstrumentMgr();
    ~MidiInstrumentMgr();
    void Init();
    void SetInstrument(MidiInstrument*);
    void UnloadInstrument();
    void Poll();

    ObjDirPtr<ObjectDir> mObjectDir; // 0x0
    ObjPtr<MidiInstrument, ObjectDir> mInstrument; // 0xc
};

#endif
