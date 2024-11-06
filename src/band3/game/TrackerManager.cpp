#include "game/TrackerManager.h"
#include "utl/Symbol.h"

TrackerManager::TrackerManager(Band* band) : unk0(-1), unk4(0), unk10(0), unk14(0), unk18(band), unk1c(0), unk20(0), unk24(0), unk28(gNullStr), unk2c(1), unk30(0), unk31(0), unk32(0),
    unk34(0), unk40(0), unk44(0), unk48(1), unk49(0), unk4c(-1.0f) {

}

TrackerManager::~TrackerManager(){

}

void TrackerManager::ForceStars(int stars){
    unk0 = stars;
}

void TrackerManager::Restart(){
    unk48 = true;
    unk49 = false;
    unk4c = -1.0f;
    if(unk1c){
        
    }
//       this[0x48] = (TrackerManager)0x1;
//   this[0x49] = (TrackerManager)0x0;
//   *(float *)(this + 0x4c) = -1.0;
//   if (*(int *)(this + 0x1c) != 0) {
//     pTVar1 = (TrackerSource *)CreateSource(this,(TrackerDesc *)(this + 0x20));
//     if (pTVar1 != (TrackerSource *)0x0) {
//       Tracker::UpdateSource(*(Tracker **)(this + 0x1c),pTVar1);
//     }
//     Tracker::Restart(*(Tracker **)(this + 0x1c));
//   }
//   return;
}