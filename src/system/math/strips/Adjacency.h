#ifndef MATH_STRIPS_ADJACENCY_H
#define MATH_STRIPS_ADJACENCY_H

struct AdjEdge {
    unsigned int Ref0;
    unsigned int Ref1;
    unsigned int FaceNb;
};

class AdjTriangle {
public:
    unsigned int VRef[3];
    unsigned int ATri[3];
    bool FindEdge(unsigned int, unsigned int);
    unsigned int OppositeVertex(unsigned int, unsigned int);
};

struct ADJACENCIESCREATE {
    unsigned int NbFaces;
    unsigned int * DFaces;
    unsigned short * WFaces;
};

class Adjacencies {
public:
    unsigned int mNbEdges;
    unsigned int mCurrentNbFaces;
    struct AdjEdge* mEdges; 
    
    unsigned int mNbFaces;
    struct AdjTriangle* mFaces;

    Adjacencies();
    ~Adjacencies();
    bool Init(ADJACENCIESCREATE& create);
    bool AddTriangle(unsigned int ref0, unsigned int ref1, unsigned int ref2);
    bool AddEdge(unsigned int ref0, unsigned int ref1, unsigned int ref2);
    bool UpdateLink(unsigned int firsttri, unsigned int secondtri, unsigned int ref0, unsigned int ref1);
};

#endif

// class RadixSorter {
//     // total size: 0x14
//     unsigned int * mHistogram; // offset 0x0, size 0x4
//     unsigned int * mOffset; // offset 0x4, size 0x4
//     unsigned int mCurrentSize; // offset 0x8, size 0x4
//     unsigned int * mIndices; // offset 0xC, size 0x4
//     unsigned int * mIndices2; // offset 0x10, size 0x4
// };
// // Range: 0x8062FAEC -> 0x8062FD74
// unsigned char Adjacencies::CreateDatabase(class Adjacencies * const this /* r27 */) {
//     // Local variables
//     class RadixSorter Core; // r1+0x14
//     unsigned int * FaceNb; // r31
//     unsigned int * VRefs0; // r30
//     unsigned int * VRefs1; // r29
//     unsigned int i; // r28
//     unsigned int LastRef0; // r6
//     unsigned int LastRef1; // r7
//     unsigned int Count; // r4
//     unsigned int TmpBuffer[3]; // r1+0x8
//     unsigned int Face; // r25
//     unsigned int Ref0; // r24
//     unsigned int Ref1; // r23
//     unsigned char Status; // r22
//     unsigned char Status; // r22
// }
