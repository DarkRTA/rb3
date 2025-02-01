#include "beatmatch/TrackWatcher.h"
#include "DrumFillTrackWatcherImpl.h"
#include "KeyboardTrackWatcherImpl.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/GuitarTrackWatcherImpl.h"
#include "beatmatch/JoypadTrackWatcherImpl.h"
#include "beatmatch/RealGuitarTrackWatcherImpl.h"
#include "beatmatch/TrackType.h"
#include "beatmatch/TrackWatcherImpl.h"
#include "beatmatch/SongData.h"
#include "os/System.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

Symbol ControllerTypeToTrackWatcherType(Symbol cntType) {
    DataArray *cfg =
        SystemConfig("beatmatcher", "controllers", "beatmatch_controller_mapping");
    Symbol watchType = cfg->FindSym(cntType);
    if (watchType == joypad_guitar)
        return guitar;
    else
        return watchType;
}

TrackWatcherImpl *NewTrackWatcherImpl(
    int track,
    const UserGuid &u,
    int slot,
    Symbol cntType,
    SongData *data,
    TrackWatcherParent *parent,
    DataArray *cfg
) {
    Symbol watchType = ControllerTypeToTrackWatcherType(cntType);
    TrackType trackType = data->TrackTypeAt(track);
    GameGemList *gemList = data->GetGemList(track);
    if (watchType == guitar) {
        return new GuitarTrackWatcherImpl(track, u, slot, data, gemList, parent, cfg);
    } else if (watchType == joypad) {
        if (data->TrackHasIndependentSlots(track)) {
            return new DrumFillTrackWatcherImpl(
                track, u, slot, data, gemList, parent, cfg
            );
        } else {
            if (trackType - 4U <= 1) {
                return new KeyboardTrackWatcherImpl(
                    track, u, slot, data, gemList, parent, cfg
                );
            } else {
                return new JoypadTrackWatcherImpl(
                    track, u, slot, data, gemList, parent, cfg, 2
                );
            }
        }
    } else if (watchType == real_guitar) {
        if (trackType - 1U <= 1) {
            return new GuitarTrackWatcherImpl(track, u, slot, data, gemList, parent, cfg);
        } else {
            return new RealGuitarTrackWatcherImpl(
                track, u, slot, data, gemList, parent, cfg
            );
        }
    } else if (watchType == keys) {
        return new KeyboardTrackWatcherImpl(track, u, slot, data, gemList, parent, cfg);
    } else {
        MILO_FAIL("Bad TrackWatcher type: %s\n", watchType);
        return nullptr;
    }
}

TrackWatcher::TrackWatcher(
    int track,
    const UserGuid &u,
    int slot,
    Symbol cntType,
    SongData *data,
    TrackWatcherParent *parent,
    DataArray *cfg
)
    : mImpl(0), mSinks(), mControllerType(), mUserGuid() {
    mTrack = track;
    mUserGuid = u;
    mPlayerSlot = slot;
    mControllerType = cntType;
    mSongData = data;
    mParent = parent;
    mCfg = cfg;
    SetImpl();
}

TrackWatcher::~TrackWatcher() { RELEASE(mImpl); }

void TrackWatcher::ReplaceImpl(Symbol sym) {
    mControllerType = sym;
    SetImpl();
}

void TrackWatcher::SetImpl() {
    TrackWatcherState state;
    bool hasImpl = false;
    if (mImpl) {
        hasImpl = true;
        mImpl->SaveState(state);
    }
    RELEASE(mImpl);
    mImpl = NewTrackWatcherImpl(
        mTrack, mUserGuid, mPlayerSlot, mControllerType, mSongData, mParent, mCfg
    );
    mImpl->Init();
    for (int i = 0; i < mSinks.size(); i++) {
        mImpl->AddSink(mSinks[i]);
    }
    if (hasImpl)
        mImpl->LoadState(state);
}

void TrackWatcher::RecalcGemList() { mImpl->RecalcGemList(); }

void TrackWatcher::SetIsCurrentTrack(bool b) { mImpl->SetIsCurrentTrack(b); }

void TrackWatcher::AddSink(BeatMatchSink *sink) {
    mSinks.push_back(sink);
    mImpl->AddSink(sink);
}

void TrackWatcher::Poll(float f) { mImpl->Poll(f); }

void TrackWatcher::Jump(float f) { mImpl->Jump(f); }

void TrackWatcher::Restart() { mImpl->Restart(); }

bool TrackWatcher::Swing(int i, bool b1, bool b2, GemHitFlags flags) {
    return mImpl->Swing(i, b1, b2, flags);
}

void TrackWatcher::NonStrumSwing(int i, bool b1, bool b2) {
    mImpl->NonStrumSwing(i, b1, b2);
}

void TrackWatcher::FretButtonDown(int i) { mImpl->FretButtonDown(i); }

void TrackWatcher::RGFretButtonDown(int i) { mImpl->RGFretButtonDown(i); }

void TrackWatcher::FretButtonUp(int i) { mImpl->FretButtonUp(i); }

void TrackWatcher::Enable(bool b) { mImpl->Enable(b); }

void TrackWatcher::SetCheating(bool b) { mImpl->SetCheating(b); }

void TrackWatcher::SetAutoplayError(int i) { mImpl->SetAutoplayError(i); }

void TrackWatcher::SetAutoplayCoda(bool b) { mImpl->SetAutoplayCoda(b); }

float TrackWatcher::CycleAutoplayAccuracy() { return mImpl->CycleAutoplayAccuracy(); }

void TrackWatcher::SetAutoplayAccuracy(float f) { mImpl->SetAutoplayAccuracy(f); }

void TrackWatcher::SetSyncOffset(float f) { mImpl->SetSyncOffset(f); }

void TrackWatcher::E3CheatIncSlop() { mImpl->E3CheatIncSlop(); }

void TrackWatcher::E3CheatDecSlop() { mImpl->E3CheatDecSlop(); }