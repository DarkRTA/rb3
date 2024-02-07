/*
    Compile unit: C:\rockband2\system\src\math\strips\Striper.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80631338 -> 0x80631FF0
*/
// Range: 0x80631338 -> 0x80631354
void * Striper::Striper() {}

// Range: 0x80631354 -> 0x806313A8
void * Striper::~Striper(class Striper * const this /* r30 */) {}

// Range: 0x806313A8 -> 0x80631438
class Striper & Striper::FreeUsedRam(class Striper * const this /* r29 */) {}

// Range: 0x80631438 -> 0x80631548
unsigned char Striper::Init(class Striper * const this /* r29 */, struct STRIPERCREATE & create /* r30 */) {
    // Local variables
    struct ADJACENCIESCREATE ac; // r1+0x8
    unsigned char Status; // r0
}

// Range: 0x80631548 -> 0x80631818
unsigned char Striper::Compute(class Striper * const this /* r29 */, struct STRIPERRESULT & result /* r30 */) {
    // Local variables
    unsigned int * Connectivity; // r31
    unsigned int i; // r5
    struct AdjTriangle * Tri; // r6
    class RadixSorter RS; // r1+0x8
    unsigned int i; // r4
    unsigned int TotalNbFaces; // r28
    unsigned int Index; // r27
}

// Range: 0x80631818 -> 0x80631C8C
unsigned int Striper::ComputeBestStrip(class Striper * const this /* r25 */, unsigned int face /* r26 */) {
    // Local variables
    unsigned int * Strip[3]; // r1+0x44
    unsigned int * Faces[3]; // r1+0x38
    unsigned int Length[3]; // r1+0x2C
    unsigned int FirstLength[3]; // r1+0x20
    unsigned int Refs0[3]; // r1+0x14
    unsigned int Refs1[3]; // r1+0x8
    unsigned int j; // r28
    unsigned char * Tags; // r27
    unsigned int i; // r4
    unsigned int ExtraLength; // r0
    unsigned int Longest; // r27
    unsigned int Best; // r29
    unsigned int NbFaces; // r30
    unsigned int Ref; // r4
}

// Range: 0x80631C8C -> 0x80631D8C
unsigned int Striper::TrackStrip(class Striper * const this /* r22 */, unsigned int face /* r23 */, unsigned int middle /* r24 */, unsigned int * strip /* r25 */, unsigned int * faces /* r26 */, unsigned char * tags /* r27 */) {
    // Local variables
    unsigned int Length; // r30
    unsigned char DoTheStrip; // r29
    unsigned int Newest; // r28
    unsigned char CurEdge; // r0
    unsigned int Link; // r3
}

// Range: 0x80631D8C -> 0x80631FF0
unsigned char Striper::ConnectAllStrips(class Striper * const this /* r27 */, struct STRIPERRESULT & result /* r28 */) {
    // Local variables
    unsigned short * wrefs; // r31
    unsigned int * drefs; // r30
    unsigned int k; // r29
    unsigned int j; // r26
}


