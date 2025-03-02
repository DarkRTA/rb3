#pragma once
#include "game/Defines.h"
#include "meta_band/Leaderboard.h"
#include "net_band/DataResults.h"
#include "obj/Msg.h"
#include "obj/Object.h"

class PerformanceData;
class AccomplishmentProgress;

class RockCentral : public MsgSource {
public:
    RockCentral();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~RockCentral();

    void ForceLogout();
    void FailAllOutstandingCalls();
    void CancelOutstandingCalls(Hmx::Object *);
    void
    GetLeaderboardByPlayer(std::vector<int> &, int, ScoreType, LeaderboardType, LeaderboardMode, int, DataResultList &, Hmx::Object *);
    void
    GetLeaderboardByRankRange(std::vector<int> &, int, ScoreType, int, int, LeaderboardType, DataResultList &, Hmx::Object *);
    void
    GetMaxRank(std::vector<int> &, int, ScoreType, LeaderboardType, DataResultList &, Hmx::Object *);
    void
    GetBattleLeaderboardByPlayer(std::vector<int> &, int, LeaderboardMode, int, DataResultList &, Hmx::Object *);
    void
    GetBattleLeaderboardByRankRange(std::vector<int> &, int, int, int, DataResultList &, Hmx::Object *);
    void GetBattleMaxRank(std::vector<int> &, int, DataResultList &, Hmx::Object *);
    void
    GetAccLeaderboardByPlayer(std::vector<int> &, Symbol &, LeaderboardMode, int, DataResultList &, Hmx::Object *);
    void
    GetAccLeaderboardByRankRange(std::vector<int> &, Symbol &, int, int, DataResultList &, Hmx::Object *);
    void GetAccMaxRank(std::vector<int> &, Symbol &, DataResultList &, Hmx::Object *);
    void
    RecordPerformance(const Profile *, const PerformanceData *, int, Hmx::Object *, DataResultList &);
    void
    RecordAccomplishmentData(const Profile *, AccomplishmentProgress *, int, Hmx::Object *, DataResultList &);
    void UpdateBandLogo(int, RndTex *, int, Hmx::Object *, int);
    void GetWebLinkStatus(const Profile *, int, DataResultList &, Hmx::Object *);
    void GetSetlistCreationStatus(const Profile *, int, DataResultList &, Hmx::Object *);
};

extern RockCentral TheRockCentral;