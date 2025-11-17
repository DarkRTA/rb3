#include "game/Tracker.h"
#include "game/Band.h"
#include "bandtrack/Track.h"
#include "bandtrack/TrackPanel.h"
#include "game/Game.h"
#include "game/Performer.h"
#include "game/TrackerDisplay.h"
#include "game/TrackerSource.h"
#include "meta_band/ModifierMgr.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

Tracker::Tracker(
    TrackerSource *src, TrackerBandDisplay &banddisp, TrackerBroadcastDisplay &bcdisp
)
    : mFirstPoll(1), mBandDisplay(banddisp), mBroadcastDisplay(bcdisp), mSource(src),
      unk44(0), unk48(gNullStr), unk4c(gNullStr) {}

Tracker::~Tracker() { RELEASE(mSource); }

void Tracker::UpdateSource(TrackerSource *src) {
    delete mSource;
    mSource = src;
}

void Tracker::Restart() {
    mPlayerDisplays.resize(5);

    int idx = 0;
    for (TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull();
         id = mSource->GetNextPlayer(id)) {
        Player *p = mSource->GetPlayer(id);
        mPlayerDisplays[idx++].mPlayer = p;
    }
    mFirstPoll = true;
    mTargets = mDesc.unk18;
    if (mDesc.unk20)
        TranslateRelativeTargets();

    for (TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull();
         id = mSource->GetNextPlayer(id)) {
        GetPlayerDisplay(id).Disable();
    }
    Restart_();
}

void Tracker::HandleAddPlayer(Player *iPlayer) {
    MILO_ASSERT(GetPlayerDisplayIndex( iPlayer ) == -1, 0x60);
    for (int i = 0; i < mPlayerDisplays.size(); i++) {
        if (!mPlayerDisplays[i].mPlayer) {
            mPlayerDisplays[i].mPlayer = iPlayer;
            break;
        }
    }
    GetTrackPanel()->SetSuppressUnisonDisplay(mDesc.unk10);
    GetTrackPanel()->SetSuppressPlayerFeedback(mDesc.unk12);
    mSource->HandleAddPlayer(iPlayer);
    HandleAddPlayer_(iPlayer);
}

void Tracker::HandleRemovePlayer(Player *player) {
    HandleRemovePlayer_(player);
    mSource->HandleRemovePlayer(player);
    int idx = GetPlayerDisplayIndex(player);
    if (idx != -1) {
        mPlayerDisplays[idx].Disable();
        mPlayerDisplays[idx].mPlayer = nullptr;
    }
    if (mSource->GetPlayerCount() == 0) {
        Restart();
    }
}

void Tracker::HandlePlayerSaved(Player *player) {
    TrackerPlayerID pid = mSource->FindPlayerID(player);
    if (pid.NotNull() && mSource->IsPlayerEligible(pid)) {
        HandlePlayerSaved_(pid);
    }
}

void Tracker::HandleGameOver(float f) {
    HandleGameOver_(f);
    mBroadcastDisplay.Hide();
    SavePlayerStats();
    float pct = CalcProgressPercentage();
    for (TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull();
         id = mSource->GetNextPlayer(id)) {
        if (mSource->IsPlayerLocal(id)) {
            Player *pPlayer = mSource->GetPlayer(id);
            MILO_ASSERT(pPlayer, 0xAD);
            pPlayer->mStats.unk1c4 = pct;
        }
    }
}

void Tracker::StartIntro() {
    if (!TheModifierMgr->IsModifierActive(mod_nohud)) {
        DataArrayPtr desc = GetBroadcastDescription();
        if (unk4c != gNullStr) {
            mBroadcastDisplay.Broadcast(DataArrayPtr(unk4c), unk48);
        } else if (desc->Size() != 0) {
            mBroadcastDisplay.Broadcast(desc, gNullStr);
        }
    }
}

void Tracker::Poll(float f) {
    if (mFirstPoll) {
        ReachedTargetLevel(-1);
        FirstFrame_(f);
        mFirstPoll = false;
        GetTrackPanel()->SetSuppressTambourineDisplay(mDesc.unk11);
        GetTrackPanel()->SetSuppressPlayerFeedback(mDesc.unk12);
        SetupDisplays();
    }
    Poll_(f);
}

void Tracker::Configure(const TrackerDesc &desc) {
    mDesc = desc;
    unk44 = desc.unk14;
    mTargets = desc.unk18;
    if (desc.unk24) {
        ConfigureTrackerSpecificData(desc.unk24);
    }
}

void Tracker::ReconcileStats() {
    float f1 = 0;
    for (TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull();
         id = mSource->GetNextPlayer(id)) {
        Player *pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0xFF);
        if (f1 < pPlayer->mStats.unk1c4) {
            f1 = pPlayer->mStats.unk1c4;
        }
    }
    Band *pBand = TheGame->GetBand();
    MILO_ASSERT(pBand, 0x107);
    Performer *pPerformer = pBand->GetBand();
    MILO_ASSERT(pPerformer, 0x109);
    pPerformer->mStats.unk1c4 = f1;
}

float Tracker::CalcProgressPercentage() const {
    float val = GetCurrentValue();
    float last = mTargets.back();
    float ret = 0;
    if (last > 0) {
        ret = Clamp(0.0f, 1.0f, val / last);
    }
    return ret;
}

int Tracker::GetTargetSuccessLevel() const {
    float val = GetCurrentValue();
    int level = -1;
    for (int i = 0; i < mTargets.size(); i++) {
        if (val < mTargets[i])
            break;
        else
            level++;
    }
    return level;
}

void Tracker::ReachedTargetLevel(int level) {
    if (level != -1) {
        TargetSuccess(level);
    }
    if (level < (int)mTargets.size() - 1) {
        DataArrayPtr desc = GetTargetDescription(level + 1);
        if (level != -1) {
            mBandDisplay.HandleTargetPass(level, desc);
        } else {
            mBandDisplay.ShowTarget(desc);
        }
        mBandDisplay.SetSuccessState(false);
    } else {
        mBandDisplay.LastTargetPass();
        mBandDisplay.SetSuccessState(true);
    }
}

void Tracker::UpdateGoalValueLabel(UILabel &) const {}
void Tracker::UpdateCurrentValueLabel(UILabel &) const {}
String Tracker::GetPlayerContributionString(Symbol) const { return ""; }

bool Tracker::HasPlayerForInstrument(Symbol s) const {
    return mSource->GetIDFromInstrument(s).NotNull();
}

bool Tracker::ReachedAnyTarget() const { return GetTargetSuccessLevel() > -1; }

void Tracker::SetupDisplays() {
    TrackerChallengeType ty = GetChallengeType();
    for (int i = 0; i < mPlayerDisplays.size(); i++) {
        if (mPlayerDisplays[i].mPlayer) {
            mPlayerDisplays[i].SetChallengeType(ty);
        }
    }
    mBroadcastDisplay.SetChallengeType(ty);
    mBandDisplay.SetChallengeType(ty);
}

const TrackerPlayerDisplay &Tracker::GetPlayerDisplay(const TrackerPlayerID &pid) const {
    Player *pPlayer = mSource->GetPlayer(pid);
    MILO_ASSERT(pPlayer, 399);
    int index = GetPlayerDisplayIndex(pPlayer);
    MILO_ASSERT(index != -1, 0x192);
    return mPlayerDisplays[index];
}

int Tracker::GetPlayerDisplayIndex(Player *p) const {
    for (int i = 0; i < mPlayerDisplays.size(); i++) {
        if (mPlayerDisplays[i].mPlayer == p)
            return i;
    }
    return -1;
}

void Tracker::SetPlayerProgress(const TrackerPlayerID &pid, float f) {
    LocalSetPlayerProgress(pid, f);
    Player *pPlayer = mSource->GetPlayer(pid);
    MILO_ASSERT(pPlayer, 0x1AE);
    static Message msg("send_tracker_player_progress", 0);
    msg[0] = f;
    pPlayer->HandleType(msg);
}

void Tracker::LocalSetPlayerProgress(const TrackerPlayerID &pid, float f) {
    if (pid.NotNull()) {
        GetPlayerDisplay(pid).SetProgressPercentage(f, true);
    }
}

void Tracker::RemoteSetPlayerProgress(Player *p, float f) {
    TrackerPlayerID pid = mSource->FindPlayerID(p);
    if (pid.NotNull()) {
        LocalSetPlayerProgress(pid, f);
    }
}

void Tracker::RemoteTrackerPlayerDisplay(Player *p, int i1, int i2, int i3) {
    TrackerPlayerID pid = mSource->FindPlayerID(p);
    if (pid.NotNull()) {
        GetPlayerDisplay(pid).RemotePlayerDisplayMsg(i1, i2, i3);
    }
}

void Tracker::RemoteEndStreak(Player *p, int i1, int i2) {
    RemoteEndStreak_(p, (float)i1 / 10000.0f, i2);
}

void Tracker::SendEndStreak(Player *p, float f, int i) {
    static Message endStreakMsg("send_tracker_end_streak", 0.0f, 0);
    endStreakMsg[0] = (int)(f * 10000.0f);
    endStreakMsg[1] = i;
    p->HandleType(endStreakMsg);
}