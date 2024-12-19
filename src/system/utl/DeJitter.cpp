#include "DeJitter.h"
#include "obj/Data.h"

float DeJitter::sTimeScale = 1;

DeJitter::DeJitter() { 
    Reset();
    unk_0x0.resize(32);
}

float DeJitter::Apply(float, float&) {
    static DataNode& dejitter_disable = DataVariable("dejitter_disable");
}

void DeJitter::Reset() {
    unk_0x8 = 0;
    unk_0xC = -2;
    unk_0x10 = 0;
    unk_0x14 = 0;
    unk_0x18 = 1e30;
}
