#pragma once
#include <vector>

class Player;

class CommonPhraseCapturer {
public:
    CommonPhraseCapturer();

    void Enabled(Player*, int, int, bool);

    std::vector<int> unk0;
};