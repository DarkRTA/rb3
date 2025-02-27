#include "game/GemTrainerPanel.h"
#include "bandtrack/GemTrack.h"
#include "beatmatch/RGUtl.h"
#include "GemPlayer.h"
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/Game.h"
#include "game/GameMode.h"
#include "game/Metronome.h"
#include "game/SongDB.h"
#include "game/TrainerGemTab.h"
#include "game/TrainerPanel.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "rndobj/Dir.h"
#include "synth/Sfx.h"
#include "track/TrackWidget.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "utl/DataPointMgr.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
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
    TheSongDB->GetData()->GetTempoMap()->ClearLoopPoints();
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
        TheSongDB->GetData()->GetTempoMap()->ClearLoopPoints();
        int start = GetSectionLoopStart(GetCurrSection());
        int end = GetSectionLoopEnd(GetCurrSection());
        TrainerSection &sect = GetSection(GetCurrSection());
        TheGame->GetBeatMaster()->GetAudio()->GetSongStream()->ClearJump();
        float startMs = TickToMs(start);
        float endMs = TickToMs(end);
        TheGame->GetBeatMaster()->GetAudio()->GetSongStream()->SetJump(
            endMs, startMs, nullptr
        );
        TheSongDB->GetData()->GetTempoMap()->SetLoopPoints(start, end);
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
    if (TheGame->IsPaused())
        return;
    if (mTrack->GetType() != real_keys)
        return;
    TrainerSection &sect = GetSection(GetCurrSection());
    float range = mTrack->GetRange();
    MILO_ASSERT(range == 10.0f, 0x233);
    int tick = GetTick();
    if (unkc4 < 0 || tick < sect.GetStartTick()) {
        mTrack->OverrideRangeShift(range, unkbc);
        unkc4 = mTrack->GetOffset();
    } else {
        tick = GetLoopTick(tick);
        if (tick > sect.GetEndTick()) {
            if (unkc4 < unkbc) {
                unkc4 += TheTaskMgr.DeltaSeconds() * 10.0f;
                unkc4 = Min(unkc4, unkbc);
            } else if (unkc4 > unkbc) {
                unkc4 -= TheTaskMgr.DeltaSeconds() * 10.0f;
                unkc4 = Max(unkc4, unkbc);
            }
            mTrack->OverrideRangeShift(range, unkc4);
        } else {
            unkc4 = mTrack->GetOffset();
        }
    }
}

bool GemTrainerPanel::ShouldLoop(int i1) const {
    if (!unkc9)
        return false;
    else {
        const GameGem &gem = mGemManager->GetGem(unkcc).GetGameGem();
        if (!gem.IgnoreDuration()) {
            int i2 = GetTick();
            int i4 = gem.GetTick() + gem.GetDurationTicks();
            if (mGemManager->GetNumGems() > unkcc + 1) {
                i4 = Min(i4, mGemManager->GetGem(unkcc + 1).GetGameGem().GetTick() - 120);
            }
            if (i2 < i4)
                return false;
        }
        return true;
    }
}

void GemTrainerPanel::ClearGems() {
    if (mTrack && mGemManager) {
        mGemManager->ClearAllGems();
        mTrack->GetTrackDir()->ResetSmashers(true);
        mTrack->RebuildBeats();
    }
}

void GemTrainerPanel::SetSpeedRatio(float f1) {
    TheGame->SetMusicSpeed(f1);
    mGemPlayer->SetPitchShiftRatio(1.0f / f1);
    SendDataPoint("trainers/speed", speed_ratio, f1);
}

void GemTrainerPanel::AddBeatMask(int i1) {
    if (TheGame->mProperties.mHasBeatMask) {
        int i2 = GetLoopTicks(GetCurrSection());
        float f4 = TickToSeconds(i1);
        float f5 = TickToSeconds(i1 + i2) - f4;
        Transform tf60;
        mTrack->GetTrackDir()->MakeSecondsXfm(f4, tf60);
        tf60.m.y.y = mTrack->GetTrackDir()->SecondsToY(f5);
        static Symbol beatMask = "beat_mask.wid";
        TrackWidget *w = mGemManager->GetWidgetByName(beatMask);
        w->AddInstance(tf60, f5);
    }
}

void GemTrainerPanel::ScoreOnFinalGem(int i1) {
    if (mPattern.empty() || i1 < 0)
        return;
    else {
        if (i1 % mPattern.size() == mPattern.size() - 1) {
            unkc9 = true;
            unkcc = i1;
        }
    }
}

void GemTrainerPanel::SetTab(int i1) {
    std::vector<GameGem> gems;
    int i24 = -1;
    int i20 = -1;
    CopyGems(gems, i1, i24, i20);
    mTab->SetPattern(&GetSection(i1), gems);
}

float GemTrainerPanel::GetLessonCompleteSpeed(int i1) const {
    Symbol name = GetNameForSection(i1);
    return GetBandProfile()->GetLessonCompleteSpeed(name);
}

bool GemTrainerPanel::ShouldDrawTab() const { return mDrawTab; }

bool GemTrainerPanel::ShouldStartEarly() const {
    return TrainerPanel::ShouldStartEarly() || (unkbc != unkc0);
}

void GemTrainerPanel::NewDifficulty(int i1, int i2) {
    TrainerPanel::NewDifficulty(i1, i2);
    SetTab(GetCurrSection());
    mDifficulty = (Difficulty)i2;
    UpdateProgressMeter();
    TrainerPanel::RestartSection();
}

void GemTrainerPanel::EnableMetronome(bool b1) {
    mMetronome->Enable(b1);
    SendDataPoint("trainers/metronome", enable_metronome, b1);
}

void GemTrainerPanel::SetMetronomeVolume(int i1, int i2) {
    mMetronome->SetVolume(i1, i2);
}

bool GemTrainerPanel::ShouldMissCauseFail() const {
    if (GetCurrSection() < 0)
        return false;
    else {
        int tick = GetTick();
        const TrainerSection &sect = GetSection(GetCurrSection());
        if (tick < sect.GetStartTick())
            return false;
        else {
            int id;
            return tick <= GetLastGameGemInSection(id).GetTick();
        }
    }
}

Difficulty GemTrainerPanel::GetDifficulty() const { return mLocalUser->GetDifficulty(); }
int GemTrainerPanel::GetNumLoops() const { return mNumLoops; }

void GemTrainerPanel::UpdateProgressMeter() {
    if (mGemPlayer) {
        if (!TheGameMode->Property("song_lessons", true)->Int()) {
            for (int i = 0; i < GetNumSections(); i++) {
                mProgressMeter->SetCompleted(
                    i, GetBandProfile()->IsLessonComplete(GetNameForSection(i), 1.0f)
                );
            }
        } else {
            Difficulty diff = mGemPlayer->GetUser()->GetLocalBandUser()->GetDifficulty();
            int songID = TheSongMgr->GetSongIDFromShortName(
                MetaPerformer::Current()->Song(), true
            );
            for (int i = 0; i < GetNumSections(); i++) {
                mProgressMeter->SetCompleted(
                    i, IsSongSectionComplete(GetBandProfile(), songID, diff, i)
                );
            }
        }
    }
}

BEGIN_HANDLERS(GemTrainerPanel)
    HANDLE_ACTION(clear_gems, ClearGems())
    HANDLE_ACTION(set_speed_ratio, SetSpeedRatio(_msg->Float(2)))
    HANDLE_EXPR(get_num_gems_float, (float)NumGems())
    HANDLE_ACTION(score_on_final_gem, ScoreOnFinalGem(_msg->Int(2)))
    HANDLE_ACTION(set_tab, SetTab(_msg->Int(2)))
    HANDLE_ACTION(set_loop_points, SetLoopPoints())
    HANDLE_EXPR(get_lesson_complete_speed, GetLessonCompleteSpeed(_msg->Int(2)))
    HANDLE_ACTION(enable_metronome, EnableMetronome(_msg->Int(2)))
    HANDLE_EXPR(metronome_enabled, mMetronome->Enabled())
    HANDLE_ACTION(set_metronome_volume, SetMetronomeVolume(_msg->Int(2), _msg->Int(3)))
    HANDLE_EXPR(get_metronome_volume, mMetronome->GetVolume(_msg->Int(2)))
    HANDLE_EXPR(should_miss_cause_fail, ShouldMissCauseFail())
    HANDLE_EXPR(get_player, mGemPlayer)
    HANDLE_ACTION(hit_notify, HitNotify(_msg->Int(2)))
    HANDLE_EXPR(miss_notify, MissNotify(_msg->Int(2)))
    HANDLE_EXPR(lesson_complete_speed, GetLessonCompleteSpeed(_msg->Int(2)))
    HANDLE_SUPERCLASS(TrainerPanel)
    HANDLE_MEMBER_PTR(DataDir())
    HANDLE_CHECK(0x35C)
END_HANDLERS

BEGIN_PROPSYNCS(GemTrainerPanel)
    SYNC_PROP(draw_tab, mDrawTab)
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS

void GemTrainerLoopPanel::Poll() {
    UIPanel::Poll();
    if (TheGemTrainerPanel)
        TheGemTrainerPanel->HandleLooping();
}