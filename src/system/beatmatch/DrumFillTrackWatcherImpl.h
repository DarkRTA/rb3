#pragma once
#include "beatmatch/DrumTrackWatcherImpl.h"
#include "beatmatch/DrumMap.h"

class DrumFillTrackWatcherImpl : public DrumTrackWatcherImpl {
public:
    DrumFillTrackWatcherImpl(int, const UserGuid &, int, SongData *, GameGemList *, TrackWatcherParent *, DataArray *);
    virtual ~DrumFillTrackWatcherImpl();
    virtual void RegisterFill(int);
    virtual void ResetFill();
    virtual void FillSwing(int, int, int, bool);
    virtual void CodaSwing(int, int);

    DrumFillInfo *mFillInfo; // 0xc8
    int mFillNotes; // 0xcc
};