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
        CustomCell* delCell = curCell;
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
    newCell->Item.Addy = new char[size];
    newCell->Item.Size = 0;
    mCurrentCell = newCell;

    if(previouscell != 0){
        previouscell->NextCustomCell = newCell;
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
    EndBits();

    CustomCell* cell = mInitCell;
    if(userbuffer == 0){
        delete[] mCollapsed;
        mCollapsed = 0;

        unsigned long offset = GetOffset();
        mCollapsed = offset != 0 ? new char[offset] : 0;
        userbuffer = mCollapsed;
    }

    void* original = userbuffer;
    if(userbuffer != 0){
        while(cell->NextCustomCell != 0){
            memcpy(userbuffer, cell->Item.Addy, cell->Item.Size);
            userbuffer = (char*)userbuffer + cell->Item.Size;
            cell = cell->NextCustomCell;
        }
        
        memcpy(userbuffer, cell->Item.Addy, cell->Item.Size);
        mNbPushedAddies = 0;
    }

    return original;
}

CustomArray& CustomArray::Store(unsigned char b){
    EndBits();
    CheckArray(sizeof(unsigned char));
    unsigned char* ptr = (unsigned char*) mCurrentCell->Item.Addy;
    ptr += mCurrentCell->Item.Size;
    *ptr = b;
    mLastAddress = ptr;
    mCurrentCell->Item.Size += sizeof(unsigned char);
    return *this;
}

CustomArray& CustomArray::Store(unsigned short w){
    EndBits();
    CheckArray(sizeof(unsigned short));
    unsigned short* ptr = (unsigned short*) mCurrentCell->Item.Addy;
    (char*)ptr += mCurrentCell->Item.Size;
    *ptr = w;
    mLastAddress = ptr;
    mCurrentCell->Item.Size += sizeof(unsigned short);
    return *this;
}

CustomArray& CustomArray::Store(unsigned int d){
    EndBits();
    CheckArray(sizeof(unsigned int));
    unsigned int* ptr = (unsigned int*) mCurrentCell->Item.Addy;
    (char*)ptr += mCurrentCell->Item.Size;
    *ptr = d;
    mLastAddress = ptr;
    mCurrentCell->Item.Size += sizeof(unsigned int);
    return *this;
}

CustomArray& CustomArray::StoreBit(bool b){
    mBitMask <<= 1;
    if(b) mBitMask |= 1;
    if(++mBitCount == 8){
        mBitCount = 0;
        Store(mBitMask);
        mBitMask = 0;
    }
    return *this;
}

CustomArray& CustomArray::EndBits(){
    while(mBitCount != 0){
        StoreBit(false);
    }
    return *this;
}
