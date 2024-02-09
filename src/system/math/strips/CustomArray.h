#ifndef MATH_STRIPS_CUSTOMARRAY_H
#define MATH_STRIPS_CUSTOMARRAY_H

class CustomArray {
public:
    struct CustomBlock {
        void* Addy;
        unsigned long Size;
        unsigned long Max;
        ~CustomBlock(){
            delete [] Addy;
            Addy = 0;
        }
    };
    struct CustomCell {
        CustomCell* NextCustomCell;
        CustomBlock Item;
        ~CustomCell(){ }
    };

    CustomCell* mCurrentCell;
    CustomCell* mInitCell;
    void* mCollapsed;
    void* mAddresses;
    void* mLastAddress;
    unsigned short mNbPushedAddies;
    unsigned short mNbAllocatedAddies;
    unsigned char mBitCount;
    unsigned char mBitMask;

    CustomArray(unsigned long startsize, void* inputbuffer);
    ~CustomArray();
    CustomArray& NewBlock(CustomCell* previouscell, unsigned long size);
    CustomArray& CheckArray(unsigned long);
    unsigned long GetOffset();
    void* Collapse(void* userbuffer);
    CustomArray& Store(unsigned char b);
    CustomArray& Store(unsigned short w);
    CustomArray& Store(unsigned int d);
    CustomArray& StoreBit(bool);
    CustomArray& EndBits();
};

#endif
