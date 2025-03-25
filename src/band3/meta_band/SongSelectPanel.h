#pragma once
#include "game/BandUser.h"
#include "game/Defines.h"
#include "meta_band/AppMiniLeaderboardDisplay.h"
#include "meta/HeldButtonPanel.h"
#include "meta_band/Leaderboard.h"

class SongSelectPanel : public HeldButtonPanel, public Leaderboard::Callback {
public:
    SongSelectPanel();
    OBJ_CLASSNAME(SongSelectPanel);
    OBJ_SET_TYPE(SongSelectPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~SongSelectPanel() {}
    virtual bool Exiting() const;
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void FinishLoad();
    virtual void ResultSuccess(bool, bool, bool);
    virtual void ResultFailure();

    DataNode OnMsg(const ButtonDownMsg &);
    Leaderboard *GetLeaderboard(LocalBandUser *, ScoreType, int, Leaderboard::Mode);
    void RestartLeaderboardTimer();
    void CancelLeaderboardTimer();

    Leaderboard *mLeaderboard; // 0x44
    AppMiniLeaderboardDisplay *unk48; // 0x48
    float unk4c;
    float unk50;
    bool unk54;
    float unk58;
};