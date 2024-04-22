#ifndef BEATMATCH_GUITARTRACKWATCHERIMPL_H
#define BEATMATCH_GUITARTRACKWATCHERIMPL_H
#include "beatmatch/BaseGuitarTrackWatcherImpl.h"

class GuitarTrackWatcherImpl : public BaseGuitarTrackWatcherImpl {
public:
    GuitarTrackWatcherImpl(int, const UserGuid&, int, SongData*, GameGemList*, TrackWatcherParent*, DataArray*);
    virtual ~GuitarTrackWatcherImpl();
    virtual bool Swing(int, bool, bool, GemHitFlags);
    virtual bool HandleHitsAndMisses(int, int, float, bool, bool, bool, GemHitFlags);
    virtual void RecordFretButtonDown(int);
    virtual void RecordFretButtonUp(int);
    virtual unsigned int GetFretButtonsDown() const;
    virtual bool FretMatch(int, bool, bool) const;
    virtual bool IsChordSubset(int) const;
    virtual bool IsHighestFret(int) const;
    virtual bool InGem(int, const GameGem&) const;
    virtual bool HarmlessFretDown(int, int) const;
    virtual bool IsCoreGuitar(void) const;

    unsigned int mFretButtonsDown;
};

#endif
