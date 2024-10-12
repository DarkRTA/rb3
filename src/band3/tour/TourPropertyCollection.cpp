#include "tour/TourPropertyCollection.h"
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

void TourPropertyCollection::SaveFixed(FixedSizeSaveableStream& stream) const {
    // FixedSizeSaveable::SaveStd(stream, mTourProperties, 0x14, 8);
}