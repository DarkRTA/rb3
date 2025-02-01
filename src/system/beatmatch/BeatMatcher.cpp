#include "beatmatch/BeatMatcher.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "beatmatch/DrumPlayer.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/MercurySwitchFilter.h"
#include "beatmatch/Output.h"
#include "beatmatch/Playback.h"
#include "obj/Data.h"
#include "os/Debug.h"

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
    : mWaitingForAudio(1), mUserGuid(u), unk1c(i1), unk20(i2), mControllerType(s),
      mSongData(data), mCfg(arr), mSink(0), mAudio(bm->GetMasterAudio()), mController(0),
      mMercurySwitchFilter(0), mWatcher(0), mDrumPlayer(new DrumPlayer(info)),
      mCurTrack(-1), unk60(1), mNow(0), unk7c(0), unk80(0), unk84(0), unk8c(0), unk90(0),
      unk94(0), unk95(0), unk98(0), unk9c(0), unka0(0x7fffffff), unka4(-1), unka8(-1),
      unkad(0), unkae(0), unkaf(0), unkb0(1), unkb8(1), unkb9(1) {
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
        unk80 = 0;
        unk8c = 0;
        unk84 = 0;
        unk88 = false;
        unka0 = 0x7FFFFFFF;
        unka4 = -1;
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
    if (!unkad) {
        MILO_ASSERT(mSink, 0xCF);
        mSink->FretButtonDown(i1, mNow);
        GameGemList *gemList = mSongData->GetGemList(mCurTrack);
        if (!gemList->Empty()) {
            if (TheBeatMatchOutput.IsActive()) {
                TheBeatMatchOutput.Print(MakeString(
                    "(%2d%10.1f DOWN\t%d\t%d)\n",
                    TheBeatMatchPlayback.GetPlaybackNum(this),
                    mNow + unk98,
                    i1,
                    i2
                ));
            }
            mWatcher->FretButtonDown(i1);
        }
    }
}

void BeatMatcher::RGFretButtonDown(int iii) {
    if (!unkad) {
        GameGemList *gemList = mSongData->GetGemList(mCurTrack);
        if (!gemList->Empty()) {
            mSink->FretButtonDown(iii, mNow);
            mWatcher->RGFretButtonDown(iii);
        }
    }
}

void BeatMatcher::FretButtonUp(int i1) {
    if (!unkad) {
        MILO_ASSERT(mSink, 0xF1);
        mSink->FretButtonUp(i1, mNow);
        GameGemList *gemList = mSongData->GetGemList(mCurTrack);
        if (!gemList->Empty()) {
            if (TheBeatMatchOutput.IsActive()) {
                TheBeatMatchOutput.Print(MakeString(
                    "(%2d%10.1f UP\t%d)\n",
                    TheBeatMatchPlayback.GetPlaybackNum(this),
                    mNow + unk98,
                    i1
                ));
            }
            mWatcher->FretButtonUp(i1);
        }
    }
}

bool BeatMatcher::Swing(int i1, bool b2, bool b3, bool b4, bool b5, GemHitFlags flags) {
    if (!unkad) {
        if (!mSongData->GetGemList(mCurTrack)->Empty()) {
            float f1 = unk80;
            bool ret = false;
            int bucket = mController->GetVelocityBucket(i1);
            if (bucket != 0 && (mNow - f1 <= 25.0f) && unk8c > 1 && bucket == 1)
                ret = true;
            if (b5 && mNow <= unk80 + 52.0f)
                ret = true;
            if (b2) {
                if (mNow <= unk80 + 150.0f && unk88 == b3 && mNow <= unk84 + 50.0f)
                    ret = true;
                unk88 = b3;
            }
            MILO_ASSERT(mSink, 0x139);
            mSink->Swing(mCurTrack, i1, mNow, b3, b4);
            if (TheBeatMatchOutput.IsActive()) {
                TheBeatMatchOutput.Print(MakeString(
                    "(%2d%10.1f SWING\t%d %d)\n",
                    TheBeatMatchPlayback.GetPlaybackNum(this),
                    i1,
                    b2
                ));
            }
            if (!b3)
                flags = (GemHitFlags)(flags | kGemHitFlagUpstrum);
            bool watcherSwing = mWatcher->Swing(i1, b2, ret, flags);
            if (watcherSwing) {
                unk80 = mNow;
                if (bucket != 0) {
                    unk8c = bucket;
                }
            }
            if (watcherSwing)
                return watcherSwing;
            if (TheBeatMatchOutput.IsActive()) {
                TheBeatMatchOutput.Print(MakeString(
                    "(%2d%10.1f NOSWING\t%d %d)\n",
                    TheBeatMatchPlayback.GetPlaybackNum(this),
                    i1,
                    b2
                ));
                return false;
            }
        }
    }
    return false;
}