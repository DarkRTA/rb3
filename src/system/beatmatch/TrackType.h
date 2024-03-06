#ifndef BEATMATCH_TRACKTYPE_H
#define BEATMATCH_TRACKTYPE_H
#include "utl/Symbol.h"

enum TrackType {
    kTrackDrum,
    kTrackGuitar,
    kTrackBass,
    kTrackVocals,
    kTrackKeys,
    kTrackRealKeys,
    kTrackRealGuitar,
    kTrackRealGuitar22Fret,
    kTrackRealBass,
    kTrackRealBass22Fret,
    kTrackNone,
    kNumTrackTypes,
    kTrackPending,
    kTrackPendingVocals
};

Symbol TrackTypeToSym(TrackType);
TrackType SymToTrackType(Symbol);

#endif
