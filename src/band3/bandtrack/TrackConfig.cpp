#include "TrackConfig.h"
#include "game/Defines.h"
#include "utl/Symbol.h"

#include "decomp.h"

TrackConfig::TrackConfig(BandUser* bu) : mUser(bu), kDualPerspective(true), mTrackNum(0), mMaxSlots(0), mNumSlots(0),
    mName(), mLefty(false), mCymbalLanes(0), mDisableHopos(0) {}

const BandUser* TrackConfig::GetBandUser() const { return mUser; }

int TrackConfig::TrackNum() const { return mTrackNum; }

#pragma push
#pragma force_active on
inline int TrackConfig::GetMaxSlots() const { return mMaxSlots; }
#pragma pop

DECOMP_FORCEFUNC(TrackConfig, TrackConfig, GetMaxSlots())

Symbol TrackConfig::Type() const { return mUser->GetTrackSym(); }
bool TrackConfig::IsLefty() const { return mLefty; }
uint TrackConfig::GetGameCymbalLanes() const { return mCymbalLanes; }
bool TrackConfig::GetDisableHopos() const { return mDisableHopos; }
bool TrackConfig::UseLeftyGems() const { return mLefty; }

bool TrackConfig::IsDrumTrack() const { return mUser->GetTrackType() == kTrackDrum; }
bool TrackConfig::IsKeyboardTrack() const { return mUser->GetTrackType() == kTrackKeys; }

bool TrackConfig::AllowsOverlappingGems() const {
    bool b = 0;
    if (mUser->GetTrackType() == kTrackKeys || mUser->GetTrackType() == 4) b = true;
    return b;
}

bool TrackConfig::AllowsPartialHits() const { return mUser->GetControllerType() == kControllerNone; }

bool TrackConfig::IsRealGuitarTrack() const {
    TrackType t = mUser->GetTrackType();
    bool b = 0;
    if (t == kTrackRealGuitar || t == kTrackRealBass) b = true;
    return b;
}

const char* TrackConfig::GetSlotColor(int slot) const {
    MILO_ASSERT(slot >= 0 && slot <= GetMaxSlots(), 156);
    Symbol s = TrackTypeToSym(mUser->GetTrackType());
    DataArray* syscfg = SystemConfig("track_graphics", "slot_colors", s);
    int i = slot;
#ifdef MILO_DEBUG
    bool b = (mUser->GetTrackType() == kTrackDrum);
    if (b && mLefty && i != 0) i = mMaxSlots - i;
#else
    if (IsDrumTrack() && UseLeftyGems() && i != 0) i = mMaxSlots - i;
#endif
    return syscfg->Str(i + 1);
}

void TrackConfig::SetMaxSlots(int i) { mMaxSlots = i; }
void TrackConfig::SetLefty(bool b) { mLefty = b; }
void TrackConfig::SetGameCymbalLanes(uint ui) { mCymbalLanes = ui; }
void TrackConfig::SetDisableHopos(bool b) { mDisableHopos = b; }
void TrackConfig::SetTrackNum(int i) { mTrackNum = i; }
#ifdef MILO_DEBUG
DECOMP_FORCEACTIVE(TrackConfig,
    "slot >= 0 && slot <= mMaxSlots\0\0R\0L\0numSlots <= mMaxSlots\0left\0right"
)
#else
DECOMP_FORCEACTIVE(TrackConfig,
    "\0R\0L\0left\0right"
)
#endif
