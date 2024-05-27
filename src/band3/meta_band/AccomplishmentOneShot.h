#ifndef METABAND_ACCOMPLISHMENTONESHOT_H
#define METABAND_ACCOMPLISHMENTONESHOT_H

#include "system/obj/Data.h"
#include "system/ui/UILabel.h"
#include "AccomplishmentConditional.h"

class AccomplishmentOneShot : public AccomplishmentConditional {
public:
    AccomplishmentOneShot(DataArray*, int);
    virtual ~AccomplishmentOneShot();

private:
    void Configure(DataArray*);
    int GetType() const;
    // void AreOneShotConditionsMet(ScoreType, Difficulty, Performer*, Symbol, int);
    void InitializeTrackerDesc(TrackerDesc&) const;
    bool HasSpecificSongsToLaunch() const;
    void UpdateIncrementalEntryName(UILabel*, Symbol);

    Symbol mOneShotSong; // 0x7c
    int mOneShotPlayerMin; // 0x80
};

#endif // METABAND_ACCOMPLISHMENTONESHOT_H