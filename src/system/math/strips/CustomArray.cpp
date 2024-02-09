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
    CustomCell* curCell = mInitCell;
    while(curCell != 0){
        CustomCell* delCell = curCell->NextCustomCell;
        curCell = curCell->NextCustomCell;
        delete delCell;
    }
}

CustomArray& CustomArray::NewBlock(CustomCell* previouscell, unsigned long size){
    CustomCell* newCell = new CustomCell();
    if(previouscell != 0){
        size = previouscell->Item.Max * 2;
    }
    newCell->Item.Max = size;
    newCell->Item.Addy = operator new[](size);
    newCell->Item.Size = 0;
    mCurrentCell = newCell;
    if(previouscell != 0){
        previouscell = newCell;
    }
    return *this;
}

CustomArray& CustomArray::CheckArray(unsigned long ul){
    CustomCell* cur = mCurrentCell;
    if(cur->Item.Size + ul > cur->Item.Max){
        NewBlock(cur, 0);
    }
    return *this;
}

unsigned long CustomArray::GetOffset(){
    unsigned long i = 0;
    CustomCell* cell = mInitCell;
    while(cell->NextCustomCell != 0){
        i += cell->Item.Size;
        cell = cell->NextCustomCell;
    }
    return i + cell->Item.Size;
}

void* CustomArray::Collapse(void* userbuffer){
    
}
