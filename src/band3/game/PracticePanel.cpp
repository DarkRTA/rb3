#include "game/PracticePanel.h"
#include "bandtrack/TrackPanel.h"
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "game/GemPlayer.h"
#include "game/Metronome.h"
#include "game/Player.h"
#include "game/SongDB.h"
#include "game/VocalGuidePitch.h"
#include "game/VocalPlayer.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/TrainingMgr.h"
#include "midi/MidiParser.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "synth/Synth.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include "utl/TimeConversion.h"

PracticePanel *ThePracticePanel;

PracticePanel::PracticePanel()
    : mInVocalMode(0), mFader(Hmx::Object::New<Fader>()), mPlayAllTracks(0),
      mGuidePitch(0), unk4c(-1), mScorePart(-1), unk54(0), unk55(0), unk56(1), unk57(0),
      unk58(1), unk59(0), unk5c(0), unk60(1), mMetronome(0) {
    ThePracticePanel = this;
    mGuidePitch = new VocalGuidePitch();
}

PracticePanel::~PracticePanel() {
    ThePracticePanel = nullptr;
    delete mFader;
    delete mGuidePitch;
}

void PracticePanel::Enter() {
    mGuidePitch->Init();
    UIPanel::Enter();
    unk59 = false;
    TheGame->AddMusicFader(mFader);
    OnFadeSongIn(0.1f);
    if (IsDrums()) {
        mMetronome = new Metronome();
        mMetronome->Enter(
            TheSynth->Find<Sfx>("metronome_hi.cue", true),
            TheSynth->Find<Sfx>("metronome_lo.cue", true)
        );
    } else {
        ObjectDir::sMainDir->Find<MidiParser>("practice_metronome", true)->AddSink(this);
    }
    unk54 = false;
    mScorePart = -1;
    unk55 = false;
    unk56 = true;
    unk5c = 1;
    unk57 = false;
    SetRestartAllowed(true);
    MarkGemsAsProcessed();
}

void PracticePanel::Exit() {
    UIPanel::Exit();
    if (mMetronome) {
        mMetronome->Exit();
        RELEASE(mMetronome);
    } else {
        ObjectDir::sMainDir->Find<MidiParser>("practice_metronome", true)
            ->RemoveSink(this);
    }
    mGuidePitch->EnableGuideTrack(-1);
    mGuidePitch->Terminate();
    unk4c = -1;
    SetRestartAllowed(true);
    unk54 = true;
}

FORCE_LOCAL_INLINE
bool PracticePanel::HasPlayer() const { return TheGame->NumActivePlayers() > 0; }
END_FORCE_LOCAL_INLINE

bool PracticePanel::IsDrums() const {
    if (!HasPlayer())
        return false;
    else {
        Player *p = TheGame->GetActivePlayer(0);
        return !p ? false : p->GetTrackType() == kTrackDrum;
    }
}

bool PracticePanel::IsVocals() const {
    if (!HasPlayer())
        return false;
    else {
        Player *p = TheGame->GetActivePlayer(0);
        return !p ? false : p->GetTrackType() == kTrackVocals;
    }
}

void PracticePanel::Load() {
    UIPanel::Load();
    mGuidePitch->Load();
}

bool PracticePanel::IsLoaded() const {
    return UIPanel::IsLoaded() && mGuidePitch->IsLoaded();
}

void PracticePanel::FinishLoad() {
    UIPanel::FinishLoad();
    mGuidePitch->FinishLoad();
}

void PracticePanel::Unload() {
    UIPanel::Unload();
    mGuidePitch->Unload();
}

#pragma push
#pragma pool_data off
void PracticePanel::Poll() {
    UIPanel::Poll();
    static Message setShowingMsg("set_showing", 0);
    if (!unk54) {
        std::vector<Player *> &players = TheGame->GetActivePlayers();
        if (!players.empty()) {
            if (TheUI->FocusPanel() != this || TheUI->InTransition()
                || (TheGame->IsWaiting() && !TheGame->InRollback())) {
                mGuidePitch->Pause(true);
                setShowingMsg[0] = 0;
                GetTrackPanel()->Handle(setShowingMsg, true);
            } else {
                players[0]->SetCrowdMeterActive(false);
                float ms = TheTaskMgr.Seconds(TaskMgr::kRealTime) * 1000.0f;
                VocalPlayer *vp = dynamic_cast<VocalPlayer *>(players[0]);
                if (vp && vp->ScoringEnabled()) {
                    mGuidePitch->Poll(ms);
                }
                if (unk56 && !unk57) {
                    if (unk5c == 1)
                        unk5c = 2;
                    else {
                        unk5c = 0;
                        static Message trackInMsg("bring_track_in");
                        Handle(trackInMsg, true);
                        unk56 = false;
                        if (!vp) {
                            GetTrackPanel()->GetTrack(players[0], true)->UpdateShifts();
                        }
                    }
                }
                bool u7 = TheGame->IsPaused() | TheGame->InRollback();
                if (u7 != mGuidePitch->IsPaused()) {
                    mGuidePitch->Pause(u7);
                }
                setShowingMsg[0] = 1;
                GetTrackPanel()->Handle(setShowingMsg, true);
                if (mMetronome) {
                    int oe = 0;
                    if (TheUI->FocusPanel() != this || !unk58) {
                        oe = 2;
                    } else if (TheGame->GetMusicSpeed() != -1.0f) {
                        oe = 1;
                    }
                    mMetronome->Poll(MsToTick(ms), (Metronome::OverrideEnabled)oe);
                    float f80, f84;
                    GetSectionBounds(f80, f84);
                    if (vp) {
                        TheGame->AdjustForVocalPhrases(f80, f84);
                    } else {
                        GemPlayer *gp = dynamic_cast<GemPlayer *>(players[0]);
                        if (gp) {
                            BeatMatchController *cnt = gp->GetController();
                            Symbol cntSym = TheGameConfig->GetController(gp->GetUser());
                            bool b1 = false;
                            if (cntSym == keys && cntSym == gp->GetControllerType())
                                b1 = true;
                            if (!b1) {
                                gp->ResetController(cnt->IsDisabled());
                            }
                        }
                    }
                    float ftick = MsToTick(f84);
                    if (!unk59) {
                        if (TheTaskMgr.GetSongPos().GetTotalTick() > ftick) {
                            if (!unk57) {
                                Handle(end_play_msg, true);
                                unk57 = true;
                                SetRestartAllowed(false);
                            }
                            if (TheTaskMgr.GetSongPos().GetTotalTick()
                                > ftick + 1920.0f) {
                                Handle(loop_msg, true);
                                unk57 = false;
                                if (TheGame->GetActivePlayer(0)
                                    && TheGame->GetActivePlayer(0)->GetBandTrack()) {
                                    TheGame->GetActivePlayer(0)
                                        ->GetBandTrack()
                                        ->ResetStreakMeter();
                                }
                                unk59 = true;
                            }
                        }
                    } else
                        unk59 = false;
                }
            }
        }
    }
}
#pragma pop

void PracticePanel::GetSectionBounds(float &f1, float &f2) const {
    int i14, i18;
    TheGameConfig->GetPracticeSections(i14, i18);
    float f1c, f20;
    TheGameConfig->GetSectionBounds(i14, f1c, f20);
    float f24, f28;
    TheGameConfig->GetSectionBounds(i18, f24, f28);
    f1 = f1c;
    f2 = f28;
}

void PracticePanel::SetPlayAllTracks(bool play) { mPlayAllTracks = play; }

FORCE_LOCAL_INLINE
bool PracticePanel::PlayAllTracks() const { return mPlayAllTracks; }
END_FORCE_LOCAL_INLINE

void PracticePanel::SetPitchShiftRatio(float f1) {
    unk40 = f1;
    GemPlayer *gp = dynamic_cast<GemPlayer *>(TheGame->GetActivePlayer(0));
    if (gp)
        gp->SetPitchShiftRatio(f1);
}

FORCE_LOCAL_INLINE
bool PracticePanel::InVocalMode() const { return mInVocalMode; }
END_FORCE_LOCAL_INLINE

void PracticePanel::OnFadeSongOut(float f1) { mFader->DoFade(-96.0f, f1 * 1000.0f); }
void PracticePanel::OnFadeSongIn(float f1) { mFader->DoFade(0.0f, f1 * 1000.0f); }

void PracticePanel::PracticeMetronome(Symbol s) {
    if (InVocalMode() || !unk58)
        return;
    else if (unk40 != 1.0f && !PlayAllTracks()) {
        Symbol seq_name;
        if (s == "metronome_kick") {
            seq_name = "click_kick.cue";
        } else if (s == "metronome_snare") {
            seq_name = "click_snare.cue";
        } else if (s == "metronome_hat") {
            seq_name = "click_hat.cue";
        }
        MILO_ASSERT(!seq_name.Null(), 0x1CA);
        GetTrackPanel()->PlaySequence(seq_name.mStr, 0, 0, 0);
    }
}

void PracticePanel::StopMics() {
    for (int i = 0; i != (unsigned int)TheSynth->GetNumMics(); i++) {
        TheSynth->GetMic(i)->Stop();
    }
}

void PracticePanel::SetUsesHarmony(bool harms) {
    TrainingMgr *pTrainingMgr = TrainingMgr::GetTrainingMgr();
    MILO_ASSERT(pTrainingMgr, 0x1DA);
    LocalBandUser *user = pTrainingMgr->GetUser();
    MILO_ASSERT(user, 0x1DD);
    if (user->GetTrackType() == kTrackVocals) {
        user->SetPreferredScoreType(harms ? kScoreHarmony : kScoreVocals);
    }
}

bool PracticePanel::GetUsesHarmony() const {
    TrainingMgr *pTrainingMgr = TrainingMgr::GetTrainingMgr();
    MILO_ASSERT(pTrainingMgr, 0x1E8);
    LocalBandUser *user = pTrainingMgr->GetUser();
    MILO_ASSERT(user, 0x1EB);
    return user->GetPreferredScoreType() == kScoreHarmony;
}

void PracticePanel::EnableGuideTrack(int i1) {
    if (!unk54)
        mGuidePitch->EnableGuideTrack(i1);
}

void PracticePanel::IncScorePart() {
    int i30, i34;
    IncPart(mScorePart, i30, i34);
    Message msg("isolate_vocal_track", i30);
    Handle(msg, true);
    VocalPlayer *player = dynamic_cast<VocalPlayer *>(TheGame->GetActivePlayer(0));
    MILO_ASSERT(player, 0x202);
    for (int i = 0; i < i34; i++) {
        player->EnablePartScoring(i, i30 == -1 || i30 == i);
    }
    mScorePart = i30;
    if (GetGuidePart() != -1)
        SyncGuidePart();
}

FORCE_LOCAL_INLINE
int PracticePanel::GetScorePart() const { return mScorePart; }
END_FORCE_LOCAL_INLINE

void PracticePanel::IncGuidePart() {
    int i14, i18;
    IncPart(mGuidePitch->GetGuideTrack(), i14, i18);
    EnableGuideTrack(i14);
    unk4c = i14;
}

FORCE_LOCAL_INLINE
int PracticePanel::GetGuidePart() const { return mGuidePitch->GetGuideTrack(); }
END_FORCE_LOCAL_INLINE

void PracticePanel::ToggleGuidePart() {
    if (mGuidePitch->GetGuideTrack() == -1) {
        SyncGuidePart();
    } else {
        mGuidePitch->EnableGuideTrack(-1);
        unk4c = -1;
    }
}

void PracticePanel::SyncGuidePart() {
    int track;
    if (!GetUsesHarmony())
        track = 0;
    else if (GetScorePart() == -1)
        track = 0;
    else
        track = GetScorePart();
    mGuidePitch->EnableGuideTrack(track);
    unk4c = track;
}

void PracticePanel::IncPart(int i1, int &i2, int &i3) {
    int numParts = GetNumVocalParts();
    i3 = numParts;
    i2 = ((i1 + 2) % (numParts + 1)) - 1;
}

void PracticePanel::SetGuidePitchPaused(bool b) {
    if (!unk54)
        mGuidePitch->Pause(b);
}

void PracticePanel::UpdateGuideTrack(const Symbol &s) { mGuidePitch->SetSong(s); }

void PracticePanel::TrackIn() {
    SetRestartAllowed(true);
    mGuidePitch->EnableGuideTrack(unk4c);
    unk4c = -1;
    if (unk55 && TheGame->GetActivePlayer(0)) {
        if (TheGame->GetActivePlayer(0)->GetBandTrack()) {
            TheGame->GetActivePlayer(0)->GetBandTrack()->PlayIntro();
            unk55 = false;
        }
    }
    unk56 = false;
}

void PracticePanel::TrackOut() {
    unk4c = mGuidePitch->GetGuideTrack();
    mGuidePitch->EnableGuideTrack(-1);
    unk56 = true;
    unk5c = 1;
}

int PracticePanel::GetNumVocalParts() const {
    if (MetaPerformer::Current()->IsNowUsingVocalHarmony()) {
        return TheSongMgr->GetNumVocalParts(MetaPerformer::Current()->Song());
    } else
        return 1;
}

void PracticePanel::PauseGuideTrack() { mGuidePitch->Pause(true); }
void PracticePanel::UnpauseGuideTrack() { mGuidePitch->Pause(false); }

void PracticePanel::SetInVocalMode() {
    TrainingMgr *pTrainingMgr = TrainingMgr::GetTrainingMgr();
    MILO_ASSERT(pTrainingMgr, 0x29C);
    LocalBandUser *user = pTrainingMgr->GetUser();
    MILO_ASSERT(user, 0x29F);
    mInVocalMode = user->GetTrackType() == kTrackVocals;
}

void PracticePanel::MarkGemsAsProcessed() {
    if (!IsVocals() && HasPlayer()) {
        float f14, f18;
        GetSectionBounds(f14, f18);
        GemPlayer *player = dynamic_cast<GemPlayer *>(TheGame->GetActivePlayer(0));
        if (player && player->GetTrackNum() >= 0) {
            Difficulty diff = TrainingMgr::GetTrainingMgr()->GetUser()->GetDifficulty();
            GameGemList *gems = TheSongDB->GetGemListByDiff(player->GetTrackNum(), diff);
            for (int i = 0; i < gems->NumGems(); i++) {
                if (gems->GetGem(i).GetMs() < f14) {
                    player->GetGemStatus()->Set0x40(i);
                    player->GetGemStatus()->SetHit(i);
                }
            }
        }
    }
}

void PracticePanel::SetRestartAllowed(bool b1) { unk60 = b1; }

bool PracticePanel::GetRestartAllowed() {
    if (ThePracticePanel && ThePracticePanel->Showing())
        return unk60;
    else
        return true;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(PracticePanel)
    HANDLE_ACTION(set_pitch_shift_ratio, SetPitchShiftRatio(_msg->Float(2)))
    HANDLE_ACTION(set_in_vocal_mode, SetInVocalMode())
    HANDLE_EXPR(in_vocal_mode, InVocalMode())
    HANDLE_ACTION(fade_song_out, OnFadeSongOut(_msg->Float(2)))
    HANDLE_ACTION(fade_song_in, OnFadeSongIn(_msg->Float(2)))
    HANDLE_ACTION(stop_mics, StopMics())
    HANDLE_ACTION(practice_metronome, PracticeMetronome(_msg->Sym(2)))
    HANDLE_ACTION(set_uses_harmony, SetUsesHarmony(_msg->Int(2)))
    HANDLE_ACTION(set_play_all_tracks, SetPlayAllTracks(_msg->Int(2)))
    HANDLE_EXPR(get_play_all_tracks, PlayAllTracks())
    HANDLE_ACTION(enable_guide_track, EnableGuideTrack(_msg->Int(2)))
    HANDLE_ACTION(inc_guide_part, IncGuidePart())
    HANDLE_EXPR(get_guide_part, GetGuidePart())
    HANDLE_ACTION(toggle_guide_part, ToggleGuidePart())
    HANDLE_ACTION(inc_score_part, IncScorePart())
    HANDLE_EXPR(get_score_part, GetScorePart())
    HANDLE_ACTION(set_guide_pitch_paused, SetGuidePitchPaused(_msg->Int(2)))
    HANDLE_ACTION(track_in, TrackIn())
    HANDLE_ACTION(track_out, TrackOut())
    HANDLE_ACTION(update_guide_track, UpdateGuideTrack(_msg->Sym(2)))
    HANDLE_ACTION(pause_guide_track, PauseGuideTrack())
    HANDLE_ACTION(unpause_guide_track, UnpauseGuideTrack())
    HANDLE_ACTION(click_cheat, unk58 = _msg->Int(2))
    HANDLE_EXPR(has_player, HasPlayer())
    HANDLE_ACTION(mark_gems_as_processed, MarkGemsAsProcessed())
    HANDLE_EXPR(get_restart_allowed, GetRestartAllowed())

    {
        const char *symStr = sym.Str();
        if (strlen(symStr) >= 4 && strncmp(symStr, "prc_", 4) == 0) {
            static Message msg("section", "");
            msg[0] = Symbol(symStr);
            Handle(msg, true);
            return 0;
        }
    }

    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_MEMBER_PTR(DataDir())
    HANDLE_CHECK(0x323)
END_HANDLERS
#pragma pop