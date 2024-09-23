#ifndef METABAND_ACCOMPLISHMENTONESHOT_H
#define METABAND_ACCOMPLISHMENTONESHOT_H

#include "system/obj/Data.h"
#include "system/ui/UILabel.h"
#include "AccomplishmentConditional.h"

class Performer;

class AccomplishmentOneShot : public AccomplishmentConditional {
public:
    AccomplishmentOneShot(DataArray*, int);
    virtual ~AccomplishmentOneShot();

private:
    void Configure(DataArray*);
    int GetType() const;
    bool AreOneShotConditionsMet(ScoreType, Difficulty, Performer*, Symbol, int);
    void InitializeTrackerDesc(TrackerDesc&) const;
    bool HasSpecificSongsToLaunch() const;

    Symbol mOneShotSong; // 0x7c
    int mOneShotPlayerMin; // 0x80
};

#endif // METABAND_ACCOMPLISHMENTONESHOT_H