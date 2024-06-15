#ifndef SYNTH_MIDIINSTRUMENT_H
#define SYNTH_MIDIINSTRUMENT_H
#include "obj/Object.h"
#include "synth/SampleZone.h"
#include "synth/Faders.h"
#include "synth/FxSend.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"

class FxSend;
class MidiInstrument;

class NoteVoiceInst : public Hmx::Object {
public:
    NoteVoiceInst(MidiInstrument*, SampleZone*, unsigned char, unsigned char, int, int, float);
    virtual ~NoteVoiceInst();
    virtual void Start();
    virtual void Stop();
    virtual bool IsRunning();
    virtual bool Started();
    virtual bool Stopped();
    virtual void SetTranspose(float);
    virtual void UpdateVolume();
    virtual void SetPan(float);
    virtual void SetVolume(float);
};

class MidiInstrument : public Hmx::Object {
public:
    MidiInstrument();
    virtual ~MidiInstrument(){}
    OBJ_CLASSNAME(MidiInstrument);
    OBJ_SET_TYPE(MidiInstrument);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    ObjVector<SampleZone> mMultiSampleMap; // 0x1c
    int mPatchNumber; // 0x28
    ObjPtr<FxSend, ObjectDir> mSend; // 0x2c
    float mReverbMixDb; // 0x38
    bool mReverbEnable; // 0x3c
    ObjPtrList<NoteVoiceInst, ObjectDir> mActiveVoices; // 0x40
    FaderGroup mFaders; // 0x50
    float mFineTuneCents; // 0x64
};

#endif
