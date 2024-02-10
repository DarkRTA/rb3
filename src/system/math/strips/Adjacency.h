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
    unsigned int FindEdge(unsigned int, unsigned int);
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
