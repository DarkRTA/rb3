
#include "obj/Dir.h"
#include "os/Debug.h"
#include "char/Char.h"
#include "char/CharUtl.h"

void CharInit() {
#ifdef MILO_DEBUG
    Character::Init();
#else 
    CharacterInit();
#endif
    CharBonesObject::Init();
    CharBoneOffset::Init();
    CharBlendBone::Init();
    CharBone::Init();
    CharBonesAlloc::Init();
    CharBoneTwist::Init();

    PreloadSharedSubdirs("char");
    CharBoneDir::Init();
    CharUtlInit();
    TheDebug.AddExitCallback(CharTerminate);
}

void CharTerminate() {
    TheDebug.RemoveExitCallback(CharTerminate);
    Character::Terminate();
    CharBoneDir::Terminate();
}