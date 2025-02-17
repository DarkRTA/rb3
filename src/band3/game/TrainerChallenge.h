#pragma once
#include "obj/Object.h"

class TrainerChallenge : public Hmx::Object {
public:
    TrainerChallenge() {}
    virtual ~TrainerChallenge() {}
    OBJ_CLASSNAME(TrainerChallenge);
    OBJ_SET_TYPE(TrainerChallenge);

    NEW_OBJ(TrainerChallenge)
    static void Init() { REGISTER_OBJ_FACTORY(TrainerChallenge) }
};