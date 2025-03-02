#include "game/VocalGuidePitch.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "obj/Data.h"
#include "synth/MidiInstrument.h"
#include "synth/Synth.h"
#include "utl/Loader.h"

VocalGuidePitch::VocalGuidePitch()
    : mGuideTrack(-1), unk8(0), mGuidePitch(0), mInstrument(0), mTuningOffset(0),
      mPaused(0), mPitchModifier(-12) {}

VocalGuidePitch::~VocalGuidePitch() {}

void VocalGuidePitch::Load() {
    DataArray *cfg = SystemConfig("sound", "instruments");
    mBank.LoadFile(
        FilePath(".", cfg->FindStr("chamberlin")), true, true, kLoadFront, false
    );
}

bool VocalGuidePitch::IsLoaded() const { return mBank.IsLoaded(); }
void VocalGuidePitch::FinishLoad() { mBank.PostLoad(nullptr); }
void VocalGuidePitch::Unload() { mBank = nullptr; }

void VocalGuidePitch::Poll(float f1) {}

void VocalGuidePitch::EnableGuideTrack(int i1) {
    if (mGuideTrack != i1) {
        mInstrument->ReleaseNote(mGuidePitch + mPitchModifier);
        mGuideTrack = i1;
        mGuidePitch = 0;
        unk8 = 0;
    }
}

void VocalGuidePitch::Init() {
    mInstrument = mBank->Find<MidiInstrument>("Chamberlin.inst", false);
    TheSynth->GetMidiInstrumentMgr()->SetInstrument(mInstrument);
    mGuideTrack = -1;
    mGuidePitch = 0;
    mTuningOffset = 0;
    unk8 = 0;
    mPaused = false;
    mPitchModifier = -12;
}

void VocalGuidePitch::Terminate() {
    mInstrument = nullptr;
    TheSynth->GetMidiInstrumentMgr()->UnloadInstrument();
}

void VocalGuidePitch::SetSong(const Symbol &s) {
    int songID = TheSongMgr.GetSongIDFromShortName(s, true);
    UpdateTuning(((BandSongMetadata *)TheSongMgr.Data(songID))->TuningOffset());
    SetVolume(((BandSongMetadata *)TheSongMgr.Data(songID))->GuidePitchVolume());
}

void VocalGuidePitch::UpdateTuning(float tuning) {
    mTuningOffset = tuning;
    mInstrument->SetFineTune(tuning);
}

int VocalGuidePitch::GetGuideTrack() const { return mGuideTrack; }
void VocalGuidePitch::SetVolume(float vol) {
    TheSynth->mMidiInstrumentFader->SetVal(vol);
}

void VocalGuidePitch::Pause(bool b1) {
    mInstrument->Pause(b1);
    mPaused = b1;
}

bool VocalGuidePitch::IsPaused() const { return mPaused; }