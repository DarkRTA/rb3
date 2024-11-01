#pragma once
#include "game/Defines.h"
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

class PlayerSongLeaderboard : public PlayerLeaderboard {
public:
    PlayerSongLeaderboard(Profile*, Callback*, ScoreType, int);
    virtual ~PlayerSongLeaderboard(){}
    virtual void EnumerateFromID();
    virtual void EnumerateRankRange(int, int);
    virtual void GetStats();
    virtual bool ShowsDifficultyAndPct() const { return mScoreType != kScoreBand; }

    ScoreType mScoreType; // 0x84
    int mSongID; // 0x88
};

class PlayerBattleLeaderboard : public PlayerLeaderboard {
public:
    PlayerBattleLeaderboard(Profile*, Callback*, int);
    virtual ~PlayerBattleLeaderboard(){}
    virtual void EnumerateFromID();
    virtual void EnumerateRankRange(int, int);
    virtual void GetStats();

    int mSongID; // 0x84
};