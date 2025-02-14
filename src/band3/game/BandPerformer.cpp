#include "game/BandPerformer.h"
#include "Player.h"
#include "bandobj/CrowdAudio.h"
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/Performer.h"
#include "game/Band.h"
#include "game/Scoring.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

BandPerformer::BandPerformer(Band *band, BandUser *user)
    : Performer(user, band), unk20c(SystemConfig("scoring", "crowd", "weights")) {
    mCrowd->SetLoseLevel(
        SystemConfig("scoring", "crowd")->FindFloat("multiplayer_lose_level")
    );
    ComputeScoreData();
}

BandPerformer::~BandPerformer() {}

void BandPerformer::Restart() {
    Performer::Restart(false);
    ComputeScoreData();
}

void BandPerformer::Poll(float f1, SongPos &pos) {
    Performer::Poll(f1, pos);
    ComputePoints();
    SetCrowdMeter();
}

int BandPerformer::GetScore() const {
    const_cast<BandPerformer *>(this)->ComputePoints();
    return mScore;
}

int BandPerformer::GetAccumulatedScore() const {
    int baseScore = GetScore();
    return baseScore + mBand->AccumulatedScore();
}

int BandPerformer::GetNumStars() const { return TheScoring->GetBandNumStars(mScore); }
float BandPerformer::GetNumStarsFloat() const {
    return TheScoring->GetBandNumStarsFloat(mScore);
}

float BandPerformer::GetTotalStars() const {
    float base = GetNumStarsFloat();
    return base + mBand->GetTotalStars();
}

int BandPerformer::GetScoreForStars(int i1) const {
    return TheScoring->GetBandScoreForStars(i1);
}

bool BandPerformer::IsNet() const {
    std::vector<Player *> &players = mBand->GetActivePlayers();
    FOREACH (it, players) {
        if ((*it)->IsNet())
            return true;
    }
    return false;
}

bool BandPerformer::PastFinalNote() const {
    std::vector<Player *> &players = mBand->GetActivePlayers();
    FOREACH (it, players) {
        if (!(*it)->PastFinalNote())
            return false;
    }
    return true;
}

void BandPerformer::ComputePoints() {
    int i5 = 0;
    std::vector<Player *> &players = mBand->GetActivePlayers();
    FOREACH (it, players) {
        if (!(*it)->GetQuarantined()) {
            BandUser *u = (*it)->GetUser();
            if (!u->IsNullUser()) {
                i5 += (*it)->GetScore();
            }
        }
    }
    mScore = i5;
}

int BandPerformer::CodaScore() const {
    int i5 = 0;
    std::vector<Player *> &players = mBand->GetActivePlayers();
    FOREACH (it, players) {
        if (!(*it)->GetQuarantined()) {
            i5 += (*it)->CodaScore();
        }
    }
    return i5;
}

void BandPerformer::ForceScore(int i1) {
    bool b1 = false;
    std::vector<Player *> &players = mBand->GetActivePlayers();
    FOREACH (it, players) {
        if (!(*it)->GetQuarantined()) {
            (*it)->ForceScore(i1 & ~-b1);
            b1 = true;
        }
    }
}

void BandPerformer::ComputeScoreData() {
    unk214 = 0;
    std::vector<Player *> &players = mBand->GetActivePlayers();
    FOREACH (it, players) {
        BandUser *user = (*it)->GetUser();
        MILO_ASSERT(user, 0xA4);
        TrackType ty = (*it)->GetTrackType();
        if (ty == kTrackNone) {
            MILO_WARN(
                "Player %s (%s) has track type of NONE",
                (*it)->GetUser()->UserName(),
                (*it)->GetUserGuid().ToString()
            );
        } else {
            if (!user->IsNullUser()) {
                unk214 |= 1 << ty;
            }
        }
    }
}

float BandPerformer::GetNotesHitFraction(bool *bptr) const {
    float f1 = 0;
    std::vector<Player *> &players = mBand->GetActivePlayers();
    FOREACH (it, players) {
        f1 += (*it)->GetNotesHitFraction(nullptr);
    }
    float f2 = 0;
    if (players.size() != 0) {
        f2 = f1 / players.size();
    }
    return f2;
}

void BandPerformer::Lose() {
    if (LoseGame()) {
        SetLost();
        std::vector<Player *> &players = mBand->GetActivePlayers();
        FOREACH (it, players) {
            (*it)->SetLost();
        }
    }
}

void BandPerformer::SetCrowdMeter() {
    mCrowd->SetValue(WeightedCrowdLevel());
    if (mCrowd->IsBelowLoseLevel()) {
        if (!MetaPerformer::Current()->IsNoFailActive() && !NoOneContributingToCrowd()
            && !mBand->EveryoneDoneWithSong()) {
            Lose();
        }
    }
}

float BandPerformer::WeightedCrowdLevel() const {
    int u12 = 0;
    std::vector<Player *> &players = mBand->GetActivePlayers();
    int numplayers = players.size();
    std::vector<float> crowdratings;
    crowdratings.reserve(numplayers);
    for (int i = 0; i < numplayers; i++) {
        BandUser *user = players[i]->GetUser();
        MILO_ASSERT(user, 0xEF);
        if (!players[i]->GetQuarantined() && !user->IsNullUser()) {
            u12 |= players[i]->GetEnabledState() != 0;
            crowdratings.push_back(players[i]->GetCrowdRating());
        }
    }
    if (u12 == 0)
        return 0;
    else {
        std::sort(crowdratings.begin(), crowdratings.end());
        DataArray *arr = unk20c->FindArray(crowdratings.size(), true)->Array(1);
        float ret = 0;
        for (int i = 0; i < crowdratings.size(); i++) {
            ret += crowdratings[i] * arr->Float(i);
        }
        return ret;
    }
}

bool BandPerformer::NoOneContributingToCrowd() const {
    std::vector<Player *> &players = mBand->GetActivePlayers();
    FOREACH (it, players) {
        if (!(*it)->GetQuarantined()) {
            if (!(*it)->GetUser()->IsNullUser()
                && (*it)->GetEnabledState() != kPlayerDisconnected) {
                return false;
            }
        }
    }
    return true;
}

ExcitementLevel BandPerformer::GetExcitement() const {
    if (NoOneContributingToCrowd()) {
        return kExcitementOkay;
    } else {
        return mCrowd->GetExcitement();
    }
}

BEGIN_HANDLERS(BandPerformer)
    HANDLE_EXPR(num_stars, GetNumStars())
    HANDLE_EXPR(star_rating, GetStarRating())
    HANDLE_SUPERCLASS(Performer)
    HANDLE_CHECK(0x12B)
END_HANDLERS