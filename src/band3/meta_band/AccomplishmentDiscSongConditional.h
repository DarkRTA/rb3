#ifndef METABAND_ACCOMPLISHMENTDISCSONGCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTDISCSONGCONDITIONAL_H
#include "AccomplishmentSongConditional.h"
#include "meta_band/SongSortMgr.h"
#include "obj/Data.h"

class AccomplishmentDiscSongConditional : public AccomplishmentSongConditional {
public:
    AccomplishmentDiscSongConditional(DataArray*, int);
    virtual ~AccomplishmentDiscSongConditional();
    virtual AccomplishmentType GetType() const;    
    virtual bool IsFulfilled(BandProfile*) const;
    virtual bool IsRelevantForSong(Symbol) const;    
    virtual bool InqIncrementalSymbols(BandProfile*, std::vector<Symbol>&) const;
    virtual bool CanBeLaunched() const;
    virtual bool HasSpecificSongsToLaunch() const;
    virtual int GetNumCompletedSongs(BandProfile*) const;
    virtual int GetTotalNumSongs() const;

    void Configure(DataArray*);
    bool InqSongs(std::vector<Symbol>&, bool) const;
    
    SongSortMgr::SongFilter mFilter; // 0x7c
    Symbol mPartDifficultySym; // 0x90
};

#endif // METABAND_ACCOMPLISHMENTDISCSONGCONDITIONAL_H