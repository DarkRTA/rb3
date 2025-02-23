#include "game/GemTrainerPanel.h"
#include "bandtrack/GemTrack.h"
#include "beatmatch/RGUtl.h"
#include "GemPlayer.h"
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/Game.h"
#include "game/Metronome.h"
#include "game/SongDB.h"
#include "game/TrainerGemTab.h"
#include "game/TrainerPanel.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "rndobj/Dir.h"
#include "synth/Sfx.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "utl/DataPointMgr.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include "utl/Symbols4.h"
#include "utl/TimeConversion.h"
#include <cstddef>

GemTrainerPanel *TheGemTrainerPanel;

GemTrainerPanel::GemTrainerPanel()
    : mGemPlayer(0), mTrack(0), mGemManager(0), mDifficulty(kDifficultyEasy),
      mLocalUser(0), mWriteTick(0), mScoreTick(0), mAddBeatMask(0),
      mAddBeatMaskImmediately(0), mNumLoops(0), unkb0(0), mMetronome(0), unkbc(-1.0f),
      unkc0(-1.0f), mDrawTab(0), unkc9(0), unkcc(-1), unkd0(0) {
    mTab = new TrainerGemTab();
    mMetronome = new Metronome();
}

GemTrainerPanel::~GemTrainerPanel() {
    delete mTab;
    delete mMetronome;
}

#pragma push
#pragma pool_data off
void GemTrainerPanel::Enter() {
    TheGemTrainerPanel = this;
    mLocalUser = 0;
    mGemPlayer = 0;
    mTrack = 0;
    unkd0 = 0;
    std::vector<LocalBandUser *> users;
    TheBandUserMgr->GetLocalParticipants(users);
    for (int i = 0; i < users.size() && !mGemPlayer; i++) {
        LocalBandUser *cur = users[i];
        mLocalUser = cur;
        mGemPlayer = dynamic_cast<GemPlayer *>(mLocalUser->GetPlayer());
        mTrack = dynamic_cast<GemTrack *>(mLocalUser->GetTrack());
    }

    if (mLocalUser) {
        mDifficulty = mLocalUser->GetDifficulty();
    }

    Message resetScoreMsg("reset_score");
    Handle(resetScoreMsg, true);

    TrainerPanel::Enter();
    Sfx *hiSfx = DataDir()->Find<Sfx>("metronome_hi.cue", true);
    Sfx *loSfx = DataDir()->Find<Sfx>("metronome_lo.cue", true);
    mMetronome->Enter(hiSfx, loSfx);

    mDrawTab = false;
    unkc9 = 0;
    unkcc = -1;
    if (mGemPlayer) {
        Symbol mpsong = MetaPerformer::Current()->Song();
        BandSongMetadata *data = (BandSongMetadata *)TheSongMgr->Data(
            TheSongMgr->GetSongIDFromShortName(mpsong, true)
        );
        int key = data->SongKey();
        int tone = data->SongTonality();
        if (key >= 0) {
            char notename[4];
            strcpy(notename, RGGetNoteName(key, key));
            if (tone == 1) {
                strcat(notename, "m");
                static Message msg("set_key", "");
                msg[0] = notename;
                Handle(msg, true);
            }
        } else {
            Handle(hide_key_msg, true);
        }
        SendDataPoint("trainers/song_name", song_name, mpsong);
    }
}
#pragma pop

void GemTrainerPanel::Exit() {
    TrainerPanel::Exit();
    mGemManager = 0;
    mGemPlayer = 0;
    TheGemTrainerPanel = 0;
    mMetronome->Exit();
    for (int i = 0; i < 4; i++) {
        ClearAndShrink(mSongGems[i]);
    }
    ClearAndShrink(mPattern);
}

void GemTrainerPanel::Poll() {
    if (!mTrack && mGemPlayer && mLocalUser->GetTrack()) {
        mTrack = dynamic_cast<GemTrack *>(mLocalUser->GetTrack());
        MILO_ASSERT(mTrack != NULL, 0xC1);
        mGemManager = mTrack->GetGemManager();
        MILO_ASSERT(mGemManager != NULL, 0xC5);
        for (int i = 0; i < 4; i++) {
            mGameGemLists[i] =
                (GameGemList *)TheSongDB->GetGemListByDiff(mGemPlayer->GetTrackNum(), i);
            mSongGems[i] = mGameGemLists[i]->mGems;
        }

        RndDir *gemprev = DataDir()->Find<RndDir>("gem_preview", true);
        mTab->Init(gemprev, SymToTrackType(mTrack->GetType()));
    }
    UIPanel::Poll();
    if (mGemManager && mGemPlayer && GetCurrSection() >= 0) {
        if (TheGame->IsWaiting()) {
            if (mDifficulty != mLocalUser->GetDifficulty() && !unkd0) {
                for (int i = 0; i < (int)mGemPlayer->mGemStatus->mGems.size(); i++) {
                    mGemPlayer->mGemStatus->Set0x40(i);
                }
                unkd0 = true;
            }
        } else {
            unkd0 = false;
            if (mAddBeatMaskImmediately) {
                TrainerSection &sect = GetSection(GetCurrSection());
                int ticks = GetSectionTicks(GetCurrSection());
                AddBeatMask(sect.GetStartTick() + ticks);
                mAddBeatMaskImmediately = false;
            }
            int tick = GetTick();
            if (tick >= mScoreTick && mScoreTick != 0) {
                if (mNumLoops > 0) {
                    Handle(loop_msg, true);
                }
                mScoreTick += GetLoopTicks(GetCurrSection());
                mNumLoops++;
            }
            int ooo = 0;
            if (TheUI->FocusPanel() != this) {
                ooo = 2;
            } else if (TheGame->GetMusicSpeed() != 1.0f) {
                ooo = 1;
            }
            mMetronome->Poll(tick, (Metronome::OverrideEnabled)ooo);
            HandleTrackShifting();
            Difficulty diff = mLocalUser->GetDifficulty();
            if (mDifficulty != diff) {
                mGemManager->ClearAllGems();
                mGemManager->ClearMissedPhrases();
                mTrack->GetTrackDir()->ClearAllGemWidgets();
                NewDifficulty(tick, diff);
            }
        }
    }
}

void GemTrainerPanel::Draw() {
    TrainerPanel::Draw();
    if (mGemPlayer && ShouldDrawTab()) {
        TheUI->GetCam()->Select();
        mTab->SetLefty(mGemPlayer->GetUser()->GetGameplayOptions()->GetLefty());
        mTab->Draw(GetLoopTick(GetTick()));
    }
}

void GemTrainerPanel::HandleLooping() {
    if (!(mGemManager && !TheGame->IsWaiting() && GetCurrSection() >= 0))
        return;
    else {
        int tick = GetTick();
        if (GetCurrSection() >= 0 && ShouldLoop(tick) != 0) {
            Handle(score_msg, true);
            if (mAddBeatMask) {
                AddBeatMask(mWriteTick + GetLoopTicks(GetCurrSection()));
            }
            unkc9 = false;
            mAddBeatMask = !mAddBeatMask;
            unkcc = -1;
            int start = GetSectionLoopStart(GetCurrSection());
            float ticktosec = TickToSeconds(start);
            float secs = TheTaskMgr.Seconds(TaskMgr::kRealTime);
            if (secs - ticktosec > 900.0f) {
                RestartSection();
            } else {
                CopyGems(tick);
                ResetChallenge();
                Looped();
            }
        }
    }
}

bool GemTrainerPanel::GetFretboardView(const GameGem &gem) const {
    char fret = gem.GetHighestFret();
    return fret <= 11;
}

int GemTrainerPanel::GetPatternSize() const { return mPattern.size(); }

bool GemTrainerPanel::IsGemInFutureLoop(int idx) const {
    const GameGem &gem = TheSongDB->GetGemList(mGemPlayer->GetTrackNum())->GetGem(idx);
    return mScoreTick <= gem.GetTick();
}

void GemTrainerPanel::HandlePlayerDeleted(Player *player) {
    if (player == mGemPlayer) {
        mGemPlayer = 0;
    }
}

void GemTrainerPanel::CopyGems(
    std::vector<GameGem> &gems, int sectIdx, int &iref1, int &iref2
) {
    gems.clear();
    iref1 = -1;
    iref2 = -1;
    Difficulty diff = mLocalUser->GetDifficulty();
    TrainerSection &sect = GetSection(sectIdx);
    for (int i = 0; i < mSongGems[diff].size(); i++) {
        GameGem &curGem = mSongGems[diff][i];
        if (curGem.GetTick() >= sect.GetStartTick()
            && curGem.GetTick() + curGem.GetDurationTicks() <= sect.GetEndTick()) {
            if (iref1 == -1) {
                iref1 = i;
            }
            iref2 = i;
            gems.push_back(curGem);
        }
    }
}

void GemTrainerPanel::StartSectionImpl() {
    TheSongDB->GetSongData()->GetTempoMap()->ClearLoopPoints();
    ClearGems();
    mTrack->GetBandTrack()->PracticeReset();
    TrainerSection &sect = GetSection(GetCurrSection());
    if (mGemPlayer->GetTrackType() == kTrackRealKeys) {
        unkbc = mTrack->TickToOffset(sect.GetStartTick());
        unkc0 = mTrack->TickToOffset(sect.GetEndTick());
        float range = mTrack->GetRange();
        MILO_ASSERT(range == 10.0f, 0x191);
        mTrack->OverrideRangeShift(range, unkbc);
        unkc4 = -1.0f;
    }
    SetLoopPoints();
    int i30 = -1;
    int i34 = -1;
    CopyGems(mPattern, GetCurrSection(), i30, i34);
    TheSongDB->SetTrainerGems(i30, i34);
    int i3 = sect.GetStartTick();
    int i4 = sect.GetStartTick();
    i3 -= TheSongDB->GetBeatsPerMeasure(i4) * 480;
    if (i3 < 0)
        i3 = 0;
    int numPatterns = mPattern.size();
    mGemPlayer->GetGemStatus()->Resize(numPatterns * 4);
    mWriteTick = sect.GetStartTick() + GetLoopTicks(GetCurrSection());
    CopyGems(i3);
    mWriteTick = sect.GetStartTick() + GetLoopTicks(GetCurrSection());
    mGemPlayer->ResetGemStates(TickToMs(sect.GetStartTick()));
    TheGame->Jump(TickToMs(i3), true);
    mGemManager->Jump(TickToMs(i3));
    mScoreTick = sect.GetStartTick();
    mGemPlayer->SetCrowdMeterActive(false);
    mAddBeatMask = false;
    mAddBeatMaskImmediately = true;
    mNumLoops = 0;
    unkb0 = 0;
    unkc9 = false;
    unkcc = -1;
    static Message msgUpdate("update_thermometer", 0);
    msgUpdate[0] = GetCurrSection();
    Handle(msgUpdate, true);
}

void GemTrainerPanel::SetLoopPoints() {
    if (GetCurrSection() >= 0) {
        TheSongDB->GetSongData()->GetTempoMap()->ClearLoopPoints();
        int start = GetSectionLoopStart(GetCurrSection());
        int end = GetSectionLoopEnd(GetCurrSection());
        TrainerSection &sect = GetSection(GetCurrSection());
        TheGame->GetBeatMaster()->GetAudio()->GetSongStream()->ClearJump();
        float startMs = TickToMs(start);
        float endMs = TickToMs(end);
        TheGame->GetBeatMaster()->GetAudio()->GetSongStream()->SetJump(
            endMs, startMs, nullptr
        );
        TheSongDB->GetSongData()->GetTempoMap()->SetLoopPoints(start, end);
    }
}

void GemTrainerPanel::CopyGems(int tick) {
    if (mGemManager) {
        float ms = TickToMs(tick);
        mGemPlayer->FinishAllHeldNotes(ms);
        Difficulty diff = mLocalUser->GetDifficulty();
        TrainerSection &sect = GetSection(GetCurrSection());
        int i5 = GetLoopTicks(GetCurrSection());
        int i1 = mWriteTick - i5;
        int startTick = sect.GetStartTick();
        mGameGemLists[diff]->SetGems(startTick, i1, mWriteTick, mPattern, 4);
        mGemManager->ClearAllGems();
        mGemManager->ClearMissedPhrases();
        mTrack->GetTrackDir()->ClearAllGemWidgets();
        TheSongDB->RecalculateGemTimes(mGemPlayer->GetTrackNum());
        if (unkb0 == 0) {
            i5 = 0;
            i1 = mPattern.size();
        } else {
            i5 = mPattern.size();
            i1 = mPattern.size() * 2;
        }
        std::vector<int> intVec;
        intVec.reserve(mPattern.size());
        for (int i = i5; i < i1; i++) {
            MILO_ASSERT(i < mGemPlayer->GetGemStatus()->GetSize(), 0x1FC);
            intVec.push_back(mGemPlayer->GetGemStatus()->GetHit(i));
        }
        int numPatterns = mPattern.size();
        mGemPlayer->GetGemStatus()->Resize(numPatterns * 4);
        mGemPlayer->ResetGemStates(ms);
        for (int i = 0; i < mPattern.size(); i++) {
            if (intVec[i] != 0) {
                MILO_ASSERT(i < mGemPlayer->GetGemStatus()->GetSize(), 0x207);
                mGemPlayer->GetGemStatus()->SetHit(i);
            } else {
                MILO_ASSERT(i < mGemPlayer->GetGemStatus()->GetSize(), 0x20C);
                mGemPlayer->GetGemStatus()->Set0x2(i);
            }
            mGemPlayer->GetGemStatus()->Set0x40(i);
            mGameGemLists[diff]->GetGem(i).SetPlayed(true);
        }
        mGemManager->SetupGems(0);
        mWriteTick += GetLoopTicks(GetCurrSection());
        unkb0++;
        PostCopyGems();
    }
}

const GameGem &GemTrainerPanel::GetLastGameGemInSection(int &gemID) const {
    MILO_ASSERT(!mPattern.empty(), 0x221);
    gemID = mPattern.size() * 2 - 1;
    if (unkb0 == 0)
        gemID = mPattern.size() - 1;
    return mGameGemLists[mLocalUser->GetDifficulty()]->GetGem(gemID);
}

void GemTrainerPanel::HandleTrackShifting() {
    if (!TheGame->IsPaused() && mTrack->GetType() == real_keys) {
        TrainerSection &sect = GetSection(GetCurrSection());
        float range = mTrack->GetRange();
        MILO_ASSERT(range == 10.0f, 0x233);

        // clang-format off
        // iVar3 = TrainerPanel::GetCurrSection(this);
        // this_00 = TrainerPanel::GetSection(this,iVar3);
        // fVar2 = *(*(this + 0x70) + 0xc4);
        // if (fVar2 != 10.0) {
        //   pcVar4 = ::MakeString(kAssertStr,s_GemTrainerPanel.cpp_80b7ec04,0x233,
        //                         s_range_==_10.0f_80b7ec47);
        //   Debug::Fail(TheDebug,pcVar4);
        // }
        // iVar3 = TrainerPanel::GetTick(this);
        // if ((*(this + 0xc4) < 0.0) || (iVar5 = TrainerSection::GetStartTick(this_00), iVar3 < iVar5)) {
        //   GemTrack::OverrideRangeShift(*(this + 0x70),fVar2,*(this + 0xbc));
        //   *(this + 0xc4) = *(*(this + 0x70) + 0xc8);
        // }
        // else {
        //   iVar3 = GetLoopTick(iVar3);
        //   iVar5 = TrainerSection::GetEndTick(this_00);
        //   if (iVar5 < iVar3) {
        //     if (*(this + 0xbc) <= *(this + 0xc4)) {
        //       if (*(this + 0xbc) < *(this + 0xc4)) {
        //         dVar6 = TaskMgr::DeltaSeconds(&TheTaskMgr);
        //         fVar1 = -(dVar6 * 10.0 - *(this + 0xc4));
        //         *(this + 0xc4) = fVar1;
        //         if (fVar1 < *(this + 0xbc)) {
        //           fVar1 = *(this + 0xbc);
        //         }
        //         *(this + 0xc4) = fVar1;
        //       }
        //     }
        //     else {
        //       dVar6 = TaskMgr::DeltaSeconds(&TheTaskMgr);
        //       fVar1 = dVar6 * 10.0 + *(this + 0xc4);
        //       *(this + 0xc4) = fVar1;
        //       if (*(this + 0xbc) < fVar1) {
        //         fVar1 = *(this + 0xbc);
        //       }
        //       *(this + 0xc4) = fVar1;
        //     }
        //     GemTrack::OverrideRangeShift(*(this + 0x70),fVar2,*(this + 0xc4));
        //   }
        //   else {
        //     *(this + 0xc4) = *(*(this + 0x70) + 200);
        //   }
        // }
        // clang-format on
    }
}