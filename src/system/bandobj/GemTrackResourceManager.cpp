#include "bandobj/GemTrackResourceManager.h"

GemTrackResourceManager::GemTrackResourceManager(ObjectDir* dir) : unk1c(this, dir) {
    InitSmasherPlates();
}

GemTrackResourceManager::~GemTrackResourceManager(){
    
}