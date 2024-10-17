#ifndef METABAND_ACCOMPLISHMENTSONGCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTSONGCONDITIONAL_H

#include "AccomplishmentConditional.h"
#include "system/ui/UILabel.h"
#include "SongStatusMgr.h"

class AccomplishmentSongConditional : public AccomplishmentConditional {
public:
    AccomplishmentSongConditional(DataArray*, int);
    virtual ~AccomplishmentSongConditional();
    virtual bool ShowBestAfterEarn() const;
    virtual void UpdateIncrementalEntryName(UILabel*, Symbol);
    virtual bool InqProgressValues(BandProfile*, int&, int&);
    virtual bool IsSymbolEntryFulfilled(BandProfile*, Symbol) const;
    virtual void InitializeTrackerDesc(TrackerDesc&) const;
    virtual int GetNumCompletedSongs(BandProfile*) const = 0;
    virtual int GetTotalNumSongs() const = 0;
    virtual bool CheckConditionsForSong(SongStatusMgr*, Symbol) const;
    
    bool CheckStarsCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckScoreCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckAccuracyCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckStreakCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckHoposPercentCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckSoloPercentCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckDoubleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckTripleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckHitBRECondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckAllDoubleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckAllTripleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckPerfectDrumRollsCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    bool CheckFullComboCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
};

#endif // METABAND_ACCOMPLISHMENTCONDITIONAL_H
