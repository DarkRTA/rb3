#include "DeJitter.h"
#include "obj/Data.h"

float DeJitter::sTimeScale = 1;

DeJitter::DeJitter() { 
    Reset(); 
    if (unk_0x0.size() > 32) {
        unk_0x0.clear();
    } else {
        unk_0x0.insert(unk_0x0.begin(), unk_0x0.size(), 0);
    }
}

void DeJitter::Apply(float, float&) {
    static DataNode& dejitter_disable = DataVariable("dejitter_disable");
}

void DeJitter::Reset() {
    unk_0x8 = 0;
    unk_0xC = -2;
    unk_0x10 = 0;
    unk_0x14 = 0;
    unk_0x18 = 1e30;
}
