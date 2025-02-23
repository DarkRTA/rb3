#include "game/PracticePanel.h"
#include "bandtrack/TrackPanel.h"
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "game/GemPlayer.h"
#include "game/Metronome.h"
#include "game/Player.h"
#include "game/VocalGuidePitch.h"
#include "game/VocalPlayer.h"
#include "midi/MidiParser.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "synth/Synth.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
#include "utl/TimeConversion.h"

PracticePanel::PracticePanel()
    : mInVocalMode(0), mFader(Hmx::Object::New<Fader>()), mPlayAllTracks(0),
      mGuidePitch(0), unk4c(-1), unk50(-1), unk54(0), unk55(0), unk56(1), unk57(0),
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
    unk50 = -1;
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