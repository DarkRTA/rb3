#pragma once
#include "game/CommonPhraseCapturer.h"
#include "game/Performer.h"
#include "game/Player.h"
#include "obj/Object.h"
#include "utl/SongPos.h"

class BandPerformer;
class BandUser;
class BeatMaster;

class Band : public Hmx::Object {
public:
    Band(bool, int, BandUser *, BeatMaster *);
    virtual ~Band();
    virtual DataNode Handle(DataArray *, bool);

    int EnergyMultiplier() const;
    int EnergyCrowdBoost() const;
    void ForceStars(int);
    void UpdateBonusLevel(float);
    int DeployBandEnergy(BandUser *);
    int GetMultiplier(bool, int &, int &, int &) const;
    Performer *MainPerformer() const;
    Performer *GetBand() const;
    Player *AddPlayer(BeatMaster *, BandUser *);
    Player *GetActivePlayer(int) const;
    int NumActivePlayers() const;
    int NumNonQuarantinedPlayers() const;
    std::vector<Player *> &GetActivePlayers();
    void SetAccumulatedScore(int);
    void SetMultiplierActive(bool);
    void SetCrowdMeterActive(bool);
    int GetLongestStreak() const;
    void SaveAll();
    void BlowCoda(Player *);
    void LocalBlowCoda(Player *);
    void FinishedCoda(Player *);
    void LocalFinishedCoda(Player *);
    void AddUserDynamically(BandUser *);
    Player *AddPlayerDynamically(BeatMaster *, BandUser *);
    Player *NewPlayer(BeatMaster *, BandUser *);
    bool EveryoneDoneWithSong() const;
    bool EveryoneFinishedCoda();
    void DealWithCodaGem(Player *, int, bool, bool);
    bool AnyoneSaveable() const;
    void SetGameOver();
    void Restart(bool);
    void RemoveUser(BandUser *);
    void Poll(float, SongPos &);
    void CheckCoda(SongPos &);
    bool IsEndOfCoda(int);
    void WinCoda();
    bool IsMultiplierActive() const { return mMultiplierActive; }
    int AccumulatedScore() const { return mAccumulatedScore; }
    float GetTotalStars() const { return mTotalStars; }

    BandPerformer *mBandPerformer; // 0x1c
    std::vector<Player *> mActivePlayers; // 0x20
    std::vector<float> mCrowdRatings; // 0x28
    float unk30; // 0x30
    int mAccumulatedScore; // 0x34
    float mTotalStars; // 0x38
    int unk3c; // 0x3c
    bool unk40; // 0x40
    int unk44; // 0x44
    int mBonusLevel; // 0x48
    int mMultiplier; // 0x4c
    int mMaxMultiplier; // 0x50
    float mMsWithMultiplier; // 0x54
    float mMsWhenMultiplierStarted; // 0x58
    bool mMultiplierActive; // 0x5c
    int unk60; // 0x60
    int mMaxBonusLevel; // 0x64
    std::vector<int> unk68; // 0x68
    std::vector<int> unk70; // 0x6c
    CommonPhraseCapturer *mCommonPhraseCapturer; // 0x78
};