#ifndef METABAND_ACCOMPLISHMENTDISCSONGCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTDISCSONGCONDITIONAL_H
#include "AccomplishmentSongConditional.h"

class AccomplishmentDiscSongConditional : public AccomplishmentSongConditional {
    AccomplishmentDiscSongConditional(DataArray*, int);
    virtual ~AccomplishmentDiscSongConditional();
    virtual AccomplishmentType GetType() const;
    
    virtual bool IsFulfilled(BandProfile*) const;
    virtual bool IsRelevantForSong(Symbol) const;
    
    virtual bool InqIncrementalSymbols(BandProfile*, std::vector<Symbol>&) const;
    
    virtual bool CanBeLaunched() const;
    virtual bool HasSpecificSongsToLaunch() const;
    virtual void InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, BandProfile*) const;
    virtual void InitializeTrackerDesc(TrackerDesc&) const;
};

#endif // METABAND_ACCOMPLISHMENTDISCSONGCONDITIONAL_H