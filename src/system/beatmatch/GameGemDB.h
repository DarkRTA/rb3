#ifndef BEATMATCH_GAMEGEMDB_H
#define BEATMATCH_GAMEGEMDB_H
#include "beatmatch/GameGemList.h"
#include "beatmatch/GemInfo.h"
#include <vector>

class GameGemDB {
public:
    GameGemDB(int, int);
    ~GameGemDB();
    void Clear();
    bool AddMultiGem(int, const MultiGemInfo&);
    bool AddRGGem(int, const RGGemInfo&);
    void MergeChordGems();
    const GameGemList* GetDiffGemList(int) const;
    GameGemList* GetDiffGemList(int);
    void Finalize();
    GameGemDB* Duplicate() const;

    std::vector<GameGemList*> mGameGemLists;
    int mHopoThreshold;
};

#endif
