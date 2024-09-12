#include "bandobj/ChordShapeGenerator.h"

ChordShapeGenerator::ChordShapeGenerator() : unk1c(this, 0), unk28(this, 0), unk34(this, 0), unk40(this, 0), unk4c(this, 0), unk58(6), unk6c(this, 0),
    unk78(this, 0), unk84(this, 0), unk90(this, 0), unk9c(this, 0), unka8(this, 0), unkc4(0), unkc8(-1.0f), unkcc(1.0f), unkd0(0.2f) {
    unkb4.resize(7);
    for(int i = 0; i < 7; i++) unkb4[i] = 1.0f;
    unkbc.resize(7);
    for(int i = 0; i < 7; i++) unkbc[i] = 0.33f;
    unk5c.resize(6);
    for(int i = 0; i < 6; i++) unk5c[i] = -1;
    unk64.resize(6);
    for(int i = 0; i < 6; i++) unk64[i] = 1;
}