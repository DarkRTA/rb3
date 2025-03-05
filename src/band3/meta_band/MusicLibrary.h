#pragma once
#include <vector>

class MusicLibrary {
public:
    class MusicLibraryTask {};

    const std::vector<int> &GetSetlist();
};

extern MusicLibrary *TheMusicLibrary;