#pragma once
#include <vector>

class Player;

class CommonPhraseCapturer {
public:
    CommonPhraseCapturer();

    void Enabled(Player*, int, int, bool);
    void LocalHitLastGem(Player*, int, int);
    void LocalFail(Player*, int, int);

    std::vector<int> unk0;
};