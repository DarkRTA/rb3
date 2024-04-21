#ifndef BEATMATCH_GAMEGEMLIST_H
#define BEATMATCH_GAMEGEMLIST_H
#include "beatmatch/GameGem.h"
#include <vector>

class GameGemList {
public:
    GameGemList(int);
    void Clear();
    bool AddMultiGem(const MultiGemInfo&);
    bool AddRGGem(const RGGemInfo&);
    void MergeChordGems();
    void Finalize();
    void CopyFrom(const GameGemList*);
    float TimeAt(int) const;
    float TimeAtNext(int) const;
    void Reset();
    int ClosestMarkerIdxAtOrAfter(float) const;

    int NumGems(){ return mGems.size(); }

    GameGem* GetGem(int id){
        MILO_ASSERT(0 <= id && id < NumGems(), 0x3A);
        return &mGems[id];
    }

    int mHopoThreshold;
    std::vector<GameGem> mGems;
};

#endif
