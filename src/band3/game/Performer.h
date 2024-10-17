#pragma once
#include "obj/Object.h"
#include "beatmatch/SongPos.h"
#include "game/CrowdRating.h"
#include "game/Stats.h"

class BandUser;
class Band;

class Performer : public virtual Hmx::Object {
public:
    Performer(BandUser*, Band*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~Performer();
    virtual int GetScore() const;
    virtual int GetAccumulatedScore() const;
    virtual int CodaScore() const;
    virtual int GetMultiplier(bool, int&, int&, int&) const;
    virtual float GetCrowdRating() const;
    virtual float GetCrowdWarningLevel() const;
    virtual float GetRawCrowdRating() const;
    virtual bool IsNet() const;
    virtual Symbol GetStarRating() const;
    virtual int GetNumStars() const = 0;
    virtual float GetNumStarsFloat() const = 0;
    virtual float GetTotalStars() const;
    virtual bool PastFinalNote() const = 0;
    virtual ExcitementLevel GetExcitement() const;
    virtual void Poll(float, const SongPos&);
    virtual void AddPoints(float, bool, bool);
    virtual void Hit();
    virtual void BuildHitStreak(int, float);
    virtual void EndHitStreak();
    virtual void Miss();
    virtual void BuildMissStreak(int);
    virtual void EndMissStreak();
    virtual void Restart(bool);
    virtual void SetMultiplierActive(bool);
    virtual float GetPartialStreakFraction() const;
    virtual bool IsInCrowdWarning() const;
    virtual void ForceScore(int);
    virtual float GetNotesHitFraction(bool*) const = 0;
    virtual void SetQuarantined(bool);
    virtual Symbol GetStreakType() const { return "default"; }
    virtual float GetCrowdBoost() const;
    virtual void RemoteUpdateCrowd(float);
    virtual int GetScoreForStars(int) const { return 0; }
    virtual void FinalizeStats();
    virtual bool CanStreak() const { return false; }

    int GetIndividualScore() const;
    int GetPercentComplete() const;
    int GetSongNumVocalParts() const;
    int GetNotesPerStreak() const;
    void WinGame(int);
    bool LoseGame();
    float GetRawValue() const;
    float GetDisplayValue() const;
    void UpdateScore(int);
    void SendRemoteStats(BandUser*);
    void SetRemoteStreak(int);
    void RemoteFinishedSong(int);
    void SetLost();
    bool GetMultiplierActive() const;
    float PollMs() const;
    void SetCrowdMeterActive(bool);
    bool GetCrowdMeterActive();
    void SetStats(int, const Stats&);
    void SendStreak();
    void TrulyWinGame();
    void ForceStars(int);
    int GetNumRestarts() const;
    void SetNoScorePercent(float);
    bool IsLocal() const { return !IsNet(); }
    Band* GetBand() const { return mBand; }
    bool GetQuarantined() const { return mQuarantined; }
    const Stats& GetStats() const { return mStats; }

    float mPollMs; // 0x8
    CrowdRating* mCrowd; // 0xc
    Stats mStats; // 0x10
    Band* mBand; // 0x1dc
    bool unk1e0;
    bool unk1e1;
    bool unk1e2;
    float mScore; // 0x1e4
    SongPos mSongPos; // 0x1e8
    bool mQuarantined; // 0x1fc
    bool unk1fd;
    bool unk1fe;
    bool unk1ff;
    float mProgressMs; // 0x200
    bool unk204;
    bool mMultiplierActive; // 0x205
    int mNumRestarts; // 0x208
};