#pragma once

#include <vector>
class DeJitter {
public:
    DeJitter();
    void Apply(float, float&);
    void Reset();

    std::vector<float> unk_0x0;
    int unk_0x8, unk_0xC;
    float unk_0x10, unk_0x14, unk_0x18;

    static float sTimeScale;
};
