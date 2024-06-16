#include "meta/Achievements.h"
#include "meta/ConnectionStatusPanel.h"
#include "meta/HeldButtonPanel.h"
#include "obj/ObjMacros.h"

void MetaTerminate() { Achievements::Terminate(); }

void MetaInit() {
    Achievements::Init();
    REGISTER_OBJ_FACTORY(ConnectionStatusPanel)
    //REGISTER_OBJ_FACTORY(DeJitterPanel)
    REGISTER_OBJ_FACTORY(HeldButtonPanel)
    //REGISTER_OBJ_FACTORY(PreloadPanel)
    TheDebug.AddExitCallback(MetaTerminate);
}
