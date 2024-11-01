#pragma once
#include "meta/Profile.h"
#include "meta_band/Leaderboard.h"

class PlayerLeaderboard : public Leaderboard {
public:
    PlayerLeaderboard(Profile*, Callback*);
    virtual ~PlayerLeaderboard(){}
    virtual Symbol OnSelectRow(int, BandUser*);
    virtual bool CanRowsBeSelected() const;
    virtual bool IsRowFriend(int) const;
    virtual bool IsRowSelf(int) const;
};