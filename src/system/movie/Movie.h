#pragma once

#include "utl/BinStream.h"

class Movie {
public:
    Movie();
    ~Movie();

    int GetFrame() const;
    bool Paused() const;
    void SetAspect(float);
    bool Ready() const;
    bool Poll();
    void End();
    void SetPaused(bool);
    void Draw();
    void SetWidthHeight(int,int);
    bool IsLoading() const;
    bool IsOpen() const;
    void CheckOpen(bool);
    void Begin(const char*, float, bool, bool, bool, bool, int, BinStream*);

    int mImpl; //Impl* mImpl;
};
