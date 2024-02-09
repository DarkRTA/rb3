#include "CustomArray.h"
#include "string.h"

CustomArray::CustomArray(unsigned long startsize, void* inputbuffer) : mCollapsed(0), mAddresses(0), mNbPushedAddies(0), mNbAllocatedAddies(0), mBitCount(0), mBitMask(0) {
    NewBlock(0, startsize);
    mInitCell = mCurrentCell;
    if(inputbuffer != 0){
        memcpy(mInitCell->Item.Addy, inputbuffer, startsize);
    }
    mLastAddress = mCurrentCell->Item.Addy;
}
CustomArray::~CustomArray(){
    delete [] mCollapsed;
    mCollapsed = 0;
    delete [] mAddresses;
    mAddresses = 0;
    CustomCell* curCell = mInitCell->NextCustomCell;
    while(curCell != 0){
        delete curCell->NextCustomCell;
    }
}
