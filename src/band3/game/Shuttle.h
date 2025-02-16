#pragma once

class Shuttle {
public:
    Shuttle();
    ~Shuttle();

    bool IsActive() const;
    void SetActive(bool);
    void Poll();
    float unk_0x0;
    float unk_0x4;
    bool mActive;
    int mPadNum;
};
