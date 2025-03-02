#include "game/VocalTrainerPanel.h"
#include "beatmatch/VocalNote.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Game.h"
#include "game/SongDB.h"
#include "game/TrainerPanel.h"
#include "game/VocalPart.h"
#include "game/VocalPlayer.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
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
        const std::vector<VocalNote> notes = unkb4[i]->GetNotes();
        int id4 = sect.GetEndTick();
        int id8 = sect.GetStartTick();
        int idc = notes.size();
        for (int j = 0; j < notes.size(); j++) {
            int tick = notes[j].GetTick();
            if (tick >= sect.GetEndTick())
                break;
            if (tick >= sect.GetStartTick()) {
                mPatternNotes[i].push_back(notes[j]);
                MinEq(id4, tick);
                MaxEq(id8, tick);
                MinEq(idc, j);
            }
        }
        const std::vector<VocalPhrase> &phrases = unkb4[i]->GetPhrases();
        for (int j = 0; j < phrases.size(); j++) {
            if (phrases[j].unk8 > id8)
                break;
            int i12 = phrases[j].unk8 + phrases[j].unkc;
            if (i12 > id4) {
                VocalPhrase curPhrase(phrases[j]);
                curPhrase.unk10 -= idc;
                curPhrase.unk14 -= idc;
                if (i12 > sect.GetEndTick()) {
                    MILO_FAIL(
                        "Vocal trainer section %s: last phrase doesn't finish within the section\n",
                        sect.GetName()
                    );
                }
                mPatternPhrases[i].push_back(curPhrase);
            }
        }

        if (i < 2) {
            mPatternLyricPhrases[i].clear();
            const std::vector<VocalPhrase> &lyricPhrases = unkb4[i]->GetLyricPhrases();
            for (int j = 0; j < lyricPhrases.size(); j++) {
                if (lyricPhrases[j].unk8 > id8)
                    break;
                if (lyricPhrases[j].unk8 + lyricPhrases[j].unkc > id4) {
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

void VocalTrainerPanel::CopyPhrasesImp(
    const std::vector<VocalPhrase> &v1,
    std::vector<VocalPhrase> &v2,
    int i3,
    int i4,
    int &i5
) {
    for (int i = 0; i < v1.size(); i++) {
        VocalPhrase curPhrase = v1[i];
        curPhrase.unk10 += i3;
        curPhrase.unk14 += i3;
        int ivar3 = curPhrase.unk8 + i4;
        curPhrase.unk8 = i5;
        curPhrase.unkc += (ivar3 - curPhrase.unk8);
        int tickSum = curPhrase.unk8 + curPhrase.unkc;
        curPhrase.unk0 = TickToMs(tickSum);
        curPhrase.unk4 = TickToMs(tickSum) - curPhrase.unk0;
        i5 = curPhrase.unk8 + curPhrase.unkc;
        v2.push_back(curPhrase);
    }
}

void VocalTrainerPanel::CopyTubes(int i1) {
    TrainerSection &sect = GetSection(GetCurrSection());
    for (int part = 0; part < 3; part++) {
        VocalNoteList *cur = unka8[part];
        cur->mNotes.clear();
        cur->mPhrases.clear();
        cur->mLyricPhrases.clear();
        int ic4 = 0;
        int ic8 = 0;
        MILO_ASSERT(mPatternPhrases[part].size(), 0x137);
        VocalPhrase phrase;
        ic4 = mPatternPhrases[part][0].unk8;
        phrase.unk4 = mPatternPhrases[part][0].unk0;
        cur->mPhrases.push_back(phrase);
        std::vector<VocalNote> &notes = mPatternNotes[part];
        for (int j = -1; j < 2; j++) {
            int ivar1 = unk9c - sect.GetStartTick();
            ivar1 += j * GetSectionTicks(GetCurrSection());
            for (int k = 0; k < notes.size(); k++) {
                VocalNote note = notes[k];
                int ticksum = ivar1 + note.GetTick();
                note.SetNoteTime(TickToMs(ticksum), ticksum);
                unka8[part]->AddNote(note);
            }
            int ivar5 = (j + 1) * notes.size();
            CopyPhrasesImp(mPatternPhrases[part], cur->mPhrases, ivar5, ivar1, ic4);
            if (part < 2) {
                CopyPhrasesImp(
                    mPatternLyricPhrases[part], cur->mLyricPhrases, ivar5, ivar1, ic8
                );
            }
        }
    }
    static bool dump;
    if (dump) {
        MILO_LOG("************ COPY GEMS\n");
        MILO_LOG("jump tick: %d\n", i1);
        MILO_LOG("write tick: %d\n", unk9c);
        MILO_LOG("section (%d, %d)\n", sect.GetStartTick(), sect.GetEndTick());
        for (int i = 0; i < 3; i++) {
            MILO_LOG("PART %d\n", i);
            VocalNoteList *curNoteList = unka8[i];
            MILO_LOG("orig phrases [%d]\n", mPatternPhrases[i].size());
            for (int j = 0; j < mPatternPhrases[i].size(); j++) {
                MILO_LOG(
                    "\t%d - %d\t(%f - %f)\n",
                    mPatternPhrases[i][j].unk8,
                    mPatternPhrases[i][j].unk8 + mPatternPhrases[i][j].unkc,
                    mPatternPhrases[i][j].unk0,
                    mPatternPhrases[i][j].unk0 + mPatternPhrases[i][j].unk4
                );
            }
            MILO_LOG("add phrases [%d]\n", curNoteList->mPhrases.size());
            for (int j = 0; j < curNoteList->mPhrases.size(); j++) {
                MILO_LOG(
                    "\t%d - %d\t(%f - %f)\n",
                    curNoteList->mPhrases[j].unk8,
                    curNoteList->mPhrases[j].unk8 + curNoteList->mPhrases[j].unkc,
                    curNoteList->mPhrases[j].unk0,
                    curNoteList->mPhrases[j].unk0 + curNoteList->mPhrases[j].unk4
                );
            }
            MILO_LOG("orig lyric phrases [%d]\n", mPatternLyricPhrases[i].size());
            for (int j = 0; j < mPatternLyricPhrases[i].size(); j++) {
                MILO_LOG(
                    "\t%d - %d\t(%f - %f)\n",
                    mPatternLyricPhrases[i][j].unk8,
                    mPatternLyricPhrases[i][j].unk8 + mPatternLyricPhrases[i][j].unkc,
                    mPatternLyricPhrases[i][j].unk0,
                    mPatternLyricPhrases[i][j].unk0 + mPatternLyricPhrases[i][j].unk4
                );
            }
            MILO_LOG("add lyric phrases [%d]\n", curNoteList->mLyricPhrases.size());
            for (int j = 0; j < curNoteList->mLyricPhrases.size(); j++) {
                MILO_LOG(
                    "\t%d - %d\t(%f - %f)\n",
                    curNoteList->mLyricPhrases[j].unk8,
                    curNoteList->mLyricPhrases[j].unk8
                        + curNoteList->mLyricPhrases[j].unkc,
                    curNoteList->mLyricPhrases[j].unk0,
                    curNoteList->mLyricPhrases[j].unk0
                        + curNoteList->mLyricPhrases[j].unk4
                );
            }
        }
        MILO_LOG("************\n");
    }
    if (i1 > unk9c) {
        unk9c += GetSectionTicks(GetCurrSection());
    }
    if (mVocalPlayer) {
        for (int i = 0; i < 3; i++) {
            VocalPart *part = mVocalPlayer->mVocalParts[i];
            VocalNoteList *list = nullptr;
            if (part) {
                list = unka8[i];
                part->SetVocalNoteList(list);
            }
            mTrack->SetAlternateNoteList(i, list);
        }
        mVocalPlayer->Jump(TickToMs(i1), false);
    }
}

void VocalTrainerPanel::ClearTubes() { mTrack->RebuildHUD(); }

void VocalTrainerPanel::Loop() {
    mVocalPlayer->EndHitStreak();
    ResetChallenge();
}

void VocalTrainerPanel::AddBeatMask(int tick) {
    int ticks = GetSectionTicks(GetCurrSection());
    TickToSeconds(tick);
    TickToSeconds(tick + ticks);
}

void VocalTrainerPanel::UpdateScore() {
    static Message msg("update_score", 0, 0);
    msg[0] = unkcc;
    msg[1] = unkd0;
    Handle(msg, true);
}

BEGIN_HANDLERS(VocalTrainerPanel)
    HANDLE_ACTION(clear_tubes, ClearTubes())
    HANDLE_EXPR(get_total_phrases_float, (float)mPatternPhrases[0].size())
    HANDLE_SUPERCLASS(TrainerPanel)
    HANDLE_MEMBER_PTR(DataDir())
    HANDLE_CHECK(0x1C0)
END_HANDLERS