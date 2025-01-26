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
    int unk0;
    int unk4;
    int unk8;
};
