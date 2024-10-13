#include "tour/TourPropertyCollection.h"
#include "decomp.h"
#include "meta/FixedSizeSaveable.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "tour/TourProperty.h"

TourPropertyCollection::TourPropertyCollection(){
    mSaveSizeMethod = &SaveSize;
}

TourPropertyCollection::~TourPropertyCollection(){

}

void TourPropertyCollection::Clear(){
    mTourProperties.clear();
}

void TourPropertyCollection::SetPropertyValue(Symbol s, float f){
    if(!TheTour->HasTourProperty(s)){
        MILO_WARN("Tour Property %s does not exist!", s);
    }
    else {
        TourProperty* pTourProperty = TheTour->GetTourProperty(s);
        MILO_ASSERT(pTourProperty, 0x2B);
        float val = Min(pTourProperty->GetMaxValue(), f);
        val = Max(pTourProperty->GetMinValue(), val);
        mTourProperties[s] = val;
    }
}

float TourPropertyCollection::GetPropertyValue(Symbol s) const {
    std::map<Symbol, float>::const_iterator it = mTourProperties.find(s);
    if(it != mTourProperties.end()) return it->second;
    else {
        if(TheTour->HasTourProperty(s)){
            TourProperty* pTourProperty = TheTour->GetTourProperty(s);
            MILO_ASSERT(pTourProperty, 0x42);
            return pTourProperty->GetDefaultValue();
        }
        else {
            MILO_WARN("Tour Property %s does not exist!", s);
            return 0;
        }
    }
}

DECOMP_FORCEACTIVE(TourPropertyCollection, "o_rEntries.empty()", "Property: %s is no longer a valid property.\n")

void TourPropertyCollection::SaveFixed(FixedSizeSaveableStream& stream) const {
    FixedSizeSaveable::SaveStd(stream, mTourProperties, 0x14, 8);
}

int TourPropertyCollection::SaveSize(int){
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "TourPropertyCollection", 0xA4);
    }
    return 0xA4;
}

void TourPropertyCollection::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    FixedSizeSaveable::LoadStd(stream, mTourProperties, 0x14, 8);
}

void TourPropertyCollection::FakeFill(){
    std::map<Symbol, TourProperty*>& propmap = TheTour->m_mapTourProperties;
    for(std::map<Symbol, TourProperty*>::iterator it = propmap.begin(); it != propmap.end(); ++it){
        propmap[it->first]->mMaxValue = mTourProperties[it->first];
    }
}