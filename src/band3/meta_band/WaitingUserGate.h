#pragma once
#include "obj/Object.h"

class WaitingUserGate : public Hmx::Object {
public:
    WaitingUserGate();

    static void Init();

    int unk1c;
};