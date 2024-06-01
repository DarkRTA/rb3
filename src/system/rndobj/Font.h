#ifndef RNDOBJ_FONT_H
#define RNDOBJ_FONT_H

#include "obj/Object.h"

class RndFont : public Hmx::Object {
public:

    NEW_OBJ(RndFont)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndFont)
    }
}; 

#endif // RNDOBJ_FONT_H
