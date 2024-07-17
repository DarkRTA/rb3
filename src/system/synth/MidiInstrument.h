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
class SampleInst;

class NoteVoiceInst : public Hmx::Object {
public:
    NoteVoiceInst(MidiInstrument*, SampleZone*, unsigned char, unsigned char, int, int, float);
    virtual ~NoteVoiceInst();
    virtual void Start();
    virtual void Stop();
    virtual bool IsRunning();
    virtual bool Started(){ return mStarted; }
    virtual bool Stopped(){ return mStopped; }
    virtual void SetTranspose(float);
    virtual void UpdateVolume();
    virtual void SetPan(float);
    virtual void SetVolume(float);

    void Poll();
    void Pause(bool);
    void SetSend(FxSend*);
    void SetReverbMixDb(float);
    void SetReverbEnable(bool);
    void SetSpeed(float);
    void GlideToNote(unsigned char, int);
    void SetFineTune(float);
    void KillAllVoices();

    NEW_POOL_OVERLOAD(NoteVoiceInst)
    DELETE_POOL_OVERLOAD(NoteVoiceInst)

    SampleInst* mSample; // 0x1c
    float mVolume; // 0x20
    float mStartProgress; // 0x24
    unsigned char mTriggerNote; // 0x28
    unsigned char mCenterNote; // 0x29
    bool mStarted; // 0x2a
    bool mStopped; // 0x2b
    int mGlideID; // 0x2c
    int mGlideFrames; // 0x30
    float mGlideToNote; // 0x34
    float mGlideFromNote; // 0x38
    int mGlideFramesLeft; // 0x3c
    float mFineTune; // 0x40
    int mDurationFramesLeft; // 0x44
    MidiInstrument* mOwner; // 0x48
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

    void Poll();
    void Pause(bool);
    void SetFineTune(float);
    void KillAllVoices();
    void SetSend(FxSend*);
    void SetReverbMixDb(float);
    void SetReverbEnable(bool);
    void PressNote(unsigned char, unsigned char, int, int);
    void StartSample(unsigned char, unsigned char, int, int);
    void ReleaseNote(unsigned char);
    void PlayNote(unsigned char, unsigned char, int);
    NoteVoiceInst* MakeNoteInst(SampleZone*, unsigned char, unsigned char, int, int);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

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
