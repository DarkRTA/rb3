#include "bandobj/GemTrackResourceManager.h"
#include "obj/Msg.h"

GemTrackResourceManager::GemTrackResourceManager(ObjectDir* dir) : unk1c(this, dir) {
    InitSmasherPlates();
}

GemTrackResourceManager::~GemTrackResourceManager(){
    
}

void GemTrackResourceManager::InitSmasherPlates(){
    SmasherPlateInfo info(this);
    unk28.reserve(7);
    info.unk0 = unk1c->Find<RndDir>("smasher_plate_guitar", true);
    info.unkc = 0;
    unk28.push_back(info);
    info.unk0 = unk1c->Find<RndDir>("smasher_plate_bass", true);
    info.unkc = 2;
    unk28.push_back(info);
    info.unk0 = unk1c->Find<RndDir>("smasher_plate_keys", true);
    info.unkc = 4;
    unk28.push_back(info);
    info.unk0 = unk1c->Find<RndDir>("smasher_plate_drum", true);
    info.unkc = 1;
    unk28.push_back(info);
    info.unk0 = unk1c->Find<RndDir>("smasher_plate_real_guitar", true);
    info.unkc = 5;
    unk28.push_back(info);
    info.unk0 = unk1c->Find<RndDir>("smasher_plate_real_bass", true);
    info.unkc = 6;
    unk28.push_back(info);
    info.unk0 = unk1c->Find<RndDir>("smasher_plate_real_keys", true);
    info.unkc = 7;
    unk28.push_back(info);
    for(int i = 0; i < unk28.size(); i++){
        static Message setup_draworder("setup_draworder", 0);
        unk28[i].unk0->HandleType(setup_draworder);
    }
}