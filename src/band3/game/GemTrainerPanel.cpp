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
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include "utl/TimeConversion.h"
#include <cstddef>

GemTrainerPanel* TheGemTrainerPanel;

GemTrainerPanel::GemTrainerPanel() : mGemPlayer(0), mTrack(0), mGemManager(0), mDifficulty(kDifficultyEasy), mLocalUser(0), unk80(0), unk84(0), unka8(0), unka9(0), unkac(0), unkb0(0), mMetronome(0), unkbc(-1.0f), unkc0(-1.0f),
    mDrawTab(0), unkc9(0), unkcc(-1), unkd0(0) {
    mTab = new TrainerGemTab();
    mMetronome = new Metronome();
}

GemTrainerPanel::~GemTrainerPanel(){
    delete mTab;
    delete mMetronome;
}

#pragma push
#pragma pool_data off
void GemTrainerPanel::Enter(){
    TheGemTrainerPanel = this;
    mLocalUser = 0;
    mGemPlayer = 0;
    mTrack = 0;
    unkd0 = 0;
    std::vector<LocalBandUser*> users;
    TheBandUserMgr->GetLocalParticipants(users);
    for(int i = 0; i < users.size() && !mGemPlayer; i++){
        LocalBandUser* cur = users[i];
        mLocalUser = cur;
        mGemPlayer = dynamic_cast<GemPlayer*>(mLocalUser->mPlayer);
        mTrack = dynamic_cast<GemTrack*>(mLocalUser->mTrack);
    }

    if(mLocalUser){
        mDifficulty = mLocalUser->GetDifficulty();
    }

    Message resetScoreMsg("reset_score");
    Handle(resetScoreMsg, true);

    TrainerPanel::Enter();
    Sfx* hiSfx = DataDir()->Find<Sfx>("metronome_hi.cue", true);
    Sfx* loSfx = DataDir()->Find<Sfx>("metronome_lo.cue", true);
    mMetronome->Enter(hiSfx, loSfx);

    mDrawTab = false;
    unkc9 = 0;
    unkcc = -1;
    if(mGemPlayer){
        Symbol mpsong = MetaPerformer::Current()->Song();
        BandSongMetadata* data = (BandSongMetadata*)TheSongMgr->Data(TheSongMgr->GetSongIDFromShortName(mpsong, true));
        int key = data->SongKey();
        int tone = data->SongTonality();
        if(key >= 0){
            char notename[4];
            strcpy(notename, RGGetNoteName(key, key));
            if(tone == 1){
                strcat(notename, "m");
                static Message msg("set_key", "");
                msg[0] = notename;
                Handle(msg, true);
            }
        }
        else {
            Handle(hide_key_msg, true);
        }
        SendDataPoint("trainers/song_name", song_name, mpsong);
    }
}
#pragma pop

void GemTrainerPanel::Exit(){
    TrainerPanel::Exit();
    mGemManager = 0;
    mGemPlayer = 0;
    TheGemTrainerPanel = 0;
    mMetronome->Exit();
    for(int i = 0; i < 4; i++){
        unk88[i].clear();
    }
    mPattern.clear();
}

void GemTrainerPanel::Poll(){
    if(!mTrack && mGemPlayer && mLocalUser->mTrack){
        mTrack = dynamic_cast<GemTrack*>(mLocalUser->mTrack);
        MILO_ASSERT(mTrack != NULL, 0xC1);
        mGemManager = mTrack->GetGemManager();
        MILO_ASSERT(mGemManager != NULL, 0xC5);
        for(int i = 0; i < 4; i++){
            unk60[i] = TheSongDB->GetGemListByDiff(mGemPlayer->unk248, i);
            // unk88[i] = unk60[i]->mGems;
        }

        RndDir* gemprev = DataDir()->Find<RndDir>("gem_preview", true);
        mTab->Init(gemprev, SymToTrackType(mTrack->GetType()));
    }
    UIPanel::Poll();
    if(mGemManager && mGemPlayer && GetCurrSection() >= 0){
        if(TheGame->IsWaiting()){
            if(mDifficulty != mLocalUser->GetDifficulty() && !unkd0){
                // for loop
                unkd0 = true;
            }
        }
        else {
            unkd0 = false;
            if(unka9){
                TrainerSection& sect = GetSection(GetCurrSection());
                int ticks = GetSectionTicks(GetCurrSection());
                AddBeatMask(sect.GetStartTick() + ticks);
                unka9 = false;
            }
            int tick = GetTick();
            if(unk84 <= tick && unk84 != 0){
                if(unkac > 0){
                    Handle(loop_msg, true);
                }
                unk84 += GetLoopTicks(GetCurrSection());
                unkac++;
            }
            int ooo = 0;
            if(TheUI->FocusPanel() != this){
                ooo = 2;
            }
            else if(TheGame->GetMusicSpeed() != 1.0f){
                ooo = 1;
            }
            mMetronome->Poll(tick, (Metronome::OverrideEnabled)ooo);
            HandleTrackShifting();
            Difficulty diff = mLocalUser->GetDifficulty();
            if(mDifficulty != diff){
                mGemManager->ClearAllGems();
                mGemManager->ClearMissedPhrases();
                // TrackDir::ClearAllGemWidgets
                NewDifficulty(tick, diff);
            }
        }
    }
}

void GemTrainerPanel::Draw(){
    TrainerPanel::Draw();
    if(mGemPlayer && ShouldDrawTab()){
        TheUI->unk34->Select();
        mTab->Draw(GetLoopTick(GetTick()));
    }
}

void GemTrainerPanel::HandleLooping(){
    if(mGemManager && !TheGame->IsWaiting() && GetCurrSection() >= 0){
        int tick = GetTick();
        if(GetCurrSection() >= 0 && ShouldLoop(tick) != 0){
            Handle(score_msg, true);
            if(unka8){
                AddBeatMask(unk80 + GetLoopTicks(GetCurrSection()));
            }
            unkc9 = false;
            unka8 = !unka8;
            unkcc = -1;
            int start = GetSectionLoopStart(GetCurrSection());
            float ticktosec = TickToSeconds(start);
            float secs = TheTaskMgr.Seconds(TaskMgr::b);
            if(secs - ticktosec > 900.0f){
                RestartSection();
            }
            else {
                CopyGems(tick);
                ResetChallenge();
                Looped();
            }
        }
    }
}

bool GemTrainerPanel::GetFretboardView(const GameGem& gem) const {
    char fret = gem.GetHighestFret();
    return fret <= 11;
}

int GemTrainerPanel::GetPatternSize() const { return mPattern.size(); }

bool GemTrainerPanel::IsGemInFutureLoop(int) const {

}

void GemTrainerPanel::HandlePlayerDeleted(Player* player){
    if(player == mGemPlayer){
        mGemPlayer = 0;
    }
}

void GemTrainerPanel::CopyGems(std::vector<GameGem>& gems, int sectIdx, int& iref1, int& iref2){
    gems.clear();
    iref1 = -1;
    iref2 = -1;
    Difficulty diff = mLocalUser->GetDifficulty();
    TrainerSection& sect = GetSection(sectIdx);
    for(int i = 0; i < unk88[diff].size(); i++){
        GameGem& curGem = unk88[diff][i];
        if(sect.GetStartTick() <= curGem.mTick && curGem.mTick + curGem.mDurationTicks <= sect.GetEndTick()){
            // gems.push_back(curGem);
        }
    }
}