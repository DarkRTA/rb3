#include "obj/Dir.h"
#include "obj/Object.h"
#include "world/CameraShot.h"
#include "world/ColorPalette.h"
#include "world/Dir.h"
#include "world/SpotlightEnder.h"
#include "world/Instance.h"
#include "world/LightHue.h"
#include "world/LightPreset.h"
#include "world/SpotlightDrawer.h"
#include "world/Crowd.h"
#include "world/Reflection.h"
#include "world/EventAnim.h"
#include "world/Spotlight.h"

void WorldInit() {
    WorldDir::Init();
    ColorPalette::Init();
    EventAnim::Init();
    WorldCrowd::Init();
    CamShot::Init();
    WorldReflection::Init();
    Spotlight::Init();
    LightPreset::Init();
    LightHue::Init();
    SpotlightDrawer::Init();
    SpotlightEnder::Init();
    WorldInstance::Init();
    PreloadSharedSubdirs("world");
}
