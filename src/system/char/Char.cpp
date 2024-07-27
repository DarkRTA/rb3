#include "obj/Dir.h"
#include "os/Debug.h"
#include "char/Char.h"
#include "char/CharUtl.h"

void CharInit() {
    Character::Init();
    CharBonesObject::Init();
    CharBoneOffset::Init();

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