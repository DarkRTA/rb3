#ifndef MATH_BSP_H
#define MATH_BSP_H

#include "math/Mtx.h"
#include "utl/PoolAlloc.h"

struct BSPNode {
public:
    BSPNode() : left(0), right(0) {}
    ~BSPNode() { delete left; delete right; }
    
    Plane plane; // 0x0
    BSPNode* left; // 0x10 yes they're called front/back but BSP works L/R, not F/B
    BSPNode* right; // 0x14

    NEW_POOL_OVERLOAD(BSPNode)
    DELETE_POOL_OVERLOAD(BSPNode)
};

/*
class BSPNode {
    // total size: 0x20
public:
    class Plane plane; // offset 0x0, size 0x10
    class BSPNode * front; // offset 0x10, size 0x4
    class BSPNode * back; // offset 0x14, size 0x4
};
*/


extern float gBSPPosTol;
extern float gBSPDirTol;
extern int gBSPMaxDepth;
extern int gBSPMaxCandidates;
extern float gBSPCheckScale;

#endif // MATH_BSP_H