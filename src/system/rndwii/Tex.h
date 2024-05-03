#ifndef RNDWII_TEX_H
#define RNDWII_TEX_H

#include "obj/Object.h"
#include "rndobj/Tex.h"
#include "utl/PoolAlloc.h"

class WiiTex : public RndTex {
public:
    WiiTex();
    virtual ~WiiTex();
    OBJ_CLASSNAME(WiiTex)
    OBJ_SET_TYPE(WiiTex)
    NEW_OBJ(WiiTex)

    void* operator new(unsigned long i) { return _PoolAlloc(i, i, FastPool); }
    void operator delete(void* obj) {_PoolFree(0xd0, FastPool, obj); }
};

#endif // RNDWII_TEX_H