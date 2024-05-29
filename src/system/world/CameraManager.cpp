#include "world/CameraManager.h"
#include "world/Dir.h"
#include "rndobj/DOFProc.h"

CameraManager::CameraManager(WorldDir* dir) : mParent(dir), unk8(0), unkc(0), unk10(0), unk14(dir, 0), unk20(dir, 0), unk2c(0.0f), unk30(0) {
    MILO_ASSERT(mParent, 0x28);
    DOFProc::Init();
}