#include "TrackConfig.h"
#include "game/Defines.h"
#include "utl/Symbol.h"

TrackConfig::TrackConfig(BandUser* bu) : mUser(bu), unk_0x4(true), mTrackNum(0), mMaxSlots(0), unk_0x10(0), 
    unk_0x14(gNullStr), mLefty(false), mCymbalLanes(0), mDisableHopos(0) {}

const BandUser* TrackConfig::GetBandUser() const { return mUser; }

int TrackConfig::TrackNum() const { return mTrackNum; }

#pragma push
#pragma force_active on
inline int TrackConfig::GetMaxSlots() const { return mMaxSlots; }
#pragma pop

Symbol TrackConfig::Type() const { return mUser->GetTrackSym(); }
bool TrackConfig::IsLefty() const { return mLefty; }
uint TrackConfig::GetGameCymbalLanes() const { return mCymbalLanes; }
bool TrackConfig::GetDisableHopos() const { return mDisableHopos; }
bool TrackConfig::UseLeftyGems() const { return mLefty; }

bool TrackConfig::IsDrumTrack() const { return mUser->GetTrackType() == kTrackDrum; }
bool TrackConfig::IsKeyboardTrack() const { return mUser->GetTrackType() == kTrackKeyboard; }

bool TrackConfig::AllowsOverlappingGems() const {
    bool b = 0;
    if (mUser->GetTrackType() == kTrackKeyboard || mUser->GetTrackType() == 4) b = true;
    return b;
}

bool TrackConfig::AllowsPartialHits() const { return mUser->GetControllerType() == kControllerNone; }

bool TrackConfig::IsRealGuitarTrack() const {
    TrackType t = mUser->GetTrackType();
    bool b = 0;
    if (t == kTrackProGuitar || t == kTrackProBass) b = true;
    return b;
}   

const char* TrackConfig::GetSlotColor(int slot) const {
    MILO_ASSERT(slot >= 0 && slot <= GetMaxSlots(), 156);
    DataArray* syscfg = SystemConfig("track_graphics", "slot_colors", TrackTypeToSym(mUser->GetTrackType()));
    int i = slot;
    bool b = (mUser->GetTrackType() == kTrackDrum);
    if (b && mLefty && i != 0) i = mMaxSlots - i;
    return syscfg->Str(i + 1);
}

void TrackConfig::SetMaxSlots(int i) { mMaxSlots = i; }
void TrackConfig::SetLefty(bool b) { mLefty = b; }
void TrackConfig::SetGameCymbalLanes(uint ui) { mCymbalLanes = ui; }
void TrackConfig::SetDisableHopos(bool b) { mDisableHopos = b; }
void TrackConfig::SetTrackNum(int i) { mTrackNum = i; }

const char* unused = "slot >= 0 && slot <= mMaxSlots\0\0R\0L\0numSlots <= mMaxSlots\0left\0right"; // fun fact: this is broken under -ipa file!