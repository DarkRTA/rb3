/*
    Compile unit: C:\rockband2\system\src\math\strips\Adjacency.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8062F730 -> 0x8062FFAC
*/
// Range: 0x8062F730 -> 0x8062F74C
void * Adjacencies::Adjacencies() {}

// Range: 0x8062F74C -> 0x8062F7C0
void * Adjacencies::~Adjacencies(class Adjacencies * const this /* r29 */) {}

// Range: 0x8062F7C0 -> 0x8062F940
unsigned char Adjacencies::Init(class Adjacencies * const this /* r29 */, struct ADJACENCIESCREATE & create /* r30 */) {
    // Local variables
    unsigned int i; // r31
}

// Range: 0x8062F940 -> 0x8062FAA0
unsigned char Adjacencies::AddTriangle(class Adjacencies * const this /* r28 */, unsigned int ref0 /* r29 */, unsigned int ref1 /* r30 */, unsigned int ref2 /* r31 */) {}

// Range: 0x8062FAA0 -> 0x8062FAEC
unsigned char Adjacencies::AddEdge() {}

class RadixSorter {
    // total size: 0x14
    unsigned int * mHistogram; // offset 0x0, size 0x4
    unsigned int * mOffset; // offset 0x4, size 0x4
    unsigned int mCurrentSize; // offset 0x8, size 0x4
    unsigned int * mIndices; // offset 0xC, size 0x4
    unsigned int * mIndices2; // offset 0x10, size 0x4
};
// Range: 0x8062FAEC -> 0x8062FD74
unsigned char Adjacencies::CreateDatabase(class Adjacencies * const this /* r27 */) {
    // Local variables
    class RadixSorter Core; // r1+0x14
    unsigned int * FaceNb; // r31
    unsigned int * VRefs0; // r30
    unsigned int * VRefs1; // r29
    unsigned int i; // r28
    unsigned int LastRef0; // r6
    unsigned int LastRef1; // r7
    unsigned int Count; // r4
    unsigned int TmpBuffer[3]; // r1+0x8
    unsigned int Face; // r25
    unsigned int Ref0; // r24
    unsigned int Ref1; // r23
    unsigned char Status; // r22
    unsigned char Status; // r22
}

// Range: 0x8062FD74 -> 0x8062FE3C
unsigned char Adjacencies::UpdateLink(unsigned int firsttri /* r25 */, unsigned int secondtri /* r26 */, unsigned int ref0 /* r27 */, unsigned int ref1 /* r28 */) {
    // Local variables
    struct AdjTriangle * Tri0; // r30
    struct AdjTriangle * Tri1; // r29
    unsigned char EdgeNb0; // r0
    unsigned char EdgeNb1; // r0
}

// Range: 0x8062FE3C -> 0x8062FEF4
unsigned char AdjTriangle::FindEdge() {
    // Local variables
    unsigned char EdgeNb; // r7
}

// Range: 0x8062FEF4 -> 0x8062FFAC
unsigned int AdjTriangle::OppositeVertex() {
    // Local variables
    unsigned int Ref; // r8
}


