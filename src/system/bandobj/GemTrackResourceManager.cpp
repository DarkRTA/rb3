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
    info.mSmasherPlate = unk1c->Find<RndDir>("smasher_plate_guitar", true);
    info.mTrackInst = kInstGuitar;
    unk28.push_back(info);
    info.mSmasherPlate = unk1c->Find<RndDir>("smasher_plate_bass", true);
    info.mTrackInst = kInstBass;
    unk28.push_back(info);
    info.mSmasherPlate = unk1c->Find<RndDir>("smasher_plate_keys", true);
    info.mTrackInst = kInstKeys;
    unk28.push_back(info);
    info.mSmasherPlate = unk1c->Find<RndDir>("smasher_plate_drum", true);
    info.mTrackInst = kInstDrum;
    unk28.push_back(info);
    info.mSmasherPlate = unk1c->Find<RndDir>("smasher_plate_real_guitar", true);
    info.mTrackInst = kInstRealGuitar;
    unk28.push_back(info);
    info.mSmasherPlate = unk1c->Find<RndDir>("smasher_plate_real_bass", true);
    info.mTrackInst = kInstRealBass;
    unk28.push_back(info);
    info.mSmasherPlate = unk1c->Find<RndDir>("smasher_plate_real_keys", true);
    info.mTrackInst = kInstRealKeys;
    unk28.push_back(info);
    for(int i = 0; i < unk28.size(); i++){
        static Message setup_draworder("setup_draworder", 0);
        unk28[i].mSmasherPlate->HandleType(setup_draworder);
    }
}

RndDir* GemTrackResourceManager::GetFreeSmasherPlate(TrackInstrument inst){
    if(inst == kInstPending) return 0;
    else {
        for(int i = 0; i < unk28.size(); i++){
            SmasherPlateInfo& curinfo = unk28[i];
            if(curinfo.mTrackInst == inst && !curinfo.mInUse){
                curinfo.mInUse = true;
                return curinfo.mSmasherPlate;
            }
        }
        MILO_WARN("Could not find free smasher plate for instrument %d", inst);
    }
    return 0;
}

void GemTrackResourceManager::ReleaseSmasherPlate(RndDir* plate){
    for(int i = 0; i < unk28.size(); i++){
        SmasherPlateInfo& info = unk28[i];
        if(info.mSmasherPlate == plate){
            MILO_ASSERT(info.mInUse, 0x60);
            info.mInUse = false;
            info.mSmasherPlate = plate;
            return;
        }
    }
    MILO_WARN("Tried to release invalid smasher 0x%08x", plate);
}