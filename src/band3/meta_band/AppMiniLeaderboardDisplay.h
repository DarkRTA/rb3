#pragma once
#include "bandobj/MiniLeaderboardDisplay.h"
#include "meta_band/Leaderboard.h"

class AppMiniLeaderboardDisplay : public MiniLeaderboardDisplay,
                                  public Leaderboard::Callback {
public:
    AppMiniLeaderboardDisplay();
    // Hmx::Object
    virtual ~AppMiniLeaderboardDisplay();
    // not an oversight
    OBJ_CLASSNAME(MiniLeaderboardDisplay);
    OBJ_SET_TYPE(MiniLeaderboardDisplay);
    virtual DataNode Handle(DataArray *, bool);
    void Poll();
    void DrawShowing();
    void SetLeaderboardStatus();
    void UpdateLeaderboardOnline(int);
    void UpdateLeaderboard(int, ScoreType);
    bool IsReady();
    bool HasRows();
    void ResultSuccess(bool, bool, bool);
    void ResultFailure();
    void Update();
    void CancelOldServerRequest();
    void Exit();
};