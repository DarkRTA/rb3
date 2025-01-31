#pragma once
#include "beatmatch/JoypadTrackWatcherImpl.h"

class KeyboardTrackWatcherImpl : public JoypadTrackWatcherImpl {
public:
    KeyboardTrackWatcherImpl(int, const UserGuid&, int, SongData*, GameGemList*, TrackWatcherParent*, DataArray*);

    int unkd4;
    int unkd8;
    int unkdc;
    int unke0;
    int unke4;
    float unke8;
    std::vector<int> unkec;
};