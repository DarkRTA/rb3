#include "bandobj/MicInputArrow.h"

MicInputArrow::MicInputArrow() : unk10c(0), unk110(0), unk15c(1.0f), unk160(0) {
    for(int i = 0; i < 3; i++){
        unk114.push_back(-1);
        unk11c.push_back(true);
        unk164[i] = 0;
    }
}

    // std::vector<char> unk114; // 0x114
    // std::vector<bool> unk11c; // 0x11c