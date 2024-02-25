#include "utl/HxGuid.h"

HxGuid::HxGuid(){
    Clear();
}

void HxGuid::Clear(){
    mData[0] = mData[1] = mData[2] = mData[3] = 0;
}

bool HxGuid::IsNull() const {
    bool ret = false;
    if(mData[0] == 0 && mData[1] == 0 && mData[2] == 0 && mData[3] == 0) ret = true;
    return ret;
}
