#include "tour/TourWeightManager.h"
#include "decomp.h"
#include "obj/Data.h"
#include "os/Debug.h"

TourWeightManager::TourWeightManager(){

}

TourWeightManager::~TourWeightManager(){
    Cleanup();
}

void TourWeightManager::Cleanup(){
    unk4.clear();
}

void TourWeightManager::Init(const DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x22);
    ConfigureQuestWeightData(i_pConfig->FindArray("quest_weights", true));
}

void TourWeightManager::ConfigureQuestWeightData(DataArray* a){
    for(int i = 1; i < a->Size(); i++){
        DataArray* pEntry = a->Array(i);
        MILO_ASSERT(pEntry, 0x2D);
        MILO_ASSERT(pEntry->Size() == 2, 0x2F);
        Symbol key = pEntry->Sym(0);
        float val = pEntry->Float(1);
        unk4[key] = val;
    }
}

DECOMP_FORCEACTIVE(TourWeightManager, "pQuest")