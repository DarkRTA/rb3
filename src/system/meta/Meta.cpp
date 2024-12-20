#include "meta/Achievements.h"
#include "meta/ConnectionStatusPanel.h"
#include "meta/DeJitterPanel.h"
#include "meta/HeldButtonPanel.h"
#include "meta/PreloadPanel.h"
#include "obj/ObjMacros.h"

void MetaTerminate() { Achievements::Terminate(); }

void MetaInit() {
    Achievements::Init();
    ConnectionStatusPanel::Init();
    DeJitterPanel::Init();
    HeldButtonPanel::Init();
    PreloadPanel::Init();
    TheDebug.AddExitCallback(MetaTerminate);
}
