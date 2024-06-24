#include "TourProperty.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

TourProperty::TourProperty(const DataArray* da) : unk_0x8(0x20), unk_0x9(0x20), mDefaultValue(0), 
    mMinValue(1.17549435082228750797e-38), mMaxValue(3.40282346638528859812e38), mIsAutomatic(false) { 
    Configure(da); 
}

TourProperty::~TourProperty() {}

void TourProperty::Configure(const DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 32);
    mName = i_pConfig->Sym(0);
    i_pConfig->FindData(default_value, mDefaultValue, false);
    i_pConfig->FindData(min_value, mMinValue, false);
    i_pConfig->FindData(max_value, mMaxValue, false);
    const char* a =NULL, *b;
    if (i_pConfig->FindData(positive_icon, a, false)) { unk_0x8 = *a; }
    b = NULL;
    if (i_pConfig->FindData(negative_icon, b, false)) { unk_0x9 = *b; }
    i_pConfig->FindData(is_automatic, mIsAutomatic, false);
}

Symbol TourProperty::GetName() const { return mName; }

float TourProperty::GetDefaultValue() const { return mDefaultValue; }
float TourProperty::GetMinValue() const { return mMinValue; }
float TourProperty::GetMaxValue() const { return mMaxValue; }
bool TourProperty::IsAutomatic() const { return mIsAutomatic; }
