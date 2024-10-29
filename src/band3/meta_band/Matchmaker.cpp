#include "meta_band/Matchmaker.h"
#include "Matchmaker.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/MsgSource.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Symbols2.h"

MatchmakerPoolStats::MatchmakerPoolStats(){
    DataArray* cfg = SystemConfig("net", "matchmaker", "pool_min_thresholds");
    for(int i = 0; i < 3; i++){
        mRatingThresholds[i] = cfg->Int(i + 1);
    }
    ClearStats();
}

Matchmaker::Matchmaker() : mMode(0), unk20(0) {
    SetName("matchmaker", ObjectDir::Main());
    mQuickFindingMode = new QuickFinding();
    mBandFindingMode = new BandFinding();
    mPoolStats = new MatchmakerPoolStats();
}

Matchmaker::~Matchmaker(){
    delete mPoolStats;
    delete mQuickFindingMode;
    delete mBandFindingMode;
}

void Matchmaker::SetQuickFindingMode(MatchmakerFindType type){
    MILO_ASSERT(!IsFinding(), 0xD1);
    mQuickFindingMode->Init(type);
    mMode = mQuickFindingMode;
    UpdateMatchmakingSettings();
}

void Matchmaker::FindPlayers(MatchmakerFindType ty){
    SetQuickFindingMode(ty);
    FindPlayersImpl();
    static MatchmakerChangedMsg msg;
    Export(msg, true);
}

void Matchmaker::CancelFind(){
    mPoolStats->ClearStats();
    CancelFindImpl();
    static MatchmakerChangedMsg msg;
    Export(msg, true);
}

bool Matchmaker::IsHostingQp() const {
    return mMode == mQuickFindingMode && mQuickFindingMode->mFindType == kMatchmaker_Qp;
}

bool Matchmaker::IsHostingTour() const {
    return mMode == mQuickFindingMode && mQuickFindingMode->mFindType == kMatchmaker_Tour;
}

BEGIN_HANDLERS(Matchmaker)
    HANDLE_ACTION(find_players, FindPlayers((MatchmakerFindType)_msg->Int(2)))
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0xFD)
END_HANDLERS

inline int QuickFinding::GetNextQueryType(){
    MILO_ASSERT(!mQueryTypes.empty(), 0xA0);
    int next = mQueryTypes.front();
    mQueryTypes.erase(mQueryTypes.begin());
    mQueryTypes.push_back(next);
    return next;
}