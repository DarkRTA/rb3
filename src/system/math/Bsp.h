#pragma once
#include "math/Geo.h"
#include "math/Mtx.h"
#include "math/Vec.h"
#include "utl/PoolAlloc.h"

class BSPNode {
public:
    BSPNode() : left(0), right(0) {}
    ~BSPNode() {
        delete left;
        delete right;
    }

    Plane plane; // 0x0
    BSPNode *left; // 0x10 yes they're called front/back but BSP works L/R, not F/B
    BSPNode *right; // 0x14

    NEW_POOL_OVERLOAD(BSPNode)
    DELETE_POOL_OVERLOAD(BSPNode)
};

class BSPFace {
public:
    BSPFace() {}
    ~BSPFace() {}
    void Set(const Vector3 &, const Vector3 &, const Vector3 &);

    Hmx::Polygon p;
    Transform t;
    float area;
    std::list<Plane> planes;
};

extern float gBSPPosTol;
extern float gBSPDirTol;
extern int gBSPMaxDepth;
extern int gBSPMaxCandidates;
extern float gBSPCheckScale;

void NumNodes(const BSPNode *, int &, int &);
BinStream &operator>>(BinStream &, BSPNode *&);
bool MakeBSPTree(BSPNode *&, std::list<BSPFace> &, int);
bool CheckBSPTree(const BSPNode *, const Box &);