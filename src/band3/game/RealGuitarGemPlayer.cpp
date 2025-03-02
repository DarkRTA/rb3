#include "game/RealGuitarGemPlayer.h"
#include "GemPlayer.h"
#include "beatmatch/RGChords.h"
#include "beatmatch/RGState.h"
#include "beatmatch/SongData.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/SongDB.h"
#include "obj/DataFunc.h"
#include "obj/ObjMacros.h"
#include "os/UsbMidiGuitar.h"
#include "utl/Symbols3.h"

DataNode E3CheatChangeRGThreshold(DataArray *a) {
    int vel = UsbMidiGuitar::E3CheatGetMinVelocity() + a->Int(1);
    vel = Clamp<int>(0, 127, vel);
    UsbMidiGuitar::E3CheatSetMinVelocity(vel);
    MILO_WARN("Min Velocity = %d", vel);
    return 0;
}

DataNode E3CheatChangeRGSlop(DataArray *a) {
    std::vector<LocalBandUser *> users;
    TheBandUserMgr->GetLocalParticipants(users);
    for (int i = 0; i < users.size(); i++) {
        RealGuitarGemPlayer *player =
            dynamic_cast<RealGuitarGemPlayer *>(users[i]->GetPlayer());
        if (a->Int(1))
            player->E3CheatIncSlop();
        else
            player->E3CheatDecSlop();
    }
    return 0;
}

void RealGuitarGemPlayer::E3CheatIncSlop() { mMatcher->E3CheatIncSlop(); }
void RealGuitarGemPlayer::E3CheatDecSlop() { mMatcher->E3CheatDecSlop(); }

RealGuitarGemPlayer::RealGuitarGemPlayer(
    BandUser *user, BeatMaster *bm, Band *band, int i, BandPerformer *perf
)
    : GemPlayer(user, bm, band, i, perf) {
    static bool registered;
    if (!registered) {
        DataRegisterFunc("e3_cheat_change_slop", E3CheatChangeRGSlop);
        DataRegisterFunc("e3_cheat_change_threshold", E3CheatChangeRGThreshold);
        registered = true;
    }
}

RealGuitarGemPlayer::~RealGuitarGemPlayer() {}

void RealGuitarGemPlayer::Swing(int i1, int i2, float f3, bool b4, bool b5) {
    for (int i = 0; i < 6 && mTrack; i++) {
        if (i2 & (1 << i)) {
            Message msg("rg_strum");
            mTrack->GetGemManager()->GetSmasherObj(i)->Handle(msg, true);
        }
    }
    GemPlayer::Swing(i1, i2, f3, b4, b5);
}

void RealGuitarGemPlayer::FretButtonDown(int ui, float f2) {
    int i1, i2;
    UnpackRGData(ui, i1, i2);
    mRGState.FretDown(i1, i2);
}

void RealGuitarGemPlayer::FretButtonUp(int ui, float f2) {
    int i1, i2;
    UnpackRGData(ui, i1, i2);
    mRGState.FretUp(i1, i2);
}

int RealGuitarGemPlayer::GetTrackSlot(int i1) const {
    int slot, i2;
    UnpackRGData(i1, slot, i2);
    return slot;
}

const RGState &RealGuitarGemPlayer::GetRGState() const { return mRGState; }
void RealGuitarGemPlayer::SetRGState(const RGState &s) { mRGState = s; }

unsigned int RealGuitarGemPlayer::GetRollSlots(int i) const {
    return mMatcher->GetRGRollSlots(i);
}

int RealGuitarGemPlayer::GetNumRolls() const {
    SongData *data = TheSongDB->GetData();
    int diff = data->TrackDiffAt(mTrackNum);
    RangedDataCollection<RGRollChord> *rollInfo = data->GetRGRollInfo(mTrackNum);
    return rollInfo->SizeAt(diff);
}

void RealGuitarGemPlayer::GetRollInfo(int i1, int &start, int &end) const {
    SongData *data = TheSongDB->GetData();
    int diff = data->TrackDiffAt(mTrackNum);
    RangedDataCollection<RGRollChord> *rollInfo = data->GetRGRollInfo(mTrackNum);
    rollInfo->GetNthStartEnd(diff, i1, start, end);
}

int RealGuitarGemPlayer::GetNumTrills() const {
    SongData *data = TheSongDB->GetData();
    int diff = data->TrackDiffAt(mTrackNum);
    RangedDataCollection<RGTrill> *trillInfo = data->GetRGTrillInfo(mTrackNum);
    return trillInfo->SizeAt(diff);
}

void RealGuitarGemPlayer::GetTrillInfo(int i1, int &start, int &end) const {
    SongData *data = TheSongDB->GetData();
    int diff = data->TrackDiffAt(mTrackNum);
    RangedDataCollection<RGTrill> *trillInfo = data->GetRGTrillInfo(mTrackNum);
    trillInfo->GetNthStartEnd(diff, i1, start, end);
}

bool RealGuitarGemPlayer::GetTrillSlots(int i2, std::pair<int, int> &slots) const {
    RGTrill trill;
    SongData *data = TheSongDB->GetData();
    if (!data->GetRGTrillAtTick(mTrackNum, i2, trill)) {
        return false;
    } else {
        slots.second = slots.first = trill.unk0;
        return true;
    }
}

void RealGuitarGemPlayer::Restart(bool b1) { GemPlayer::Restart(b1); }

void RealGuitarGemPlayer::ResetController(bool b1) {
    GemPlayer::ResetController(b1);
    for (int i = 0; i < 6U; i++) {
        mRGState.FretDown(i, GetRGFret(i));
    }
}

void RealGuitarGemPlayer::SwingHook(int, int, float, bool, bool) {}
void RealGuitarGemPlayer::HitHook(int, float, int, unsigned int, GemHitFlags) {}
void RealGuitarGemPlayer::MissHook(int, int, float, int, int) {}
void RealGuitarGemPlayer::PassHook(int, float, int, bool) {}
void RealGuitarGemPlayer::SeeGemHook(int, float, int) {}

BEGIN_HANDLERS(RealGuitarGemPlayer)
    HANDLE_SUPERCLASS(GemPlayer)
    HANDLE_CHECK(0xE4)
END_HANDLERS