/*
    Compile unit: C:\rockband2\system\src\utl\StlAlloc.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8062C034 -> 0x8062CB60
*/
// Range: 0x8062C034 -> 0x8062CB34
unsigned char MakeBSPTree(class BSPNode * & n /* r23 */, class list & faces /* r24 */, int depth /* r25 */) {
    // Local variables
    int numFaces; // r0
    float lowestSum; // f31
    struct _List_iterator t; // r1+0x10C
    int i; // r29
    struct _List_iterator p; // r1+0x108
    float frontArea; // f30
    float backArea; // f29
    int frontFaces; // r28
    int backFaces; // r27
    int numSplit; // r26
    struct _List_iterator ti; // r1+0x104
    unsigned char front; // r1+0x3F
    unsigned char back; // r1+0x3E
    float sum; // f1
    class list frontFaces; // r1+0x158
    class list backFaces; // r1+0x150
    unsigned char front; // r1+0x3D
    unsigned char back; // r1+0x3C
    class Ray r; // r1+0x160
    class BSPFace tf; // r1+0x170

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std18_List_node<5Plane>;
    // -> struct [anonymous] __RTTI__P7Vector2;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<7BSPFace>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static int gBSPMaxCandidates;
    // -> static float gBSPDirTol;
    // -> class Debug TheDebug;
    // -> static int gBSPMaxDepth;
}

// Range: 0x8062CB34 -> 0x8062CB60
void _Vector_base::_M_throw_length_error() {}


