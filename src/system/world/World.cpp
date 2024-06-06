#include "obj/Dir.h"
#include "obj/Object.h"
#include "world/CameraShot.h"
#include "world/ColorPalette.h"
#include "world/Dir.h"
#include "world/Instance.h"
#include "world/LightHue.h"
#include "world/LightPreset.h"
#include "world/SpotlightDrawer.h"
#include "world/SpotlightEnder.h"

void WorldInit() {
    WorldDir::Init();
    REGISTER_OBJ_FACTORY(ColorPalette)
    //REGISTER_OBJ_FACTORY(EventAnim)
    //REGISTER_OBJ_FACTORY(WorldCrowd)
    CamShot::Init();
    //REGISTER_OBJ_FACTORY(WorldReflection)
    REGISTER_OBJ_FACTORY(LightPreset)
    REGISTER_OBJ_FACTORY(LightHue)
    SpotlightDrawer::Init();
    REGISTER_OBJ_FACTORY(SpotlightEnder)
    REGISTER_OBJ_FACTORY(WorldInstance)
    PreloadSharedSubdirs("world");
}
