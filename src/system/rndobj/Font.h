#ifndef RNDOBJ_FONT_H
#define RNDOBJ_FONT_H

#include "obj/Object.h"
#include "utl/MemMgr.h"

class RndFont : public Hmx::Object { // 0x84
    public:
    RndFont();
    OBJ_CLASSNAME(RndFont)
    NEW_OBJ(RndFont)

    NEW_OVERLOAD
}; 

#endif // RNDOBJ_FONT_H
