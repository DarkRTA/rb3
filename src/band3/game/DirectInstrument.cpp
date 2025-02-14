#include "DirectInstrument.h"
#include "synth/Faders.h"
#include "synth/MidiInstrument.h"
#include "synth/Synth.h"

DirectInstrument::DirectInstrument()
    : mVolume(127), mInstrument(nullptr), mFader(nullptr) {
    DataArray *sounddotinstruments = SystemConfig("sound", "instruments");
    const char *path = sounddotinstruments->FindStr("chamberlin");
    mVolume = SystemConfig("sound")->FindInt("direct_instrument_volume");
    FilePath fp(".", path);
    mDir.LoadFile(fp, 1, true, kLoadFront, false);
}

DirectInstrument::~DirectInstrument() { Disable(); }

bool DirectInstrument::IsLoaded() { return mDir.IsLoaded(); }

void DirectInstrument::PostLoad() { mDir.PostLoad(NULL); }

void DirectInstrument::Enable() {
    if (mInstrument == 0) {
        mDir.PostLoad(NULL);
        RELEASE(mFader);
        mFader = Hmx::Object::New<Fader>();
        mInstrument = mDir->Find<MidiInstrument>("Chamberlin.inst", false);
        mInstrument->mFaders.Add(mFader);
        TheSynth->GetMidiInstrumentMgr()->SetInstrument(mInstrument);
    }
}

void DirectInstrument::Disable() {
    TheSynth->GetMidiInstrumentMgr()->UnloadInstrument();
    RELEASE(mFader);
    mInstrument = nullptr;
}

bool DirectInstrument::Enabled() const { return mInstrument; }

void DirectInstrument::SetVolume(int vol) { mVolume = vol; }

void DirectInstrument::NoteOn(int note_id) {
    mInstrument->PressNote(note_id, mVolume, -1, -1);
}

void DirectInstrument::NoteOff(int note_id) { mInstrument->ReleaseNote(note_id); }

void DirectInstrument::PlayNote(int note_id, int duration) {
    mInstrument->PlayNote(note_id, mVolume, duration);
}
