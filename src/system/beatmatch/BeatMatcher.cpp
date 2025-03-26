#include "beatmatch/BeatMatcher.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "beatmatch/DrumMap.h"
#include "beatmatch/DrumPlayer.h"
#include "beatmatch/FillInfo.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/MercurySwitchFilter.h"
#include "beatmatch/Output.h"
#include "beatmatch/Playback.h"
#include "beatmatch/RGChords.h"
#include "beatmatch/TrackType.h"
#include "beatmatch/TrackWatcher.h"
#include "decomp.h"
#include "game/Player.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "utl/MakeString.h"
#include <climits>

BeatMatcher::BeatMatcher(
    const UserGuid &u,
    int i1,
    int i2,
    Symbol s,
    SongData *data,
    SongInfo &info,
    DataArray *arr,
    BeatMaster *bm
)
    : mWaitingForAudio(1), mUserGuid(u), mPlayerSlot(i1), mNumPlayers(i2),
      mControllerType(s), mSongData(data), mCfg(arr), mSink(0), mAudio(bm->GetAudio()),
      mController(0), mMercurySwitchFilter(0), mWatcher(0),
      mDrumPlayer(new DrumPlayer(info)), mCurTrack(-1), unk60(1), mNow(0), mTick(0),
      mLastSwing(0), mLastReleaseSwing(0), mLastVelocityBucket(0),
      mRawMercurySwitchState(0), mMercurySwitchState(0), mForceMercurySwitch(0),
      mSyncOffset(0), mDrivingPitchBendExternally(0), mFillStartTick(0x7fffffff),
      mLastFillEndTick(-1), mCodaStartTick(-1), mAutoplay(0), mForceFill(0), mNoFills(0),
      mFillAudio(1), mEnableWhammy(1), mEnableCapStrip(1) {
    mSongData->AddBeatMatcher(this);
    DataArray *filterArr = arr->FindArray("mercury_switch_filter", false);
    if (filterArr) {
        mMercurySwitchFilter = NewMercurySwitchFilter(filterArr->Array(1));
    }
    TheBeatMatchPlayback.AddSink(this);
}

void BeatMatcher::PostDynamicAdd(int i, float f) {
    mSongData->PostDynamicAdd(this, i);
    SetTrack(i);
    mAudio->ResetTrack(mCurTrack, true);
    ResetGemStates(f);
}

void BeatMatcher::Leave() { mAudio->ResetTrack(mCurTrack, false); }

BeatMatcher::~BeatMatcher() {
    mSongData->RemoveBeatMatcher(this);
    delete mWatcher;
    delete mMercurySwitchFilter;
    delete mDrumPlayer;
}

void BeatMatcher::PostLoad() {}

bool BeatMatcher::IsReady() {
    if (mWaitingForAudio) {
        if (mAudio->Fail() || mAudio->IsReady())
            mWaitingForAudio = false;
    }
    return !mWaitingForAudio;
}

void BeatMatcher::Start() {
    if (TheBeatMatchOutput.IsActive()) {
        TheBeatMatchOutput.Print(MakeString(
            "(%2d%10.1f TRACK\t%d)\n",
            TheBeatMatchPlayback.GetPlaybackNum(this),
            mNow,
            mCurTrack
        ));
    }
}

void BeatMatcher::AddTrack(int, Symbol, SongInfoAudioType, TrackType t, bool) {
    mTrackTypes.push_back(t);
    unk50.push_back(0);
}

void BeatMatcher::RegisterSink(BeatMatchSink &sink) { mSink = &sink; }

void BeatMatcher::Poll(float f) {
    SetNow(f);
    if (mController)
        mController->Poll();
    CheckMercurySwitch(mNow);
    mWatcher->Poll(f);
}

void BeatMatcher::Jump(float f) {
    if (mNow != f) {
        SetNow(f);
        mLastSwing = 0;
        mLastVelocityBucket = 0;
        mLastReleaseSwing = 0;
        unk88 = false;
        mFillStartTick = 0x7FFFFFFF;
        mLastFillEndTick = -1;
        mWatcher->Jump(f);
        if (mMercurySwitchFilter)
            mMercurySwitchFilter->Reset();
        mWaitingForAudio = true;
    }
}

void BeatMatcher::Restart() { mWatcher->Restart(); }

void BeatMatcher::ResetGemStates(float f) {
    mWatcher->RecalcGemList();
    mWatcher->Jump(f);
}

void BeatMatcher::FretButtonDown(int i1, int i2) {
    if (!mAutoplay) {
        MILO_ASSERT(mSink, 0xCF);
        mSink->FretButtonDown(i1, mNow);
        GameGemList *gemList = mSongData->GetGemList(mCurTrack);
        if (!gemList->Empty()) {
            if (TheBeatMatchOutput.IsActive()) {
                TheBeatMatchOutput.Print(MakeString(
                    "(%2d%10.1f DOWN\t%d\t%d)\n",
                    TheBeatMatchPlayback.GetPlaybackNum(this),
                    mNow + mSyncOffset,
                    i1,
                    i2
                ));
            }
            mWatcher->FretButtonDown(i1);
        }
    }
}

void BeatMatcher::RGFretButtonDown(int iii) {
    if (!mAutoplay) {
        GameGemList *gemList = mSongData->GetGemList(mCurTrack);
        if (!gemList->Empty()) {
            mSink->FretButtonDown(iii, mNow);
            mWatcher->RGFretButtonDown(iii);
        }
    }
}

void BeatMatcher::FretButtonUp(int i1) {
    if (!mAutoplay) {
        MILO_ASSERT(mSink, 0xF1);
        mSink->FretButtonUp(i1, mNow);
        GameGemList *gemList = mSongData->GetGemList(mCurTrack);
        if (!gemList->Empty()) {
            if (TheBeatMatchOutput.IsActive()) {
                TheBeatMatchOutput.Print(MakeString(
                    "(%2d%10.1f UP\t%d)\n",
                    TheBeatMatchPlayback.GetPlaybackNum(this),
                    mNow + mSyncOffset,
                    i1
                ));
            }
            mWatcher->FretButtonUp(i1);
        }
    }
}

bool BeatMatcher::Swing(int i1, bool b2, bool b3, bool b4, bool b5, GemHitFlags flags) {
    if (mAutoplay || mSongData->GetGemList(mCurTrack)->Empty())
        return false;
    else {
        float f1 = mLastSwing;
        bool ret = false;
        int bucket = mController->GetVelocityBucket(i1);
        if (bucket != 0 && (mNow - f1 <= 25.0f) && mLastVelocityBucket >= 2
            && bucket == 1)
            ret = true;
        if (b5 && mLastSwing + 52.0f >= mNow)
            ret = true;
        if (b2) {
            if (mLastSwing + 150.0f >= mNow && unk88 == b3
                && mLastReleaseSwing + 50.0f >= mNow)
                ret = true;
            unk88 = b3;
        }
        MILO_ASSERT(mSink, 0x139);
        mSink->Swing(mCurTrack, i1, mNow, b3, b4);
        if (TheBeatMatchOutput.IsActive()) {
            TheBeatMatchOutput.Print(MakeString(
                "(%2d%10.1f SWING\t%d %d)\n",
                TheBeatMatchPlayback.GetPlaybackNum(this),
                mNow + mSyncOffset,
                i1,
                b2
            ));
        }
        if (!b3)
            flags = (GemHitFlags)(flags | kGemHitFlagUpstrum);
        bool watcherSwing = mWatcher->Swing(i1, b2, ret, flags);
        if (watcherSwing) {
            mLastSwing = mNow;
            if (bucket != 0) {
                mLastVelocityBucket = bucket;
            }
        }
        if (!watcherSwing) {
            if (TheBeatMatchOutput.IsActive()) {
                TheBeatMatchOutput.Print(MakeString(
                    "(%2d%10.1f NOSWING\t%d %d)\n",
                    TheBeatMatchPlayback.GetPlaybackNum(this),
                    mNow + mSyncOffset,
                    i1,
                    b2
                ));
            }
        }
        return watcherSwing;
    }
}

void BeatMatcher::ReleaseSwing() { mLastReleaseSwing = mNow; }
void BeatMatcher::OutOfRangeSwing() { mSink->OutOfRangeSwing(); }

void BeatMatcher::NonStrumSwing(int i1, bool b2, bool b3) {
    if (mAutoplay || mSongData->GetGemList(mCurTrack)->Empty())
        return;
    mWatcher->NonStrumSwing(i1, b2, b3);
    if (TheBeatMatchOutput.IsActive()) {
        TheBeatMatchOutput.Print(MakeString(
            "(%2d%10.1f HOPO\t%d %d)\n",
            TheBeatMatchPlayback.GetPlaybackNum(this),
            mNow + mSyncOffset,
            i1,
            b2
        ));
    }
}

void BeatMatcher::MercurySwitch(float f1) {
    if (!mAutoplay) {
        if (TheBeatMatchOutput.IsActive() && mRawMercurySwitchState != f1) {
            TheBeatMatchOutput.Print(MakeString(
                "(%2d%10.1f FLIP\t%4.2f)\n",
                TheBeatMatchPlayback.GetPlaybackNum(this),
                mNow + mSyncOffset,
                f1
            ));
        }
        mRawMercurySwitchState = f1;
    }
}

void BeatMatcher::ForceMercurySwitch(bool b) {
    if (!mAutoplay) {
        mForceMercurySwitch = b;
        mMercurySwitchState = b;
        UpdateMercurySwitch();
        if (TheBeatMatchOutput.IsActive()) {
            TheBeatMatchOutput.Print(MakeString(
                "(%2d%10.1f FFLIP\t%d)\n",
                TheBeatMatchPlayback.GetPlaybackNum(this),
                mNow,
                b
            ));
        }
    }
}

void BeatMatcher::SetController(BeatMatchController *controller) {
    MILO_ASSERT(controller && controller->GetUser()->GetUserGuid() == mUserGuid, 0x1AA);
    mController = controller;
}

void BeatMatcher::NoteOn(int i) { mSink->NoteOn(i); }
void BeatMatcher::NoteOff(int i) { mSink->NoteOff(i); }
void BeatMatcher::PlayNote(int i) { mSink->PlayNote(i); }

void BeatMatcher::SetTrack(int track) {
    if (mWatcher)
        MILO_ASSERT(mCurTrack == track, 0x1C9);
    else {
        MILO_ASSERT(mCurTrack == -1, 0x1CE);
        mCurTrack = track;
        mWatcher = new TrackWatcher(
            track,
            mUserGuid,
            mPlayerSlot,
            mControllerType,
            mSongData,
            this,
            mCfg->FindArray("watcher", false)
        );
        MILO_ASSERT(mSink, 0x1D9);
        mWatcher->AddSink(mSink);
        MILO_ASSERT(mAudio, 0x1DA);
        mWatcher->AddSink(mAudio);
        mWatcher->SetIsCurrentTrack(true);
        mWatcher->SetSyncOffset(mSyncOffset);
        mAudio->SetTrack(mUserGuid, track);
        if (TheBeatMatchOutput.IsActive()) {
            TheBeatMatchOutput.Print(MakeString(
                "(%2d%10.1f TRACK\t%d)\n",
                TheBeatMatchPlayback.GetPlaybackNum(this),
                mNow + mSyncOffset,
                mCurTrack
            ));
        }
    }
}

void BeatMatcher::UpdateMercurySwitch() {
    bool b = mMercurySwitchState;
    MILO_ASSERT(mSink, 0x1ED);
    mSink->MercurySwitch(b, mNow);
}

int BeatMatcher::GetVelocityBucket(int i) {
    MILO_ASSERT(mController, 0x1F5);
    return mController->GetVelocityBucket(i);
}

int BeatMatcher::GetVirtualSlot(int i) {
    MILO_ASSERT(mController, 0x1FB);
    return mController->GetVirtualSlot(i);
}

void BeatMatcher::PlayDrum(int i1, bool b2, float f3) {
    if (!b2 || mFillAudio) {
        mDrumPlayer->Play(i1, f3);
    }
}

void BeatMatcher::SetDrumKitBank(ObjectDir *bank) {
    MILO_ASSERT(bank, 0x208);
    mDrumPlayer->mDrumKitBank = bank;
}

DECOMP_FORCEACTIVE(BeatMatcher, "seq_list")

float BeatMatcher::GetWhammyBar() const {
    MILO_ASSERT(mController, 0x21B);
    if (mEnableWhammy)
        return mController->GetWhammyBar();
    else
        return 0;
}

float BeatMatcher::GetCapStrip() const {
    MILO_ASSERT(mController, 0x225);
    if (mEnableCapStrip)
        return mController->GetCapStrip();
    else
        return 0;
}

int BeatMatcher::GetMaxSlots() const {}

TrackType BeatMatcher::GetTrackType(int idx) const { return mTrackTypes[idx]; }
bool BeatMatcher::IsAutoplay() { return mAutoplay; }

void BeatMatcher::SetAutoplay(bool autoplay) {
    mAutoplay = autoplay;
    mWatcher->SetCheating(autoplay);
}

void BeatMatcher::AutoplayCoda(bool b) { mWatcher->SetAutoplayCoda(b); }
void BeatMatcher::SetAutoplayError(int err) { mWatcher->SetAutoplayError(err); }
void BeatMatcher::SetAutoOn(bool b) { mAudio->SetAutoOn(mCurTrack, b); }
float BeatMatcher::CycleAutoplayAccuracy() { return mWatcher->CycleAutoplayAccuracy(); }
void BeatMatcher::SetAutoplayAccuracy(float f) { mWatcher->SetAutoplayAccuracy(f); }
void BeatMatcher::DrivePitchBendExternally(bool b) { mDrivingPitchBendExternally = b; }

void BeatMatcher::SetPitchBend(int i1, float f2, bool b3) {
    if (mTrackTypes[i1] != kTrackDrum && b3 == mDrivingPitchBendExternally
        && f2 != unk50[i1] && !b3) {
        mAudio->SetSpeed(i1, mUserGuid, powf(1.059463143348694, f2));
    }
    unk50[i1] = f2;
}

void BeatMatcher::ResetPitchBend(int i1) {
    if (mTrackTypes[i1] != kTrackDrum && i1 == mCurTrack && mAudio) {
        mAudio->ResetSlipTrack(mCurTrack, false);
    }
    unk50[i1] = 0;
}

bool BeatMatcher::InFillNow() { return InFill(mSongPos.GetTotalTick(), true); }

bool BeatMatcher::InFill(int i1, bool b2) {
    if (mForceFill)
        return true;
    if (mCurTrack >= mTrackTypes.size())
        return false;
    TrackType curTrackType = mTrackTypes[mCurTrack];
    if (!FillsEnabled(mCurTrack))
        return false;
    else {
        int tick = mSongData->GetTempoMap()->GetLoopTick(i1);
        if (curTrackType == kTrackDrum || curTrackType == kTrackGuitar
            || curTrackType == kTrackBass || curTrackType == kTrackNone) {
            return mSongData->GetFillInfo(mCurTrack)->FillAt(tick, b2);
        } else
            return false;
    }
}

bool BeatMatcher::InSolo(int i) {
    return mSongData->GetPhraseList(mCurTrack, kSoloPhrase).IsTickInPhrase(i);
}

bool BeatMatcher::InCoda(int i) { return mCodaStartTick != -1 && i >= mCodaStartTick; }

bool BeatMatcher::InCodaFreestyle(int i1, bool b2) {
    return InCoda(i1) && mSongData->GetDrumFillInfo(mCurTrack)->FillAt(i1, b2);
}

void BeatMatcher::SetCodaStartTick(int tick) { mCodaStartTick = tick; }
void BeatMatcher::EnterCoda() { SetFillsEnabled(true); }

void BeatMatcher::SetButtonMashingMode(bool b) {
    TrackType curTrackType = mTrackTypes[mCurTrack];
    if (curTrackType - 10U > 2 && curTrackType != kTrackDrum
        && curTrackType != kTrackVocals) {
        mAudio->SetButtonMashingMode(mCurTrack, b);
    }
}

void BeatMatcher::Enable(bool b) {
    mWatcher->Enable(b);
    EnableController(b);
    if (!b)
        mAudio->MuteTrack(mCurTrack);
}

void BeatMatcher::EnableController(bool b) {
    MILO_ASSERT(mController, 0x2F6);
    mController->Disable(!b);
}

bool BeatMatcher::FillsEnabled(int i) {
    if (mForceFill)
        return true;
    else
        return !mNoFills && (i >= mFillStartTick || i <= mLastFillEndTick);
}

void BeatMatcher::SetFillsEnabled(bool b) {
    if (b)
        SetFillsEnabled(mTick, false);
    else {
        int i2 = mFillStartTick;
        SetFillsEnabled(INT_MAX, false);
        if (i2 != INT_MAX) {
            int tick = mSongPos.GetTotalTick();
            FillExtent ext(-1, -1, false);
            if (mSongData->GetFillInfo(mCurTrack)->FillExtentAtOrBefore(tick, ext)) {
                mLastFillEndTick = ext.end;
            }
        }
    }
}

void BeatMatcher::DisableFillsCompletely() {
    SetFillsEnabled(0x7fffffff, false);
    mLastFillEndTick = -1;
}

void BeatMatcher::SetFillsEnabled(int i1, bool b2) {
    mFillStartTick = 0;
    if (i1 != INT_MAX && InFill(i1, true) && !b2) {
        FillExtent ext(0, 0, false);
        int i28 = 0;
        i1 = mSongData->GetTempoMap()->GetLoopTick(i1, i28);
        if (mSongData->GetFillInfo(mCurTrack)->NextFillExtents(i1, ext)) {
            i1 = ext.start + i28;
        }
    }
    mFillStartTick = i1;
}

void BeatMatcher::ForceFill(bool b) { mForceFill = b; }

bool BeatMatcher::IsFillCompletion(int i1) {
    if (!FillsEnabled(i1))
        return false;
    else {
        FillExtent ext(0, 0, false);
        return mSongData->GetFillInfo(mCurTrack)->FillAt(i1, ext, true) && ext.end == i1;
    }
}

void BeatMatcher::SetFillLogic(FillLogic logic) { mFillLogic = logic; }
FillLogic BeatMatcher::GetFillLogic() const { return mFillLogic; }

unsigned int BeatMatcher::GetRGRollSlots(int i1) const {
    MILO_ASSERT(mSongData, 0x366);
    RGRollChord chord = mSongData->GetRGRollingSlotsAtTick(mCurTrack, i1);
    unsigned int slots = 0;
    for (int i = 0, mask = 1; i < 6; i++, mask <<= 1) {
        if (chord.mString[i] != -1) {
            slots |= mask;
        }
    }
    return slots;
}

void BeatMatcher::SetSyncOffset(float offset) {
    mSyncOffset = offset;
    if (mWatcher)
        mWatcher->SetSyncOffset(offset);
}

void BeatMatcher::SetControllerType(Symbol s) {
    if (mControllerType != s) {
        mControllerType = s;
        mWatcher->ReplaceImpl(s);
    }
}

bool BeatMatcher::UsingAlternateButtons() const {
    return mController && mController->IsShifted();
}

void BeatMatcher::EnableWhammy(bool b) { mEnableWhammy = b; }
void BeatMatcher::EnableCapStrip(bool b) { mEnableCapStrip = b; }
void BeatMatcher::E3CheatIncSlop() { mWatcher->E3CheatIncSlop(); }
void BeatMatcher::E3CheatDecSlop() { mWatcher->E3CheatDecSlop(); }

void BeatMatcher::CheckMercurySwitch(float f) {
    if (mMercurySwitchFilter) {
        bool b1 =
            mMercurySwitchFilter->Poll(f, mRawMercurySwitchState) | mForceMercurySwitch;
        if (b1 != mMercurySwitchState) {
            mMercurySwitchState = b1;
            UpdateMercurySwitch();
        }
    }
}

void BeatMatcher::SetNow(float f) {
    mNow = f;
    mSongPos = mSongData->CalcSongPos(f);
    mTick = mSongPos.GetTotalTick();
}
