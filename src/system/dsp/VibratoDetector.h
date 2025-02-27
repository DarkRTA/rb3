#pragma once

class VibratoDetector {
public:
    VibratoDetector(int, int);
    ~VibratoDetector();
    int Analyze(float);
    int Detect();

    int mBuffer[5]; // 0x0
    float mPitches[5]; // 0x14
    int unk28;
    int unk2c;
    int unk30;
    int unk34;
    int unk38;
    int unk3c;
    int unk40;
    int unk44;
    int unk48;
};