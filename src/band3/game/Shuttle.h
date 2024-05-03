#ifndef GAME_SHUTTLE_H
#define GAME_SHUTTLE_H

class Shuttle {
public:
    Shuttle();
    ~Shuttle();
    void SetActive(bool);
    void Poll();
    float unk_0x0;
    float unk_0x4;
    bool mActive;
    int mPadNum;
};

#endif // GAME_SHUTTLE_H