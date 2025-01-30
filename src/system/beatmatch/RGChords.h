#pragma once

class RGRollChord {
public:
    RGRollChord(){
        for(int i = 0; i < 6; i++) unk0[i] = -1;
    }
    int unk0[6];
};

class RGTrill {
public:
    RGTrill() : unk0(-1) {
        unk4 = unk8 = -1;
    }
    int unk0;
    // unk4 and unk8 could actually be a std::pair<int, int>?
    int unk4;
    int unk8;
};
