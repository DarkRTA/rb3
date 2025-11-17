#include "game/Band.h"
#include "BandPerformer.h"
#include "bandobj/BandDirector.h"
#include "bandobj/BandTrack.h"
#include "bandtrack/TrackPanel.h"
#include "beatmatch/PlayerTrackConfig.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/CommonPhraseCapturer.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "game/GameMode.h"
#include "game/GamePanel.h"
#include "game/GemPlayer.h"
#include "game/Player.h"
#include "game/RealGuitarGemPlayer.h"
#include "game/SongDB.h"
#include "game/TrainerPanel.h"
#include "game/VocalPlayer.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Messages.h"
#include "utl/Std.h"
#include "utl/Symbols.h"

Band::Band(bool bbb, int i2, BandUser *user, BeatMaster *bm)
    : mBandPerformer(0), unk30(0), mAccumulatedScore(0), mTotalStars(0), unk3c(0),
      unk40(0), unk44(0), mBonusLevel(0), mMultiplier(1), mMaxMultiplier(1),
      mMsWithMultiplier(0), mMsWhenMultiplierStarted(0), mMultiplierActive(1), unk60(0) {
    DataArray *cfg = SystemConfig("scoring", "bonuses");
    mMaxBonusLevel = cfg->FindInt("max_bonus");
    DataArray *multArr = cfg->FindArray("multiplier")->Array(1);
    for (int i = 0; i < multArr->Size(); i++) {
        unk68.push_back(multArr->Int(i));
    }
    DataArray *crowdArr = cfg->FindArray("crowd_boost")->Array(1);
    for (int i = 0; i < crowdArr->Size(); i++) {
        unk70.push_back(crowdArr->Int(i));
    }
    SetName(MakeString("band_%i", i2), ObjectDir::sMainDir);
    mBandPerformer = new BandPerformer(this, nullptr);
    mCommonPhraseCapturer = new CommonPhraseCapturer();
    MetaPerformer *perf = MetaPerformer::Current();
    std::vector<BandUser *> users;
    TheBandUserMgr->GetParticipatingBandUsers(users);
    FOREACH (it, users) {
        BandUser *pUser = *it;
        MILO_ASSERT(pUser, 0x57);
        bool b1 = false;
        if (perf && !perf->PartPlaysInSong(pUser->GetTrackSym())) {
            b1 = true;
        }
        if (!b1 && (!bbb || pUser == user)) {
            AddPlayer(bm, pUser);
        }
    }
    if (TheGameConfig->GetConfigList()->GetAutoVocals()) {
        Player *p = AddPlayer(bm, TheBandUserMgr->GetNullUser());
        p->SetQuarantined(true);
    }
}

Band::~Band() {
    if (unk60 == 1)
        TheBandDirector->SetCharacterHideHackEnabled(false);
    unk60 = 0;
    for (int i = 0; i < mActivePlayers.size(); i++) {
        BandUser *u = mActivePlayers[i]->GetUser();
        if (u)
            u->SetPlayer(nullptr);
    }
    DeleteAll(mActivePlayers);
    RELEASE(mBandPerformer);
    RELEASE(mCommonPhraseCapturer);
}

void Band::SetGameOver() {
    for (int i = 0; i != mActivePlayers.size(); i++) {
        mActivePlayers[i]->SetGameOver();
    }
}

void Band::Restart(bool b1) {
    for (int i = 0; i != mActivePlayers.size(); i++) {
        mActivePlayers[i]->Restart(b1);
    }
    mBandPerformer->Restart();
    mMaxMultiplier = 1;
    mMsWithMultiplier = 0;
    mMsWhenMultiplierStarted = 0;
    unk40 = false;
    unk44 = 0;
    if (unk60 == 1) {
        TheBandDirector->SetCharacterHideHackEnabled(false);
    }
    unk60 = 0;
    if (mCommonPhraseCapturer)
        mCommonPhraseCapturer->Reset();
    UpdateBonusLevel(0);
}

Performer *Band::GetBand() const { return mBandPerformer; }

Player *Band::GetActivePlayer(int player) const {
    MILO_ASSERT_RANGE(player, 0, mActivePlayers.size(), 0xBC);
    return mActivePlayers[player];
}

int Band::NumActivePlayers() const { return mActivePlayers.size(); }

int Band::NumNonQuarantinedPlayers() const {
    int count = 0;
    for (int i = 0; i < mActivePlayers.size(); i++) {
        if (!mActivePlayers[i]->GetQuarantined())
            count++;
    }
    return count;
}

FORCE_LOCAL_INLINE
Performer *Band::MainPerformer() const { return mBandPerformer; }
END_FORCE_LOCAL_INLINE

void Band::RemoveUser(BandUser *u) {
    Player *p = u->GetPlayer();
    if (p) {
        p->Leave();
        GetTrackPanel()->HandleRemoveUser(u);
        TheGame->RemovePlayer(p);
        u->DeletePlayer();
        bool foundPlayer = false;
        for (int i = 0; i < mActivePlayers.size(); i++) {
            if (mActivePlayers[i] == p) {
                mActivePlayers.erase(mActivePlayers.begin() + i);
                mCrowdRatings.erase(mCrowdRatings.begin() + i);
                foundPlayer = true;
                break;
            }
        }
        MILO_ASSERT(foundPlayer, 0x112);
        mBandPerformer->SetCrowdMeter();
        if (TheGameMode->InMode("trainer") && TheTrainerPanel) {
            TheTrainerPanel->HandlePlayerDeleted(p);
        }
        TheGame->OnPlayerRemoved(p);
        delete p;
    } else {
        GetTrackPanel()->HandleRemoveUser(u);
    }
    GetTrackPanel()->PostHandleRemoveUser(u);
    u->SetTrack(nullptr);
    UpdateBonusLevel(TheTaskMgr.Seconds(TaskMgr::kRealTime) * 1000.0f);
}

std::vector<Player *> &Band::GetActivePlayers() { return mActivePlayers; }
void Band::SetAccumulatedScore(int score) { mAccumulatedScore = score; }

int Band::GetLongestStreak() const {
    int ret = unk3c;
    FOREACH (it, mActivePlayers) {
        int curStreak = (*it)->mStats.GetLongestStreak();
        if (ret < curStreak)
            ret = curStreak;
    }
    return ret;
}

void Band::Poll(float f1, SongPos &pos) {
    for (int i = 0; i < mActivePlayers.size(); i++) {
        mActivePlayers[i]->Poll(f1, pos);
        float rating = mActivePlayers[i]->GetCrowdRating();
        if (rating != mCrowdRatings[i]) {
            mCrowdRatings[i] = rating;
        }
    }
    mBandPerformer->Poll(f1, pos);
    float rating = mBandPerformer->GetCrowdRating();
    if (rating != unk30) {
        unk30 = rating;
    }
    CheckCoda(pos);
    UpdateBonusLevel(f1);
}

void Band::SetMultiplierActive(bool active) {
    mMultiplierActive = active;
    if (!active) {
        mMaxMultiplier = 1;
        mMsWithMultiplier = 0;
        mMsWhenMultiplierStarted = 0;
    }
    for (int i = 0; i < mActivePlayers.size(); i++) {
        mActivePlayers[i]->SetMultiplierActive(active);
    }
    mBandPerformer->SetMultiplierActive(active);
}

void Band::SetCrowdMeterActive(bool active) {
    for (int i = 0; i < mActivePlayers.size(); i++) {
        mActivePlayers[i]->SetCrowdMeterActive(active);
    }
    mBandPerformer->SetCrowdMeterActive(active);
}

bool Band::AnyoneSaveable() const {
    if (mBandPerformer->mGameOver)
        return false;
    else {
        for (int i = 0; i < mActivePlayers.size(); i++) {
            if (mActivePlayers[i]->Saveable())
                return true;
        }
    }
    return false;
}

int Band::DeployBandEnergy(BandUser *u) {
    int numSaved = 0;
    for (int i = 0; i < mActivePlayers.size(); i++) {
        if (mActivePlayers[i]->Saveable()) {
            mActivePlayers[i]->Save(u, false);
            numSaved++;
        }
    }
    return numSaved;
}

void Band::SaveAll() {
    std::vector<BandUser *> users;
    TheBandUserMgr->GetParticipatingBandUsers(users);
    MILO_ASSERT(!users.empty(), 0x1E6);
    for (int i = 0; i < mActivePlayers.size(); i++) {
        if (mActivePlayers[i]->GetEnabledState() == kPlayerDisabled) {
            mActivePlayers[i]->Save(users.front(), true);
        }
    }
}

void Band::CheckCoda(SongPos &pos) {
    if (NumNonQuarantinedPlayers() != 1
        || mActivePlayers[1]->mTrackType != kTrackVocals) {
        bool past_start_of_coda = false;
        if (TheSongDB->GetCodaStartTick() >= 0
            && TheSongDB->GetCodaStartTick() >= pos.GetTick()) {
            past_start_of_coda = true;
        }
        bool end_of_coda = IsEndOfCoda(pos.GetTick());
        if (past_start_of_coda) {
            if (end_of_coda && unk60 == 1) {
                unk60 = 2;
                TheBandDirector->SetCharacterHideHackEnabled(false);
            } else if (!end_of_coda && unk60 == 0 && mActivePlayers.size() > 2) {
                unk60 = 1;
                TheBandDirector->SetCharacterHideHackEnabled(true);
            }
        }
        if (unk40 && past_start_of_coda && end_of_coda) {
        }
        if (EveryoneFinishedCoda()) {
            WinCoda();
        }
        GetTrackPanelDir()->CodaEnd();
        unk40 = true;
    }
}

void Band::BlowCoda(Player *p) {
    if (p->IsLocal()) {
        LocalBlowCoda(p);
        p->Handle(send_blow_coda_msg, true);
    }
}

void Band::LocalBlowCoda(Player *p) {
    if (!p->mHasBlownCoda) {
        TheGamePanel->Handle(coda_blown_msg, false);
        for (int i = 0; i < mActivePlayers.size(); i++) {
            BandTrack *bandtrack = mActivePlayers[i]->GetBandTrack();
            if (bandtrack) {
                bandtrack->CodaFail(p == mActivePlayers[i]);
            }
            mActivePlayers[i]->ResetCodaPoints();
        }
        p->SetBlownCoda();
        unk44 = 2;
    }
}

void Band::DealWithCodaGem(Player *p, int, bool b3, bool b4) {
    if (!b3)
        BlowCoda(p);
    else if (b4)
        FinishedCoda(p);
}

bool Band::IsEndOfCoda(int i1) {
    if (unk40)
        return false;
    else {
        int i8 = 0;
        int i7 = 0;
        for (int i = 0; i < mActivePlayers.size(); i++) {
            int num = mActivePlayers[i]->GetTrackNum();
            if (TheSongDB->GetTotalGems(num) != 0) {
                i8 = TheSongDB->GetGem(num, TheSongDB->GetTotalGems(num) - 1).GetTick();
            }
            if (i8 > i7)
                i7 = i8;
        }
        return i7 <= i1;
    }
}

bool Band::EveryoneFinishedCoda() {
    if (unk44 == 2)
        return false;
    for (int i = 0; i < mActivePlayers.size(); i++) {
        Player *p = mActivePlayers[i];
        bool b = false;
        if (p->AutoplaysCoda() || p->mHasFinishedCoda || p->mQuarantined) {
            b = true;
        }
        if (!b)
            return false;
    }
    return true;
}

void Band::WinCoda() {
    TheGamePanel->Handle(coda_success_msg, false);
    for (int i = 0; i < mActivePlayers.size(); i++) {
        BandTrack *bt = mActivePlayers[i]->GetBandTrack();
        if (bt)
            bt->CodaSuccess();
        mActivePlayers[i]->AddCodaPoints();
    }
    unk44 = 1;
}

void Band::FinishedCoda(Player *p) {
    if (p->IsLocal()) {
        LocalFinishedCoda(p);
        static Message codaMsg("send_hit_last_coda_gem", 0);
        codaMsg[0] = p->GetCodaPoints();
        p->Handle(codaMsg, true);
    }
}

void Band::LocalFinishedCoda(Player *p) {
    if (!p->mHasBlownCoda) {
        p->SetFinishedCoda();
        GetTrackPanel()->UnisonPlayerSuccess(p);
    }
}

int Band::EnergyMultiplier() const { return mMultiplier; }
int Band::EnergyCrowdBoost() const { return unk70[mBonusLevel]; }

void Band::ForceStars(int stars) {
    FOREACH (it, mActivePlayers) {
        (*it)->ForceStars(stars);
    }
    TheGame->ForceTrackerStars(stars);
}

int Band::GetMultiplier(bool, int &, int &, int &) const { return mMultiplier; }

void Band::AddUserDynamically(BandUser *u) { GetTrackPanel()->HandleAddUser(u); }

Player *Band::AddPlayerDynamically(BeatMaster *m, BandUser *u) {
    Player *p = AddPlayer(m, u);
    GetTrackPanel()->HandleAddPlayer(p);
    p->DynamicAddBeatmatch();
    GetTrackPanel()->PostHandleAddPlayer(p);
    p->PostDynamicAdd();
    UpdateBonusLevel(TheTaskMgr.Seconds(TaskMgr::kRealTime) * 1000.0f);
    p->SetMultiplierActive(mMultiplierActive);
    p->SetCrowdMeterActive(mBandPerformer->GetCrowdMeterActive());
    return p;
}

Player *Band::AddPlayer(BeatMaster *m, BandUser *u) {
    Player *p = NewPlayer(m, u);
    mActivePlayers.push_back(p);
    u->SetPlayer(p);
    p->Crowd()->SetLoseLevel(mBandPerformer->Crowd()->GetLoseLevel());
    mCrowdRatings.push_back(0);
    p->ConfigureBehavior();
    return p;
}

Player *Band::NewPlayer(BeatMaster *master, BandUser *user) {
    MILO_ASSERT(user, 820);
    const PlayerTrackConfigList *ptclist = TheGameConfig->GetConfigList();
    int track_num = ptclist->GetConfigByUserGuid(user->GetUserGuid()).TrackNum();
    switch (user->GetTrackType()) {
    case kTrackVocals:
        int sing_ct = ptclist->NumSingers();
        return new VocalPlayer(user, master, this, track_num, mBandPerformer, sing_ct);
    case kTrackRealGuitar:
    case kTrackRealBass:
        return new RealGuitarGemPlayer(user, master, this, track_num, mBandPerformer);
    default:
        return new GemPlayer(user, master, this, track_num, mBandPerformer);
    }
}

void Band::UpdateBonusLevel(float f1) {
    if (IsMultiplierActive()) {
        int count = 0;
        FOREACH (it, mActivePlayers) {
            if ((*it)->IsDeployingBandEnergy() && !(*it)->GetQuarantined()) {
                count++;
            }
        }
        if (count != mBonusLevel) {
            if (mBonusLevel == 0) {
                mMsWhenMultiplierStarted = f1;
            }
            mBonusLevel = count;
            mMultiplier = unk68[mBonusLevel];
            mMaxMultiplier = Max(mMaxMultiplier, mMultiplier);
            MILO_ASSERT(mBonusLevel <= mMaxBonusLevel, 0x36D);
        }
        if (count > 0) {
            mMsWithMultiplier = Max(mMsWithMultiplier, f1 - mMsWhenMultiplierStarted);
        }
    }
}

bool Band::EveryoneDoneWithSong() const {
    for (int i = 0; i < mActivePlayers.size(); i++) {
        if (!mActivePlayers[i]->DoneWithSong())
            return false;
    }
    return true;
}

BEGIN_HANDLERS(Band)
    HANDLE_EXPR(band_performer, mBandPerformer)
    HANDLE_EXPR(num_active_players, (int)mActivePlayers.size())
    HANDLE_EXPR(active_player, mActivePlayers[_msg->Int(2)])
    HANDLE_EXPR(main_performer, MainPerformer())
    HANDLE_EXPR(get_multiplier_active, IsMultiplierActive())
    HANDLE_ACTION(set_multiplier_active, SetMultiplierActive(_msg->Int(2)))
    HANDLE_ACTION(set_crowd_meter_active, SetCrowdMeterActive(_msg->Int(2)))
    HANDLE_EXPR(multiplier, mMultiplier)
    HANDLE_EXPR(max_multiplier, mMaxMultiplier)
    HANDLE_EXPR(longest_multiplier_ms, mMsWithMultiplier)
    HANDLE_EXPR(longest_streak, GetLongestStreak())
    HANDLE_ACTION(save_all, SaveAll())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x39E)
END_HANDLERS