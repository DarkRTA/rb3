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
    virtual int GetExcitement() const;
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
    virtual Symbol GetStreakType() const;
    virtual float GetCrowdBoost() const;
    virtual void RemoteUpdateCrowd(float);
    virtual int GetScoreForStars(int) const;
    virtual void FinalizeStats();
    virtual bool CanStreak() const;

    float unk8;
    CrowdRating* unkc;
    Stats unk10;
    Band* unk1dc;
    bool unk1e0;
    bool unk1e1;
    bool unk1e2;
    float unk1e4;
    SongPos unk1e8;
    bool unk1fc;
    bool unk1fd;
    bool unk1fe;
    bool unk1ff;
    float unk200;
    bool unk204;
    bool unk205;
    int unk208;
};