#include "game/Band.h"
#include "BandPerformer.h"
#include "bandobj/BandDirector.h"
#include "bandtrack/TrackPanel.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/CommonPhraseCapturer.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "game/Player.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Messages.h"
#include "utl/Messages3.h"
#include "utl/Std.h"
#include "utl/Symbols.h"

Band::Band(bool bbb, int i2, BandUser *user, BeatMaster *bm)
    : mBandPerformer(0), unk30(0), mAccumulatedScore(0), unk38(0), unk3c(0), unk40(0),
      unk44(0), mBonusLevel(0), mMultiplier(1), mMaxMultiplier(1), mMsWithMultiplier(0),
      mMsWhenMultiplierStarted(0), mMultiplierActive(1), unk60(0) {
    DataArray *cfg = SystemConfig("scoring", "bonuses");
    mMaxBonusLevel = cfg->FindInt("max_bonus");
    DataArray *multArr = cfg->FindArray("multiplier", true)->Array(1);
    for (int i = 0; i < multArr->Size(); i++) {
        unk68.push_back(multArr->Int(i));
    }
    DataArray *crowdArr = cfg->FindArray("crowd_boost", true)->Array(1);
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

std::vector<Player *> &Band::GetActivePlayers() { return mActivePlayers; }
void Band::SetAccumulatedScore(int score) { mAccumulatedScore = score; }

bool Band::AnyoneSaveable() const {}

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

void Band::BlowCoda(Player *p) {
    if (p->IsLocal()) {
        LocalBlowCoda(p);
        p->Handle(send_blow_coda_msg, true);
    }
}

void Band::LocalBlowCoda(Player *p) {}

void Band::DealWithCodaGem(Player *p, int, bool b3, bool b4) {
    if (!b3)
        BlowCoda(p);
    else if (b4)
        FinishedCoda(p);
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
    unk28.push_back(0);
    p->ConfigureBehavior();
    return p;
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