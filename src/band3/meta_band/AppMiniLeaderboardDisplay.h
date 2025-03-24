#pragma once
#include "bandobj/MiniLeaderboardDisplay.h"
#include "meta_band/Leaderboard.h"

class AppMiniLeaderboardDisplay : public MiniLeaderboardDisplay,
                                  public Leaderboard::Callback {
public:
    AppMiniLeaderboardDisplay();
};