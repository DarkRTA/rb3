#include "Metronome.h"
#include "game/SongDB.h"
#include "meta_band/ProfileMgr.h"
#include "os/Debug.h"
#include "synth/Sfx.h"
#include "utl/TimeConversion.h"

Metronome::Metronome()
    : mBeat(-1), mEnabled(false), mHiSfx(NULL), mLoSfx(NULL), mFader(0) {}
Metronome::~Metronome() {}

void Metronome::Enter(Sfx *hi, Sfx *lo) {
    MILO_ASSERT(hi, 44);
    MILO_ASSERT(lo, 45);
    mHiSfx = hi;
    mLoSfx = lo;
    mFader = Hmx::Object::New<Fader>();
    mFader->SetVal(0);
    mHiSfx->mFaders.Add(mFader);
    mLoSfx->mFaders.Add(mFader);
}

void Metronome::Exit() { RELEASE(mFader); }

void Metronome::Poll(int i1, Metronome::OverrideEnabled oe) {
    float tick = MsToTick(TickToMs(i1) - TheProfileMgr.GetSongToTaskMgrMs((LagContext)0));
    MBT mbt = TheSongDB->GetMBT(tick);
    if (mBeat != mbt.beat) {
        mBeat = mbt.beat;
        if (mbt.tick <= 0x64 && (mEnabled || oe == 1) && oe != 2) {
            PlayBeat(mBeat);
        }
    }
}

void Metronome::PlayBeat(int) {
    if (mBeat == 0)
        mHiSfx->Play(0, 0, 0);
    else
        mLoSfx->Play(0, 0, 0);
}

void Metronome::Enable(bool b) { mEnabled = b; }
bool Metronome::Enabled() const { return mEnabled; }

void Metronome::SetVolume(int v, int steps) {
    MILO_ASSERT(v >= 0 && v <= steps, 105);
    float d = (float)v / (steps + -1);
    mFader->SetVal(d * 20.0f + -20.0f);
}

int Metronome::GetVolume(int steps) const {
    if (mFader) {
        return (mFader->mVal - -20.0f) / 20.0f * (steps + -1);
    } else
        return 0;
}
