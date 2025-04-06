#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class WaterMark : public RootObject {
    public:
        WaterMark(const char *, bool, unsigned int);
        ~WaterMark();

        int unk0;
        int unk4;
        bool unk8;
        int unkc;
        int unk10;
        int unk14;
        int unk18;
        int unk1c;
        int unk20;
        int unk24;
        int unk28;
        int unk2c;
    };
}