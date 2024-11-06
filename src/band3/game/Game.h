#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "game/BandUser.h"
#include "game/Player.h"
#include "obj/Object.h"
#include "types.h"

class Game : public Hmx::Object {
    public:
    Game();
    virtual ~Game();

    void SetPaused(bool, bool, bool);
    void SetGameOver(bool);
    bool ResumedNoScore() const;
    bool IsActiveUser(BandUser*) const;
    bool IsWaiting();
    float GetMusicSpeed();
    int NumActivePlayers() const;
    void AddBonusPoints(BandUser*, int, int);
    void OnPlayerAddEnergy(Player*, float);
    void OnRemoteTrackerFocus(Player*, int, int, int);
    void OnRemoteTrackerPlayerProgress(Player*, float);
    void OnRemoteTrackerSectionComplete(Player*, int, int, int);
    void OnRemoteTrackerPlayerDisplay(Player*, int, int, int);
    void OnRemoteTrackerDeploy(Player*);
    void OnRemoteTrackerEndDeployStreak(Player*, int);
    void OnRemoteTrackerEndStreak(Player*, int, int);
    void OnPlayerQuarantined(Player*);

    u8 pad[0x4C];
    bool mIsPaused; // 0x68 iunno
};

extern Game* /*you just lost*/ TheGame;

#endif // GAME_GAME_H
