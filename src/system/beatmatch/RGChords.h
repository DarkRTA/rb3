#pragma once

class RGRollChord {
public:
    RGRollChord() {
        for (int i = 0; i < 6; i++)
            mString[i] = -1;
    }
    int mString[6];
};

class RGTrill {
public:
    RGTrill() : mString(-1) { mFrets[0] = mFrets[1] = -1; }
    int mString;
    // unk4 and unk8 could actually be a std::pair<int, int>?
    // int unk4;
    // int unk8;
    int mFrets[2]; // I think?
};
