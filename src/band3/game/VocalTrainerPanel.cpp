#include "game/VocalTrainerPanel.h"
#include "beatmatch/VocalNote.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Game.h"
#include "game/SongDB.h"
#include "game/TrainerPanel.h"
#include "game/VocalPlayer.h"
#include "os/Debug.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
#include "utl/TimeConversion.h"

VocalTrainerPanel::VocalTrainerPanel()
    : mTrack(0), mVocalPlayer(0), unk9c(0), unka0(0), unka4(0), unkc0(0), unkc1(0),
      unkc4(0), unkcc(0), unkd0(0) {
    for (int i = 0; i < 3; i++) {
        unka8[i] = 0;
    }
}

VocalTrainerPanel::~VocalTrainerPanel() {
    for (int i = 0; i < 3; i++) {
        RELEASE(unka8[i]);
    }
}

void VocalTrainerPanel::Enter() {
    std::vector<BandUser *> users;
    TheBandUserMgr->GetParticipatingBandUsers(users);
    for (int i = 0; i < users.size() && !mVocalPlayer; i++) {
        BandUser *user = users[i];
        mVocalPlayer = dynamic_cast<VocalPlayer *>(user->GetPlayer());
        mTrack = dynamic_cast<VocalTrack *>(user->GetTrack());
    }
    MILO_ASSERT(mVocalPlayer != NULL, 0x40);
    MILO_ASSERT(mTrack != NULL, 0x41);
    for (int i = 0; i < 3; i++) {
        unkb4[i] = TheSongDB->GetVocalNoteList(i);
    }
    Message msg("reset_score");
    Handle(msg, true);
    TrainerPanel::Enter();
    for (int i = 0; i < 3; i++) {
        RELEASE(unka8[i]);
        unka8[i] = new VocalNoteList(TheSongDB->GetData());
    }
}

void VocalTrainerPanel::Exit() {
    TrainerPanel::Exit();
    for (int i = 0; i < 3; i++) {
        RELEASE(unka8[i]);
    }
}

void VocalTrainerPanel::Poll() {
    UIPanel::Poll();
    if (TheGame->IsWaiting() || GetCurrSection() < 0)
        return;
    else {
        TrainerSection &sect = GetSection(GetCurrSection());
        if (unkc1) {
            AddBeatMask(sect.GetStartTick() + GetSectionTicks(GetCurrSection()));
            unkc1 = false;
        }
        int tick = GetTick();
        if (GetCurrSection() >= 0 && tick >= unk9c) {
            if (unkc0) {
                AddBeatMask(unk9c + GetSectionTicks(GetCurrSection()));
            }
            unkc0 = !unkc0;
            CopyTubes(tick);
        }
        if (tick >= unka0 && unka0 != 0) {
            if (unkc4 > 0) {
                Handle(loop_msg, true);
                Loop();
            }
            unka0 += GetSectionTicks(GetCurrSection());
            unkc4++;
        }

        float pct = mVocalPlayer->GetHitPercentage(0);
        if (pct != unkcc) {
            unkcc = pct;
            MaxEq(unkd0, pct);
            UpdateScore();
        }
    }
}

#pragma push
#pragma dont_inline on
void VocalTrainerPanel::StartSectionImpl() {
    TheSongDB->GetData()->GetTempoMap()->ClearLoopPoints();
    ClearTubes();

    TrainerSection &sect = GetSection(GetCurrSection());
    for (int i = 0; i < 3; i++) {
        mPatternNotes[i].clear();
        mPatternPhrases[i].clear();
        std::vector<VocalNote> notes = unkb4[i]->GetNotes();
        int id4 = sect.GetEndTick();
        int id8 = sect.GetStartTick();
        int idc = notes.size();
        for (int j = 0; j < notes.size(); j++) {
            int tick = notes[j].GetTick();
            if (sect.GetEndTick() <= tick)
                break;
            if (sect.GetStartTick() <= tick) {
                mPatternNotes[i].push_back(notes[j]);
                MinEq(id4, tick);
                MinEq(id8, tick);
                MaxEq(idc, j);
            }
        }
        std::vector<VocalPhrase> &phrases = unkb4[i]->GetPhrases();
        for (int j = 0; j < phrases.size() && phrases[j].unk8 <= id8; j++) {
            int i12 = phrases[j].unk8 + phrases[j].unkc;
            if (id4 < i12) {
                VocalPhrase curPhrase(phrases[j]);
                curPhrase.unk10 -= idc;
                curPhrase.unk14 -= idc;
                if (sect.GetEndTick() < i12) {
                    MILO_FAIL(
                        "Vocal trainer section %s: last phrase doesn't finish within the section\n",
                        sect.GetName()
                    );
                }
            }
        }

        if (i < 2) {
            mPatternLyricPhrases[i].clear();
            std::vector<VocalPhrase> &lyricPhrases = unkb4[i]->GetLyricPhrases();
            for (int j = 0; j < lyricPhrases.size() && lyricPhrases[j].unk8 <= id8; j++) {
                if (id4 < lyricPhrases[j].unk8 + lyricPhrases[j].unkc) {
                    VocalPhrase curPhrase(lyricPhrases[j]);
                    curPhrase.unk10 -= idc;
                    curPhrase.unk14 -= idc;
                    mPatternLyricPhrases[i].push_back(curPhrase);
                }
            }
        }
    }

    int tick = sect.GetStartTick() - 1920;
    if (tick < 0)
        tick = 0;
    unk9c = sect.GetStartTick() + GetSectionTicks(GetCurrSection());
    CopyTubes(tick);
    TheGame->Jump(TickToMs(tick), true);
    TheGame->GetBeatMaster()->GetAudio()->GetSongStream()->ClearJump();
    TheGame->GetBeatMaster()->GetAudio()->GetSongStream()->SetJump(
        TickToMs(sect.GetEndTick()), TickToMs(sect.GetStartTick()), nullptr
    );
    TheSongDB->GetData()->GetTempoMap()->SetLoopPoints(
        sect.GetStartTick(), sect.GetEndTick()
    );
    unka0 = sect.GetStartTick();
    mVocalPlayer->SetCrowdMeterActive(false);
    unkc0 = true;
    unkc1 = true;
    unkc4 = 0;
    unkcc = 0;
    unkd0 = 0;
    UpdateScore();
}
#pragma pop