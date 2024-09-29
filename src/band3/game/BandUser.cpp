#include "BandUser.h"
#include "game/Defines.h"
#include "utl/Symbols.h"

BandUser::BandUser()
    : mDifficulty(DefaultDifficulty()), unk_0xC(0), mTrackType(kTrackDrum),
      mControllerType(kControllerNone), unk_0x18(0), unk_0x19(0), unk_0x1C(10),
      unk_0x20(5), mChar(0), mAutoplay(0), mLastHitFraction(0), mTrack(0), mPlayer(0),
      mParticipating(0), mIsWiiRemoteController(0), mJustDisconnected(0) {
    mPreviousAward = none;
}

BandUser::~BandUser() {}

Difficulty BandUser::GetDifficulty() const {
    return mDifficulty;
}

Symbol BandUser::GetDifficultySym() const {
    return DifficultyToSym(mDifficulty);
}

ControllerType BandUser::GetControllerType() const {
    return mControllerType;
}

TrackType BandUser::GetTrackType() const {
    return mTrackType;
}

Symbol BandUser::GetTrackSym() const {
    return TrackTypeToSym(mTrackType);
}

bool BandUser::HasChar() {
    return mChar != 0;
}

bool NullLocalBandUser::IsNullUser() const {
    return true;
}