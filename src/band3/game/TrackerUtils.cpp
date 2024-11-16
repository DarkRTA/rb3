#include "game/TrackerUtils.h"
#include "game/TrackerSource.h"
#include "math/Utl.h"
#include "obj/Data.h"
#include "os/Debug.h"

TrackerMultiplierMap::TrackerMultiplierMap() : unk0(-1.0f) {

}

TrackerMultiplierMap::~TrackerMultiplierMap(){

}

void TrackerMultiplierMap::InitFromDataArray(const DataArray* iDataArray){
    unk4.clear();
    int idx = 0;
    MultiplierEntry& entry = unk4[0.0f];
    entry.unk0 = 1.0f;
    entry.unk4 = 0;
    if(iDataArray){
        MILO_ASSERT(!iDataArray->Sym( 0 ).Null(), 0x2B);
        for(int i = 1; i < iDataArray->Size(); i++){
            DataArray* arr = iDataArray->Array(i);
            float f10 = arr->Float(0);
            float f11 = arr->Float(1);
            idx++;
            MultiplierEntry& curentry = unk4[f10];
            curentry.unk0 = f11;
            curentry.unk4 = idx;
            if(unk0 < f10){
                unk0 = f10;
            }
        }
    }
}

float TrackerMultiplierMap::GetMultiplier(float f) const {
    return FindEntry(f).unk0;
}

int TrackerMultiplierMap::GetMultiplierIndex(float f) const {
    return FindEntry(f).unk4;
}

float TrackerMultiplierMap::GetPercentOfMaxMultiplier(float f) const {
    return Max(f / unk0, 1.0f);
}

const TrackerMultiplierMap::MultiplierEntry& TrackerMultiplierMap::FindEntry(float f) const {
    return unk4.find(f)->second;
}

TrackerSectionManager::TrackerSectionManager(){

}

TrackerSectionManager::~TrackerSectionManager(){
    
}

void TrackerSectionManager::Init(){ GatherSections(); }
int TrackerSectionManager::GetSectionCount() const { return mSections.size(); }

int TrackerSectionManager::CountNonEmptySections(const TrackerSource* source, bool b) const {
    int count = 0;
    for(int i = 0; i < mSections.size(); i++){
        for(TrackerPlayerID id = source->GetFirstPlayer(); id.NotNull(); id = source->GetNextPlayer(id)){
            Player* pPlayer = source->GetPlayer(id);
            MILO_ASSERT(pPlayer, 0x8A);
            if(CountGemsInSection(pPlayer, i) > 0){
                count++;
                if(!b) break;
            }
        }
    }
    return count;
}

int TrackerSectionManager::GetSectionStartTick(int idx) const { return mSections[idx].mStartTick; }
int TrackerSectionManager::GetSectionEndTick(int idx) const { return mSections[idx].mEndTick; }

int TrackerSectionManager::FindSectionContainingTick(int tick) const {
    int idx;
    for(idx = 0; idx < mSections.size(); idx++){
        if(mSections[idx].mEndTick > tick) break;
    }
    if(idx == mSections.size()) return -1;
    return idx;
}

bool TrackerSectionManager::TickInSection(int tick, int section) const {
    const Section& sect = mSections[section];
    return tick >= sect.mStartTick && tick <= sect.mEndTick;
}

bool TrackerSectionManager::TickAfterSection(int tick, int section) const {
    return tick > mSections[section].mEndTick;
}

void TrackerSectionManager::GatherSections(){
    mSections.clear();
}