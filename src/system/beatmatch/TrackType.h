#ifndef BEATMATCH_TRACKTYPE_H
#define BEATMATCH_TRACKTYPE_H
#include "utl/Symbol.h"

enum TrackType {
    kTrackDrum = 0,
    kTrackGuitar = 1,
    kTrackBass = 2,
    kTrackVocals = 3,
    kTrackKeys = 4,
    kTrackRealKeys = 5,
    kTrackRealGuitar = 6,
    kTrackRealGuitar22Fret = 7,
    kTrackRealBass = 8,
    kTrackRealBass22Fret = 9,
    kTrackNone = 10,
    kNumTrackTypes = 10,
    kTrackPending = 11,
    kTrackPendingVocals = 12
};

Symbol TrackTypeToSym(TrackType);
TrackType SymToTrackType(Symbol);

#endif
