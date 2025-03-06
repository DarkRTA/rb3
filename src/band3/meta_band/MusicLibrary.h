#pragma once
#include <vector>

class MusicLibrary {
public:
    class MusicLibraryTask {};

    const std::vector<int> &GetSetlist();
    void AppendToSetlist(int);
    void RemoveLastSongFromSetlist();
};

extern MusicLibrary *TheMusicLibrary;