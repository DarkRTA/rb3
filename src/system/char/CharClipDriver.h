#ifndef CHAR_CHARCLIPDRIVER_H
#define CHAR_CHARCLIPDRIVER_H
#include "obj/Object.h"
#include "char/CharClip.h"

class CharClipDriver {
public:
    CharClipDriver(Hmx::Object*, const CharClipDriver&);
    CharClipDriver(Hmx::Object*, CharClip*, int, float, CharClipDriver*, float, float, bool);

    void DeleteStack();

    NEW_POOL_OVERLOAD(CharClipDriver)
    DELETE_POOL_OVERLOAD(CharClipDriver)
};

#endif
