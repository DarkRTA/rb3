#ifndef CHAR_CHARUTL_H
#define CHAR_CHARUTL_H
#include "obj/Dir.h"
#include "rndobj/Trans.h"

class Character;

void CharUtlResetHair(Character*);
void CharUtlInit();
void CharUtlMergeBones(ObjectDir*, ObjectDir*, int);
RndTransformable* CharUtlFindBoneTrans(const char*, ObjectDir*);
bool CharUtlIsAnimatable(RndTransformable*);

class CharUtlBoneSaver {
public:
    CharUtlBoneSaver(ObjectDir*);
    ~CharUtlBoneSaver();

    ObjectDir* mDir; // 0x0
    std::vector<Transform> mXfms; // 0x4
};

#endif