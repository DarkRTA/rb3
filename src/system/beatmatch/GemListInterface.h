#ifndef BEATMATCH_GEMLISTINTERFACE_H
#define BEATMATCH_GEMLISTINTERFACE_H
#include "utl/Symbol.h"

class GemListInterface {
public:
    GemListInterface(){}
    virtual ~GemListInterface(){}
    virtual void SetTrack(Symbol) = 0;
    virtual bool GetGem(int, int&, int&, int&) = 0;
};

#endif
