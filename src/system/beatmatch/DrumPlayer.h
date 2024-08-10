#ifndef BEATMATCH_DRUMPLAYER_H
#define BEATMATCH_DRUMPLAYER_H
#include "utl/SongInfoCopy.h"
#include <vector>
#include "obj/Dir.h"

class DrumPlayer {
public:
    DrumPlayer(SongInfo&);
    ~DrumPlayer();
    void Play(int, float);

    float mAttenuation; // 0x0
    std::vector<Symbol> v1; // 0x4
    std::vector<Symbol> v2; // 0xc
    ObjDirPtr<ObjectDir> mDrumKitBank; // 0x14
};

#endif