/*
    Compile unit: C:\rockband2\system\src\math\strips\CustomArray.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80630484 -> 0x806309E4
*/
// Range: 0x80630484 -> 0x8063051C
void * CustomArray::CustomArray(class CustomArray * const this /* r29 */, unsigned long startsize /* r30 */, void * inputbuffer /* r31 */) {}

// Range: 0x8063051C -> 0x806305D4
void * CustomArray::~CustomArray(class CustomArray * const this /* r28 */) {
    // Local variables
    struct CustomCell * CurCell; // r31
    struct CustomCell * Cell; // r30
}

// Range: 0x806305D4 -> 0x80630678
class CustomArray & CustomArray::NewBlock(class CustomArray * const this /* r28 */, struct CustomCell * previouscell /* r29 */, unsigned long size /* r30 */) {}

// Range: 0x80630678 -> 0x806306C8
class CustomArray & CustomArray::CheckArray(class CustomArray * const this /* r31 */) {}

// Range: 0x806306C8 -> 0x806306F8
unsigned long CustomArray::GetOffset() {
    // Local variables
    unsigned long Offset; // r4
    struct CustomCell * p; // r5
}

// Range: 0x806306F8 -> 0x806307D4
void * CustomArray::Collapse(class CustomArray * const this /* r28 */, void * userbuffer /* r29 */) {
    // Local variables
    char * Addy; // [invalid]
    struct CustomCell * p; // r30
    unsigned long CurrentSize; // r0
    char * AddyCopy; // r31
}

// Range: 0x806307D4 -> 0x80630840
class CustomArray & CustomArray::Store(class CustomArray * const this /* r30 */, unsigned char b /* r31 */) {
    // Local variables
    char * CurrentAddy; // r4
    unsigned char * Current; // r0
}

// Range: 0x80630840 -> 0x806308AC
class CustomArray & CustomArray::Store(class CustomArray * const this /* r30 */, unsigned short w /* r31 */) {
    // Local variables
    char * CurrentAddy; // r4
    unsigned short * Current; // r0
}

// Range: 0x806308AC -> 0x80630918
class CustomArray & CustomArray::Store(class CustomArray * const this /* r30 */, unsigned int d /* r31 */) {
    // Local variables
    char * CurrentAddy; // r4
    unsigned int * Current; // r0
}

// Range: 0x80630918 -> 0x8063099C
class CustomArray & CustomArray::StoreBit(class CustomArray * const this /* r30 */) {}

// Range: 0x8063099C -> 0x806309E4
class CustomArray & CustomArray::EndBits(class CustomArray * const this /* r31 */) {}


