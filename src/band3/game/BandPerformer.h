#pragma once
#include "game/Performer.h"
#include "obj/Data.h"

class BandPerformer : public Performer {
public:
    BandPerformer(Band *, BandUser *);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~BandPerformer();
    virtual int GetScore() const;
    virtual int GetAccumulatedScore() const;
    virtual int CodaScore() const;
    virtual bool IsNet() const;
    virtual int GetNumStars() const;
    virtual float GetNumStarsFloat() const;
    virtual float GetTotalStars() const;
    virtual bool PastFinalNote() const;
    virtual ExcitementLevel GetExcitement() const;
    virtual void ForceScore(int);
    virtual float GetNotesHitFraction(bool *) const;
    virtual Symbol GetStreakType() const { return "multi"; }
    virtual int GetScoreForStars(int) const;
    virtual void Lose();

    void Restart();
    void ComputeScoreData();
    void SetCrowdMeter();
    void Poll(float, SongPos &);
    void ComputePoints();
    float WeightedCrowdLevel() const;
    bool NoOneContributingToCrowd() const;

    DataArray *unk20c; // 0x20c
    int unk210; // 0x210
    int unk214; // 0x214
};