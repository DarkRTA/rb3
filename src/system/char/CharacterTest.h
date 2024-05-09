#ifndef CHAR_CHARACTERTEST_H
#define CHAR_CHARACTERTEST_H
#include "rndobj/Overlay.h"

class Character;

class CharacterTest : public RndOverlay::Callback {
public:
    CharacterTest(Character*);
    virtual ~CharacterTest();
    virtual float UpdateOverlay(RndOverlay*, float);
    virtual DataNode Handle(DataArray*, bool);

    void* operator new(size_t s){
        return _PoolAlloc(s, sizeof(CharacterTest), FastPool);
    }

    void operator delete(void* v){
        _PoolFree(sizeof(CharacterTest), FastPool, v);
    }
};

#endif