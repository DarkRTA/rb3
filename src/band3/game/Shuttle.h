#pragma once

class Shuttle {
public:
    Shuttle();
    ~Shuttle();

    bool IsActive() const;
    void SetActive(bool);
    void Poll();

    float mMs; // 0x0
    float mEndMs; // 0x4
    bool mActive; // 0x8
    int mPadNum; // 0xc
};
